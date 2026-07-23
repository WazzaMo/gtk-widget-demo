/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "introspection/inspector-pane.h"

#include "introspection/inspector-pane/pick-mode.h"

static void
detach_controller_if_attached(GtkWidget *widget, GtkEventController *controller)
{
  if (widget == NULL || controller == NULL)
    return;

  if (gtk_event_controller_get_widget(controller) == widget)
    gtk_widget_remove_controller(widget, controller);
}

static void
attach_controller_if_detached(GtkWidget *widget, GtkEventController *controller)
{
  if (widget == NULL || controller == NULL)
    return;

  if (gtk_event_controller_get_widget(controller) != widget)
    {
      gtk_event_controller_set_propagation_phase(controller,
                                               GTK_PHASE_CAPTURE);
      gtk_widget_add_controller(widget, controller);
    }
}

static void
remove_pick_controllers(IntrospectionInspectorPane *pane)
{
  if (pane->pick_root == NULL)
    return;

  detach_controller_if_attached(pane->pick_root,
                                GTK_EVENT_CONTROLLER(pane->pick_gesture));
  detach_controller_if_attached(pane->pick_root, pane->pick_key_controller);
}

static void
add_pick_controllers(IntrospectionInspectorPane *pane)
{
  if (pane->pick_root == NULL)
    return;

  attach_controller_if_detached(pane->pick_root,
                                GTK_EVENT_CONTROLLER(pane->pick_gesture));
  attach_controller_if_detached(pane->pick_root, pane->pick_key_controller);
}

static gboolean
widget_is_descendant(GtkWidget *widget, GtkWidget *ancestor)
{
  while (widget != NULL)
    {
      if (widget == ancestor)
        return TRUE;

      widget = gtk_widget_get_parent(widget);
    }

  return FALSE;
}

static void
on_pick_pressed(GtkGestureClick *gesture,
                int n_press,
                double x,
                double y,
                gpointer user_data)
{
  IntrospectionInspectorPane *pane = user_data;
  GtkWidget *picked;
  GtkWidget *pick_root;

  (void) gesture;

  if (!pane->pick_mode || n_press != 1)
    return;

  pick_root = pane->pick_root;
  if (pick_root == NULL)
    return;

  picked = gtk_widget_pick(pick_root, x, y, GTK_PICK_DEFAULT);
  if (picked == NULL)
    return;

  if (widget_is_descendant(pane->root, picked))
    return;

  gtk_gesture_set_state(GTK_GESTURE(gesture), GTK_EVENT_SEQUENCE_CLAIMED);
  introspection_inspector_pane_inspect_widget(pane, picked);
}

static gboolean
on_pick_root_key_pressed(GtkEventControllerKey *controller,
                         guint keyval,
                         guint keycode,
                         GdkModifierType state,
                         gpointer user_data)
{
  IntrospectionInspectorPane *pane = user_data;

  (void) controller;
  (void) keycode;
  (void) state;

  if (!pane->pick_mode || keyval != GDK_KEY_Escape)
    return FALSE;

  if (pane->exit_pick_mode_func != NULL)
    pane->exit_pick_mode_func(pane->exit_pick_mode_data);

  return TRUE;
}

void
introspection_inspector_pane_pick_mode_init(IntrospectionInspectorPane *pane)
{
  pane->pick_gesture = GTK_GESTURE(gtk_gesture_click_new());
  gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(pane->pick_gesture),
                                GDK_BUTTON_PRIMARY);
  g_signal_connect(pane->pick_gesture, "pressed",
                   G_CALLBACK(on_pick_pressed), pane);

  pane->pick_key_controller = GTK_EVENT_CONTROLLER(gtk_event_controller_key_new());
  g_signal_connect(pane->pick_key_controller, "key-pressed",
                   G_CALLBACK(on_pick_root_key_pressed), pane);
}

void
introspection_inspector_pane_pick_mode_uninit(IntrospectionInspectorPane *pane)
{
  remove_pick_controllers(pane);
}

void
introspection_inspector_pane_set_pick_root(IntrospectionInspectorPane *pane,
                                           GtkWidget *pick_root)
{
  gboolean enabled;

  if (pane->pick_root == pick_root)
    return;

  remove_pick_controllers(pane);

  pane->pick_root = pick_root;
  enabled = pane->pick_mode;
  introspection_inspector_pane_set_pick_mode(pane, enabled);
}

void
introspection_inspector_pane_set_exit_pick_mode_handler(
  IntrospectionInspectorPane *pane,
  IntrospectionExitPickModeFunc func,
  gpointer user_data)
{
  pane->exit_pick_mode_func = func;
  pane->exit_pick_mode_data = user_data;
}

void
introspection_inspector_pane_set_pick_mode(IntrospectionInspectorPane *pane,
                                           gboolean enabled)
{
  pane->pick_mode = enabled;

  if (pane->pick_root == NULL)
    return;

  remove_pick_controllers(pane);

  if (enabled)
    {
      add_pick_controllers(pane);
      gtk_widget_set_cursor_from_name(pane->pick_root, "crosshair");
    }
  else
    {
      gtk_widget_set_cursor_from_name(pane->pick_root, "default");
    }
}

gboolean
introspection_inspector_pane_get_pick_mode(IntrospectionInspectorPane *pane)
{
  return pane->pick_mode;
}

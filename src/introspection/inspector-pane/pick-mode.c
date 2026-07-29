/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "introspection/inspector-pane/inspector-pane-private.h"
#include "introspection/inspector-pane/pick-mode.h"

static void
__detach_controller_if_attached(GtkWidget *widget, GtkEventController *controller)
{
  if (widget == NULL || controller == NULL || !GTK_IS_EVENT_CONTROLLER(controller))
    return;

  if (gtk_event_controller_get_widget(controller) == widget)
    gtk_widget_remove_controller(widget, controller);
}

static void
__attach_controller_if_detached(GtkWidget *widget, GtkEventController *controller)
{
  if (widget == NULL || controller == NULL || !GTK_IS_EVENT_CONTROLLER(controller))
    return;

  if (gtk_event_controller_get_widget(controller) != widget)
    {
      gtk_event_controller_set_propagation_phase(controller,
                                               GTK_PHASE_CAPTURE);
      gtk_widget_add_controller(widget, controller);
    }
}

static void
__remove_pick_controllers(IntrospectionInspectorPane *pane)
{
  if (pane->pick_root == NULL)
    return;

  __detach_controller_if_attached(pane->pick_root,
                                GTK_EVENT_CONTROLLER(pane->pick_gesture));
  __detach_controller_if_attached(pane->pick_root, pane->pick_key_controller);
}

static void
__add_pick_controllers(IntrospectionInspectorPane *pane)
{
  if (pane->pick_root == NULL)
    return;

  __attach_controller_if_detached(pane->pick_root,
                                GTK_EVENT_CONTROLLER(pane->pick_gesture));
  __attach_controller_if_detached(pane->pick_root, pane->pick_key_controller);
}

static gboolean
__widget_is_descendant(GtkWidget *widget, GtkWidget *ancestor)
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
__on_pick_pressed(GtkGestureClick *gesture,
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

  if (__widget_is_descendant(pane->root, picked))
    return;

  gtk_gesture_set_state(GTK_GESTURE(gesture), GTK_EVENT_SEQUENCE_CLAIMED);
  introspection_inspector_pane_inspect_widget(pane, picked);
}

static gboolean
__exit_pick_mode_idle(gpointer user_data)
{
  IntrospectionInspectorPane *pane = user_data;

  if (pane->exit_pick_mode_func != NULL)
    pane->exit_pick_mode_func(pane->exit_pick_mode_data);

  return G_SOURCE_REMOVE;
}

static gboolean
__on_pick_root_key_pressed(GtkEventControllerKey *controller,
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
    g_idle_add(__exit_pick_mode_idle, pane);

  return TRUE;
}

void
introspection_inspector_pane_pick_mode_init(IntrospectionInspectorPane *pane)
{
  pane->pick_gesture = GTK_GESTURE(gtk_gesture_click_new());
  gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(pane->pick_gesture),
                                GDK_BUTTON_PRIMARY);
  g_signal_connect(pane->pick_gesture, "pressed",
                   G_CALLBACK(__on_pick_pressed), pane);
  g_object_ref(pane->pick_gesture);

  pane->pick_key_controller = GTK_EVENT_CONTROLLER(gtk_event_controller_key_new());
  g_signal_connect(pane->pick_key_controller, "key-pressed",
                   G_CALLBACK(__on_pick_root_key_pressed), pane);
  g_object_ref(pane->pick_key_controller);
}

void
introspection_inspector_pane_pick_mode_uninit(IntrospectionInspectorPane *pane)
{
  __remove_pick_controllers(pane);
}

void
introspection_inspector_pane_set_pick_root(IntrospectionInspectorPane *pane,
                                           GtkWidget *pick_root)
{
  if (pane->pick_root == pick_root)
    return;

  __remove_pick_controllers(pane);

  pane->pick_root = pick_root;

  if (pick_root != NULL)
    __add_pick_controllers(pane);

  if (pick_root == NULL)
    return;

  gtk_widget_set_cursor_from_name(pick_root,
                                  pane->pick_mode ? "crosshair" : "default");
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

  gtk_widget_set_cursor_from_name(pane->pick_root,
                                  enabled ? "crosshair" : "default");
}

gboolean
introspection_inspector_pane_get_pick_mode(IntrospectionInspectorPane *pane)
{
  return pane->pick_mode;
}

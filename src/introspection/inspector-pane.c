/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "introspection/inspector-pane.h"

#include "introspection/type-ancestry.h"
#include "introspection/property-list.h"
#include "introspection/signal-list.h"

struct _IntrospectionInspectorPane
{
  GtkWidget *root;
  GtkWidget *text_view;
  GtkWidget *pick_root;
  GtkGesture *pick_gesture;
  GtkEventController *pick_key_controller;
  IntrospectionExitPickModeFunc exit_pick_mode_func;
  gpointer exit_pick_mode_data;
  GWeakRef selected_widget;
  gboolean pick_mode;
};

static void clear_selection(IntrospectionInspectorPane *pane);

static void
update_display(IntrospectionInspectorPane *pane, GObject *object)
{
  GtkTextBuffer *buffer;
  GType type;
  gchar *type_name;
  gchar *ancestry;
  gchar *interfaces;
  gchar *properties;
  gchar *signals;
  GString *text;

  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pane->text_view));
  type = G_OBJECT_TYPE(object);
  type_name = introspection_type_name(type);
  ancestry = introspection_format_ancestry(type);
  interfaces = introspection_format_interfaces(type);
  properties = introspection_format_properties(object);
  signals = introspection_format_signals(type);

  text = g_string_new(NULL);
  g_string_append_printf(text, "Type\n%s\n\n", type_name);
  g_string_append_printf(text, "Ancestry\n%s\n\n", ancestry);
  g_string_append_printf(text, "Interfaces\n%s\n\n", interfaces);
  g_string_append_printf(text, "Properties\n%s\n", properties);
  g_string_append_printf(text, "Signals\n%s", signals);

  gtk_text_buffer_set_text(buffer, text->str, (int) text->len);

  g_string_free(text, TRUE);
  g_free(type_name);
  g_free(ancestry);
  g_free(interfaces);
  g_free(properties);
  g_free(signals);
}

static void
show_empty_display(IntrospectionInspectorPane *pane, const gchar *message)
{
  GtkTextBuffer *buffer;

  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pane->text_view));
  gtk_text_buffer_set_text(buffer, message, -1);
}

static void
on_selected_widget_destroyed(gpointer data, GObject *where_the_object_was)
{
  IntrospectionInspectorPane *pane = data;

  (void) where_the_object_was;

  g_weak_ref_set(&pane->selected_widget, NULL);
  show_empty_display(pane, "Selected widget was destroyed.\n");
}

static void
clear_selection(IntrospectionInspectorPane *pane)
{
  GObject *selected;

  selected = g_weak_ref_get(&pane->selected_widget);
  if (selected != NULL)
    {
      g_object_weak_unref(selected, on_selected_widget_destroyed, pane);
      g_object_unref(selected);
    }

  g_weak_ref_set(&pane->selected_widget, NULL);
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

IntrospectionInspectorPane *
introspection_inspector_pane_new(void)
{
  IntrospectionInspectorPane *pane;
  GtkWidget *scrolled;
  GtkTextBuffer *buffer;

  pane = g_new0(IntrospectionInspectorPane, 1);
  g_weak_ref_init(&pane->selected_widget, NULL);

  pane->root = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request(pane->root, 280, -1);

  scrolled = gtk_scrolled_window_new();
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                 GTK_POLICY_AUTOMATIC,
                                 GTK_POLICY_AUTOMATIC);
  gtk_widget_set_vexpand(scrolled, TRUE);

  pane->text_view = gtk_text_view_new();
  gtk_text_view_set_editable(GTK_TEXT_VIEW(pane->text_view), FALSE);
  gtk_text_view_set_monospace(GTK_TEXT_VIEW(pane->text_view), TRUE);
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(pane->text_view), GTK_WRAP_WORD);
  gtk_widget_set_margin_start(pane->text_view, 8);
  gtk_widget_set_margin_end(pane->text_view, 8);
  gtk_widget_set_margin_top(pane->text_view, 8);
  gtk_widget_set_margin_bottom(pane->text_view, 8);

  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pane->text_view));
  gtk_text_buffer_set_text(buffer,
                           "Enable View → Inspect widget, then click a widget "
                           "to inspect its GObject metadata.",
                           -1);

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), pane->text_view);
  gtk_box_append(GTK_BOX(pane->root), scrolled);

  pane->pick_gesture = GTK_GESTURE(gtk_gesture_click_new());
  gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(pane->pick_gesture),
                                GDK_BUTTON_PRIMARY);
  g_signal_connect(pane->pick_gesture, "pressed",
                   G_CALLBACK(on_pick_pressed), pane);

  pane->pick_key_controller = GTK_EVENT_CONTROLLER(gtk_event_controller_key_new());
  g_signal_connect(pane->pick_key_controller, "key-pressed",
                   G_CALLBACK(on_pick_root_key_pressed), pane);

  return pane;
}

void
introspection_inspector_pane_free(IntrospectionInspectorPane *pane)
{
  if (pane == NULL)
    return;

  remove_pick_controllers(pane);

  clear_selection(pane);
  g_weak_ref_clear(&pane->selected_widget);

  if (pane->pick_gesture != NULL)
    g_object_unref(pane->pick_gesture);

  if (pane->pick_key_controller != NULL)
    g_object_unref(pane->pick_key_controller);

  g_free(pane);
}

GtkWidget *
introspection_inspector_pane_get_widget(IntrospectionInspectorPane *pane)
{
  return pane->root;
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

void
introspection_inspector_pane_inspect_widget(IntrospectionInspectorPane *pane,
                                            GtkWidget *widget)
{
  GObject *previous;
  GObject *object;

  if (widget == NULL || !G_IS_OBJECT(widget))
    return;

  object = G_OBJECT(widget);

  previous = g_weak_ref_get(&pane->selected_widget);
  if (previous == object)
    {
      g_object_unref(previous);
      return;
    }

  clear_selection(pane);

  g_weak_ref_set(&pane->selected_widget, object);
  g_object_weak_ref(object, on_selected_widget_destroyed, pane);

  if (previous != NULL)
    g_object_unref(previous);

  update_display(pane, object);
}

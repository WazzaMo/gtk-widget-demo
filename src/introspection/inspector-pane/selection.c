/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "introspection/inspector-pane.h"

#include "introspection/inspector-pane/display.h"
#include "introspection/inspector-pane/selection.h"

static void
on_selected_widget_destroyed(gpointer data, GObject *where_the_object_was)
{
  IntrospectionInspectorPane *pane = data;

  (void) where_the_object_was;

  g_weak_ref_set(&pane->selected_widget, NULL);
  introspection_inspector_pane_display_show_message(pane,
                                                    "Selected widget was destroyed.\n");
}

void
introspection_inspector_pane_selection_clear(IntrospectionInspectorPane *pane)
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

  introspection_inspector_pane_selection_clear(pane);

  g_weak_ref_set(&pane->selected_widget, object);
  g_object_weak_ref(object, on_selected_widget_destroyed, pane);

  if (previous != NULL)
    g_object_unref(previous);

  introspection_inspector_pane_display_update(pane, object);
}

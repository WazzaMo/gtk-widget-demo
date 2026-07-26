/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "introspection/inspector-pane.h"

#include "introspection/inspector-pane/display.h"
#include "introspection/inspector-pane/pick-mode.h"
#include "introspection/inspector-pane/selection.h"

IntrospectionInspectorPane *
introspection_inspector_pane_new(void)
{
  IntrospectionInspectorPane *pane;
  GtkWidget *scrolled;

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

  introspection_inspector_pane_display_set_initial_text(pane);

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), pane->text_view);
  gtk_box_append(GTK_BOX(pane->root), scrolled);

  introspection_inspector_pane_pick_mode_init(pane);

  return pane;
}

void
introspection_inspector_pane_free(IntrospectionInspectorPane *pane)
{
  if (pane == NULL)
    return;

  introspection_inspector_pane_pick_mode_uninit(pane);

  introspection_inspector_pane_selection_clear(pane);
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

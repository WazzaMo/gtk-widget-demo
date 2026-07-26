/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef INTROSPECTION_INSPECTOR_PANE_H
#define INTROSPECTION_INSPECTOR_PANE_H

#include <gtk/gtk.h>

typedef struct _IntrospectionInspectorPane IntrospectionInspectorPane;

typedef void (*IntrospectionExitPickModeFunc)(gpointer user_data);

IntrospectionInspectorPane *introspection_inspector_pane_new(void);

void introspection_inspector_pane_free(IntrospectionInspectorPane *pane);

GtkWidget *introspection_inspector_pane_get_widget(IntrospectionInspectorPane *pane);

void introspection_inspector_pane_set_pick_root(IntrospectionInspectorPane *pane,
                                                GtkWidget *pick_root);

void introspection_inspector_pane_set_exit_pick_mode_handler(
  IntrospectionInspectorPane *pane,
  IntrospectionExitPickModeFunc func,
  gpointer user_data);

void introspection_inspector_pane_set_pick_mode(IntrospectionInspectorPane *pane,
                                                gboolean enabled);

gboolean introspection_inspector_pane_get_pick_mode(IntrospectionInspectorPane *pane);

void introspection_inspector_pane_inspect_widget(IntrospectionInspectorPane *pane,
                                                 GtkWidget *widget);

#endif

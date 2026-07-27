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

/** Callback invoked when pick mode should exit (for example on Escape). */
typedef void (*IntrospectionExitPickModeFunc)(gpointer user_data);

/**
 * Allocate a new inspector pane widget hierarchy.
 * @return a new inspector pane
 */
IntrospectionInspectorPane *introspection_inspector_pane_new(void);

/**
 * Release an inspector pane and its internal resources.
 * @param pane the inspector pane to free
 * @return none
 */
void introspection_inspector_pane_free(IntrospectionInspectorPane *pane);

/**
 * Return the root widget for embedding the inspector pane in a layout.
 * @param pane the inspector pane
 * @return the root container widget
 */
GtkWidget *introspection_inspector_pane_get_widget(IntrospectionInspectorPane *pane);

/**
 * Set the widget tree used as the pick root during inspect mode.
 * @param pane the inspector pane
 * @param pick_root the widget that receives pick gestures
 * @return none
 */
void introspection_inspector_pane_set_pick_root(IntrospectionInspectorPane *pane,
                                                GtkWidget *pick_root);

/**
 * Register a callback invoked when pick mode should exit.
 * @param pane the inspector pane
 * @param func the callback to invoke
 * @param user_data data passed to the callback
 * @return none
 */
void introspection_inspector_pane_set_exit_pick_mode_handler(
  IntrospectionInspectorPane *pane,
  IntrospectionExitPickModeFunc func,
  gpointer user_data);

/**
 * Enable or disable widget pick mode.
 * @param pane the inspector pane
 * @param enabled TRUE to enable pick mode
 * @return none
 */
void introspection_inspector_pane_set_pick_mode(IntrospectionInspectorPane *pane,
                                                gboolean enabled);

/**
 * Query whether widget pick mode is active.
 * @param pane the inspector pane
 * @return TRUE when pick mode is enabled
 */
gboolean introspection_inspector_pane_get_pick_mode(IntrospectionInspectorPane *pane);

/**
 * Inspect a widget and refresh the pane with its GObject metadata.
 * @param pane the inspector pane
 * @param widget the widget to inspect
 * @return none
 */
void introspection_inspector_pane_inspect_widget(IntrospectionInspectorPane *pane,
                                                 GtkWidget *widget);

#endif

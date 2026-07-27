/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef INTROSPECTION_INSPECTOR_PANE_DISPLAY_H
#define INTROSPECTION_INSPECTOR_PANE_DISPLAY_H

#include <gtk/gtk.h>

#include "introspection/inspector-pane.h"

/**
 * Write the initial help message into the inspector pane.
 * @param pane the pane object to populate
 * @return none
 */
void introspection_inspector_pane_display_set_initial_text(
  IntrospectionInspectorPane *pane);

/**
 * Refresh the inspector pane with metadata for a GObject instance.
 * @param pane the inspector pane
 * @param object the object whose metadata should be shown
 * @return none
 */
void introspection_inspector_pane_display_update(IntrospectionInspectorPane *pane,
                                                 GObject *object);

/**
 * Replace the inspector pane text with a plain message.
 * @param pane the inspector pane
 * @param message the message to display
 * @return none
 */
void introspection_inspector_pane_display_show_message(
  IntrospectionInspectorPane *pane,
  const gchar *message);

#endif

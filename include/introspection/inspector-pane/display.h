/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef INTROSPECTION_INSPECTOR_PANE_DISPLAY_H
#define INTROSPECTION_INSPECTOR_PANE_DISPLAY_H

#include "introspection/inspector-pane/inspector-pane-private.h"

void introspection_inspector_pane_display_set_initial_text(
  IntrospectionInspectorPane *pane);

void introspection_inspector_pane_display_update(IntrospectionInspectorPane *pane,
                                                 GObject *object);

void introspection_inspector_pane_display_show_message(
  IntrospectionInspectorPane *pane,
  const gchar *message);

#endif

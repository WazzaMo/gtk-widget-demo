/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef INTROSPECTION_INSPECTOR_PANE_PICK_MODE_H
#define INTROSPECTION_INSPECTOR_PANE_PICK_MODE_H

#include <gtk/gtk.h>

#include "introspection/inspector-pane.h"

/**
 * Initialize pick-mode controllers on an inspector pane.
 * @param pane the inspector pane
 * @return none
 */
void introspection_inspector_pane_pick_mode_init(IntrospectionInspectorPane *pane);

/**
 * Detach pick-mode controllers from an inspector pane.
 * @param pane the inspector pane
 * @return none
 */
void introspection_inspector_pane_pick_mode_uninit(IntrospectionInspectorPane *pane);

#endif

/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef INTROSPECTION_INSPECTOR_PANE_SELECTION_H
#define INTROSPECTION_INSPECTOR_PANE_SELECTION_H

#include <gtk/gtk.h>

#include "introspection/inspector-pane.h"

/**
 * Clear the currently selected widget and its weak-reference handlers.
 * @param pane the inspector pane
 * @return none
 */
void introspection_inspector_pane_selection_clear(IntrospectionInspectorPane *pane);

#endif

/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef INTROSPECTION_INSPECTOR_PANE_PRIVATE_H
#define INTROSPECTION_INSPECTOR_PANE_PRIVATE_H

#include "introspection/inspector-pane.h"

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

#endif

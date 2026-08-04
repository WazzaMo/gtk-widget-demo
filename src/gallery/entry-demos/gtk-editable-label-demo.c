/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/entry-demos/gtk-editable-label-demo.h"

GtkWidget *
gallery_entry_gtk_editable_label_demo_build(GtkWindow *parent_window)
{
  GtkWidget *label;

  (void) parent_window;

  label = gtk_editable_label_new("Double-click to edit this label");
  gtk_widget_set_hexpand(label, FALSE);
  return label;
}

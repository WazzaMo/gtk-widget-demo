/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-label-demo.h"

GtkWidget *
gallery_display_gtk_label_demo_build(GtkWindow *parent_window)
{
  GtkWidget *label;

  (void) parent_window;

  label = gtk_label_new("Hello from GtkLabel");
  gtk_label_set_xalign(GTK_LABEL(label), 0.0f);
  return label;
}

/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/entry-demos/gtk-spin-button-demo.h"

GtkWidget *
gallery_entry_gtk_spin_button_demo_build(GtkWindow *parent_window)
{
  GtkWidget *spin;
  GtkAdjustment *adjustment;

  (void) parent_window;

  adjustment = gtk_adjustment_new(5.0, 0.0, 10.0, 1.0, 2.0, 0.0);
  spin = gtk_spin_button_new(adjustment, 1.0, 0);
  return spin;
}

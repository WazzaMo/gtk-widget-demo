/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-level-bar-demo.h"

static void
__on_level_scale_changed(GtkRange *range, gpointer user_data)
{
  GtkLevelBar *level_bar = user_data;
  double value;

  value = gtk_range_get_value(range);
  gtk_level_bar_set_value(level_bar, value);
}

GtkWidget *
gallery_display_gtk_level_bar_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *level_bar;
  GtkWidget *scale;
  GtkAdjustment *adjustment;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);

  level_bar = gtk_level_bar_new_for_interval(0.0, 100.0);
  gtk_level_bar_set_value(GTK_LEVEL_BAR(level_bar), 40.0);
  gtk_widget_set_size_request(level_bar, 240, -1);
  gtk_widget_set_hexpand(level_bar, FALSE);

  adjustment = gtk_adjustment_new(40.0, 0.0, 100.0, 1.0, 5.0, 0.0);
  scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adjustment);
  gtk_widget_set_size_request(scale, 240, -1);
  gtk_widget_set_hexpand(scale, FALSE);
  g_signal_connect(scale, "value-changed",
                   G_CALLBACK(__on_level_scale_changed), level_bar);

  gtk_box_append(GTK_BOX(box), level_bar);
  gtk_box_append(GTK_BOX(box), scale);
  return box;
}

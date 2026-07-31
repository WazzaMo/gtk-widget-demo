/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-scale-demo.h"

static void
__on_scale_value_changed(GtkRange *range, gpointer user_data)
{
  GtkWidget *value_label = user_data;
  char *text;

  text = g_strdup_printf("%.0f", gtk_range_get_value(range));
  gtk_label_set_text(GTK_LABEL(value_label), text);
  g_free(text);
}

GtkWidget *
gallery_display_gtk_scale_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *scale;
  GtkWidget *value_label;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
  scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 100.0, 1.0);
  gtk_range_set_value(GTK_RANGE(scale), 50.0);
  gtk_widget_set_size_request(scale, 240, -1);

  value_label = gtk_label_new("50");
  gtk_label_set_xalign(GTK_LABEL(value_label), 0.0f);
  g_signal_connect(scale, "value-changed",
                   G_CALLBACK(__on_scale_value_changed), value_label);

  gtk_box_append(GTK_BOX(box), scale);
  gtk_box_append(GTK_BOX(box), value_label);
  return box;
}

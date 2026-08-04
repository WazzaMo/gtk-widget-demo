/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-separator-demo.h"

GtkWidget *
gallery_display_gtk_separator_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *horizontal_group;
  GtkWidget *vertical_group;
  GtkWidget *separator;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);

  horizontal_group = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
  gtk_box_append(GTK_BOX(horizontal_group), gtk_label_new("Above"));
  separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_widget_set_size_request(separator, 200, -1);
  gtk_box_append(GTK_BOX(horizontal_group), separator);
  gtk_box_append(GTK_BOX(horizontal_group), gtk_label_new("Below"));

  vertical_group = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
  gtk_box_append(GTK_BOX(vertical_group), gtk_label_new("Left"));
  separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
  gtk_widget_set_size_request(separator, -1, 48);
  gtk_box_append(GTK_BOX(vertical_group), separator);
  gtk_box_append(GTK_BOX(vertical_group), gtk_label_new("Right"));

  gtk_box_append(GTK_BOX(box), horizontal_group);
  gtk_box_append(GTK_BOX(box), vertical_group);
  return box;
}

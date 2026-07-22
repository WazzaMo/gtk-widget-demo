/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "main/sample-palette.h"

GtkWidget *
main_sample_palette_new(void)
{
  GtkWidget *palette;
  GtkWidget *heading;
  GtkWidget *demo_label;
  GtkWidget *button;
  GtkWidget *entry;
  GtkWidget *switch_widget;
  GtkWidget *scale;
  GtkWidget *nested_box;
  GtkWidget *nested_label;
  GtkWidget *check;

  palette = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(palette), 8);
  gtk_grid_set_column_spacing(GTK_GRID(palette), 8);
  gtk_widget_set_margin_start(palette, 12);
  gtk_widget_set_margin_end(palette, 12);
  gtk_widget_set_margin_top(palette, 12);
  gtk_widget_set_margin_bottom(palette, 12);
  gtk_widget_set_halign(palette, GTK_ALIGN_START);
  gtk_widget_set_valign(palette, GTK_ALIGN_START);

  heading = gtk_label_new(
    "Sample palette — use View → Inspect widget, then click a control.");
  gtk_label_set_xalign(GTK_LABEL(heading), 0.0f);
  gtk_widget_set_hexpand(heading, TRUE);
  gtk_grid_attach(GTK_GRID(palette), heading, 0, 0, 2, 1);

  demo_label = gtk_label_new("GtkLabel");
  gtk_grid_attach(GTK_GRID(palette), demo_label, 0, 1, 1, 1);

  button = gtk_button_new_with_label("GtkButton");
  gtk_grid_attach(GTK_GRID(palette), button, 1, 1, 1, 1);

  entry = gtk_entry_new();
  gtk_editable_set_text(GTK_EDITABLE(entry), "GtkEntry");
  gtk_grid_attach(GTK_GRID(palette), entry, 0, 2, 2, 1);

  switch_widget = gtk_switch_new();
  gtk_grid_attach(GTK_GRID(palette), switch_widget, 0, 3, 1, 1);

  scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 100.0, 1.0);
  gtk_range_set_value(GTK_RANGE(scale), 50.0);
  gtk_widget_set_size_request(scale, 180, -1);
  gtk_grid_attach(GTK_GRID(palette), scale, 1, 3, 1, 1);

  nested_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
  nested_label = gtk_label_new("Nested GtkBox");
  check = gtk_check_button_new_with_label("GtkCheckButton");
  gtk_box_append(GTK_BOX(nested_box), nested_label);
  gtk_box_append(GTK_BOX(nested_box), check);
  gtk_grid_attach(GTK_GRID(palette), nested_box, 0, 4, 2, 1);

  return palette;
}

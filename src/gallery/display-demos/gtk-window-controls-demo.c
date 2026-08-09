/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-window-controls-demo.h"

GtkWidget *
gallery_display_gtk_window_controls_demo_build(GtkWindow *parent_window)
{
  GtkWidget *header;
  GtkWidget *controls;

  (void) parent_window;

  header = gtk_header_bar_new();
  gtk_header_bar_set_title_widget(GTK_HEADER_BAR(header),
                                  gtk_label_new("Gallery demo titlebar"));
  gtk_widget_set_size_request(header, 360, -1);
  gtk_widget_set_hexpand(header, FALSE);

  controls = gtk_window_controls_new(GTK_PACK_END);
  gtk_header_bar_pack_end(GTK_HEADER_BAR(header), controls);

  return header;
}

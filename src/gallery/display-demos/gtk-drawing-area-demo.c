/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-drawing-area-demo.h"

static void
__on_drawing_area_draw(GtkDrawingArea *area,
                       cairo_t *cr,
                       int width,
                       int height,
                       gpointer user_data)
{
  (void) area;
  (void) user_data;

  cairo_set_source_rgb(cr, 0.18, 0.20, 0.25);
  cairo_paint(cr);

  cairo_set_source_rgb(cr, 0.35, 0.55, 0.85);
  cairo_rectangle(cr, width * 0.2, height * 0.2, width * 0.6, height * 0.6);
  cairo_fill(cr);
}

GtkWidget *
gallery_display_gtk_drawing_area_demo_build(GtkWindow *parent_window)
{
  GtkWidget *area;

  (void) parent_window;

  area = gtk_drawing_area_new();
  gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(area), 320);
  gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(area), 180);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area),
                                 __on_drawing_area_draw,
                                 NULL,
                                 NULL);
  gtk_widget_set_hexpand(area, FALSE);

  return area;
}

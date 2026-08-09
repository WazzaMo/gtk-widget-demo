/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include <epoxy/gl.h>

#include "gallery/display-demos/gtk-gl-area-demo.h"

static gboolean
__on_gl_area_render(GtkGLArea *area,
                    GdkGLContext *context,
                    gpointer user_data)
{
  GtkWidget *fallback_label = user_data;

  (void) context;

  gtk_gl_area_make_current(area);
  if (gtk_gl_area_get_error(area) != NULL)
    {
      gtk_widget_set_visible(GTK_WIDGET(area), FALSE);
      gtk_widget_set_visible(fallback_label, TRUE);
      return FALSE;
    }

  glClearColor(0.18f, 0.20f, 0.25f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  return TRUE;
}

GtkWidget *
gallery_display_gtk_gl_area_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *gl_area;
  GtkWidget *fallback_label;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);

  fallback_label = gtk_label_new(
    "OpenGL context unavailable on this host — GtkGLArea could not render.");
  gtk_label_set_wrap(GTK_LABEL(fallback_label), TRUE);
  gtk_widget_set_visible(fallback_label, FALSE);
  gtk_widget_set_halign(fallback_label, GTK_ALIGN_START);

  gl_area = gtk_gl_area_new();
  gtk_widget_set_size_request(gl_area, 320, 180);
  gtk_widget_set_hexpand(gl_area, FALSE);
  gtk_gl_area_set_auto_render(GTK_GL_AREA(gl_area), TRUE);
  g_signal_connect(gl_area, "render",
                   G_CALLBACK(__on_gl_area_render), fallback_label);

  gtk_box_append(GTK_BOX(box), gl_area);
  gtk_box_append(GTK_BOX(box), fallback_label);

  return box;
}

/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-picture-demo.h"
#include "gallery/gallery-data-path.h"

GtkWidget *
gallery_display_gtk_picture_demo_build(GtkWindow *parent_window)
{
  GtkWidget *picture;

  (void) parent_window;

  picture = gtk_picture_new_for_filename(GALLERY_DATA_PATH("demo-icon.svg"));
  gtk_picture_set_can_shrink(GTK_PICTURE(picture), TRUE);
  gtk_picture_set_content_fit(GTK_PICTURE(picture), GTK_CONTENT_FIT_SCALE_DOWN);
  gtk_widget_set_size_request(picture, 96, 96);
  gtk_widget_set_hexpand(picture, FALSE);
  return picture;
}

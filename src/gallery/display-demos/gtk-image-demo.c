/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-image-demo.h"
#include "gallery/gallery-data-path.h"

GtkWidget *
gallery_display_gtk_image_demo_build(GtkWindow *parent_window)
{
  GtkWidget *image;

  (void) parent_window;

  image = gtk_image_new_from_file(GALLERY_DATA_PATH("demo-icon.svg"));
  gtk_widget_set_hexpand(image, FALSE);
  return image;
}

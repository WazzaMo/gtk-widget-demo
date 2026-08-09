/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/button-demos/gtk-link-button-demo.h"

GtkWidget *
gallery_button_gtk_link_button_demo_build(GtkWindow *parent_window)
{
  GtkWidget *link;

  (void) parent_window;

  link = gtk_link_button_new_with_label("https://docs.gtk.org/gtk4/",
                                        "GTK 4 documentation");
  return link;
}

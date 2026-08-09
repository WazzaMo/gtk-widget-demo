/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/button-demos/gtk-check-button-demo.h"

GtkWidget *
gallery_button_gtk_check_button_demo_build(GtkWindow *parent_window)
{
  GtkWidget *check;

  (void) parent_window;

  check = gtk_check_button_new_with_label("Enable option");
  gtk_check_button_set_active(GTK_CHECK_BUTTON(check), TRUE);
  return check;
}

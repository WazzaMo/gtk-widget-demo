/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/button-demos/gtk-menu-button-demo.h"

GtkWidget *
gallery_button_gtk_menu_button_demo_build(GtkWindow *parent_window)
{
  GtkWidget *menu_button;
  GMenu *menu;

  (void) parent_window;

  menu = g_menu_new();
  g_menu_append(menu, "Gallery action one", NULL);
  g_menu_append(menu, "Gallery action two", NULL);

  menu_button = gtk_menu_button_new();
  gtk_menu_button_set_label(GTK_MENU_BUTTON(menu_button), "Open menu");
  gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(menu_button),
                                 G_MENU_MODEL(menu));
  g_object_unref(menu);

  return menu_button;
}

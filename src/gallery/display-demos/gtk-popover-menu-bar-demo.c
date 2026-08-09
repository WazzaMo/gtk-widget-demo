/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-popover-menu-bar-demo.h"

GtkWidget *
gallery_display_gtk_popover_menu_bar_demo_build(GtkWindow *parent_window)
{
  GtkWidget *menu_bar;
  GMenu *menu;
  GMenu *gallery_menu;

  (void) parent_window;

  menu = g_menu_new();
  gallery_menu = g_menu_new();
  g_menu_append(gallery_menu, "Gallery action one", NULL);
  g_menu_append(gallery_menu, "Gallery action two", NULL);
  g_menu_append_submenu(menu, "Gallery", G_MENU_MODEL(gallery_menu));
  g_object_unref(gallery_menu);

  menu_bar = gtk_popover_menu_bar_new_from_model(G_MENU_MODEL(menu));
  g_object_unref(menu);

  gtk_widget_set_hexpand(menu_bar, FALSE);

  return menu_bar;
}

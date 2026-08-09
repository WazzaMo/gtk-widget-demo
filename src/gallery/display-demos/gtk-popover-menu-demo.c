/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-popover-menu-demo.h"

GtkWidget *
gallery_display_gtk_popover_menu_demo_build(GtkWindow *parent_window)
{
  GtkWidget *menu_button;
  GtkWidget *popover;
  GMenu *menu;

  (void) parent_window;

  menu = g_menu_new();
  g_menu_append(menu, "Gallery item one", NULL);
  g_menu_append(menu, "Gallery item two", NULL);

  popover = gtk_popover_menu_new_from_model(G_MENU_MODEL(menu));
  g_object_unref(menu);

  menu_button = gtk_menu_button_new();
  gtk_menu_button_set_label(GTK_MENU_BUTTON(menu_button), "Show popover menu");
  gtk_menu_button_set_popover(GTK_MENU_BUTTON(menu_button), popover);
  gtk_widget_set_hexpand(menu_button, FALSE);

  return menu_button;
}

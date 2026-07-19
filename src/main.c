/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include <gtk/gtk.h>

static void quit_activated(GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
  (void) action;
  (void) parameter;

  g_application_quit(G_APPLICATION(user_data));
}

static void on_startup(GtkApplication *app, gpointer user_data)
{
  GSimpleAction *quit_action;

  (void) user_data; // remove unused param warning.

  quit_action = g_simple_action_new("quit", NULL);
  g_signal_connect(quit_action, "activate", G_CALLBACK(quit_activated), app);
  g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(quit_action));
  g_object_unref(quit_action);
}

static void
on_activate(GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *root_box;
  GtkWidget *menubar_widget;
  GtkWidget *content;
  GMenu *file_menu;
  GMenu *menubar;

  (void) user_data; // remove unused param warning.

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "GTK Widget Demo");
  gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

  file_menu = g_menu_new();
  g_menu_append(file_menu, "Exit", "app.quit");

  menubar = g_menu_new();
  g_menu_append_submenu(menubar, "File", G_MENU_MODEL(file_menu));

  menubar_widget = gtk_popover_menu_bar_new_from_model(G_MENU_MODEL(menubar));

  content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_vexpand(content, TRUE);

  root_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_append(GTK_BOX(root_box), menubar_widget);
  gtk_box_append(GTK_BOX(root_box), content);

  gtk_window_set_child(GTK_WINDOW(window), root_box);

  g_object_unref(file_menu);
  g_object_unref(menubar);

  gtk_window_present(GTK_WINDOW(window));
}

int
main(int argc, char *argv[])
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("com.example.gtk-widget-demo",
                            G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "startup", G_CALLBACK(on_startup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

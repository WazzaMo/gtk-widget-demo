/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "main/window-shell.h"

#include "introspection.h"
#include "main/sample-palette.h"

typedef struct
{
  IntrospectionInspectorPane *inspector;
  GSimpleAction *inspect_action;
} WindowData;

static void
quit_activated(GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
  (void) action;
  (void) parameter;

  g_application_quit(G_APPLICATION(user_data));
}

static void
inspect_change_state(GSimpleAction *action, GVariant *state, gpointer user_data)
{
  WindowData *data = user_data;
  gboolean enabled;

  (void) action;

  enabled = g_variant_get_boolean(state);
  g_simple_action_set_state(action, state);
  introspection_inspector_pane_set_pick_mode(data->inspector, enabled);
}

static void
exit_pick_mode(gpointer user_data)
{
  WindowData *data = user_data;

  if (!introspection_inspector_pane_get_pick_mode(data->inspector))
    return;

  g_action_change_state(G_ACTION(data->inspect_action),
                        g_variant_new_boolean(FALSE));
}

static void
window_data_free(gpointer data)
{
  WindowData *window_data = data;

  if (window_data->inspect_action != NULL)
    g_object_unref(window_data->inspect_action);

  introspection_inspector_pane_free(window_data->inspector);
  g_free(window_data);
}

void
main_window_shell_startup(GtkApplication *app)
{
  GSimpleAction *quit_action;

  quit_action = g_simple_action_new("quit", NULL);
  g_signal_connect(quit_action, "activate", G_CALLBACK(quit_activated), app);
  g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(quit_action));
  g_object_unref(quit_action);
}

void
main_window_shell_activate(GtkApplication *app)
{
  GtkWidget *window;
  GtkWidget *paned;
  GtkWidget *root_box;
  GtkWidget *menubar_widget;
  GtkWidget *content;
  GtkWidget *sample_palette;
  GtkWidget *inspector_widget;
  GMenu *file_menu;
  GMenu *view_menu;
  GMenu *menubar;
  GSimpleAction *inspect_action;
  GSimpleActionGroup *window_actions;
  WindowData *window_data;

  window_data = g_new0(WindowData, 1);
  window_data->inspector = introspection_inspector_pane_new();

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "GTK Widget Demo");
  gtk_window_set_default_size(GTK_WINDOW(window), 960, 520);
  g_object_set_data_full(G_OBJECT(window), "window-data", window_data,
                         window_data_free);

  inspect_action = g_simple_action_new_stateful("inspect",
                                                NULL,
                                                g_variant_new_boolean(FALSE));
  g_signal_connect(inspect_action, "change-state",
                   G_CALLBACK(inspect_change_state), window_data);
  window_data->inspect_action = inspect_action;
  g_object_ref(inspect_action);

  window_actions = g_simple_action_group_new();
  g_action_map_add_action(G_ACTION_MAP(window_actions),
                          G_ACTION(inspect_action));
  gtk_widget_insert_action_group(window, "win", G_ACTION_GROUP(window_actions));
  g_object_unref(inspect_action);
  g_object_unref(window_actions);

  file_menu = g_menu_new();
  g_menu_append(file_menu, "Exit", "app.quit");

  view_menu = g_menu_new();
  g_menu_append(view_menu, "Inspect widget", "win.inspect");

  menubar = g_menu_new();
  g_menu_append_submenu(menubar, "File", G_MENU_MODEL(file_menu));
  g_menu_append_submenu(menubar, "View", G_MENU_MODEL(view_menu));

  menubar_widget = gtk_popover_menu_bar_new_from_model(G_MENU_MODEL(menubar));

  sample_palette = main_sample_palette_new();

  content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_vexpand(content, TRUE);
  gtk_box_append(GTK_BOX(content), sample_palette);

  root_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_append(GTK_BOX(root_box), menubar_widget);
  gtk_box_append(GTK_BOX(root_box), content);

  inspector_widget = introspection_inspector_pane_get_widget(
    window_data->inspector);

  paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_paned_set_start_child(GTK_PANED(paned), root_box);
  gtk_paned_set_end_child(GTK_PANED(paned), inspector_widget);
  gtk_paned_set_resize_start_child(GTK_PANED(paned), TRUE);
  gtk_paned_set_resize_end_child(GTK_PANED(paned), FALSE);
  gtk_paned_set_shrink_start_child(GTK_PANED(paned), FALSE);
  gtk_paned_set_shrink_end_child(GTK_PANED(paned), TRUE);
  gtk_widget_set_vexpand(paned, TRUE);

  introspection_inspector_pane_set_pick_root(window_data->inspector, root_box);
  introspection_inspector_pane_set_exit_pick_mode_handler(window_data->inspector,
                                                          exit_pick_mode,
                                                          window_data);

  gtk_window_set_child(GTK_WINDOW(window), paned);

  g_object_unref(file_menu);
  g_object_unref(view_menu);
  g_object_unref(menubar);

  gtk_window_present(GTK_WINDOW(window));
}

/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include <gtk/gtk.h>

#include "introspection.h"

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

static GtkWidget *
build_sample_palette(void)
{
  GtkWidget *palette;
  GtkWidget *heading;
  GtkWidget *demo_label;
  GtkWidget *button;
  GtkWidget *entry;
  GtkWidget *switch_widget;
  GtkWidget *scale;
  GtkWidget *nested_box;
  GtkWidget *nested_label;
  GtkWidget *check;

  palette = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(palette), 8);
  gtk_grid_set_column_spacing(GTK_GRID(palette), 8);
  gtk_widget_set_margin_start(palette, 12);
  gtk_widget_set_margin_end(palette, 12);
  gtk_widget_set_margin_top(palette, 12);
  gtk_widget_set_margin_bottom(palette, 12);
  gtk_widget_set_halign(palette, GTK_ALIGN_START);
  gtk_widget_set_valign(palette, GTK_ALIGN_START);

  heading = gtk_label_new(
    "Sample palette — use View → Inspect widget, then click a control.");
  gtk_label_set_xalign(GTK_LABEL(heading), 0.0f);
  gtk_widget_set_hexpand(heading, TRUE);
  gtk_grid_attach(GTK_GRID(palette), heading, 0, 0, 2, 1);

  demo_label = gtk_label_new("GtkLabel");
  gtk_grid_attach(GTK_GRID(palette), demo_label, 0, 1, 1, 1);

  button = gtk_button_new_with_label("GtkButton");
  gtk_grid_attach(GTK_GRID(palette), button, 1, 1, 1, 1);

  entry = gtk_entry_new();
  gtk_editable_set_text(GTK_EDITABLE(entry), "GtkEntry");
  gtk_grid_attach(GTK_GRID(palette), entry, 0, 2, 2, 1);

  switch_widget = gtk_switch_new();
  gtk_grid_attach(GTK_GRID(palette), switch_widget, 0, 3, 1, 1);

  scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 100.0, 1.0);
  gtk_range_set_value(GTK_RANGE(scale), 50.0);
  gtk_widget_set_size_request(scale, 180, -1);
  gtk_grid_attach(GTK_GRID(palette), scale, 1, 3, 1, 1);

  nested_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
  nested_label = gtk_label_new("Nested GtkBox");
  check = gtk_check_button_new_with_label("GtkCheckButton");
  gtk_box_append(GTK_BOX(nested_box), nested_label);
  gtk_box_append(GTK_BOX(nested_box), check);
  gtk_grid_attach(GTK_GRID(palette), nested_box, 0, 4, 2, 1);

  return palette;
}

static void
on_startup(GtkApplication *app, gpointer user_data)
{
  GSimpleAction *quit_action;

  (void) user_data;

  quit_action = g_simple_action_new("quit", NULL);
  g_signal_connect(quit_action, "activate", G_CALLBACK(quit_activated), app);
  g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(quit_action));
  g_object_unref(quit_action);
}

static void
on_activate(GtkApplication *app, gpointer user_data)
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

  (void) user_data;

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

  sample_palette = build_sample_palette();

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

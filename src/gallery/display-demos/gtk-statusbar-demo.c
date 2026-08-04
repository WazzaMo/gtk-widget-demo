/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-statusbar-demo.h"

typedef struct
{
  GtkWidget *statusbar;
  guint context_id;
  guint clear_timeout_id;
} StatusbarDemoData;

static void
__statusbar_demo_data_free(gpointer user_data)
{
  StatusbarDemoData *data = user_data;

  if (data->clear_timeout_id != 0)
    g_source_remove(data->clear_timeout_id);

  g_free(data);
}

static void
__on_status_push_clicked(GtkButton *button, gpointer user_data)
{
  StatusbarDemoData *data = user_data;
  static guint push_count;
  char *message;

  (void) button;

  push_count++;
  message = g_strdup_printf("Status message %u", push_count);
  gtk_statusbar_push(GTK_STATUSBAR(data->statusbar), data->context_id, message);
  g_free(message);
}

static void
__on_status_pop_clicked(GtkButton *button, gpointer user_data)
{
  StatusbarDemoData *data = user_data;

  (void) button;

  gtk_statusbar_pop(GTK_STATUSBAR(data->statusbar), data->context_id);
}

static gboolean
__on_status_clear_timeout(gpointer user_data)
{
  StatusbarDemoData *data = user_data;

  gtk_statusbar_pop(GTK_STATUSBAR(data->statusbar), data->context_id);
  data->clear_timeout_id = 0;
  return G_SOURCE_REMOVE;
}

static void
__on_status_timed_clear_clicked(GtkButton *button, gpointer user_data)
{
  StatusbarDemoData *data = user_data;

  (void) button;

  if (data->clear_timeout_id != 0)
    g_source_remove(data->clear_timeout_id);

  gtk_statusbar_push(GTK_STATUSBAR(data->statusbar), data->context_id,
                     "Clears automatically in two seconds");

  data->clear_timeout_id = g_timeout_add_seconds(2,
                                                 __on_status_clear_timeout,
                                                 data);
}

GtkWidget *
gallery_display_gtk_statusbar_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *button_row;
  GtkWidget *statusbar;
  GtkWidget *push_button;
  GtkWidget *pop_button;
  GtkWidget *timed_button;
  StatusbarDemoData *data;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
  data = g_new0(StatusbarDemoData, 1);
  g_object_set_data_full(G_OBJECT(box), "statusbar-demo-data", data,
                         __statusbar_demo_data_free);

  statusbar = gtk_statusbar_new();
  data->statusbar = statusbar;
  data->context_id = gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar),
                                                  "gallery-statusbar-demo");
  gtk_statusbar_push(GTK_STATUSBAR(statusbar), data->context_id, "Ready");
  gtk_widget_set_size_request(statusbar, 320, -1);

  button_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
  push_button = gtk_button_new_with_label("Push message");
  pop_button = gtk_button_new_with_label("Pop message");
  timed_button = gtk_button_new_with_label("Timed clear");
  gtk_widget_set_hexpand(push_button, FALSE);
  gtk_widget_set_hexpand(pop_button, FALSE);
  gtk_widget_set_hexpand(timed_button, FALSE);
  g_signal_connect(push_button, "clicked",
                   G_CALLBACK(__on_status_push_clicked), data);
  g_signal_connect(pop_button, "clicked",
                   G_CALLBACK(__on_status_pop_clicked), data);
  g_signal_connect(timed_button, "clicked",
                   G_CALLBACK(__on_status_timed_clear_clicked), data);
  gtk_box_append(GTK_BOX(button_row), push_button);
  gtk_box_append(GTK_BOX(button_row), pop_button);
  gtk_box_append(GTK_BOX(button_row), timed_button);

  gtk_box_append(GTK_BOX(box), statusbar);
  gtk_box_append(GTK_BOX(box), button_row);
  return box;
}

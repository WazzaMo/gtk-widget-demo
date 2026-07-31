/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-spinner-demo.h"

typedef struct
{
  GtkWidget *spinner;
  GtkWidget *start_button;
  GtkWidget *stop_button;
} SpinnerDemoData;

static void
__on_start_spinner_clicked(GtkButton *button, gpointer user_data)
{
  SpinnerDemoData *data = user_data;

  (void) button;

  gtk_spinner_start(GTK_SPINNER(data->spinner));
  gtk_widget_set_sensitive(data->start_button, FALSE);
  gtk_widget_set_sensitive(data->stop_button, TRUE);
}

static void
__on_stop_spinner_clicked(GtkButton *button, gpointer user_data)
{
  SpinnerDemoData *data = user_data;

  (void) button;

  gtk_spinner_stop(GTK_SPINNER(data->spinner));
  gtk_widget_set_sensitive(data->start_button, TRUE);
  gtk_widget_set_sensitive(data->stop_button, FALSE);
}

GtkWidget *
gallery_display_gtk_spinner_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *button_row;
  GtkWidget *spinner;
  GtkWidget *start_button;
  GtkWidget *stop_button;
  SpinnerDemoData *data;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
  data = g_new0(SpinnerDemoData, 1);
  g_object_set_data_full(G_OBJECT(box), "spinner-demo-data", data, g_free);

  spinner = gtk_spinner_new();
  gtk_widget_set_hexpand(spinner, FALSE);
  data->spinner = spinner;

  button_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
  start_button = gtk_button_new_with_label("Start spinner");
  stop_button = gtk_button_new_with_label("Stop spinner");
  gtk_widget_set_hexpand(start_button, FALSE);
  gtk_widget_set_hexpand(stop_button, FALSE);
  data->start_button = start_button;
  data->stop_button = stop_button;
  gtk_widget_set_sensitive(stop_button, FALSE);
  g_signal_connect(start_button, "clicked",
                   G_CALLBACK(__on_start_spinner_clicked), data);
  g_signal_connect(stop_button, "clicked",
                   G_CALLBACK(__on_stop_spinner_clicked), data);
  gtk_box_append(GTK_BOX(button_row), start_button);
  gtk_box_append(GTK_BOX(button_row), stop_button);

  gtk_box_append(GTK_BOX(box), spinner);
  gtk_box_append(GTK_BOX(box), button_row);
  return box;
}

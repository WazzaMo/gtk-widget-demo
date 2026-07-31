/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-progress-bar-demo.h"

typedef struct
{
  GtkWidget *progress;
  GtkWidget *fraction_actions;
  GtkWidget *pulse_actions;
  GtkWidget *start_pulse_button;
  GtkWidget *stop_pulse_button;
  guint pulse_timeout_id;
} ProgressBarDemoData;

static void
__stop_progress_pulse(ProgressBarDemoData *data)
{
  if (data->pulse_timeout_id == 0)
    return;

  g_source_remove(data->pulse_timeout_id);
  data->pulse_timeout_id = 0;
}

static void
__progress_bar_demo_data_free(gpointer user_data)
{
  ProgressBarDemoData *data = user_data;

  __stop_progress_pulse(data);
  g_free(data);
}

static void
__on_progress_add_clicked(GtkButton *button, gpointer user_data)
{
  GtkWidget *progress = user_data;
  double fraction;

  (void) button;

  fraction = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(progress));
  fraction += 0.1;
  if (fraction > 1.0)
    fraction = 1.0;
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress), fraction);
}

static void
__on_progress_reset_clicked(GtkButton *button, gpointer user_data)
{
  GtkWidget *progress = user_data;

  (void) button;

  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress), 0.0);
}

static gboolean
__on_progress_pulse_timeout(gpointer user_data)
{
  GtkWidget *progress = user_data;

  gtk_progress_bar_pulse(GTK_PROGRESS_BAR(progress));
  return G_SOURCE_CONTINUE;
}

static void
__on_start_pulse_clicked(GtkButton *button, gpointer user_data)
{
  ProgressBarDemoData *data = user_data;

  (void) button;

  if (data->pulse_timeout_id != 0)
    return;

  data->pulse_timeout_id = g_timeout_add(100, __on_progress_pulse_timeout,
                                         data->progress);
  gtk_widget_set_sensitive(data->start_pulse_button, FALSE);
  gtk_widget_set_sensitive(data->stop_pulse_button, TRUE);
}

static void
__on_stop_pulse_clicked(GtkButton *button, gpointer user_data)
{
  ProgressBarDemoData *data = user_data;

  (void) button;

  __stop_progress_pulse(data);
  gtk_widget_set_sensitive(data->start_pulse_button, TRUE);
  gtk_widget_set_sensitive(data->stop_pulse_button, FALSE);
}

static void
__on_fraction_mode_toggled(GtkToggleButton *button, gpointer user_data)
{
  ProgressBarDemoData *data = user_data;

  if (!gtk_toggle_button_get_active(button))
    return;

  __stop_progress_pulse(data);
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(data->progress), 0.0);
  gtk_widget_set_visible(data->fraction_actions, TRUE);
  gtk_widget_set_visible(data->pulse_actions, FALSE);
}

static void
__on_pulse_mode_toggled(GtkToggleButton *button, gpointer user_data)
{
  ProgressBarDemoData *data = user_data;

  if (!gtk_toggle_button_get_active(button))
    return;

  __stop_progress_pulse(data);
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(data->progress), 0.0);
  gtk_widget_set_visible(data->fraction_actions, FALSE);
  gtk_widget_set_visible(data->pulse_actions, TRUE);
  gtk_widget_set_sensitive(data->start_pulse_button, TRUE);
  gtk_widget_set_sensitive(data->stop_pulse_button, FALSE);
}

GtkWidget *
gallery_display_gtk_progress_bar_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *mode_row;
  GtkWidget *fraction_row;
  GtkWidget *pulse_row;
  GtkWidget *progress;
  GtkWidget *fraction_button;
  GtkWidget *pulse_button;
  GtkWidget *add_button;
  GtkWidget *reset_button;
  GtkWidget *start_pulse_button;
  GtkWidget *stop_pulse_button;
  ProgressBarDemoData *data;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
  data = g_new0(ProgressBarDemoData, 1);
  g_object_set_data_full(G_OBJECT(box), "progress-bar-demo-data", data,
                         __progress_bar_demo_data_free);

  mode_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
  fraction_button = gtk_toggle_button_new_with_label("Fraction");
  pulse_button = gtk_toggle_button_new_with_label("Pulse");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fraction_button), TRUE);
  gtk_toggle_button_set_group(GTK_TOGGLE_BUTTON(pulse_button),
                              GTK_TOGGLE_BUTTON(fraction_button));
  gtk_widget_set_hexpand(fraction_button, FALSE);
  gtk_widget_set_hexpand(pulse_button, FALSE);
  g_signal_connect(fraction_button, "toggled",
                   G_CALLBACK(__on_fraction_mode_toggled), data);
  g_signal_connect(pulse_button, "toggled",
                   G_CALLBACK(__on_pulse_mode_toggled), data);
  gtk_box_append(GTK_BOX(mode_row), fraction_button);
  gtk_box_append(GTK_BOX(mode_row), pulse_button);

  progress = gtk_progress_bar_new();
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress), 0.0);
  gtk_widget_set_size_request(progress, 240, -1);
  data->progress = progress;

  fraction_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
  add_button = gtk_button_new_with_label("Add 10%");
  reset_button = gtk_button_new_with_label("Reset");
  gtk_widget_set_hexpand(add_button, FALSE);
  gtk_widget_set_hexpand(reset_button, FALSE);
  g_signal_connect(add_button, "clicked",
                   G_CALLBACK(__on_progress_add_clicked), progress);
  g_signal_connect(reset_button, "clicked",
                   G_CALLBACK(__on_progress_reset_clicked), progress);
  gtk_box_append(GTK_BOX(fraction_row), add_button);
  gtk_box_append(GTK_BOX(fraction_row), reset_button);
  data->fraction_actions = fraction_row;

  pulse_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
  start_pulse_button = gtk_button_new_with_label("Start pulse");
  stop_pulse_button = gtk_button_new_with_label("Stop pulse");
  gtk_widget_set_hexpand(start_pulse_button, FALSE);
  gtk_widget_set_hexpand(stop_pulse_button, FALSE);
  gtk_widget_set_sensitive(stop_pulse_button, FALSE);
  g_signal_connect(start_pulse_button, "clicked",
                   G_CALLBACK(__on_start_pulse_clicked), data);
  g_signal_connect(stop_pulse_button, "clicked",
                   G_CALLBACK(__on_stop_pulse_clicked), data);
  gtk_box_append(GTK_BOX(pulse_row), start_pulse_button);
  gtk_box_append(GTK_BOX(pulse_row), stop_pulse_button);
  data->pulse_actions = pulse_row;
  data->start_pulse_button = start_pulse_button;
  data->stop_pulse_button = stop_pulse_button;
  gtk_widget_set_visible(pulse_row, FALSE);

  gtk_box_append(GTK_BOX(box), mode_row);
  gtk_box_append(GTK_BOX(box), progress);
  gtk_box_append(GTK_BOX(box), fraction_row);
  gtk_box_append(GTK_BOX(box), pulse_row);
  return box;
}

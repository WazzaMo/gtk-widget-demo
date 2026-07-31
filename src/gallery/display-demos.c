/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos.h"

typedef struct
{
  GtkWidget *spinner;
  GtkWidget *start_button;
  GtkWidget *stop_button;
} SpinnerDemoData;

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

static void
__on_scale_value_changed(GtkRange *range, gpointer user_data)
{
  GtkWidget *value_label = user_data;
  char *text;

  text = g_strdup_printf("%.0f", gtk_range_get_value(range));
  gtk_label_set_text(GTK_LABEL(value_label), text);
  g_free(text);
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

static GtkWidget *
__build_gtk_label(GtkWindow *parent_window)
{
  GtkWidget *label;

  (void) parent_window;

  label = gtk_label_new("Hello from GtkLabel");
  gtk_label_set_xalign(GTK_LABEL(label), 0.0f);
  return label;
}

static GtkWidget *
__build_gtk_spinner(GtkWindow *parent_window)
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

static GtkWidget *
__build_gtk_progress_bar(GtkWindow *parent_window)
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

static GtkWidget *
__build_gtk_scale(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *scale;
  GtkWidget *value_label;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
  scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 100.0, 1.0);
  gtk_range_set_value(GTK_RANGE(scale), 50.0);
  gtk_widget_set_size_request(scale, 240, -1);

  value_label = gtk_label_new("50");
  gtk_label_set_xalign(GTK_LABEL(value_label), 0.0f);
  g_signal_connect(scale, "value-changed",
                   G_CALLBACK(__on_scale_value_changed), value_label);

  gtk_box_append(GTK_BOX(box), scale);
  gtk_box_append(GTK_BOX(box), value_label);
  return box;
}

static const GalleryDemoEntry display_demos[] =
{
  {
    "gtk-label",
    "GtkLabel",
    "Static text with left alignment.",
    "https://docs.gtk.org/gtk4/class.Label.html",
    __build_gtk_label,
  },
  {
    "gtk-spinner",
    "GtkSpinner",
    "Start and stop the activity indicator; buttons enable and disable with spinner state.",
    "https://docs.gtk.org/gtk4/class.Spinner.html",
    __build_gtk_spinner,
  },
  {
    "gtk-progress-bar",
    "GtkProgressBar",
    "Switch between fraction and pulse modes; use the buttons below to drive each mode.",
    "https://docs.gtk.org/gtk4/class.ProgressBar.html",
    __build_gtk_progress_bar,
  },
  {
    "gtk-scale",
    "GtkScale",
    "Drag the slider; the label below shows the current value.",
    "https://docs.gtk.org/gtk4/class.Scale.html",
    __build_gtk_scale,
  },
};

const GalleryDemoEntry *
gallery_display_demos_get(gsize *demo_count)
{
  if (demo_count != NULL)
    *demo_count = G_N_ELEMENTS(display_demos);

  return display_demos;
}

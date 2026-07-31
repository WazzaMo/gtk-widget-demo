/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos.h"

static void
__on_start_spinner_clicked(GtkButton *button, gpointer user_data)
{
  GtkWidget *spinner = user_data;

  (void) button;

  gtk_spinner_start(GTK_SPINNER(spinner));
}

static void
__on_stop_spinner_clicked(GtkButton *button, gpointer user_data)
{
  GtkWidget *spinner = user_data;

  (void) button;

  gtk_spinner_stop(GTK_SPINNER(spinner));
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

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
  spinner = gtk_spinner_new();
  gtk_widget_set_hexpand(spinner, FALSE);

  button_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
  start_button = gtk_button_new_with_label("Start spinner");
  stop_button = gtk_button_new_with_label("Stop spinner");
  gtk_widget_set_hexpand(start_button, FALSE);
  gtk_widget_set_hexpand(stop_button, FALSE);
  g_signal_connect(start_button, "clicked",
                   G_CALLBACK(__on_start_spinner_clicked), spinner);
  g_signal_connect(stop_button, "clicked",
                   G_CALLBACK(__on_stop_spinner_clicked), spinner);
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
  GtkWidget *button_row;
  GtkWidget *progress;
  GtkWidget *add_button;
  GtkWidget *reset_button;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
  progress = gtk_progress_bar_new();
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress), 0.0);
  gtk_widget_set_size_request(progress, 240, -1);

  button_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
  add_button = gtk_button_new_with_label("Add 10%");
  reset_button = gtk_button_new_with_label("Reset");
  gtk_widget_set_hexpand(add_button, FALSE);
  gtk_widget_set_hexpand(reset_button, FALSE);
  g_signal_connect(add_button, "clicked",
                   G_CALLBACK(__on_progress_add_clicked), progress);
  g_signal_connect(reset_button, "clicked",
                   G_CALLBACK(__on_progress_reset_clicked), progress);
  gtk_box_append(GTK_BOX(button_row), add_button);
  gtk_box_append(GTK_BOX(button_row), reset_button);

  gtk_box_append(GTK_BOX(box), progress);
  gtk_box_append(GTK_BOX(box), button_row);
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
    "Start and stop the activity indicator with the buttons below.",
    "https://docs.gtk.org/gtk4/class.Spinner.html",
    __build_gtk_spinner,
  },
  {
    "gtk-progress-bar",
    "GtkProgressBar",
    "Add 10% or reset the completion fraction with the buttons below.",
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

/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include <gtk/gtk.h>

#include "gallery/display-demos.h"

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
  GtkWidget *spinner;

  (void) parent_window;

  spinner = gtk_spinner_new();
  gtk_spinner_start(GTK_SPINNER(spinner));
  return spinner;
}

static GtkWidget *
__build_gtk_progress_bar(GtkWindow *parent_window)
{
  GtkWidget *progress;

  (void) parent_window;

  progress = gtk_progress_bar_new();
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress), 0.65);
  gtk_widget_set_size_request(progress, 240, -1);
  return progress;
}

static GtkWidget *
__build_gtk_scale(GtkWindow *parent_window)
{
  GtkWidget *scale;

  (void) parent_window;

  scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 100.0, 1.0);
  gtk_range_set_value(GTK_RANGE(scale), 50.0);
  gtk_widget_set_size_request(scale, 240, -1);
  return scale;
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
    "Indeterminate activity indicator while work is in progress.",
    "https://docs.gtk.org/gtk4/class.Spinner.html",
    __build_gtk_spinner,
  },
  {
    "gtk-progress-bar",
    "GtkProgressBar",
    "Horizontal bar showing completion as a fraction of the whole.",
    "https://docs.gtk.org/gtk4/class.ProgressBar.html",
    __build_gtk_progress_bar,
  },
  {
    "gtk-scale",
    "GtkScale",
    "Horizontal slider for choosing a value from a numeric range.",
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

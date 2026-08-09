/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/button-demos/gtk-volume-button-demo.h"

static void
__on_volume_value_changed(GObject *object,
                          GParamSpec *pspec,
                          gpointer user_data)
{
  GtkWidget *label = user_data;
  GtkScaleButton *scale_button = GTK_SCALE_BUTTON(object);
  double value;
  char *text;

  (void) pspec;

  value = gtk_scale_button_get_value(scale_button);
  text = g_strdup_printf("Volume: %.0f%%", value * 100.0);
  gtk_label_set_text(GTK_LABEL(label), text);
  g_free(text);
}

GtkWidget *
gallery_button_gtk_volume_button_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *volume_button;
  GtkWidget *label;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);

  label = gtk_label_new("Volume: 100%");
  gtk_label_set_xalign(GTK_LABEL(label), 0.0f);

G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  volume_button = gtk_volume_button_new();
G_GNUC_END_IGNORE_DEPRECATIONS

  g_signal_connect(volume_button, "notify::value",
                   G_CALLBACK(__on_volume_value_changed), label);

  gtk_box_append(GTK_BOX(box), volume_button);
  gtk_box_append(GTK_BOX(box), label);

  return box;
}

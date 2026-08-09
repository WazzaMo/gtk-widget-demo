/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/button-demos/gtk-button-demo.h"

static void
__on_demo_button_clicked(GtkButton *button, gpointer user_data)
{
  GtkWidget *feedback = user_data;

  (void) button;

  gtk_label_set_text(GTK_LABEL(feedback), "GtkButton clicked.");
}

GtkWidget *
gallery_button_gtk_button_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *button;
  GtkWidget *feedback;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
  button = gtk_button_new_with_label("Click me");
  feedback = gtk_label_new("Click the button for feedback.");
  gtk_label_set_xalign(GTK_LABEL(feedback), 0.0f);
  g_signal_connect(button, "clicked", G_CALLBACK(__on_demo_button_clicked),
                   feedback);
  gtk_box_append(GTK_BOX(box), button);
  gtk_box_append(GTK_BOX(box), feedback);
  return box;
}

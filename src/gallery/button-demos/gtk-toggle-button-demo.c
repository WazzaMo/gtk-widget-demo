/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/button-demos/gtk-toggle-button-demo.h"

static void
__on_toggle_button_toggled(GtkToggleButton *button, gpointer user_data)
{
  (void) user_data;

  if (gtk_toggle_button_get_active(button))
    gtk_button_set_label(GTK_BUTTON(button), "Toggled on");
  else
    gtk_button_set_label(GTK_BUTTON(button), "Toggled off");
}

GtkWidget *
gallery_button_gtk_toggle_button_demo_build(GtkWindow *parent_window)
{
  GtkWidget *toggle;

  (void) parent_window;

  toggle = gtk_toggle_button_new_with_label("Toggled off");
  g_signal_connect(toggle, "toggled",
                   G_CALLBACK(__on_toggle_button_toggled), NULL);
  return toggle;
}

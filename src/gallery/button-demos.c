/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include <gtk/gtk.h>

#include "gallery/button-demos.h"

static void
__on_demo_button_clicked(GtkButton *button, gpointer user_data)
{
  GtkWidget *feedback = user_data;

  (void) button;

  gtk_label_set_text(GTK_LABEL(feedback), "GtkButton clicked.");
}

static GtkWidget *
__build_gtk_button(GtkWindow *parent_window)
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

static GtkWidget *
__build_gtk_check_button(GtkWindow *parent_window)
{
  GtkWidget *check;

  (void) parent_window;

  check = gtk_check_button_new_with_label("Enable option");
  gtk_check_button_set_active(GTK_CHECK_BUTTON(check), TRUE);
  return check;
}

static GtkWidget *
__build_gtk_switch(GtkWindow *parent_window)
{
  GtkWidget *switch_widget;

  (void) parent_window;

  switch_widget = gtk_switch_new();
  gtk_switch_set_active(GTK_SWITCH(switch_widget), TRUE);
  return switch_widget;
}

static void
__on_toggle_button_toggled(GtkToggleButton *button, gpointer user_data)
{
  (void) user_data;

  if (gtk_toggle_button_get_active(button))
    gtk_button_set_label(GTK_BUTTON(button), "Toggled on");
  else
    gtk_button_set_label(GTK_BUTTON(button), "Toggled off");
}

static GtkWidget *
__build_gtk_toggle_button(GtkWindow *parent_window)
{
  GtkWidget *toggle;

  (void) parent_window;

  toggle = gtk_toggle_button_new_with_label("Toggled off");
  g_signal_connect(toggle, "toggled",
                   G_CALLBACK(__on_toggle_button_toggled), NULL);
  return toggle;
}

static const GalleryDemoEntry button_demos[] =
{
  {
    "gtk-button",
    "GtkButton",
    "Standard push button with a click handler and feedback label.",
    "https://docs.gtk.org/gtk4/class.Button.html",
    __build_gtk_button,
  },
  {
    "gtk-check-button",
    "GtkCheckButton",
    "Checkbox control for boolean on/off state.",
    "https://docs.gtk.org/gtk4/class.CheckButton.html",
    __build_gtk_check_button,
  },
  {
    "gtk-switch",
    "GtkSwitch",
    "Compact on/off switch control.",
    "https://docs.gtk.org/gtk4/class.Switch.html",
    __build_gtk_switch,
  },
  {
    "gtk-toggle-button",
    "GtkToggleButton",
    "Button that stays pressed until clicked again.",
    "https://docs.gtk.org/gtk4/class.ToggleButton.html",
    __build_gtk_toggle_button,
  },
};

const GalleryDemoEntry *
gallery_button_demos_get(gsize *demo_count)
{
  if (demo_count != NULL)
    *demo_count = G_N_ELEMENTS(button_demos);

  return button_demos;
}

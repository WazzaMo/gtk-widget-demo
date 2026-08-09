/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/button-demos/gtk-radio-button-demo.h"

static void
__update_radio_feedback(GtkCheckButton *button, gpointer user_data)
{
  GtkWidget *label = user_data;
  const char *choice;

  if (!gtk_check_button_get_active(button))
    return;

  choice = gtk_check_button_get_label(button);
  if (choice == NULL)
    choice = "Selected option";

  gtk_label_set_text(GTK_LABEL(label), choice);
}

GtkWidget *
gallery_button_gtk_radio_button_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *option_a;
  GtkWidget *option_b;
  GtkWidget *option_c;
  GtkWidget *feedback;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);

  option_a = gtk_check_button_new_with_label("Option A");
  option_b = gtk_check_button_new_with_label("Option B");
  option_c = gtk_check_button_new_with_label("Option C");

  gtk_check_button_set_group(GTK_CHECK_BUTTON(option_b),
                             GTK_CHECK_BUTTON(option_a));
  gtk_check_button_set_group(GTK_CHECK_BUTTON(option_c),
                             GTK_CHECK_BUTTON(option_a));
  gtk_check_button_set_active(GTK_CHECK_BUTTON(option_a), TRUE);

  feedback = gtk_label_new("Option A");
  gtk_label_set_xalign(GTK_LABEL(feedback), 0.0f);

  g_signal_connect(option_a, "notify::active",
                   G_CALLBACK(__update_radio_feedback), feedback);
  g_signal_connect(option_b, "notify::active",
                   G_CALLBACK(__update_radio_feedback), feedback);
  g_signal_connect(option_c, "notify::active",
                   G_CALLBACK(__update_radio_feedback), feedback);

  gtk_box_append(GTK_BOX(box), option_a);
  gtk_box_append(GTK_BOX(box), option_b);
  gtk_box_append(GTK_BOX(box), option_c);
  gtk_box_append(GTK_BOX(box), feedback);

  return box;
}

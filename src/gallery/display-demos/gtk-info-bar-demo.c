/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-info-bar-demo.h"

static void
__on_info_bar_response(GtkInfoBar *info_bar, int response_id, gpointer user_data)
{
  (void) user_data;

  if (response_id == GTK_RESPONSE_CLOSE)
    gtk_widget_set_visible(GTK_WIDGET(info_bar), FALSE);
}

static void
__on_show_info_bar_clicked(GtkButton *button, gpointer user_data)
{
  GtkWidget *info_bar = user_data;

  (void) button;

  gtk_widget_set_visible(info_bar, TRUE);
}

GtkWidget *
gallery_display_gtk_info_bar_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *info_bar;
  GtkWidget *message_label;
  GtkWidget *show_button;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);

G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  info_bar = gtk_info_bar_new();
  gtk_info_bar_set_message_type(GTK_INFO_BAR(info_bar), GTK_MESSAGE_INFO);
  gtk_info_bar_set_show_close_button(GTK_INFO_BAR(info_bar), TRUE);
  message_label = gtk_label_new("This is an information message.");
  gtk_info_bar_add_child(GTK_INFO_BAR(info_bar), message_label);
  gtk_info_bar_add_button(GTK_INFO_BAR(info_bar), "Dismiss", GTK_RESPONSE_CLOSE);
  g_signal_connect(info_bar, "response",
                   G_CALLBACK(__on_info_bar_response), NULL);
G_GNUC_END_IGNORE_DEPRECATIONS
  gtk_widget_set_visible(info_bar, FALSE);

  show_button = gtk_button_new_with_label("Show info bar");
  gtk_widget_set_hexpand(show_button, FALSE);
  g_signal_connect(show_button, "clicked",
                   G_CALLBACK(__on_show_info_bar_clicked), info_bar);

  gtk_box_append(GTK_BOX(box), info_bar);
  gtk_box_append(GTK_BOX(box), show_button);
  return box;
}

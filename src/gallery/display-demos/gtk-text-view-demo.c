/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-text-view-demo.h"

typedef struct
{
  GtkWidget *text_view;
  GtkTextTag *small_tag;
  GtkTextTag *normal_tag;
  GtkTextTag *large_tag;
} TextViewDemoData;

static void
__apply_text_scale(TextViewDemoData *data, GtkTextTag *tag)
{
  GtkTextBuffer *buffer;
  GtkTextIter start;
  GtkTextIter end;

  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(data->text_view));
  if (!gtk_text_buffer_get_selection_bounds(buffer, &start, &end))
    return;

  gtk_text_buffer_apply_tag(buffer, tag, &start, &end);
}

static void
__on_small_text_clicked(GtkButton *button, gpointer user_data)
{
  TextViewDemoData *data = user_data;

  (void) button;

  __apply_text_scale(data, data->small_tag);
}

static void
__on_normal_text_clicked(GtkButton *button, gpointer user_data)
{
  TextViewDemoData *data = user_data;

  (void) button;

  __apply_text_scale(data, data->normal_tag);
}

static void
__on_large_text_clicked(GtkButton *button, gpointer user_data)
{
  TextViewDemoData *data = user_data;

  (void) button;

  __apply_text_scale(data, data->large_tag);
}

GtkWidget *
gallery_display_gtk_text_view_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *button_row;
  GtkWidget *small_button;
  GtkWidget *normal_button;
  GtkWidget *large_button;
  GtkWidget *text_view;
  GtkWidget *scrolled_window;
  GtkTextBuffer *buffer;
  TextViewDemoData *data;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
  data = g_new0(TextViewDemoData, 1);
  g_object_set_data_full(G_OBJECT(box), "text-view-demo-data", data, g_free);

  button_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
  small_button = gtk_button_new_with_label("Small");
  normal_button = gtk_button_new_with_label("Normal");
  large_button = gtk_button_new_with_label("Large");
  gtk_widget_set_hexpand(small_button, FALSE);
  gtk_widget_set_hexpand(normal_button, FALSE);
  gtk_widget_set_hexpand(large_button, FALSE);
  g_signal_connect(small_button, "clicked",
                   G_CALLBACK(__on_small_text_clicked), data);
  g_signal_connect(normal_button, "clicked",
                   G_CALLBACK(__on_normal_text_clicked), data);
  g_signal_connect(large_button, "clicked",
                   G_CALLBACK(__on_large_text_clicked), data);
  gtk_box_append(GTK_BOX(button_row), small_button);
  gtk_box_append(GTK_BOX(button_row), normal_button);
  gtk_box_append(GTK_BOX(button_row), large_button);

  scrolled_window = gtk_scrolled_window_new();
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                 GTK_POLICY_AUTOMATIC,
                                 GTK_POLICY_AUTOMATIC);
  gtk_widget_set_size_request(scrolled_window, 320, 140);

  text_view = gtk_text_view_new();
  data->text_view = text_view;
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
  gtk_text_buffer_set_text(buffer,
                           "Select text, then apply Small, Normal, or Large.",
                           -1);
  data->small_tag = gtk_text_buffer_create_tag(buffer, "small",
                                               "scale", 0.75,
                                               NULL);
  data->normal_tag = gtk_text_buffer_create_tag(buffer, "normal",
                                                "scale", 1.0,
                                                NULL);
  data->large_tag = gtk_text_buffer_create_tag(buffer, "large",
                                               "scale", 1.5,
                                               NULL);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), text_view);

  gtk_box_append(GTK_BOX(box), button_row);
  gtk_box_append(GTK_BOX(box), scrolled_window);
  return box;
}

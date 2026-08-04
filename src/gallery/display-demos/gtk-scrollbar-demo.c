/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-scrollbar-demo.h"

GtkWidget *
gallery_display_gtk_scrollbar_demo_build(GtkWindow *parent_window)
{
  GtkWidget *scrolled_window;
  GtkWidget *text_view;
  GtkTextBuffer *buffer;
  GString *body;
  int line_index;

  (void) parent_window;

  scrolled_window = gtk_scrolled_window_new();
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                 GTK_POLICY_NEVER,
                                 GTK_POLICY_AUTOMATIC);
  gtk_widget_set_size_request(scrolled_window, 280, 160);

  text_view = gtk_text_view_new();
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);
  gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
  gtk_widget_set_margin_start(text_view, 8);
  gtk_widget_set_margin_end(text_view, 8);
  gtk_widget_set_margin_top(text_view, 8);
  gtk_widget_set_margin_bottom(text_view, 8);

  body = g_string_new("Scroll the vertical GtkScrollbar beside this text.\n\n");
  for (line_index = 1; line_index <= 30; line_index++)
    g_string_append_printf(body, "Line %d of sample content.\n", line_index);

  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
  gtk_text_buffer_set_text(buffer, body->str, (int) body->len);
  g_string_free(body, TRUE);

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), text_view);
  return scrolled_window;
}

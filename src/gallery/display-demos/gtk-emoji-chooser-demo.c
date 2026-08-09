/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-emoji-chooser-demo.h"

static void
__on_emoji_picked(GtkEmojiChooser *chooser,
                  const char *text,
                  gpointer user_data)
{
  GtkWidget *label = user_data;
  char *message;

  (void) chooser;

  if (text == NULL || text[0] == '\0')
    return;

  message = g_strdup_printf("Selected emoji: %s", text);
  gtk_label_set_text(GTK_LABEL(label), message);
  g_free(message);
}

GtkWidget *
gallery_display_gtk_emoji_chooser_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *chooser;
  GtkWidget *label;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);

  chooser = gtk_emoji_chooser_new();
  gtk_widget_set_size_request(chooser, 320, 240);
  gtk_widget_set_hexpand(chooser, FALSE);

  label = gtk_label_new("Pick an emoji from the chooser.");
  gtk_label_set_xalign(GTK_LABEL(label), 0.0f);

  g_signal_connect(chooser,
                   "emoji-picked",
                   G_CALLBACK(__on_emoji_picked),
                   label);

  gtk_box_append(GTK_BOX(box), chooser);
  gtk_box_append(GTK_BOX(box), label);

  return box;
}

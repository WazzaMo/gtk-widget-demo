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

static void
__on_open_chooser_clicked(GtkButton *button, gpointer user_data)
{
  GtkWidget *chooser = user_data;

  (void) button;

  gtk_popover_popup(GTK_POPOVER(chooser));
}

GtkWidget *
gallery_display_gtk_emoji_chooser_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *open_button;
  GtkWidget *chooser;
  GtkWidget *label;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);

  open_button = gtk_button_new_with_label("Open emoji chooser");
  gtk_widget_set_hexpand(open_button, FALSE);

  chooser = gtk_emoji_chooser_new();
  gtk_widget_set_parent(chooser, box);

  label = gtk_label_new("Pick an emoji from the chooser.");
  gtk_label_set_xalign(GTK_LABEL(label), 0.0f);

  g_signal_connect(open_button,
                   "clicked",
                   G_CALLBACK(__on_open_chooser_clicked),
                   chooser);
  g_signal_connect(chooser,
                   "emoji-picked",
                   G_CALLBACK(__on_emoji_picked),
                   label);

  gtk_box_append(GTK_BOX(box), open_button);
  gtk_box_append(GTK_BOX(box), label);

  return box;
}

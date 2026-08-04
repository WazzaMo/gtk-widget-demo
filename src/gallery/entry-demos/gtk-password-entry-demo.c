/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/entry-demos/gtk-password-entry-demo.h"

GtkWidget *
gallery_entry_gtk_password_entry_demo_build(GtkWindow *parent_window)
{
  GtkWidget *entry;

  (void) parent_window;

  entry = gtk_password_entry_new();
  gtk_password_entry_set_show_peek_icon(GTK_PASSWORD_ENTRY(entry), TRUE);
  gtk_editable_set_text(GTK_EDITABLE(entry), "secret");
  gtk_widget_set_size_request(entry, 240, -1);
  return entry;
}

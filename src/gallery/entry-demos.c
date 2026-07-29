/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"


#include "gallery/entry-demos.h"

static GtkWidget *
__build_gtk_entry(GtkWindow *parent_window)
{
  GtkWidget *entry;

  (void) parent_window;

  entry = gtk_entry_new();
  gtk_editable_set_text(GTK_EDITABLE(entry), "Editable text");
  gtk_widget_set_size_request(entry, 240, -1);
  return entry;
}

static GtkWidget *
__build_gtk_spin_button(GtkWindow *parent_window)
{
  GtkWidget *spin;
  GtkAdjustment *adjustment;

  (void) parent_window;

  adjustment = gtk_adjustment_new(5.0, 0.0, 10.0, 1.0, 2.0, 0.0);
  spin = gtk_spin_button_new(adjustment, 1.0, 0);
  return spin;
}

static const GalleryDemoEntry entry_demos[] =
{
  {
    "gtk-entry",
    "GtkEntry",
    "Single-line text entry for user input.",
    "https://docs.gtk.org/gtk4/class.Entry.html",
    __build_gtk_entry,
  },
  {
    "gtk-spin-button",
    "GtkSpinButton",
    "Numeric entry with stepper buttons bound to a GtkAdjustment.",
    "https://docs.gtk.org/gtk4/class.SpinButton.html",
    __build_gtk_spin_button,
  },
};

const GalleryDemoEntry *
gallery_entry_demos_get(gsize *demo_count)
{
  if (demo_count != NULL)
    *demo_count = G_N_ELEMENTS(entry_demos);

  return entry_demos;
}

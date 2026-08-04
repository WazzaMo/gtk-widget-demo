/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/entry-demos.h"
#include "gallery/entry-demos/gtk-editable-label-demo.h"
#include "gallery/entry-demos/gtk-entry-demo.h"
#include "gallery/entry-demos/gtk-password-entry-demo.h"
#include "gallery/entry-demos/gtk-search-entry-demo.h"
#include "gallery/entry-demos/gtk-spin-button-demo.h"

static const GalleryDemoEntry entry_demos[] =
{
  {
    "gtk-entry",
    "GtkEntry",
    "Single-line text entry for user input.",
    "https://docs.gtk.org/gtk4/class.Entry.html",
    gallery_entry_gtk_entry_demo_build,
  },
  {
    "gtk-search-entry",
    "GtkSearchEntry",
    "Search entry with placeholder text.",
    "https://docs.gtk.org/gtk4/class.SearchEntry.html",
    gallery_entry_gtk_search_entry_demo_build,
  },
  {
    "gtk-password-entry",
    "GtkPasswordEntry",
    "Masked password entry with peek icon to reveal text.",
    "https://docs.gtk.org/gtk4/class.PasswordEntry.html",
    gallery_entry_gtk_password_entry_demo_build,
  },
  {
    "gtk-spin-button",
    "GtkSpinButton",
    "Numeric entry with stepper buttons bound to a GtkAdjustment.",
    "https://docs.gtk.org/gtk4/class.SpinButton.html",
    gallery_entry_gtk_spin_button_demo_build,
  },
  {
    "gtk-editable-label",
    "GtkEditableLabel",
    "Label that switches to editable mode on activation.",
    "https://docs.gtk.org/gtk4/class.EditableLabel.html",
    gallery_entry_gtk_editable_label_demo_build,
  },
};

const GalleryDemoEntry *
gallery_entry_demos_get(gsize *demo_count)
{
  if (demo_count != NULL)
    *demo_count = G_N_ELEMENTS(entry_demos);

  return entry_demos;
}

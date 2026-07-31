/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos.h"
#include "gallery/display-demos/gtk-label-demo.h"
#include "gallery/display-demos/gtk-progress-bar-demo.h"
#include "gallery/display-demos/gtk-scale-demo.h"
#include "gallery/display-demos/gtk-spinner-demo.h"

static const GalleryDemoEntry display_demos[] =
{
  {
    "gtk-label",
    "GtkLabel",
    "Static text with left alignment.",
    "https://docs.gtk.org/gtk4/class.Label.html",
    gallery_display_gtk_label_demo_build,
  },
  {
    "gtk-spinner",
    "GtkSpinner",
    "Start and stop the activity indicator; buttons enable and disable with spinner state.",
    "https://docs.gtk.org/gtk4/class.Spinner.html",
    gallery_display_gtk_spinner_demo_build,
  },
  {
    "gtk-progress-bar",
    "GtkProgressBar",
    "Switch between fraction and pulse modes; use the buttons below to drive each mode.",
    "https://docs.gtk.org/gtk4/class.ProgressBar.html",
    gallery_display_gtk_progress_bar_demo_build,
  },
  {
    "gtk-scale",
    "GtkScale",
    "Drag the slider; the label below shows the current value.",
    "https://docs.gtk.org/gtk4/class.Scale.html",
    gallery_display_gtk_scale_demo_build,
  },
};

const GalleryDemoEntry *
gallery_display_demos_get(gsize *demo_count)
{
  if (demo_count != NULL)
    *demo_count = G_N_ELEMENTS(display_demos);

  return display_demos;
}

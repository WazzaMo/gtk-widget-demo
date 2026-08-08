/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos.h"
#include "gallery/display-demos/gtk-info-bar-demo.h"
#include "gallery/display-demos/gtk-gl-area-demo.h"
#include "gallery/display-demos/gtk-image-demo.h"
#include "gallery/display-demos/gtk-label-demo.h"
#include "gallery/display-demos/gtk-level-bar-demo.h"
#include "gallery/display-demos/gtk-picture-demo.h"
#include "gallery/display-demos/gtk-popover-menu-demo.h"
#include "gallery/display-demos/gtk-progress-bar-demo.h"
#include "gallery/display-demos/gtk-scale-demo.h"
#include "gallery/display-demos/gtk-scrollbar-demo.h"
#include "gallery/display-demos/gtk-separator-demo.h"
#include "gallery/display-demos/gtk-spinner-demo.h"
#include "gallery/display-demos/gtk-statusbar-demo.h"
#include "gallery/display-demos/gtk-text-view-demo.h"
#include "gallery/display-demos/gtk-video-demo.h"

static const GalleryDemoEntry display_demos[] =
{
  {
    "gtk-label",
    "GtkLabel",
    "Static text with left alignment.",
    "https://docs.gtk.org/gtk4/class.Label.html",
    gallery_display_gtk_label_demo_build,
    GALLERY_DEMO_SUPPORTED,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
  },
  {
    "gtk-spinner",
    "GtkSpinner",
    "Start and stop the activity indicator; buttons enable and disable with spinner state.",
    "https://docs.gtk.org/gtk4/class.Spinner.html",
    gallery_display_gtk_spinner_demo_build,
    GALLERY_DEMO_SUPPORTED,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
  },
  {
    "gtk-statusbar",
    "GtkStatusbar",
    "Push, pop, and timed status messages on the bar.",
    "https://docs.gtk.org/gtk4/class.Statusbar.html",
    gallery_display_gtk_statusbar_demo_build,
    GALLERY_DEMO_DEPRECATED,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
  },
  {
    "gtk-level-bar",
    "GtkLevelBar",
    "Filled level for a numeric range; adjust with the scale below.",
    "https://docs.gtk.org/gtk4/class.LevelBar.html",
    gallery_display_gtk_level_bar_demo_build,
    GALLERY_DEMO_SUPPORTED,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
  },
  {
    "gtk-progress-bar",
    "GtkProgressBar",
    "Switch between fraction and pulse modes; use the buttons below to drive each mode.",
    "https://docs.gtk.org/gtk4/class.ProgressBar.html",
    gallery_display_gtk_progress_bar_demo_build,
    GALLERY_DEMO_SUPPORTED,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
  },
  {
    "gtk-info-bar",
    "GtkInfoBar",
    "Information bar with dismiss control; open it with the button below.",
    "https://docs.gtk.org/gtk4/class.InfoBar.html",
    gallery_display_gtk_info_bar_demo_build,
    GALLERY_DEMO_DEPRECATED,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
  },
  {
    "gtk-scrollbar",
    "GtkScrollbar",
    "Vertical scrollbar on a tall GtkTextView inside GtkScrolledWindow.",
    "https://docs.gtk.org/gtk4/class.Scrollbar.html",
    gallery_display_gtk_scrollbar_demo_build,
    GALLERY_DEMO_SUPPORTED,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
  },
  {
    "gtk-image",
    "GtkImage",
    "Static image loaded from bundled demo-icon.svg.",
    "https://docs.gtk.org/gtk4/class.Image.html",
    gallery_display_gtk_image_demo_build,
    GALLERY_DEMO_SUPPORTED,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
  },
  {
    "gtk-picture",
    "GtkPicture",
    "Scalable picture from bundled demo-icon.svg.",
    "https://docs.gtk.org/gtk4/class.Picture.html",
    gallery_display_gtk_picture_demo_build,
    GALLERY_DEMO_SUPPORTED,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
  },
  {
    "gtk-separator",
    "GtkSeparator",
    "Horizontal and vertical rules separating labels.",
    "https://docs.gtk.org/gtk4/class.Separator.html",
    gallery_display_gtk_separator_demo_build,
    GALLERY_DEMO_SUPPORTED,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
  },
  {
    "gtk-text-view",
    "GtkTextView",
    "Editable text; select a range and apply Small, Normal, or Large scale tags.",
    "https://docs.gtk.org/gtk4/class.TextView.html",
    gallery_display_gtk_text_view_demo_build,
    GALLERY_DEMO_SUPPORTED,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
  },
  {
    "gtk-scale",
    "GtkScale",
    "Drag the slider; the label below shows the current value.",
    "https://docs.gtk.org/gtk4/class.Scale.html",
    gallery_display_gtk_scale_demo_build,
    GALLERY_DEMO_SUPPORTED,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
  },
  {
    "gtk-gl-area",
    "GtkGLArea",
    "Minimal OpenGL clear colour render; shows a fallback label when GL is unavailable.",
    "https://docs.gtk.org/gtk4/class.GLArea.html",
    gallery_display_gtk_gl_area_demo_build,
    GALLERY_DEMO_SUPPORTED,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
  },
  {
    "gtk-video",
    "GtkVideo",
    "Plays bundled demo-sample.mp4 (2 s); requires GStreamer plugins at runtime.",
    "https://docs.gtk.org/gtk4/class.Video.html",
    gallery_display_gtk_video_demo_build,
    GALLERY_DEMO_SUPPORTED,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
  },
  {
    "gtk-popover-menu",
    "GtkPopoverMenu",
    "Popover menu on a GtkMenuButton; inspect GtkPopoverMenu while the menu is open.",
    "https://docs.gtk.org/gtk4/class.PopoverMenu.html",
    gallery_display_gtk_popover_menu_demo_build,
    GALLERY_DEMO_SUPPORTED,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
  },
};

const GalleryDemoEntry *
gallery_display_demos_get(gsize *demo_count)
{
  if (demo_count != NULL)
    *demo_count = G_N_ELEMENTS(display_demos);

  return display_demos;
}

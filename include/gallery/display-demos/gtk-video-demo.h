/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef GALLERY_DISPLAY_DEMOS_GTK_VIDEO_DEMO_H
#define GALLERY_DISPLAY_DEMOS_GTK_VIDEO_DEMO_H

#include "gtk-version.h"

/**
 * Build the GtkVideo display-widget gallery demo.
 * @param parent_window parent window for modal demos, unused here
 * @return the demo content widget
 */
GtkWidget *gallery_display_gtk_video_demo_build(GtkWindow *parent_window);

#define DEMO_VIDEO_CLIP "demo-short.mp4"

#endif

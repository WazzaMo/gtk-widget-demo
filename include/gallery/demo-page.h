/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */
#include "gtk-version.h"

#ifndef GALLERY_DEMO_PAGE_H
#define GALLERY_DEMO_PAGE_H

#include "gallery/demo-registry.h"

/**
 * Build a demo page with title, description, upstream link, and content area.
 * @param demo gallery registry entry for title, links, and lifecycle metadata
 * @param legacy_content the primary demo widget, may be NULL
 * @param comparison_content optional modern-alternative widget, may be NULL
 * @return a new demo page widget
 */
GtkWidget *gallery_demo_page_new(const GalleryDemoEntry *demo,
                                 GtkWidget *legacy_content,
                                 GtkWidget *comparison_content);

#endif

/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef GALLERY_DEMO_PAGE_H
#define GALLERY_DEMO_PAGE_H

#include <gtk/gtk.h>

/**
 * Build a demo page with title, description, upstream link, and content area.
 * @param title the widget name shown as the page heading
 * @param description optional short description, may be NULL
 * @param doc_url upstream GTK documentation URL
 * @param content the primary demo widget, may be NULL
 * @return a new demo page widget
 */
GtkWidget *gallery_demo_page_new(const char *title,
                                 const char *description,
                                 const char *doc_url,
                                 GtkWidget *content);

#endif

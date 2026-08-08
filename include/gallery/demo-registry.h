/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef GALLERY_DEMO_REGISTRY_H
#define GALLERY_DEMO_REGISTRY_H

#include "gtk-version.h"


typedef GtkWidget *(*GalleryDemoContentFunc)(GtkWindow *parent_window);
typedef GtkWidget *(*GalleryDemoComparisonFunc)(GtkWindow *parent_window);

typedef enum
{
  GALLERY_DEMO_SUPPORTED = 0,
  GALLERY_DEMO_DEPRECATED,
} GalleryDemoLifecycle;

typedef struct
{
  const char *id;
  const char *title;
  const char *description;
  const char *doc_url;
  GalleryDemoContentFunc build_content;
  GalleryDemoLifecycle lifecycle;
  const char *replacement_doc_url;
  const char *deprecation_note;
  GalleryDemoComparisonFunc build_comparison;
  const char *comparison_title;
  const char *comparison_doc_url;
} GalleryDemoEntry;

typedef struct
{
  const char *id;
  const char *title;
  const GalleryDemoEntry *demos;
  gsize demo_count;
} GalleryCategoryEntry;

/**
 * Return the number of registered gallery categories.
 * @return the category count
 */
gsize gallery_demo_registry_get_category_count(void);

/**
 * Return a gallery category entry by index.
 * @param index zero-based category index
 * @return the category entry, or NULL when out of range
 */
const GalleryCategoryEntry *gallery_demo_registry_get_category(gsize index);

/**
 * Find a demo entry by its stable id.
 * @param demo_id the demo id to look up
 * @return the demo entry, or NULL when not found
 */
const GalleryDemoEntry *gallery_demo_registry_find_demo(const char *demo_id);

/**
 * Return the id of the default demo selected on startup.
 * @return the default demo id
 */
const char *gallery_demo_registry_get_default_demo_id(void);

/**
 * Return whether a category contains at least one deprecated demo.
 * @param category the category entry
 * @return TRUE when the category has deprecated demos
 */
gboolean gallery_demo_registry_category_has_deprecated(
  const GalleryCategoryEntry *category);

#endif

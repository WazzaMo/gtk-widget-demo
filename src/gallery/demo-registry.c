/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gallery/button-demos.h"
#include "gallery/container-demos.h"
#include "gallery/demo-registry.h"
#include "gallery/display-demos.h"
#include "gallery/entry-demos.h"
#include "gallery/window-demos.h"

static const GalleryCategoryEntry gallery_categories[] =
{
  {
    "display-widgets",
    "Display widgets",
    NULL,
    0,
  },
  {
    "buttons",
    "Buttons",
    NULL,
    0,
  },
  {
    "entries",
    "Entries",
    NULL,
    0,
  },
  {
    "containers",
    "Containers",
    NULL,
    0,
  },
  {
    "windows",
    "Windows",
    NULL,
    0,
  },
};

static GalleryCategoryEntry gallery_categories_runtime[G_N_ELEMENTS(gallery_categories)];
static gboolean gallery_categories_initialized;

static void
__init_categories(void)
{
  gsize i;

  if (gallery_categories_initialized)
    return;

  for (i = 0; i < G_N_ELEMENTS(gallery_categories); i++)
    gallery_categories_runtime[i] = gallery_categories[i];

  gallery_categories_runtime[0].demos = gallery_display_demos_get(
    &gallery_categories_runtime[0].demo_count);
  gallery_categories_runtime[1].demos = gallery_button_demos_get(
    &gallery_categories_runtime[1].demo_count);
  gallery_categories_runtime[2].demos = gallery_entry_demos_get(
    &gallery_categories_runtime[2].demo_count);
  gallery_categories_runtime[3].demos = gallery_container_demos_get(
    &gallery_categories_runtime[3].demo_count);
  gallery_categories_runtime[4].demos = gallery_window_demos_get(
    &gallery_categories_runtime[4].demo_count);

  gallery_categories_initialized = TRUE;
}

gsize
gallery_demo_registry_get_category_count(void)
{
  __init_categories();
  return G_N_ELEMENTS(gallery_categories_runtime);
}

const GalleryCategoryEntry *
gallery_demo_registry_get_category(gsize index)
{
  __init_categories();

  if (index >= G_N_ELEMENTS(gallery_categories_runtime))
    return NULL;

  return &gallery_categories_runtime[index];
}

const GalleryDemoEntry *
gallery_demo_registry_find_demo(const char *demo_id)
{
  gsize category_index;
  gsize demo_index;

  __init_categories();

  if (demo_id == NULL)
    return NULL;

  for (category_index = 0;
       category_index < G_N_ELEMENTS(gallery_categories_runtime);
       category_index++)
    {
      const GalleryCategoryEntry *category;

      category = &gallery_categories_runtime[category_index];

      for (demo_index = 0; demo_index < category->demo_count; demo_index++)
        {
          const GalleryDemoEntry *demo;

          demo = &category->demos[demo_index];
          if (g_strcmp0(demo->id, demo_id) == 0)
            return demo;
        }
    }

  return NULL;
}

const char *
gallery_demo_registry_get_default_demo_id(void)
{
  const GalleryCategoryEntry *category;

  __init_categories();

  category = &gallery_categories_runtime[0];
  if (category->demo_count == 0)
    return NULL;

  return category->demos[0].id;
}

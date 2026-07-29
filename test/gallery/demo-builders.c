/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/demo-page.h"
#include "gallery/demo-registry.h"

static void
__test_all_demo_builders(void)
{
  gsize category_index;

  for (category_index = 0;
       category_index < gallery_demo_registry_get_category_count();
       category_index++)
    {
      const GalleryCategoryEntry *category;
      gsize demo_index;

      category = gallery_demo_registry_get_category(category_index);

      for (demo_index = 0; demo_index < category->demo_count; demo_index++)
        {
          const GalleryDemoEntry *demo;
          GtkWidget *content;
          GtkWidget *page;

          demo = &category->demos[demo_index];
          content = demo->build_content(NULL);
          g_assert_nonnull(content);

          page = gallery_demo_page_new(demo->title,
                                       demo->description,
                                       demo->doc_url,
                                       content);
          g_assert_nonnull(page);
        }
    }
}

int
main(int argc, char *argv[])
{
  int status;

  gtk_init();
  g_test_init(&argc, &argv, NULL);

  g_test_add_func("/gallery/demo-builders/all-demos",
                  __test_all_demo_builders);

  status = g_test_run();

  return status;
}

/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/demo-registry.h"

static void
__test_category_count(void)
{
  g_assert_cmpuint(gallery_demo_registry_get_category_count(), ==, 5);
}

static void
__test_demo_counts(void)
{
  g_assert_cmpuint(gallery_demo_registry_get_category(0)->demo_count, ==, 12);
  g_assert_cmpuint(gallery_demo_registry_get_category(1)->demo_count, ==, 4);
  g_assert_cmpuint(gallery_demo_registry_get_category(2)->demo_count, ==, 5);
  g_assert_cmpuint(gallery_demo_registry_get_category(3)->demo_count, ==, 4);
  g_assert_cmpuint(gallery_demo_registry_get_category(4)->demo_count, ==, 2);
}

static void
__test_category_titles(void)
{
  g_assert_cmpstr(gallery_demo_registry_get_category(0)->title,
                  ==, "Display widgets");
  g_assert_cmpstr(gallery_demo_registry_get_category(1)->title,
                  ==, "Buttons");
  g_assert_cmpstr(gallery_demo_registry_get_category(2)->title,
                  ==, "Entries");
  g_assert_cmpstr(gallery_demo_registry_get_category(3)->title,
                  ==, "Containers");
  g_assert_cmpstr(gallery_demo_registry_get_category(4)->title,
                  ==, "Windows");
}

static void
__test_default_demo(void)
{
  const GalleryDemoEntry *demo;

  g_assert_cmpstr(gallery_demo_registry_get_default_demo_id(), ==, "gtk-label");

  demo = gallery_demo_registry_find_demo("gtk-label");
  g_assert_nonnull(demo);
  g_assert_cmpstr(demo->title, ==, "GtkLabel");
}

static void
__test_find_demo_missing(void)
{
  g_assert_null(gallery_demo_registry_find_demo("missing-demo"));
}

static void
__test_category_demo_order(gsize category_index,
                           const char *const *expected_ids,
                           gsize expected_count)
{
  const GalleryCategoryEntry *category;
  gsize demo_index;

  category = gallery_demo_registry_get_category(category_index);
  g_assert_cmpuint(category->demo_count, ==, expected_count);

  for (demo_index = 0; demo_index < expected_count; demo_index++)
    g_assert_cmpstr(category->demos[demo_index].id, ==, expected_ids[demo_index]);
}

static void
__test_deprecated_demo_lifecycle(void)
{
  const GalleryDemoEntry *demo;

  demo = gallery_demo_registry_find_demo("gtk-statusbar");
  g_assert_nonnull(demo);
  g_assert_cmpint(demo->lifecycle, ==, GALLERY_DEMO_DEPRECATED);

  demo = gallery_demo_registry_find_demo("gtk-info-bar");
  g_assert_nonnull(demo);
  g_assert_cmpint(demo->lifecycle, ==, GALLERY_DEMO_DEPRECATED);

  demo = gallery_demo_registry_find_demo("gtk-message-dialog");
  g_assert_nonnull(demo);
  g_assert_cmpint(demo->lifecycle, ==, GALLERY_DEMO_DEPRECATED);
  g_assert_nonnull(demo->replacement_doc_url);
}

static void
__test_supported_demo_lifecycle(void)
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

          demo = &category->demos[demo_index];
          if (g_strcmp0(demo->id, "gtk-statusbar") == 0
              || g_strcmp0(demo->id, "gtk-info-bar") == 0
              || g_strcmp0(demo->id, "gtk-message-dialog") == 0)
            continue;

          g_assert_cmpint(demo->lifecycle, ==, GALLERY_DEMO_SUPPORTED);
        }
    }
}

static void
__test_category_deprecated_flags(void)
{
  const GalleryCategoryEntry *display;
  const GalleryCategoryEntry *buttons;

  display = gallery_demo_registry_get_category(0);
  buttons = gallery_demo_registry_get_category(1);

  g_assert_true(gallery_demo_registry_category_has_deprecated(display));
  g_assert_false(gallery_demo_registry_category_has_deprecated(buttons));
}

static void
__test_display_demo_order(void)
{
  static const char *const expected_ids[] =
  {
    "gtk-label",
    "gtk-spinner",
    "gtk-statusbar",
    "gtk-level-bar",
    "gtk-progress-bar",
    "gtk-info-bar",
    "gtk-scrollbar",
    "gtk-image",
    "gtk-picture",
    "gtk-separator",
    "gtk-text-view",
    "gtk-scale",
  };

  __test_category_demo_order(0, expected_ids, G_N_ELEMENTS(expected_ids));
}

static void
__test_entries_demo_order(void)
{
  static const char *const expected_ids[] =
  {
    "gtk-entry",
    "gtk-search-entry",
    "gtk-password-entry",
    "gtk-spin-button",
    "gtk-editable-label",
  };

  __test_category_demo_order(2, expected_ids, G_N_ELEMENTS(expected_ids));
}

static void
__test_demo_metadata(void)
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

          demo = &category->demos[demo_index];
          g_assert_nonnull(demo->id);
          g_assert_nonnull(demo->title);
          g_assert_nonnull(demo->description);
          g_assert_nonnull(demo->doc_url);
          g_assert(g_str_has_prefix(demo->doc_url,
                                    "https://docs.gtk.org/gtk4/"));
          g_assert_nonnull(demo->build_content);
        }
    }
}

int
main(int argc, char *argv[])
{
  int status;

  gtk_init();
  g_test_init(&argc, &argv, NULL);

  g_test_add_func("/gallery/demo-registry/category-count",
                  __test_category_count);
  g_test_add_func("/gallery/demo-registry/demo-counts", __test_demo_counts);
  g_test_add_func("/gallery/demo-registry/category-titles",
                  __test_category_titles);
  g_test_add_func("/gallery/demo-registry/default-demo", __test_default_demo);
  g_test_add_func("/gallery/demo-registry/find-demo-missing",
                  __test_find_demo_missing);
  g_test_add_func("/gallery/demo-registry/deprecated-demo-lifecycle",
                  __test_deprecated_demo_lifecycle);
  g_test_add_func("/gallery/demo-registry/supported-demo-lifecycle",
                  __test_supported_demo_lifecycle);
  g_test_add_func("/gallery/demo-registry/category-deprecated-flags",
                  __test_category_deprecated_flags);
  g_test_add_func("/gallery/demo-registry/display-demo-order",
                  __test_display_demo_order);
  g_test_add_func("/gallery/demo-registry/entries-demo-order",
                  __test_entries_demo_order);
  g_test_add_func("/gallery/demo-registry/demo-metadata",
                  __test_demo_metadata);

  status = g_test_run();

  return status;
}

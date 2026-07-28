/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include <gtk/gtk.h>

#include "gallery/demo-registry.h"

static void
__test_category_count(void)
{
  g_assert_cmpuint(gallery_demo_registry_get_category_count(), ==, 5);
}

static void
__test_demo_counts(void)
{
  g_assert_cmpuint(gallery_demo_registry_get_category(0)->demo_count, ==, 4);
  g_assert_cmpuint(gallery_demo_registry_get_category(1)->demo_count, ==, 4);
  g_assert_cmpuint(gallery_demo_registry_get_category(2)->demo_count, ==, 2);
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

  status = g_test_run();

  return status;
}

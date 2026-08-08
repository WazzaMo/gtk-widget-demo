/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/demo-page.h"
#include "gallery/demo-registry.h"

static GtkWidget *
__find_label_by_text(GtkWidget *root, const char *text)
{
  GtkWidget *child;

  if (root == NULL || text == NULL)
    return NULL;

  if (GTK_IS_LABEL(root))
    {
      const char *label_text;

      label_text = gtk_label_get_text(GTK_LABEL(root));
      if (label_text != NULL && g_strcmp0(label_text, text) == 0)
        return root;
    }

  for (child = gtk_widget_get_first_child(root);
       child != NULL;
       child = gtk_widget_get_next_sibling(child))
    {
      GtkWidget *match;

      match = __find_label_by_text(child, text);
      if (match != NULL)
        return match;
    }

  return NULL;
}

static GtkWidget *
__find_button_by_label(GtkWidget *root, const char *label_text)
{
  GtkWidget *child;

  if (root == NULL || label_text == NULL)
    return NULL;

  if (GTK_IS_BUTTON(root))
    {
      const char *label;

      label = gtk_button_get_label(GTK_BUTTON(root));
      if (label != NULL && g_strcmp0(label, label_text) == 0)
        return root;
    }

  for (child = gtk_widget_get_first_child(root);
       child != NULL;
       child = gtk_widget_get_next_sibling(child))
    {
      GtkWidget *match;

      match = __find_button_by_label(child, label_text);
      if (match != NULL)
        return match;
    }

  return NULL;
}

static GtkWidget *
__find_frame_by_label(GtkWidget *root, const char *label_text)
{
  GtkWidget *child;

  if (root == NULL || label_text == NULL)
    return NULL;

  if (GTK_IS_FRAME(root))
    {
      const char *frame_label;

      frame_label = gtk_frame_get_label(GTK_FRAME(root));
      if (frame_label != NULL && g_strcmp0(frame_label, label_text) == 0)
        return root;
    }

  for (child = gtk_widget_get_first_child(root);
       child != NULL;
       child = gtk_widget_get_next_sibling(child))
    {
      GtkWidget *match;

      match = __find_frame_by_label(child, label_text);
      if (match != NULL)
        return match;
    }

  return NULL;
}

static void
__test_supported_demo_page(void)
{
  const GalleryDemoEntry *demo;
  GtkWidget *page;

  demo = gallery_demo_registry_find_demo("gtk-label");
  g_assert_nonnull(demo);

  page = gallery_demo_page_new(demo, gtk_label_new("Demo content"), NULL);
  g_assert_nonnull(page);
  g_assert_null(__find_label_by_text(page,
                                     "Deprecated in GTK 4 — avoid for new designs."));
  g_assert_nonnull(__find_button_by_label(page, "Open GTK documentation"));
  g_assert_null(__find_button_by_label(page, "See replacement API"));
}

static void
__test_deprecated_demo_banner(void)
{
  const GalleryDemoEntry *demo;
  GtkWidget *page;
  GtkWidget *banner;

  demo = gallery_demo_registry_find_demo("gtk-statusbar");
  g_assert_nonnull(demo);
  g_assert_cmpint(demo->lifecycle, ==, GALLERY_DEMO_DEPRECATED);

  page = gallery_demo_page_new(demo, gtk_label_new("Legacy content"), NULL);
  g_assert_nonnull(page);

  banner = __find_label_by_text(page,
                                "Deprecated in GTK 4 — avoid for new designs.");
  g_assert_nonnull(banner);
  g_assert_true(gtk_widget_has_css_class(banner, "warning"));
}

static void
__test_deprecated_demo_replacement_link(void)
{
  const GalleryDemoEntry *demo;
  GtkWidget *page;

  demo = gallery_demo_registry_find_demo("gtk-message-dialog");
  g_assert_nonnull(demo);
  g_assert_nonnull(demo->replacement_doc_url);

  page = gallery_demo_page_new(demo, gtk_label_new("Legacy content"), NULL);
  g_assert_nonnull(page);
  g_assert_nonnull(__find_button_by_label(page, "See replacement API"));
}

static void
__test_comparison_section(void)
{
  static const GalleryDemoEntry mock_demo =
  {
    "mock-deprecated",
    "MockDeprecated",
    "Mock description.",
    "https://docs.gtk.org/gtk4/class.Widget.html",
    NULL,
    GALLERY_DEMO_DEPRECATED,
    "https://docs.gtk.org/gtk4/class.AlertDialog.html",
    NULL,
    NULL,
    "GtkModern equivalent",
    "https://docs.gtk.org/gtk4/class.Modern.html",
  };
  GtkWidget *page;

  page = gallery_demo_page_new(&mock_demo,
                               gtk_label_new("Legacy content"),
                               gtk_label_new("Modern content"));
  g_assert_nonnull(page);
  g_assert_nonnull(__find_frame_by_label(page, "GtkModern equivalent"));
  g_assert_nonnull(__find_button_by_label(page, "Open replacement documentation"));
}

int
main(int argc, char *argv[])
{
  int status;

  gtk_init();
  g_test_init(&argc, &argv, NULL);

  g_test_add_func("/gallery/demo-page/supported-demo-page",
                  __test_supported_demo_page);
  g_test_add_func("/gallery/demo-page/deprecated-demo-banner",
                  __test_deprecated_demo_banner);
  g_test_add_func("/gallery/demo-page/deprecated-demo-replacement-link",
                  __test_deprecated_demo_replacement_link);
  g_test_add_func("/gallery/demo-page/comparison-section",
                  __test_comparison_section);

  status = g_test_run();

  return status;
}

/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/demo-registry.h"
#include "gallery/gallery-shell.h"

static GtkWidget *
__shell_get_list_box(GtkWidget *shell)
{
  GtkWidget *sidebar_frame;
  GtkWidget *scrolled;
  GtkWidget *child;

  sidebar_frame = gtk_paned_get_start_child(GTK_PANED(shell));
  scrolled = gtk_frame_get_child(GTK_FRAME(sidebar_frame));
  child = gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(scrolled));

  if (GTK_IS_VIEWPORT(child))
    return gtk_viewport_get_child(GTK_VIEWPORT(child));

  return child;
}

static GtkWidget *
__shell_get_demo_stack(GtkWidget *shell)
{
  return gtk_paned_get_end_child(GTK_PANED(shell));
}

static void
__count_sidebar_rows(GtkListBox *list_box,
                     gsize *header_count,
                     gsize *deprecated_subheader_count,
                     gsize *demo_count)
{
  int row_index;

  *header_count = 0;
  *deprecated_subheader_count = 0;
  *demo_count = 0;

  for (row_index = 0; ; row_index++)
    {
      GtkListBoxRow *row;

      row = gtk_list_box_get_row_at_index(list_box, row_index);
      if (row == NULL)
        break;

      if (g_object_get_data(G_OBJECT(row), "demo-id") != NULL)
        {
          (*demo_count)++;
          continue;
        }

      if (g_object_get_data(G_OBJECT(row), "row-kind") != NULL)
        (*deprecated_subheader_count)++;
      else
        (*header_count)++;
    }
}

static gsize
__total_demo_count(void)
{
  gsize category_index;
  gsize total;

  total = 0;

  for (category_index = 0;
       category_index < gallery_demo_registry_get_category_count();
       category_index++)
    total += gallery_demo_registry_get_category(category_index)->demo_count;

  return total;
}

static gsize
__total_deprecated_subheader_count(void)
{
  gsize category_index;
  gsize total;

  total = 0;

  for (category_index = 0;
       category_index < gallery_demo_registry_get_category_count();
       category_index++)
    {
      const GalleryCategoryEntry *category;

      category = gallery_demo_registry_get_category(category_index);
      if (gallery_demo_registry_category_has_deprecated(category))
        total++;
    }

  return total;
}

static GtkListBoxRow *
__find_demo_row(GtkListBox *list_box, const char *demo_id)
{
  int row_index;

  for (row_index = 0; ; row_index++)
    {
      GtkListBoxRow *row;
      const char *row_demo_id;

      row = gtk_list_box_get_row_at_index(list_box, row_index);
      if (row == NULL)
        return NULL;

      row_demo_id = g_object_get_data(G_OBJECT(row), "demo-id");
      if (row_demo_id != NULL && g_strcmp0(row_demo_id, demo_id) == 0)
        return row;
    }
}

static void
__test_shell_builds(void)
{
  GtkWidget *shell;

  shell = gallery_gallery_shell_new(NULL);
  g_assert_nonnull(shell);
  g_object_ref_sink(shell);
  g_object_unref(shell);
}

static void
__test_shell_sidebar_structure(void)
{
  GtkWidget *shell;
  GtkWidget *list_box;
  gsize header_count;
  gsize deprecated_subheader_count;
  gsize demo_count;

  shell = gallery_gallery_shell_new(NULL);
  list_box = __shell_get_list_box(shell);

  __count_sidebar_rows(GTK_LIST_BOX(list_box),
                       &header_count,
                       &deprecated_subheader_count,
                       &demo_count);
  g_assert_cmpuint(header_count, ==, gallery_demo_registry_get_category_count());
  g_assert_cmpuint(deprecated_subheader_count,
                   ==, __total_deprecated_subheader_count());
  g_assert_cmpuint(demo_count, ==, __total_demo_count());

  g_object_ref_sink(shell);
  g_object_unref(shell);
}

static void
__test_shell_default_selection(void)
{
  GtkWidget *shell;
  GtkWidget *stack;
  const char *visible_name;

  shell = gallery_gallery_shell_new(NULL);
  stack = __shell_get_demo_stack(shell);

  visible_name = gtk_stack_get_visible_child_name(GTK_STACK(stack));
  g_assert_cmpstr(visible_name, ==, gallery_demo_registry_get_default_demo_id());
  g_assert_cmpstr(visible_name, ==, "gtk-label");

  g_object_ref_sink(shell);
  g_object_unref(shell);
}

static void
__test_shell_demo_switch(void)
{
  GtkWidget *shell;
  GtkWidget *list_box;
  GtkWidget *stack;
  GtkListBoxRow *row;

  shell = gallery_gallery_shell_new(NULL);
  list_box = __shell_get_list_box(shell);
  stack = __shell_get_demo_stack(shell);

  row = __find_demo_row(GTK_LIST_BOX(list_box), "gtk-scale");
  g_assert_nonnull(row);

  gtk_list_box_select_row(GTK_LIST_BOX(list_box), row);
  g_assert_cmpstr(gtk_stack_get_visible_child_name(GTK_STACK(stack)),
                  ==, "gtk-scale");

  g_object_ref_sink(shell);
  g_object_unref(shell);
}

static void
__test_shell_deprecated_subheader_count(void)
{
  g_assert_cmpuint(__total_deprecated_subheader_count(), ==, 2);
}

int
main(int argc, char *argv[])
{
  int status;

  gtk_init();
  g_test_init(&argc, &argv, NULL);

  g_test_add_func("/gallery/gallery-shell/builds", __test_shell_builds);
  g_test_add_func("/gallery/gallery-shell/sidebar-structure",
                  __test_shell_sidebar_structure);
  g_test_add_func("/gallery/gallery-shell/default-selection",
                  __test_shell_default_selection);
  g_test_add_func("/gallery/gallery-shell/demo-switch",
                  __test_shell_demo_switch);
  g_test_add_func("/gallery/gallery-shell/deprecated-subheader-count",
                  __test_shell_deprecated_subheader_count);

  status = g_test_run();

  return status;
}

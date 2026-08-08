/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/demo-page.h"
#include "gallery/demo-registry.h"
#include "gallery/gallery-shell.h"

static GtkWidget *
__build_header_row(const char *title, int margin_start, int margin_top)
{
  GtkWidget *row;
  GtkWidget *label;

  row = gtk_list_box_row_new();
  gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);
  gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);

  label = gtk_label_new(title);
  gtk_label_set_xalign(GTK_LABEL(label), 0.0f);
  gtk_widget_add_css_class(label, "heading");
  gtk_widget_set_margin_start(label, margin_start);
  gtk_widget_set_margin_end(label, 4);
  gtk_widget_set_margin_top(label, margin_top);
  gtk_widget_set_margin_bottom(label, 4);
  gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(row), label);

  return row;
}

static GtkWidget *
__build_category_header(const char *title)
{
  return __build_header_row(title, 4, 12);
}

static GtkWidget *
__build_deprecated_subheader(void)
{
  GtkWidget *row;

  row = __build_header_row("Deprecated", 12, 8);
  g_object_set_data(G_OBJECT(row), "row-kind", "deprecated-subsection");

  return row;
}

static GtkWidget *
__build_demo_row(const GalleryDemoEntry *demo)
{
  GtkWidget *row;
  GtkWidget *label;

  row = gtk_list_box_row_new();
  g_object_set_data(G_OBJECT(row), "demo-id", (gpointer) demo->id);

  label = gtk_label_new(demo->title);
  gtk_label_set_xalign(GTK_LABEL(label), 0.0f);
  gtk_widget_set_margin_start(label, 12);
  gtk_widget_set_margin_end(label, 4);
  gtk_widget_set_margin_top(label, 4);
  gtk_widget_set_margin_bottom(label, 4);
  gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(row), label);

  return row;
}

static void
__append_demo(GtkWindow *parent_window,
              GtkListBox *sidebar,
              GtkStack *demo_stack,
              const GalleryDemoEntry *demo)
{
  GtkWidget *legacy_content;
  GtkWidget *comparison_content;
  GtkWidget *page;

  legacy_content = demo->build_content(parent_window);
  comparison_content = NULL;
  if (demo->build_comparison != NULL)
    comparison_content = demo->build_comparison(parent_window);

  page = gallery_demo_page_new(demo, legacy_content, comparison_content);
  gtk_stack_add_named(demo_stack, page, demo->id);
  gtk_list_box_append(sidebar, __build_demo_row(demo));
}

static void
__append_category_demos(GtkWindow *parent_window,
                        GtkListBox *sidebar,
                        GtkStack *demo_stack,
                        const GalleryCategoryEntry *category)
{
  gsize demo_index;
  gboolean has_deprecated;

  has_deprecated = gallery_demo_registry_category_has_deprecated(category);

  for (demo_index = 0; demo_index < category->demo_count; demo_index++)
    {
      const GalleryDemoEntry *demo;

      demo = &category->demos[demo_index];
      if (demo->lifecycle == GALLERY_DEMO_DEPRECATED)
        continue;

      __append_demo(parent_window, sidebar, demo_stack, demo);
    }

  if (!has_deprecated)
    return;

  gtk_list_box_append(sidebar, __build_deprecated_subheader());

  for (demo_index = 0; demo_index < category->demo_count; demo_index++)
    {
      const GalleryDemoEntry *demo;

      demo = &category->demos[demo_index];
      if (demo->lifecycle != GALLERY_DEMO_DEPRECATED)
        continue;

      __append_demo(parent_window, sidebar, demo_stack, demo);
    }
}

static void
__select_demo_row(GtkListBox *list_box, const char *demo_id)
{
  int row_index;
  GtkListBoxRow *row;

  for (row_index = 0;
       (row = gtk_list_box_get_row_at_index(list_box, row_index)) != NULL;
       row_index++)
    {
      const char *row_demo_id;

      row_demo_id = g_object_get_data(G_OBJECT(row), "demo-id");

      if (row_demo_id != NULL && g_strcmp0(row_demo_id, demo_id) == 0)
        {
          gtk_list_box_select_row(list_box, row);
          return;
        }
    }
}

static void
__on_demo_row_selected(GtkListBox *list_box, GtkListBoxRow *row, gpointer user_data)
{
  GtkStack *demo_stack = user_data;
  const char *demo_id;

  (void) list_box;

  if (row == NULL)
    return;

  demo_id = g_object_get_data(G_OBJECT(row), "demo-id");
  if (demo_id == NULL)
    return;

  gtk_stack_set_visible_child_name(demo_stack, demo_id);
}

GtkWidget *
gallery_gallery_shell_new(GtkWindow *parent_window)
{
  GtkWidget *shell;
  GtkWidget *sidebar;
  GtkWidget *sidebar_frame;
  GtkWidget *demo_stack;
  GtkWidget *scrolled;
  gsize category_index;

  shell = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_widget_set_vexpand(shell, TRUE);
  gtk_widget_set_hexpand(shell, TRUE);

  sidebar_frame = gtk_frame_new("Widget gallery");
  gtk_widget_set_size_request(sidebar_frame, 220, -1);

  scrolled = gtk_scrolled_window_new();
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                               GTK_POLICY_NEVER,
                               GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scrolled), 200);

  sidebar = gtk_list_box_new();
  gtk_list_box_set_selection_mode(GTK_LIST_BOX(sidebar), GTK_SELECTION_SINGLE);
  gtk_widget_set_vexpand(sidebar, TRUE);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), sidebar);
  gtk_frame_set_child(GTK_FRAME(sidebar_frame), scrolled);

  demo_stack = gtk_stack_new();
  gtk_stack_set_transition_type(GTK_STACK(demo_stack),
                              GTK_STACK_TRANSITION_TYPE_CROSSFADE);
  gtk_stack_set_transition_duration(GTK_STACK(demo_stack), 150);
  gtk_widget_set_vexpand(demo_stack, TRUE);
  gtk_widget_set_hexpand(demo_stack, TRUE);

  for (category_index = 0;
       category_index < gallery_demo_registry_get_category_count();
       category_index++)
    {
      const GalleryCategoryEntry *category;

      category = gallery_demo_registry_get_category(category_index);
      gtk_list_box_append(GTK_LIST_BOX(sidebar),
                          __build_category_header(category->title));
      __append_category_demos(parent_window,
                              GTK_LIST_BOX(sidebar),
                              GTK_STACK(demo_stack),
                              category);
    }

  g_signal_connect(sidebar, "row-selected",
                   G_CALLBACK(__on_demo_row_selected), demo_stack);

  gtk_paned_set_start_child(GTK_PANED(shell), sidebar_frame);
  gtk_paned_set_end_child(GTK_PANED(shell), demo_stack);
  gtk_paned_set_resize_start_child(GTK_PANED(shell), FALSE);
  gtk_paned_set_resize_end_child(GTK_PANED(shell), TRUE);
  gtk_paned_set_shrink_start_child(GTK_PANED(shell), TRUE);
  gtk_paned_set_shrink_end_child(GTK_PANED(shell), FALSE);

  __select_demo_row(GTK_LIST_BOX(sidebar),
                    gallery_demo_registry_get_default_demo_id());

  return shell;
}

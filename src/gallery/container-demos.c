/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/container-demos.h"

static GtkWidget *
__build_gtk_box(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *first;
  GtkWidget *second;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
  first = gtk_label_new("First");
  second = gtk_label_new("Second");
  gtk_box_append(GTK_BOX(box), first);
  gtk_box_append(GTK_BOX(box), second);
  return box;
}

static GtkWidget *
__build_gtk_grid(GtkWindow *parent_window)
{
  GtkWidget *grid;
  GtkWidget *label;

  (void) parent_window;

  grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 6);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 6);

  label = gtk_label_new("Row 0, Col 0");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

  label = gtk_label_new("Row 0, Col 1");
  gtk_grid_attach(GTK_GRID(grid), label, 1, 0, 1, 1);

  label = gtk_label_new("Row 1, Col 0");
  gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);

  label = gtk_label_new("Row 1, Col 1");
  gtk_grid_attach(GTK_GRID(grid), label, 1, 1, 1, 1);

  return grid;
}

static GtkWidget *
__build_gtk_frame(GtkWindow *parent_window)
{
  GtkWidget *frame;
  GtkWidget *child;

  (void) parent_window;

  frame = gtk_frame_new("Framed content");
  child = gtk_label_new("Widget packed inside a GtkFrame.");
  gtk_frame_set_child(GTK_FRAME(frame), child);
  return frame;
}

static GtkWidget *
__build_gtk_notebook(GtkWindow *parent_window)
{
  GtkWidget *notebook;
  GtkWidget *page_one;
  GtkWidget *page_two;

  (void) parent_window;

  notebook = gtk_notebook_new();
  page_one = gtk_label_new("Notebook page one");
  page_two = gtk_label_new("Notebook page two");
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_one,
                           gtk_label_new("One"));
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_two,
                           gtk_label_new("Two"));
  return notebook;
}

static const GalleryDemoEntry container_demos[] =
{
  {
    "gtk-box",
    "GtkBox",
    "Horizontal box packing two labels in a row.",
    "https://docs.gtk.org/gtk4/class.Box.html",
    __build_gtk_box,
  },
  {
    "gtk-grid",
    "GtkGrid",
    "Table-like layout with widgets at row and column positions.",
    "https://docs.gtk.org/gtk4/class.Grid.html",
    __build_gtk_grid,
  },
  {
    "gtk-frame",
    "GtkFrame",
    "Bordered container with an optional label.",
    "https://docs.gtk.org/gtk4/class.Frame.html",
    __build_gtk_frame,
  },
  {
    "gtk-notebook",
    "GtkNotebook",
    "Tabbed container with multiple pages.",
    "https://docs.gtk.org/gtk4/class.Notebook.html",
    __build_gtk_notebook,
  },
};

const GalleryDemoEntry *
gallery_container_demos_get(gsize *demo_count)
{
  if (demo_count != NULL)
    *demo_count = G_N_ELEMENTS(container_demos);

  return container_demos;
}

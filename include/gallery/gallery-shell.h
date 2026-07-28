/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef GALLERY_GALLERY_SHELL_H
#define GALLERY_GALLERY_SHELL_H

#include <gtk/gtk.h>

/**
 * Build the widget gallery navigation shell and demo stack.
 * @param parent_window the main window used to parent modal dialogs
 * @return a new gallery shell widget
 */
GtkWidget *gallery_gallery_shell_new(GtkWindow *parent_window);

#endif

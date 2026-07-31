/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef MAIN_WINDOW_SHELL_H
#define MAIN_WINDOW_SHELL_H

#include <gtk-4.0/gtk/gtk.h>

/**
 * Register application-level actions for the main window shell.
 * @param app the GTK application
 * @return none
 */
void main_window_shell_startup(GtkApplication *app);

/**
 * Create and present the main application window.
 * @param app the GTK application
 * @return none
 */
void main_window_shell_activate(GtkApplication *app);

#endif

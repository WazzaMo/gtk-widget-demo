/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef MAIN_ABOUT_DIALOG_H
#define MAIN_ABOUT_DIALOG_H

#include <gtk-4.0/gtk/gtk.h>

/**
 * Register the application-level About action on @app.
 * @param app the GTK application
 * @return none
 */
void main_about_dialog_register_action(GtkApplication *app);

#endif

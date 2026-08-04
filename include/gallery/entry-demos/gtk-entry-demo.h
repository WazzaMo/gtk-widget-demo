/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef GALLERY_ENTRY_DEMOS_GTK_ENTRY_DEMO_H
#define GALLERY_ENTRY_DEMOS_GTK_ENTRY_DEMO_H

#include "gtk-version.h"

/**
 * Build the GtkEntry gallery demo.
 * @param parent_window parent window for modal demos, unused here
 * @return the demo content widget
 */
GtkWidget *gallery_entry_gtk_entry_demo_build(GtkWindow *parent_window);

#endif

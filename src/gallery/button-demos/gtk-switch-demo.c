/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/button-demos/gtk-switch-demo.h"

/*
 * Returns the demo widget only. Page chrome (title, frame, full-width wrapper)
 * and default sizing (hexpand FALSE, halign CENTER when still FILL) are applied
 * in gallery_demo_page_new() — see demo-page.c. Set halign here to override
 * centre/start/end placement within that wrapper; see docs/notes/2026-07-30-plan-
 * widget-align-natural-size.md.
 */
GtkWidget *
gallery_button_gtk_switch_demo_build(GtkWindow *parent_window)
{
  GtkWidget *switch_widget;

  (void) parent_window;

  switch_widget = gtk_switch_new();
  gtk_switch_set_active(GTK_SWITCH(switch_widget), TRUE);
  gtk_widget_set_halign(switch_widget, GTK_ALIGN_CENTER);
  gtk_widget_set_hexpand(switch_widget, FALSE);
  return switch_widget;
}

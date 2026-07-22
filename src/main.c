/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include <gtk/gtk.h>

#include "main/window-shell.h"

int
main(int argc, char *argv[])
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("com.example.gtk-widget-demo",
                            G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "startup", G_CALLBACK(main_window_shell_startup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(main_window_shell_activate), NULL);

  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

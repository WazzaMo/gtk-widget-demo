/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "main/window-shell.h"

static int
__on_command_line(GApplication *app, GApplicationCommandLine *command_line)
{
  (void) command_line;

  g_application_activate(app);
  return 0;
}

int
main(int argc, char *argv[])
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("com.example.gtk-widget-demo",
                            G_APPLICATION_HANDLES_COMMAND_LINE);
  g_signal_connect(app, "command-line", G_CALLBACK(__on_command_line), NULL);
  g_signal_connect(app, "startup", G_CALLBACK(main_window_shell_startup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(main_window_shell_activate), NULL);

  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

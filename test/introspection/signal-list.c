/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include <gtk/gtk.h>

#include "introspection/signal-list.h"

static void
test_gtk_button_signals(void)
{
  gchar *formatted;

  formatted = introspection_format_signals(GTK_TYPE_BUTTON);
  g_assert_nonnull(formatted);
  g_assert(strstr(formatted, "clicked") != NULL);
  g_free(formatted);
}

int
main(int argc, char *argv[])
{
  int status;

  gtk_init();
  g_test_init(&argc, &argv, NULL);

  g_test_add_func("/introspection/signal-list/gtk-button",
                  test_gtk_button_signals);

  status = g_test_run();

  return status;
}

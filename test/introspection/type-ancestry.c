/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include <gtk/gtk.h>

#include "introspection/type-ancestry.h"

static void
test_gobject_ancestry(void)
{
  gchar *chain;

  chain = introspection_format_ancestry(G_TYPE_OBJECT);
  g_assert_nonnull(chain);
  g_assert(strstr(chain, "GObject") != NULL);
  g_free(chain);
}

static void
test_gtk_label_ancestry(void)
{
  gchar *chain;

  g_assert_true(introspection_type_is_ancestor(GTK_TYPE_LABEL, G_TYPE_OBJECT));
  g_assert_true(introspection_type_is_ancestor(GTK_TYPE_LABEL, GTK_TYPE_WIDGET));

  chain = introspection_format_ancestry(GTK_TYPE_LABEL);
  g_assert_nonnull(chain);
  g_assert(strstr(chain, "GtkLabel") != NULL);
  g_assert(strstr(chain, "GtkWidget") != NULL);
  g_assert(strstr(chain, "GObject") != NULL);
  g_free(chain);
}

int
main(int argc, char *argv[])
{
  int status;

  gtk_init();
  g_test_init(&argc, &argv, NULL);

  g_test_add_func("/introspection/type-ancestry/gobject", test_gobject_ancestry);
  g_test_add_func("/introspection/type-ancestry/gtk-label", test_gtk_label_ancestry);

  status = g_test_run();

  return status;
}

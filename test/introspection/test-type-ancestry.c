/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include <gtk/gtk.h>

#include "introspection/type-ancestry.h"
#include "introspection/property-list.h"

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

static void
test_gtk_label_properties(void)
{
  guint count;

  count = introspection_property_count(GTK_TYPE_LABEL);
  g_assert_cmpuint(count, >, 0);
}

static void
test_gtk_label_instance_properties(void)
{
  GtkWidget *label;
  gchar *formatted;

  label = gtk_label_new("Property test");
  g_object_ref_sink(label);
  formatted = introspection_format_properties(G_OBJECT(label));
  g_assert_nonnull(formatted);
  g_assert(strstr(formatted, "label") != NULL);
  g_free(formatted);
  g_object_unref(label);
}

int
main(int argc, char *argv[])
{
  int status;

  gtk_init();
  g_test_init(&argc, &argv, NULL);

  g_test_add_func("/introspection/ancestry/gobject", test_gobject_ancestry);
  g_test_add_func("/introspection/ancestry/gtk-label", test_gtk_label_ancestry);
  g_test_add_func("/introspection/properties/gtk-label-class",
                  test_gtk_label_properties);
  g_test_add_func("/introspection/properties/gtk-label-instance",
                  test_gtk_label_instance_properties);

  status = g_test_run();

  return status;
}

/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include <gtk/gtk.h>

#include "introspection/property-list.h"

static void
test_gtk_label_class_properties(void)
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

  g_test_add_func("/introspection/property-list/gtk-label-class",
                  test_gtk_label_class_properties);
  g_test_add_func("/introspection/property-list/gtk-label-instance",
                  test_gtk_label_instance_properties);

  status = g_test_run();

  return status;
}

/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "introspection/type-ancestry.h"

gchar *
introspection_type_name(GType type)
{
  if (type == G_TYPE_INVALID)
    return g_strdup("(invalid type)");

  return g_strdup(g_type_name(type));
}

gchar *
introspection_format_ancestry(GType type)
{
  GString *chain;
  GType current;

  if (type == G_TYPE_INVALID)
    return g_strdup("(invalid type)");

  chain = g_string_new(NULL);
  current = type;

  while (current != G_TYPE_INVALID)
    {
      if (chain->len > 0)
        g_string_append(chain, " → ");

      g_string_append(chain, g_type_name(current));

      if (current == G_TYPE_OBJECT)
        break;

      current = g_type_parent(current);
    }

  return g_string_free(chain, FALSE);
}

gchar *
introspection_format_interfaces(GType type)
{
  GString *list;
  guint n_interfaces;
  GType *interfaces;
  guint i;

  if (!G_TYPE_IS_CLASSED(type))
    return g_strdup("(none)");

  interfaces = g_type_interfaces(type, &n_interfaces);
  if (n_interfaces == 0)
    return g_strdup("(none)");

  list = g_string_new(NULL);

  for (i = 0; i < n_interfaces; i++)
    {
      if (i > 0)
        g_string_append(list, ", ");

      g_string_append(list, g_type_name(interfaces[i]));
    }

  g_free(interfaces);

  return g_string_free(list, FALSE);
}

gboolean
introspection_type_is_ancestor(GType type, GType ancestor)
{
  if (type == G_TYPE_INVALID || ancestor == G_TYPE_INVALID)
    return FALSE;

  return g_type_is_a(type, ancestor);
}

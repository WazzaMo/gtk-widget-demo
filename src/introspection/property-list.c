/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "introspection/property-list.h"

static gchar *
format_param_flags(GParamSpec *pspec)
{
  GString *flags;
  guint f;

  flags = g_string_new(NULL);
  f = pspec->flags;

  if (f & G_PARAM_READABLE)
    g_string_append(flags, "readable");

  if (f & G_PARAM_WRITABLE)
    {
      if (flags->len > 0)
        g_string_append(flags, ", ");

      g_string_append(flags, "writable");
    }

  if (f & G_PARAM_CONSTRUCT)
    {
      if (flags->len > 0)
        g_string_append(flags, ", ");

      g_string_append(flags, "construct");
    }

  if (f & G_PARAM_CONSTRUCT_ONLY)
    {
      if (flags->len > 0)
        g_string_append(flags, ", ");

      g_string_append(flags, "construct-only");
    }

  if (flags->len == 0)
    g_string_append(flags, "(none)");

  return g_string_free(flags, FALSE);
}

static gchar *
format_property_value(GObject *object, GParamSpec *pspec)
{
  GValue value = G_VALUE_INIT;
  gchar *contents;

  if (!(pspec->flags & G_PARAM_READABLE))
    return g_strdup("(not readable)");

  g_value_init(&value, G_PARAM_SPEC_VALUE_TYPE(pspec));
  g_object_get_property(object, pspec->name, &value);

  contents = g_strdup_value_contents(&value);
  g_value_unset(&value);

  if (contents == NULL)
    return g_strdup("(null)");

  return contents;
}

guint
introspection_property_count(GType type)
{
  GParamSpec **pspecs;
  guint n_properties;
  GObjectClass *klass;

  if (!G_TYPE_IS_CLASSED(type))
    return 0;

  klass = g_type_class_ref(type);
  pspecs = g_object_class_list_properties(klass, &n_properties);
  g_type_class_unref(klass);

  if (pspecs != NULL)
    g_free(pspecs);

  return n_properties;
}

gchar *
introspection_format_properties(GObject *object)
{
  GString *text;
  GParamSpec **pspecs;
  guint n_properties;
  guint i;
  GObjectClass *klass;

  if (object == NULL)
    return g_strdup("(no object selected)");

  klass = G_OBJECT_GET_CLASS(object);
  pspecs = g_object_class_list_properties(klass, &n_properties);

  if (n_properties == 0)
    {
      if (pspecs != NULL)
        g_free(pspecs);

      return g_strdup("(no properties)");
    }

  text = g_string_new(NULL);

  for (i = 0; i < n_properties; i++)
    {
      GParamSpec *pspec = pspecs[i];
      gchar *flags;
      gchar *value;
      const gchar *blurb;

      flags = format_param_flags(pspec);
      value = format_property_value(object, pspec);
      blurb = g_param_spec_get_blurb(pspec);

      g_string_append_printf(text,
                             "%s\n  type: %s\n  flags: %s\n",
                             pspec->name,
                             g_type_name(G_PARAM_SPEC_VALUE_TYPE(pspec)),
                             flags);

      if (blurb != NULL && blurb[0] != '\0')
        g_string_append_printf(text, "  blurb: %s\n", blurb);

      g_string_append_printf(text, "  value: %s\n\n", value);

      g_free(flags);
      g_free(value);
    }

  if (pspecs != NULL)
    g_free(pspecs);

  return g_string_free(text, FALSE);
}

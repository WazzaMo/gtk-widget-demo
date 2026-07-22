/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "introspection/signal-list.h"

gchar *
introspection_format_signals(GType type)
{
  GString *text;
  guint *signal_ids;
  guint n_signals;
  guint i;
  GTypeClass *klass;

  if (!G_TYPE_IS_CLASSED(type))
    return g_strdup("(no signals)");

  klass = g_type_class_ref(type);
  signal_ids = g_signal_list_ids(type, &n_signals);
  g_type_class_unref(klass);

  if (n_signals == 0)
    {
      if (signal_ids != NULL)
        g_free(signal_ids);

      return g_strdup("(no signals)");
    }

  text = g_string_new(NULL);

  for (i = 0; i < n_signals; i++)
    {
      GSignalQuery query;

      g_signal_query(signal_ids[i], &query);

      g_string_append_printf(text,
                             "%s (%u params)\n",
                             g_signal_name(signal_ids[i]),
                             query.n_params);
    }

  g_free(signal_ids);

  return g_string_free(text, FALSE);
}

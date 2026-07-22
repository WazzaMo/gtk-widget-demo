/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef INTROSPECTION_TYPE_ANCESTRY_H
#define INTROSPECTION_TYPE_ANCESTRY_H

#include <glib-object.h>

gchar *introspection_type_name(GType type);

gchar *introspection_format_ancestry(GType type);

gchar *introspection_format_interfaces(GType type);

gboolean introspection_type_is_ancestor(GType type, GType ancestor);

#endif

/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef INTROSPECTION_PROPERTY_LIST_H
#define INTROSPECTION_PROPERTY_LIST_H

#include <glib-object.h>

guint introspection_property_count(GType type);

gchar *introspection_format_properties(GObject *object);

#endif

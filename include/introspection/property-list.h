/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef INTROSPECTION_PROPERTY_LIST_H
#define INTROSPECTION_PROPERTY_LIST_H

#include <glib-object.h>

/**
 * Count the GObject properties registered on a classed type.
 * @param type the GType to inspect
 * @return the number of properties, or 0 for non-classed types
 */
guint introspection_property_count(GType type);

/**
 * Format readable property metadata and values for an object instance.
 * @param object the GObject to inspect
 * @return a newly allocated multi-line property report
 */
gchar *introspection_format_properties(GObject *object);

#endif

/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef INTROSPECTION_TYPE_ANCESTRY_H
#define INTROSPECTION_TYPE_ANCESTRY_H

#include <glib-object.h>

/**
 * Return the name of a GType as a newly allocated string.
 * @param type the GType to name
 * @return the type name, or a placeholder for invalid types
 */
gchar *introspection_type_name(GType type);

/**
 * Format the inheritance chain from a type up to GObject.
 * @param type the GType to describe
 * @return a newly allocated ancestry string
 */
gchar *introspection_format_ancestry(GType type);

/**
 * Format the interface list implemented by a classed type.
 * @param type the GType to describe
 * @return a newly allocated interface list, or "(none)"
 */
gchar *introspection_format_interfaces(GType type);

/**
 * Test whether one GType is an ancestor of another.
 * @param type the candidate type
 * @param ancestor the ancestor GType to test against
 * @return TRUE when @a type derives from @a ancestor
 */
gboolean introspection_type_is_ancestor(GType type, GType ancestor);

#endif

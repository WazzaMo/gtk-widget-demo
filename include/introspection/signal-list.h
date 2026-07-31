/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef INTROSPECTION_SIGNAL_LIST_H
#define INTROSPECTION_SIGNAL_LIST_H

#include <glib-object.h>

/**
 * Format the signal list registered on a classed type.
 * @param type the GType to inspect
 * @return a newly allocated multi-line signal report
 */
gchar *introspection_format_signals(GType type);

#endif

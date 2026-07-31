/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef GALLERY_WINDOW_DEMOS_H
#define GALLERY_WINDOW_DEMOS_H

#include "gallery/demo-registry.h"

/**
 * Return windows category demos for registry assembly.
 * @param demo_count receives the number of demos
 * @return the demo entry array
 */
const GalleryDemoEntry *gallery_window_demos_get(gsize *demo_count);

#endif

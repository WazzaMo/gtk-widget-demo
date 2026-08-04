/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef GALLERY_GALLERY_DATA_PATH_H
#define GALLERY_GALLERY_DATA_PATH_H

#ifndef GALLERY_DATA_DIR
#error "GALLERY_DATA_DIR must be defined by the build system"
#endif

#define GALLERY_DATA_PATH(filename) GALLERY_DATA_DIR "/" filename

#endif

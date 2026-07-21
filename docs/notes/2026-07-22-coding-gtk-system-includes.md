# GTK System Includes

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Context

Feature 1 sets `warning_level=3` in `meson.build`, which enables
`-Wpedantic` on project source. GTK and GLib headers use macros such as
`G_DECLARE_FINAL_TYPE` that expand to trailing semicolons outside functions,
triggering pedantic warnings such as:

```
ISO C does not allow extra ';' outside of a function [-Wpedantic]
```

These warnings originate in system headers, not in project code.

# Change

The GTK4 dependency is declared with Meson's `include_type: 'system'`:

```meson
gtk4_dep = dependency('gtk4', include_type: 'system')
```

Meson passes `-isystem` for GTK/GLib include paths instead of `-I`. GCC and
Clang suppress most warnings (including `-Wpedantic`) in system headers while
keeping strict warnings on files under `src/`.

# Alternatives considered

| Approach | Drawback |
|----------|----------|
| `-Wno-pedantic` globally | Silences pedantic warnings in project code too |
| Lower `warning_level` to 2 | Same — removes `-Wpedantic` project-wide |
| `#pragma GCC diagnostic` around `#include <gtk/gtk.h>` | Must repeat in every file that includes GTK |

`include_type: 'system'` is the usual Meson pattern for pkg-config
dependencies when building with strict warnings or `-Werror`.

# References

[feature-1-base-application.md](../features/feature-1-base-application.md)

[Meson dependency reference — include_type](https://mesonbuild.com/Reference-manual.html#dependency)

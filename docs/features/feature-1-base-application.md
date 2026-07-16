# Feature 1 Base Application

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Overview

This feature establishes the project foundation: a cross-platform Meson build
and a minimal GTK4 desktop application that future widget demos can extend.

It implements the build-system decision in
[2026-07-16-plan-gtk-build-systems.md](../notes/2026-07-16-plan-gtk-build-systems.md)
(Meson with Ninja backend) and the code layout in
[c-code-standard.md](../c-code-standard.md).

The application is not the full Widget Gallery yet. It is a runnable shell with
a window and a **File → Exit** menu so later features can add demo groups under
`src/` without reworking the build or entry point.

# Use cases

1. A developer clones the repository, installs GTK4 development packages, runs
   the documented build commands, and launches a desktop window.

2. A developer selects **File → Exit** (or the platform-equivalent accelerator)
   and the application closes cleanly.

3. A developer adding the first widget demo group can follow the existing
   `src/main.c` entry point and Meson layout without introducing a new build
   system or directory convention.

# Acceptance criteria

1. On a Linux system with GTK4 development libraries installed, `meson setup build`
   followed by `meson compile -C build` completes without errors.

2. Running the built executable opens a GTK4 application window that remains
   visible until the user closes it.

3. The window shows a menu bar with a **File** menu containing an **Exit** item
   that terminates the application.

4. [README.md](../../README.md) documents build prerequisites and the configure,
   compile, and run commands a new contributor needs.

5. Source and build files follow [c-code-standard.md](../c-code-standard.md):
   entry point at `src/main.c`, with room to add grouped modules under
   `src/<GROUP>/` and `include/` as later features land.

6. The repository root contains a `meson.build` that declares a GTK4 dependency
   via `dependency('gtk4')` and builds one executable target from `src/main.c`.

# Technical acceptance criteria

## Build system

Meson is the build system (see the
[build-system plan note](../notes/2026-07-16-plan-gtk-build-systems.md)).

| Requirement     | Detail                              |
|-----------------|-------------------------------------|
| Root build file | `meson.build` at repository root    |
| GTK dependency  | `dependency('gtk4')`                |
| Backend         | Ninja (Meson default)               |
| Executable      | One target built from `src/main.c`  |
| Project name    | from (Meson `project()` name)       |

Expected contributor workflow on Linux:

```bash
meson setup build
meson compile -C build
./build/gtk-widget-demo
```

## Application behaviour

| Requirement   | Detail |
|---------------|--------|
| Toolkit       | GTK4 (`GtkApplication` or equivalent) |
| Window        | At least one top-level window with a sensible default title |
| Menu          | **File → Exit** wired to quit the application |
| Entry point   | `src/main.c` only; no business logic buried in build files |

For Feature 1, application logic may live entirely in `src/main.c`. Separate
groups under `src/<GROUP>/` are expected in later features but are not required
here unless they improve clarity without expanding scope.

## Documentation

| Requirement | Detail |
|-------------|--------|
| README      | Prerequisites (compiler, Meson, Ninja, GTK4 dev packages) |
| README      | Configure, build, and run commands |
| Copyright   | New source files carry the project copyright notice |

# Out of scope

The following belong in later features, not Feature 1:

1. Widget Gallery demos or navigation between widget examples.

2. Unit or integration tests under `test/` (test layout is defined in
   [c-code-standard.md](../c-code-standard.md) but infrastructure comes later).

3. Cross-platform CI or Windows/macOS verification (manual Linux success is
   enough for this milestone).

4. Packaging, installation targets, or desktop integration beyond a bare
   executable.

5. CMake or GNU make build files (Meson only unless the build-system note is
   revised).

# References

[README.md](../../README.md)

[c-code-standard.md](../c-code-standard.md)

[2026-07-16-plan-gtk-build-systems.md](../notes/2026-07-16-plan-gtk-build-systems.md)

[GTK4 Documentation](https://docs.gtk.org/gtk4/index.html)

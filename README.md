# GTK Widget Demo Program

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Overview

For maximum portability and performance, this will be built in the C language.

This is intended to be an implementation of the GTK4 Widget Gallery, see references below,
for code examples and executions of different widgets to make UI design and app design
a bit easier, by example.

# Build

## Prerequisites

On Debian or Ubuntu:

```bash
sudo apt install build-essential meson ninja-build libgtk-4-dev
```

You also need a working C compiler, Meson, Ninja, and pkg-config (included in
the packages above).

## Configure, compile, and run

From the repository root:

```bash
meson setup build
meson compile -C build
./build/gtk-widget-demo
```

Re-run `meson compile -C build` after changing source files. Re-run
`meson setup build` when `meson.build` changes.

# Documents to note

- [Documentation standard](docs/doc-guide.md)

- [C coding standard](docs/c-code-standard.md)

- [Agent guidance](AGENTS.md)

# References

[GTK4 Documentation index page](https://docs.gtk.org/gtk4/index.html)

[GTK4 Frequently asked questions](https://docs.gtk.org/gtk4/question_index.html)

[GTK4 Widget Gallery](https://docs.gtk.org/gtk4/visual_index.html)

[General GTK Documentation](https://www.gtk.org/docs/)

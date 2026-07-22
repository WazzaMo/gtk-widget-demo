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
meson test -C build
./build/gtk-widget-demo
```

Re-run `meson compile -C build` after changing source files. Re-run
`meson setup build` when `meson.build` changes.

# GObject introspection

The application includes a read-only introspection pane for exploring GObject
types on widgets in the window.

## In-app inspect workflow

1. Run `./build/gtk-widget-demo`.

2. Choose **View → Inspect widget** to enable pick mode (the cursor becomes a
   crosshair over the main window).

3. Click a widget — for example a control in the sample palette, the menu bar,
   or a container — to show its GType name, ancestry, interfaces, properties,
   and signals in the side pane.

4. Toggle **View → Inspect widget** off, or press Escape, to interact with
   controls normally.

## GTK Inspector

For widget tree navigation, CSS, allocations, and layout debugging, use GTK
Inspector alongside the in-app pane:

- Run with `GTK_DEBUG=interactive ./build/gtk-widget-demo`, or

- Press Control+Shift+I or Control+Shift+D while the app is running.

See [GTK running and debugging](https://docs.gtk.org/gtk4/running.html) in the
upstream GTK documentation.

# Documents to note

- [Documentation standard](docs/doc-guide.md)

- [C coding standard](docs/c-code-standard.md)

- [Agent guidance](AGENTS.md)

# References

[GTK4 Documentation index page](https://docs.gtk.org/gtk4/index.html)

[GTK4 Frequently asked questions](https://docs.gtk.org/gtk4/question_index.html)

[GTK4 Widget Gallery](https://docs.gtk.org/gtk4/visual_index.html)

[General GTK Documentation](https://www.gtk.org/docs/)

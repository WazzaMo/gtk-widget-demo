# Feature 3 Widget Gallery

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Context

Feature 3 adds a navigable widget gallery aligned with the upstream
[GTK4 visual index](https://docs.gtk.org/gtk4/visual_index.html): gallery
framework, 14 initial demos, content-mode switching with the Feature 2 sample
palette, and smoke tests under `test/gallery/`.

The feature spec is
[feature-3-widget-gallery.md](../features/feature-3-widget-gallery.md).
Planning and closed open decisions are in the dated notes under `docs/notes/`
linked from that spec.

# Delivered

## Code layout

Second major code group under `src/` and `include/` per
[c-code-standard.md](../c-code-standard.md):

| Unit            | Path                            | Role |
| --------------- | ------------------------------- | --- |
| gallery-shell   | `src/gallery/gallery-shell.c`   | Sidebar navigation, `GtkStack` of demo pages |
| demo-registry   | `src/gallery/demo-registry.c`   | Five visual-index categories, demo lookup |
| demo-page       | `src/gallery/demo-page.c`       | Shared page chrome: title, description, doc link, content slot |
| display-demos   | `src/gallery/display-demos.c`   | `GtkLabel`, `GtkSpinner`, `GtkProgressBar`, `GtkScale` |
| button-demos    | `src/gallery/button-demos.c`    | `GtkButton`, `GtkCheckButton`, `GtkSwitch`, `GtkToggleButton` |
| entry-demos     | `src/gallery/entry-demos.c`     | `GtkEntry`, `GtkSpinButton` |
| container-demos | `src/gallery/container-demos.c` | `GtkBox`, `GtkGrid`, `GtkFrame`, `GtkNotebook` |
| window-demos    | `src/gallery/window-demos.c`    | `GtkAboutDialog`, `GtkMessageDialog` (modal launch) |

Umbrella header: `include/gallery.h`.

## Application

`src/main/window-shell.c` was extended with:

- **View → Widget gallery** and **View → Sample palette** as a radio group
  (`win.content-mode` stateful action; gallery default on startup)
- `GtkStack` in the main content area holding the gallery shell and sample palette
- static window title **GTK Widget Demo**

`gallery-shell.c` builds a flat `GtkListBox`: unselectable category header rows
(CSS class `heading`), selectable demo rows, and a `GtkStack` for active demo
pages. Demo selection updates the stack without restarting the application.

Window-category demos launch `GtkAboutDialog` and `GtkMessageDialog` modally
from buttons on the demo page, parented to the main window.

## Build and tests

`meson.build` links the gallery group into `gtk-widget-demo` and adds two test
executables under `test/gallery/`:

| Test                    | File                           | Coverage |
| ----------------------- | ------------------------------ | --- |
| `gallery-demo-registry` | `test/gallery/demo-registry.c` | Five categories; demo counts per category |
| `gallery-demo-builders` | `test/gallery/demo-builders.c` | Each demo builder returns a non-NULL root widget |

Verified with:

```bash
meson setup build
meson compile -C build
meson test -C build
./build/gtk-widget-demo
```

[README.md](../../README.md) documents gallery navigation, content-mode
switching, and the upstream visual index link.

## Delivery decisions

Closed during implementation (2026-07-29); see
[2026-07-26-todo-feature-3-open-decisions.md](./2026-07-26-todo-feature-3-open-decisions.md):

1. **Window title** — static **GTK Widget Demo**.

2. **Sidebar widget** — `GtkListBox` with category headers.

# Fixes after initial delivery

## Pick-mode Escape idle use-after-free

During gallery hardening, Escape in pick mode deferred exit through a GLib idle
callback with a raw `IntrospectionInspectorPane *`. Closing the main window
before the idle ran could dereference freed memory.

Fix in `src/introspection/inspector-pane/pick-mode.c`: track
`exit_pick_mode_idle_id` on the pane, guard against double scheduling, and
`g_source_remove()` on pane free. See
[2026-07-29-plan-pick-mode-escape-idle-uaf.md](./2026-07-29-plan-pick-mode-escape-idle-uaf.md).

## Widget alignment without horizontal scaling

Gallery and sample-palette review found `GtkSwitch` controls stretched
horizontally when placed in wide demo frames. Compact controls default to
`halign = GTK_ALIGN_FILL`, which scales them to fill extra space.

Fix in `src/gallery/demo-page.c`: wrap demo content in a full-width vertical
`GtkBox`, set `hexpand = FALSE` on content, and default `halign` to
`GTK_ALIGN_CENTER` when still `FILL`. The `GtkSwitch` demo and sample-palette
switch set explicit alignment. See
[2026-07-30-plan-widget-align-natural-size.md](./2026-07-30-plan-widget-align-natural-size.md).

# Addendum — Help About dialog

Added after initial Feature 3 delivery (2026-07-30):

| Item   | Detail |
| ------ | --- |
| Menu   | **Help → About** in `src/main/window-shell.c` |
| Unit   | `src/main/about-dialog.c`, `include/main/about-dialog.h` |
| Action | `app.about` registered at startup via `main_about_dialog_register_action()` |
| Dialog | Modal `GtkAboutDialog` — program name, version `0.1.0`, comments, author, copyright, project GitHub URL, Apache 2.0 license |
| Parent | Transient for the active window when present; destroyed on close-request |

# Follow-on work

Feature 3 ships the gallery **framework** plus 14 initial demos. Remaining
visual-index widgets are incremental follow-on catalog work using the same
registry and demo-page pattern — see
[2026-07-26-plan-feature-3-framework-first-catalog-later.md](./2026-07-26-plan-feature-3-framework-first-catalog-later.md).

# References

[feature-3-widget-gallery.md](../features/feature-3-widget-gallery.md)

[2026-07-26-todo-feature-3-open-decisions.md](./2026-07-26-todo-feature-3-open-decisions.md)

[2026-07-26-plan-feature-3-framework-first-catalog-later.md](./2026-07-26-plan-feature-3-framework-first-catalog-later.md)

[2026-07-29-plan-pick-mode-escape-idle-uaf.md](./2026-07-29-plan-pick-mode-escape-idle-uaf.md)

[2026-07-30-plan-widget-align-natural-size.md](./2026-07-30-plan-widget-align-natural-size.md)

[src/main/about-dialog.c](../../src/main/about-dialog.c)

[c-code-standard.md](../c-code-standard.md)

[README.md](../../README.md)

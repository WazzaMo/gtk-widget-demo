# Agent Guidance (AGENTS.md)

This document is the entry point for AI agents working on **GTK Widget Demo**.
It links to the authoritative convention docs rather than duplicating them.

## Project vision

A cross-platform **C / GTK4** application that implements the
[GTK4 Widget Gallery](https://docs.gtk.org/gtk4/visual_index.html): runnable
examples of GTK widgets to support UI and app design by example.

See [README.md](./README.md) for overview and upstream GTK references.

## Current state

Feature 1 (base application) is **complete**. Feature 2 (GObject introspection) is
**complete**. Feature 3 (widget gallery) is **draft** — spec and plan notes are
written; implementation has not started.

The repository has a runnable Meson/GTK4 app with an in-app introspection pane,
a sample widget palette, and unit tests. Next work is the `gallery` code group
per [feature-3-widget-gallery.md](./docs/features/feature-3-widget-gallery.md).

| Present | Not yet present |
|---------|-----------------|
| `docs/` conventions and feature specs (Features 1–3) | `gallery` group and widget gallery demos |
| Meson build and GTK4 executable | Full visual-index catalog |
| `src/main.c` entry point; `src/main/` shell units | `docs/stories/` (planned, unused) |
| `src/introspection/` introspection units | |
| `test/introspection/` unit tests | |

When adding code, follow the layout and decisions below before inventing new
structure.

## Authoritative docs

| Topic | Document |
|-------|----------|
| Markdown, notes, features, stories | [docs/doc-guide.md](./docs/doc-guide.md) |
| C layout, groups, units, tests | [docs/c-code-standard.md](./docs/c-code-standard.md) |
| First deliverable | [docs/features/feature-1-base-application.md](./docs/features/feature-1-base-application.md) |
| GObject introspection | [docs/features/feature-2-gobject-introspection.md](./docs/features/feature-2-gobject-introspection.md) |
| Widget gallery (draft) | [docs/features/feature-3-widget-gallery.md](./docs/features/feature-3-widget-gallery.md) |
| Feature 3 open decisions | [docs/notes/2026-07-26-todo-feature-3-open-decisions.md](./docs/notes/2026-07-26-todo-feature-3-open-decisions.md) |
| Build system choice | [docs/notes/2026-07-16-plan-gtk-build-systems.md](./docs/notes/2026-07-16-plan-gtk-build-systems.md) |

## Key decisions

- **Language:** C (portability and performance).
- **UI toolkit:** GTK4.
- **Build system:** Meson with Ninja backend
  (`dependency('gtk4', include_type: 'system')`). CMake is the fallback if CI
  requires native MSVC; GNU make is out of scope unless the project is
  explicitly Linux-only.
- **Entry point:** `src/main.c` (outside code groups).
- **Modules:** `src/<GROUP>/<UNIT>.c` with `include/<GROUP>.h` and
  `include/<GROUP>/<UNIT>.h`.
- **Tests:** `test/` mirroring group and unit names.
- **License:** Apache 2.0; include the project copyright block in new docs
  (see existing docs for the wording).

## Agent workflow

1. Read this file, then the doc or feature relevant to the task.
2. For new work, check `docs/features/` and `docs/notes/` before changing
   structure or conventions.
3. Record planning decisions as dated notes under `docs/notes/` using the
   naming rules in [doc-guide.md](./docs/doc-guide.md).
4. Prefer many small source files over few large ones
   ([c-code-standard.md](./docs/c-code-standard.md)).
5. Do not commit or push unless the user explicitly asks.

## Build

Prerequisites on Debian/Ubuntu:

```bash
sudo apt install build-essential meson ninja-build libgtk-4-dev
```

Expected workflow:

```bash
meson setup build
meson compile -C build
meson test -C build
./build/gtk-widget-demo
```

Re-run `meson compile -C build` after changing source files. Re-run
`meson setup build` when `meson.build` changes.

## Feature 1 (complete)

Acceptance criteria are in
[feature-1-base-application.md](./docs/features/feature-1-base-application.md).
Delivered as of 2026-07-22:

1. Root `meson.build` — project `gtk-widget-demo`, GTK4 dependency with
   system includes, executable from `src/main.c`.
2. `src/main.c` — GTK4 window with **File → Exit** menu.
3. Build prerequisites and commands documented in [README.md](./README.md).
4. Verified on Linux: `meson setup build`, `meson compile -C build`, run
   `./build/gtk-widget-demo`.

## Feature 2 (complete)

Acceptance criteria are in
[feature-2-gobject-introspection.md](./docs/features/feature-2-gobject-introspection.md).
Delivered as of 2026-07-23:

1. `introspection` group — type ancestry, property list, signal list, inspector pane.
2. **View → Inspect widget** pick mode with side introspection pane.
3. Sample palette in `src/main/sample-palette.c`; shell in `src/main/window-shell.c`.
4. Unit tests under `test/introspection/` via `meson test -C build`.

See [2026-07-23-coding-feature-2-gobject-introspection.md](./docs/notes/2026-07-23-coding-feature-2-gobject-introspection.md)
for delivery details and post-delivery refactors.

## Feature 3 (draft)

Acceptance criteria are in
[feature-3-widget-gallery.md](./docs/features/feature-3-widget-gallery.md).
Spec dated 2026-07-26; not yet implemented.

1. `gallery` group — navigation shell, demo registry, category demo units.
2. **View → Widget gallery** (default) and **View → Sample palette** content modes.
3. Initial set of 14 demos across five visual-index categories.
4. Tests under `test/gallery/`; README updated when shipped.

Open decisions (window title, sidebar widget, stories granularity) are in
[2026-07-26-todo-feature-3-open-decisions.md](./docs/notes/2026-07-26-todo-feature-3-open-decisions.md).
Resolve or defer before or during implementation.

## Documentation naming (summary)

Full rules are in [doc-guide.md](./docs/doc-guide.md).

- **Notes:** `docs/notes/{YYYY-MM-DD}-{kind}-{name}.md`
- **Features:** `docs/features/feature-{n}-{short-name}.md`
- **Stories:** `docs/stories/{epic|story}-{feature}-{component}-{description}.md`
- **Release notes:** `docs/release-notes/{semver}-Release-{date}.md`

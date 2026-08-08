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
**complete**. Feature 3 (widget gallery) is **complete** — gallery navigation,
content-mode switching, and tests under `test/gallery/`. Feature 4 (catalog wave 1)
is **complete** — **25** runnable demos with Display and Entries categories
extended per [feature-4-widget-gallery-catalog-wave-1.md](./docs/features/feature-4-widget-gallery-catalog-wave-1.md).

Deprecated-widget separation (Feature 5 part 1) is **complete** on `main`
(2026-08-08, PR #6). Catalog wave 2 (Feature 5 part 2) is **in progress** on
branch `wm/feature-5`. See
[feature-5-widget-gallery-catalog-wave-2.md](./docs/features/feature-5-widget-gallery-catalog-wave-2.md).

| Present                                               | Not yet present |
| ----------------------------------------------------- | --- |
| `docs/` conventions and feature specs (Features 1–5)  | Feature 5 part 2 (wave 2 demos) |
| Meson build and GTK4 executable                       | Full visual-index catalog (waves 3–9) |
| `src/main.c` entry point; `src/main/` shell units     | Phase 3 hide-deprecated toggle |
| `src/gallery/` gallery framework and **25** demos     | Migration comparison builders (phase 2 content) |
| Deprecated lifecycle metadata and sidebar subsections |  |
| `src/introspection/` introspection units              |  |
| `test/introspection/` and `test/gallery/` unit tests  |  |

When adding code, follow the layout and decisions below before inventing new
structure.

## Authoritative docs

| Topic                              | Document |
| ---------------------------------- | --- |
| Markdown, notes, features          | [docs/doc-guide.md](./docs/doc-guide.md) |
| C layout, groups, units, tests     | [docs/c-code-standard.md](./docs/c-code-standard.md) |
| First deliverable                  | [docs/features/feature-1-base-application.md](./docs/features/feature-1-base-application.md) |
| GObject introspection              | [docs/features/feature-2-gobject-introspection.md](./docs/features/feature-2-gobject-introspection.md) |
| Widget gallery                     | [docs/features/feature-3-widget-gallery.md](./docs/features/feature-3-widget-gallery.md) |
| Catalog wave 1                     | [docs/features/feature-4-widget-gallery-catalog-wave-1.md](./docs/features/feature-4-widget-gallery-catalog-wave-1.md) |
| Catalog wave 2 + deprecation infra | [docs/features/feature-5-widget-gallery-catalog-wave-2.md](./docs/features/feature-5-widget-gallery-catalog-wave-2.md) |
| Deprecated widget separation       | [docs/notes/2026-08-05-plan-gallery-deprecated-widget-separation.md](./docs/notes/2026-08-05-plan-gallery-deprecated-widget-separation.md) |
| Deprecation delivery order         | [docs/notes/2026-08-08-plan-deprecated-widget-delivery-order.md](./docs/notes/2026-08-08-plan-deprecated-widget-delivery-order.md) |
| Catalog nine waves                 | [docs/notes/2026-08-05-plan-widget-gallery-catalog-nine-waves.md](./docs/notes/2026-08-05-plan-widget-gallery-catalog-nine-waves.md) |
| Feature 3 delivery decisions       | [docs/notes/2026-07-26-todo-feature-3-open-decisions.md](./docs/notes/2026-07-26-todo-feature-3-open-decisions.md) |
| Build system choice                | [docs/notes/2026-07-16-plan-gtk-build-systems.md](./docs/notes/2026-07-16-plan-gtk-build-systems.md) |

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

## Feature 3 (complete)

Acceptance criteria are in
[feature-3-widget-gallery.md](./docs/features/feature-3-widget-gallery.md).
Delivered as of 2026-07-29:

1. `gallery` group — navigation shell, demo registry, demo page chrome, category demo units.
2. **View → Widget gallery** (default) and **View → Sample palette** content modes.
3. Initial set of 14 demos across five visual-index categories.
4. Tests under `test/gallery/` via `meson test -C build`; README updated.

Delivery decisions (closed 2026-07-29): static window title **GTK Widget Demo**;
`GtkListBox` sidebar with category headers — see
[2026-07-26-todo-feature-3-open-decisions.md](./docs/notes/2026-07-26-todo-feature-3-open-decisions.md).

See [2026-07-29-coding-feature-3-widget-gallery.md](./docs/notes/2026-07-29-coding-feature-3-widget-gallery.md)
for delivery details and post-delivery fixes.

Follow-on work extends the gallery catalog beyond the initial 14 demos.

## Feature 4 (complete)

Acceptance criteria are in
[feature-4-widget-gallery-catalog-wave-1.md](./docs/features/feature-4-widget-gallery-catalog-wave-1.md).
Delivered as of 2026-08-05:

1. Eleven new demos in Display widgets and Entries (**25** total).
2. Visual-index order preserved within each category.
3. Registry and demo-page pattern unchanged; gallery tests updated.

Catalog waves 2–9 are planned in
[2026-08-05-plan-widget-gallery-catalog-nine-waves.md](./docs/notes/2026-08-05-plan-widget-gallery-catalog-nine-waves.md).

## Feature 5 (in progress)

Acceptance criteria are in
[feature-5-widget-gallery-catalog-wave-2.md](./docs/features/feature-5-widget-gallery-catalog-wave-2.md).
Two-part delivery:

**Part 1 — Deprecated widget separation** (phase 1 + phase 2 infrastructure):
**complete** on `main` (2026-08-08, PR #6).

1. `GalleryDemoLifecycle` on `GalleryDemoEntry`; three deprecated demos classified.
2. Sidebar **Deprecated** subsections under Display and Windows.
3. Deprecation banner and **See replacement API** link on demo pages.
4. `build_comparison` hooks and **Modern alternative** page chrome (builders deferred).
5. Tests under `test/gallery/` including `demo-page`, `demo-registry`, and
   `gallery-shell`.

**Part 2 — Catalog wave 2:** in progress on `wm/feature-5` — three supported
Display demos (**GtkGLArea**, **GtkVideo**, **GtkPopoverMenu**); **28** total
demos when complete.

Phase 2 comparison content and phase 3 hide toggle remain follow-on work per
[2026-08-08-plan-deprecated-widget-delivery-order.md](./docs/notes/2026-08-08-plan-deprecated-widget-delivery-order.md).

## Documentation naming (summary)

Full rules are in [doc-guide.md](./docs/doc-guide.md).

- **Notes:** `docs/notes/{YYYY-MM-DD}-{kind}-{name}.md`
- **Features:** `docs/features/feature-{n}-{short-name}.md`
- **Release notes:** `docs/release-notes/{semver}-Release-{date}.md`

# Agent Guidance (AGENTS.md)

This document is the entry point for AI agents working on **GTK Widget Demo**.
It links to the authoritative convention docs rather than duplicating them.

## Project vision

A cross-platform **C / GTK4** application that implements the
[GTK4 Widget Gallery](https://docs.gtk.org/gtk4/visual_index.html): runnable
examples of GTK widgets to support UI and app design by example.

See [README.md](./README.md) for overview and upstream GTK references.

## Current state

The repository is in an early **planning and documentation** phase.

| Present | Not yet present |
|---------|-----------------|
| `docs/` conventions and feature specs | `src/`, `include/` |
| Build-system decision (Meson) | `meson.build` |
| Feature 1 spec | `test/` |

When adding code, follow the layout and decisions below before inventing new
structure.

## Authoritative docs

| Topic | Document |
|-------|----------|
| Markdown, notes, features, stories | [docs/doc-guide.md](./docs/doc-guide.md) |
| C layout, groups, units, tests | [docs/c-code-standard.md](./docs/c-code-standard.md) |
| First deliverable | [docs/features/feature-1-base-application.md](./docs/features/feature-1-base-application.md) |
| Build system choice | [docs/notes/2026-07-16-plan-gtk-build-systems.md](./docs/notes/2026-07-16-plan-gtk-build-systems.md) |

## Key decisions

- **Language:** C (portability and performance).
- **UI toolkit:** GTK4.
- **Build system:** Meson with Ninja backend (`dependency('gtk4')`).
  CMake is the fallback if CI requires native MSVC; GNU make is out of scope
  unless the project is explicitly Linux-only.
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

## Build (once source exists)

Prerequisites on Debian/Ubuntu:

```bash
sudo apt install build-essential meson ninja-build libgtk-4-dev
```

Expected workflow:

```bash
meson setup build
meson compile -C build
./build/gtk-widget-demo
```

Update this section when `meson.build` lands.

## Feature 1 checklist

Binding acceptance criteria are in
[feature-1-base-application.md](./docs/features/feature-1-base-application.md).
Summary:

1. Add root `meson.build` — project `gtk-widget-demo`, `dependency('gtk4')`,
   executable from `src/main.c`.
2. Add `src/main.c` — GTK4 window with **File → Exit** menu.
3. Document prerequisites and build/run commands in [README.md](./README.md).
4. Verify on Linux: `meson setup build`, `meson compile -C build`, run
   `./build/gtk-widget-demo`.

## Documentation naming (summary)

Full rules are in [doc-guide.md](./docs/doc-guide.md).

- **Notes:** `docs/notes/{YYYY-MM-DD}-{kind}-{name}.md`
- **Features:** `docs/features/feature-{n}-{short-name}.md`
- **Stories:** `docs/stories/{epic|story}-{feature}-{component}-{description}.md`
- **Release notes:** `docs/release-notes/{semver}-Release-{date}.md`

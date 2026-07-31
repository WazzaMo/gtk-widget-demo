# Feature 4 Widget Gallery Catalog Wave 1

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Status

**Draft** — not started.

Extends the Feature 3 gallery with the next visual-index demos in **Display
widgets** and **Entries**. Builds on the delivered framework, registry, demo page
pattern, and display-demos sub-unit split; does not rework gallery shell or
navigation.

# Overview

Feature 3 shipped a navigable gallery **framework** and **14** initial demos —
one runnable example per visual-index category plus teaching coverage of the
Feature 2 sample palette widgets. The upstream
[GTK4 visual index](https://docs.gtk.org/gtk4/visual_index.html) lists many
more widgets in the same five sections.

Feature 4 is the **first catalog expansion wave**: add **11** new demos using
the existing registry and demo-page pattern, inserted at the correct visual-index
positions within their categories. No new application modes, menu items, or
introspection behaviour are required.

Taxonomy, naming, ordering, and doc links continue to follow
[2026-07-26-plan-feature-3-visual-index-source-of-truth.md](../notes/2026-07-26-plan-feature-3-visual-index-source-of-truth.md).
Phasing rationale is in
[2026-07-26-plan-feature-3-framework-first-catalog-later.md](../notes/2026-07-26-plan-feature-3-framework-first-catalog-later.md).

Feature 4 does not implement search, favourites, live property editing, or
widgets that need heavy external assets, OpenGL contexts, or media pipelines
(deferred to later waves).

# Use cases

1. A developer opens the gallery, selects **Display widgets**, and finds new
   entries (for example **GtkStatusbar**, **GtkImage**) in visual-index order
   after the Feature 3 demos.

2. A developer opens **Entries** and runs **GtkSearchEntry**,
   **GtkPasswordEntry**, and **GtkEditableLabel** demos distinct from the plain
   **GtkEntry** page.

3. A developer reads each new demo page description, follows the upstream doc
   link, and compares the in-app example with the official GTK reference.

4. A developer enables **View → Inspect widget** and inspects the primary widget
   on a new demo page without gallery-specific introspection changes.

5. A contributor adds a demo by implementing a builder in the appropriate
   category unit (or a new sub-unit under `src/gallery/<category>/`), registering
   it in the category registry table, and extending gallery smoke tests — without
   editing `gallery-shell.c` navigation logic.

# Relationship to Feature 3

| Aspect           | Feature 3 (complete)                       | Feature 4 (this feature) |
| ---------------- | ------------------------------------------ | --- |
| Gallery shell    | `GtkListBox` sidebar, `GtkStack` pages     | Unchanged |
| Demo count       | 14                                         | **25** (+11) |
| Registry API     | `GalleryDemoEntry`, category getters       | Unchanged; counts grow |
| Demo page chrome | Title, description, doc link, content      | Unchanged |
| Introspection    | Pick mode on gallery widgets               | Unchanged |
| Code layout      | Category units; `display-demos/` sub-units | Extend same pattern |

Post–Feature 3 refinements (interactive display demos, pulse mode, About dialog,
display-demos file split) remain in place; Feature 4 adds demos only.

# Wave 1 demo set

Eleven demos in visual-index order within each category. Demos marked *interactive*
should exercise APIs or signals where that aids teaching, following Feature 3
display and button demo conventions.

## Display widgets

Insert after **GtkScale** (last Feature 3 display demo). Stop before **GtkGLArea**
(deferred — see [Out of scope](#out-of-scope)).

| Demo           | Notes |
| -------------- | --- |
| `GtkStatusbar` | Status message with push/pop or timed clear |
| `GtkLevelBar`  | Filled level in a defined range |
| `GtkInfoBar`   | Message area with dismiss or action button |
| `GtkScrollbar` | Linked to a scrollable widget or adjustment |
| `GtkImage`     | Static image from icon name or resource |
| `GtkPicture`   | Scalable picture from file or resource |
| `GtkSeparator` | Horizontal and/or vertical rule |
| `GtkTextView`  | Read-only or editable buffer with short sample text |

## Entries

Insert after **GtkSpinButton**.

| Demo               | Notes |
| ------------------ | --- |
| `GtkSearchEntry`   | Search icon entry; optional placeholder text |
| `GtkPasswordEntry` | Masked input with visibility toggle if API allows |
| `GtkEditableLabel` | Label toggling to editable mode |

Total after Feature 4: **25** demos (Display **12**, Buttons **4**, Entries **5**,
Containers **4**, Windows **2**).

Remaining visual-index widgets stay in later waves — see
[2026-07-26-plan-feature-3-framework-first-catalog-later.md](../notes/2026-07-26-plan-feature-3-framework-first-catalog-later.md).

# Application UI

No shell changes expected. The sidebar lists new entries under existing category
headers when registered in the category demo arrays.

| Element            | Detail |
| ------------------ | --- |
| File menu          | Unchanged |
| View menu          | Unchanged (**Widget gallery**, **Sample palette**, **Inspect widget**) |
| Help menu          | Unchanged (**About**) |
| Gallery navigation | New rows appear in **Display widgets** and **Entries** |
| Default selection  | Unchanged (first display demo on startup) |

# Acceptance criteria

1. On a Linux system with GTK4 development libraries installed, `meson setup build`
   followed by `meson compile -C build` completes without errors, including new
   gallery demo sources.

2. Feature 1, 2, and 3 behaviour is preserved: menu bar, content-mode switching,
   introspection pick mode, Escape, and modal window demos from Feature 3.

3. Each demo in the [wave 1 demo set](#wave-1-demo-set) is present in the
   sidebar under the correct category, in visual-index order relative to existing
   entries.

4. Selecting each new demo shows a runnable page with the primary widget type
   described in its table row.

5. Each new demo page includes a link to the matching upstream GTK class
   documentation.

6. Pick mode can target the primary widget on each new demo page.

7. New demos that use buttons or editable controls remain usable alongside pick
   mode (Feature 2 claimed-click behaviour).

8. `meson test -C build` passes, including updated registry count expectations
   and non-NULL builder smoke tests for all demos (Feature 3 + Feature 4).

9. New source and header files follow [c-code-standard.md](../c-code-standard.md),
   use `include/gtk-version.h` for GTK includes, and carry the project copyright
   notice.

10. Demos do not require network access at runtime.

# Technical acceptance criteria

## Build system

| Requirement     | Detail |
| --------------- | --- |
| Root build file | Extend `meson.build` with new demo sub-unit sources |
| GTK dependency  | Continue `dependency('gtk4', include_type: 'system')` |
| Warnings        | `warning_level=3` on project code |
| Executable      | Still one target (`gtk-widget-demo`) |
| Tests           | Update `test/gallery/` registry counts for expanded demo set |

Expected contributor workflow:

```bash
meson setup build
meson compile -C build
meson test -C build
./build/gtk-widget-demo
```

## Code layout

Extend existing category units; prefer one demo per sub-unit file when a category
unit grows large (established pattern in `src/gallery/display-demos/`).

| Path                            | Role |
| ------------------------------- | --- |
| `src/gallery/display-demos.c`   | Registry table for display category; add new entries |
| `src/gallery/display-demos/*.c` | One sub-unit per new display demo (headers under `include/gallery/display-demos/`) |
| `src/gallery/entry-demos.c`     | Registry table for entries category |
| `src/gallery/entry-demos/*.c`   | New entry demo sub-units when `entry-demos.c` would exceed ~300–400 lines |
| `test/gallery/demo-registry.c`  | Assert category demo counts including wave 1 totals |
| `test/gallery/demo-builders.c`  | Smoke-test all builders, including new demos |

No changes to `demo-page.c`, `gallery-shell.c`, or `demo-registry.c` category
structure unless a demo requires a new page pattern (out of scope for standard
widgets).

## Demo implementation rules

Reuse Feature 3 conventions:

1. **One primary widget per page** — supporting labels and buttons are incidental
   chrome; see
   [2026-07-26-plan-feature-3-one-widget-per-demo-page.md](../notes/2026-07-26-plan-feature-3-one-widget-per-demo-page.md).

2. **Natural size** — compact controls use `hexpand = FALSE` and sensible
   alignment; see
   [2026-07-30-plan-widget-align-natural-size.md](../notes/2026-07-30-plan-widget-align-natural-size.md).

3. **Lifetime** — timers, signal handlers, and heap data attached with
   `g_object_set_data_full()` must clean up on page destroy (same pattern as
   display progress-bar pulse mode).

4. **Assets** — prefer GTK icon names or embedded resources over runtime network
   or arbitrary host paths; document any small bundled asset in the demo
   description.

## Tests

| Requirement | Detail |
| ----------- | --- |
| Registry    | Display category count **12**; Entries **5**; total demos **25** |
| Builders    | Each new builder returns non-NULL root widget |
| Drift       | Avoid brittle property-value assertions; smoke-test types and presence |

Gallery UI for new demos is verified manually; automated tests focus on registry
and builder stability as in Feature 3.

# Design decisions

1. **Wave scope — display through TextView plus entries trio:** proposed — covers
   the next visual-index segment that avoids GL, video, and popover-only demos in
   one reviewable milestone. Alternatives: display-only wave (8 demos) or a
   single category to completion; revisit before implementation if effort estimates
   differ.

2. **Sub-unit files per demo:** resolved by precedent — follow
   `src/gallery/display-demos/<demo>.c` for new display demos; split
   `entry-demos` similarly when the parent unit grows.

3. **Registry ordering:** resolved — visual-index order within category per
   [2026-07-26-plan-feature-3-visual-index-source-of-truth.md](../notes/2026-07-26-plan-feature-3-visual-index-source-of-truth.md).

4. **Framework unchanged:** resolved — no sidebar search, icons, or dynamic title;
   catalog growth only.

# Open decisions

Record outcomes in dated notes under `docs/notes/` before or during implementation.

| #   | Topic                              | Options |
| --- | ---------------------------------- | --- |
| 1   | **GtkImage vs GtkPicture assets**  | Icon name only; bundled PNG/SVG in repo; generate at runtime |
| 2   | **GtkScrollbar demo shape**        | Standalone scrollbar with adjustment vs scrollbar attached to `GtkTextView` / `GtkScrolledWindow` preview |
| 3   | **GtkTextView interactivity**      | Read-only buffer vs editable; affects pick-mode interaction |
| 4   | **Entry sub-unit split threshold** | Split at first new entry demo vs when file exceeds ~300 lines |
| 5   | **Wave 1 delivery split**          | One PR/feature vs stories per category (`docs/stories/` when used) |

# Out of scope

The following belong in later features or waves, not Feature 4:

1. Display widgets from **GtkGLArea** onward in the visual index (`GtkGLArea`,
   `GtkDrawingArea`, `GtkVideo`, `GtkMediaControls`, `GtkWindowControls`,
   `GtkPopoverMenuBar`, `GtkCalendar`, `GtkEmojiChooser`, `GtkPopoverMenu`).

2. New demos in **Buttons**, **Containers**, or **Windows** categories (later
   waves).

3. Gallery search, favourites, recents, or category collapse.

4. Per-demo curated “type facts” panels; live property editing; signal logging.

5. Custom `G_DEFINE_FINAL_TYPE` tutorial types.

6. Automated UI tests driving new widgets (manual gallery verification is
   enough for this wave).

7. Changes to introspection algorithms or inspector pane layout.

8. Cross-platform CI or packaging.

# Risks

| Risk                                    | Mitigation |
| --------------------------------------- | --- |
| Scope creep into GL/video/popover demos | Hold wave boundary at GtkTextView; defer listed widgets explicitly |
| Large category files again              | One sub-unit per demo; parent file holds registry only |
| Asset path portability                  | Icon names and repo-local resources; no `$HOME` paths |
| Scrollbar demo without context          | Pair with adjustment or minimal scrollable content; keep one primary widget |
| Registry test drift                     | Update expected counts in same change as new registrations |
| Pick mode vs search/password entry      | Verify claimed-click on interactive entry demos |

# References

[feature-3-widget-gallery.md](./feature-3-widget-gallery.md)

[2026-07-26-plan-feature-3-framework-first-catalog-later.md](../notes/2026-07-26-plan-feature-3-framework-first-catalog-later.md)

[2026-07-26-plan-feature-3-visual-index-source-of-truth.md](../notes/2026-07-26-plan-feature-3-visual-index-source-of-truth.md)

[2026-07-26-plan-feature-3-one-widget-per-demo-page.md](../notes/2026-07-26-plan-feature-3-one-widget-per-demo-page.md)

[2026-07-30-plan-widget-align-natural-size.md](../notes/2026-07-30-plan-widget-align-natural-size.md)

[2026-08-01-coding-display-demos-interactive-and-pulse.md](../notes/2026-08-01-coding-display-demos-interactive-and-pulse.md)

[c-code-standard.md](../c-code-standard.md)

[README.md](../../README.md)

[GTK4 Widget Gallery — visual index](https://docs.gtk.org/gtk4/visual_index.html)

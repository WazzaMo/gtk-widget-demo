# Widget Gallery Catalog Nine Waves

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Context

[Feature 3](../features/feature-3-widget-gallery.md) delivered the gallery
framework and **14** initial demos. [Feature 4](../features/feature-4-widget-gallery-catalog-wave-1.md)
defines **catalog wave 1**: **11** more demos (Display through **GtkTextView** plus
the three remaining **Entries** widgets).

[2026-07-26-plan-feature-3-framework-first-catalog-later.md](./2026-07-26-plan-feature-3-framework-first-catalog-later.md)
records the full follow-on backlog but leaves batch size open — “by category” or
“by complexity”. Review of wave 1 scope showed **11 demos** is workable yet at
the upper bound for a single reviewable milestone. Smaller waves reduce review
fatigue and keep PRs focused. **Wave 2 is a deliberate risk spike:** one OpenGL
(**GtkGLArea**), one video (**GtkVideo**), and one popover-only display demo
(**GtkPopoverMenu**) land immediately after wave 1 so platform, GPU, media, and
popover lifecycle issues surface early — before most of the catalog depends on
patterns learned from those widgets.

This note proposes **nine catalog expansion waves** (including Feature 4 as wave 1)
to complete the follow-on catalog from the framework-first plan. Taxonomy, naming,
and in-category order continue to follow
[2026-07-26-plan-feature-3-visual-index-source-of-truth.md](./2026-07-26-plan-feature-3-visual-index-source-of-truth.md).

# Decision

**Nine review-friendly catalog waves**, each adding roughly **3–8** demos (wave 1
is **11** and already specced in Feature 4). **Wave 2** delivers one each of GL,
video, and popover-only display demos as a small hard-things-first spike. Later
waves finish the remaining Display segment, then batch Buttons, Containers, and
Windows by category and complexity (chooser dialogs stay in the final wave).

Each wave is expected to map to one feature spec (or one focused PR series) using
the existing registry and demo-page pattern — no gallery shell changes unless a
demo requires a new page pattern (unlikely for standard widgets).

# Wave sizing principles

1. **Target 4–8 demos per wave** for waves 3–9. Wave 2 is intentionally smaller
   (**3** demos) for the GL / video / popover risk spike. Fewer is also acceptable
   when complexity is high (chooser dialogs).

2. **Hard things early** — wave 2 proves **GtkGLArea**, **GtkVideo**, and one
   popover-only display demo before the bulk of Display, Containers, and Windows
   land. Fix build, runtime, and asset patterns once; reuse in later waves.

3. **Visual-index order within each category** when registering demos. A wave may
   implement demos out of visual-index sequence for risk reasons; each registration
   still inserts at the correct index position among entries already shipped.

4. **One primary widget per page** — supporting chrome only; see
   [2026-07-26-plan-feature-3-one-widget-per-demo-page.md](./2026-07-26-plan-feature-3-one-widget-per-demo-page.md).

5. **One sub-unit per demo builder** in category directories; parent units hold
   registry tables only — see [c-code-standard.md](../c-code-standard.md).

6. **Modal window demos** use the launch-button pattern from Feature 3; chooser
   dialogs batch together — see
   [2026-07-26-plan-feature-3-modal-dialogs-window-types.md](./2026-07-26-plan-feature-3-modal-dialogs-window-types.md).

7. **Update registry smoke tests** in the same change as new registrations.

8. **Defer cross-cutting gallery features** (search, favourites, live property
   editing) until after the catalog is complete.

# Summary

| Wave | Feature (expected) | New demos | Cumulative total | Category focus |
| ---- | ------------------ | --------- | ---------------- | --- |
| 1    | Feature 4          | 11        | 25               | Display (8) + Entries (3) |
| 2    | Feature 5          | 3         | 28               | Display — GL, video, popover risk spike |
| 3    | Feature 6          | 6         | 34               | Display — remainder (drawing, media, chrome) |
| 4    | Feature 7          | 5         | 39               | Buttons — links, menus, toggles |
| 5    | Feature 8          | 6         | 45               | Buttons — combos and dialog buttons |
| 6    | Feature 9          | 8         | 53               | Containers — layout and bars |
| 7    | Feature 10         | 8         | 61               | Containers — lists, stacks, popover |
| 8    | Feature 11         | 4         | 65               | Windows — top-level patterns |
| 9    | Feature 12         | 6         | **71**           | Windows — chooser and print dialogs |

After wave 9 every widget in the follow-on catalog from the framework-first plan
is covered, plus the Feature 3 initial set. **Entries** completes in wave 1;
**Display** in wave 3 (wave 2 proves the three highest-risk display types first);
**Buttons** in wave 5; **Containers** in wave 7; **Windows** in wave 9.

# Wave descriptions

## Wave 1 — Display core and Entries complete (Feature 4)

**Status:** specced in
[feature-4-widget-gallery-catalog-wave-1.md](../features/feature-4-widget-gallery-catalog-wave-1.md).

Completes the “straightforward” Display segment and the entire Entries category.
Stops before **GtkGLArea** (deferred heavy widgets).

| Category | Demos |
| -------- | --- |
| Display  | `GtkStatusbar`, `GtkLevelBar`, `GtkInfoBar`, `GtkScrollbar`, `GtkImage`, `GtkPicture`, `GtkSeparator`, `GtkTextView` |
| Entries  | `GtkSearchEntry`, `GtkPasswordEntry`, `GtkEditableLabel` |

**Notes:** bundle SVG Repo assets for image demos; **GtkTextView** uses
`GtkTextTag` scale on selection (no direct Pango calls) per
[2026-08-01-plan-pango-text-rendering.md](./2026-08-01-plan-pango-text-rendering.md).

Category counts after wave 1: Display **12**, Entries **5**, total **25**.

## Wave 2 — Display risk spike (GL, video, popover)

Three demos that prove the hardest Display patterns immediately after wave 1.
Keep each demo minimal. Document platform prerequisites and optional manual
verification in demo descriptions where CI or host environments may lack GPU,
GStreamer, or popover parent semantics.

Deliver out of strict visual-index sequence on purpose; register each demo at
its visual-index slot among entries already shipped (sidebar gaps fill in when
wave 3 lands the Display widgets between them).

| Demo              | Notes |
| ----------------- | --- |
| `GtkGLArea`       | Minimal GL clear or triangle; guard compile/runtime where needed |
| `GtkVideo`        | Short bundled sample; no network at runtime |
| `GtkPopoverMenu`  | Popover-only display demo — menu anchored to a button; establishes popover parent and dismiss patterns reused by **GtkPopoverMenuBar** and container **GtkPopover** in later waves |

Category counts after wave 2: Display **15**, total **28**.

## Wave 3 — Display remainder

Six demos that finish the Display category using patterns established in wave 2
where applicable (media controls after **GtkVideo**; **GtkPopoverMenuBar** after
**GtkPopoverMenu**). Straightforward drawing and chrome widgets batch here once
the risk spike is green.

| Demo                 | Notes |
| -------------------- | --- |
| `GtkDrawingArea`     | Simple draw callback (for example fill or stroke a shape) |
| `GtkMediaControls`   | Paired with a media source or stubbed controller state; reuse wave 2 video asset approach |
| `GtkWindowControls`  | Window control widget in a representative header context |
| `GtkPopoverMenuBar`  | Menu bar that opens popover menus; builds on wave 2 popover pattern |
| `GtkCalendar`        | Date selection; show selected date feedback |
| `GtkEmojiChooser`    | Emoji pick with selection feedback |

**Display category complete** after wave 3 (**21** demos). Cumulative total **34**.

## Wave 4 — Buttons links, menus, and toggles

Five interactive button-family widgets without list models or font/color dialog
machinery. Follow Feature 3 button demo conventions (visible state feedback).

| Demo              | Notes |
| ----------------- | --- |
| `GtkLinkButton`   | URI link with accessible label |
| `GtkRadioButton`  | Mutually exclusive group |
| `GtkMenuButton`   | Opens a `GMenu` or popover menu |
| `GtkLockButton`   | Locked / unlocked state |
| `GtkVolumeButton` | Volume popover or scale |

Cumulative total **39**.

## Wave 5 — Buttons combos and dialog buttons

Six demos that introduce models, dropdowns, or dialog-button APIs. May share
helper patterns for launching transient dialogs (same modal approach as Windows
category).

| Demo                    | Notes |
| ----------------------- | --- |
| `GtkComboBox`           | Small static model |
| `GtkComboBoxText`       | Text items without custom `GtkTreeModel` |
| `GtkDropDown`           | `GtkStringList` or equivalent |
| `GtkColorDialogButton`  | Opens color dialog on click |
| `GtkFontDialogButton`   | Opens font dialog on click |
| `GtkAppChooserButton`   | Application selection |

**Buttons category complete** after wave 5 (**15** demos). Cumulative total **45**.

## Wave 6 — Containers layout and bars

Eight container demos covering alignment, scrolling, splitting, and action chrome.
Natural-size alignment rules apply — see
[2026-07-30-plan-widget-align-natural-size.md](./2026-07-30-plan-widget-align-natural-size.md).

| Demo                 | Notes |
| -------------------- | --- |
| `GtkCenterBox`       | Start, center, and end children |
| `GtkScrolledWindow`  | Scroll policy on overflowing content |
| `GtkPaned`           | Resizable split |
| `GtkExpander`        | Expand/collapse disclosure |
| `GtkSearchBar`       | Search entry reveal |
| `GtkActionBar`       | Bottom action area |
| `GtkHeaderBar`       | Title and window controls |
| `GtkListBox`         | Selectable rows |

Cumulative total **53**.

## Wave 7 — Containers lists, stacks, and popover

Eight demos for data views and stack navigation. **GtkTreeView** and
**GtkIconView** need small static models; keep row/column count minimal for
teaching.

| Demo                | Notes |
| ------------------- | --- |
| `GtkFlowBox`        | Wrapping child layout |
| `GtkTreeView`       | List store with a few columns |
| `GtkIconView`       | Icon + label from a small model |
| `GtkOverlay`        | Overlay child on base content |
| `GtkStack`          | Multiple pages; programmatic switch |
| `GtkStackSwitcher`  | Tabs bound to a `GtkStack` |
| `GtkStackSidebar`   | Sidebar bound to a `GtkStack` |
| `GtkPopover`        | Popover anchored to a control |

**Containers category complete** after wave 7 (**20** demos). Cumulative total **61**.

## Wave 8 — Windows top-level patterns

Four window types that establish general top-level behaviour before chooser
dialogs. All use the modal launch pattern from Feature 3.

| Demo                  | Notes |
| --------------------- | --- |
| `GtkWindow`           | Secondary window or transient example |
| `GtkDialog`           | Generic dialog with response buttons |
| `GtkAssistant`        | Multi-page assistant flow |
| `GtkShortcutsWindow`  | Shortcuts overlay |

Cumulative total **65**.

## Wave 9 — Windows chooser and print dialogs

Six chooser and platform print dialogs batched by shared launch and dismiss
patterns. **GtkPageSetupUnixDialog** and **GtkPrintUnixDialog** are Unix-specific;
note platform scope in demo descriptions.

| Demo                       | Notes |
| -------------------------- | --- |
| `GtkColorChooserDialog`    | Modal color selection |
| `GtkFileChooserDialog`     | Open or save action |
| `GtkFontChooserDialog`     | Font family and size |
| `GtkAppChooserDialog`      | Application pick |
| `GtkPageSetupUnixDialog`   | Page setup (Unix) |
| `GtkPrintUnixDialog`       | Print dialog (Unix) |

**Windows category complete** after wave 9 (**12** demos). **Full catalog complete**
at **71** demos.

# Per-wave delivery checklist

Each wave should, unless noted otherwise in its feature spec:

1. Add demo sub-units under the appropriate `src/gallery/<category>/` directory.

2. Register entries in the category registry table in visual-index order.

3. Update `test/gallery/demo-registry.c` expected category counts.

4. Extend `test/gallery/demo-builders.c` smoke coverage for new builders.

5. Verify manually: sidebar order, runnable page, upstream doc link, pick mode on
   primary widget.

6. Record delivery in a dated coding note when the wave lands.

# Alternatives considered

## Fewer, larger waves (5–6 total)

Combine waves 2–3 (all remaining Display), 4–5 (all Buttons), or 6–7 (all
Containers) into single features.

**Rejected for planning default:** review load and late discovery of GL/video/
popover failures. Revisit if maintainer bandwidth favours fewer PRs after wave 2
is green.

## Defer all hard Display widgets to wave 3 (previous plan)

Batch **GtkGLArea**, **GtkVideo**, popover display demos, and simpler Display
widgets into separate sequential waves without an early spike.

**Superseded:** defers learning from GPU, media, and popover constraints until
after drawing and calendar demos — higher risk that later waves repeat the same
fixes. Wave 2 now front-loads one demo of each hard type.

## More than nine waves

Split wave 1 (Feature 4) into display-only (8) and entries-only (3), or split
wave 9 chooser dialogs into two waves of three.

**Deferred:** Feature 4 is already drafted as an 11-demo milestone; splitting
now would rework an accepted spec. Future waves can subdivide further if
implementation estimates grow.

# Risks

| Risk                                       | Mitigation |
| ------------------------------------------ | ------ |
| Wave 1 remains large (11 demos)            | Keep Feature 4 boundary; use sub-unit split from the start |
| Wave 2 spike blocks follow-on Display work | Keep wave 2 to three demos; wave 3 completes Display only after spike passes |
| GL/video demos fail on some CI hosts       | Wave 2 surfaces failures early; minimal demos; document optional manual verification |
| Popover parent/dismiss bugs found late     | Wave 2 **GtkPopoverMenu** proves pattern before **GtkPopoverMenuBar** and **GtkPopover** |
| Unix print dialogs on non-Unix platforms   | Guard or skip with clear demo description; no crash on open |
| TreeView/IconView model boilerplate        | Shared tiny static models; one list per demo |
| Out-of-order wave delivery vs sidebar      | Register at visual-index slot; accept temporary sidebar gaps until wave 3 fills Display |
| Feature numbering drift                    | Map feature N+3 to catalog wave N for waves 1–9; adjust when opening each spec |
| Upstream visual index changes              | Insert new widgets in visual-index order within the relevant category wave |

# Relationship to feature specs

| Catalog wave | Expected feature doc |
| ------------ | --- |
| 1            | [feature-4-widget-gallery-catalog-wave-1.md](../features/feature-4-widget-gallery-catalog-wave-1.md) |
| 2            | `feature-5-widget-gallery-catalog-wave-2.md` (to create) |
| 3            | `feature-6-widget-gallery-catalog-wave-3.md` (to create) |
| 4–9          | `feature-{n}-widget-gallery-catalog-wave-{w}.md` (to create when prior wave completes) |

Wave plans in this note are **proposed scope** for those specs. Each feature
document should repeat acceptance criteria, resolved design decisions, and any
wave-specific out-of-scope items before implementation.

# References

[feature-3-widget-gallery.md](../features/feature-3-widget-gallery.md)

[feature-4-widget-gallery-catalog-wave-1.md](../features/feature-4-widget-gallery-catalog-wave-1.md)

[2026-07-26-plan-feature-3-framework-first-catalog-later.md](./2026-07-26-plan-feature-3-framework-first-catalog-later.md)

[2026-07-26-plan-feature-3-visual-index-source-of-truth.md](./2026-07-26-plan-feature-3-visual-index-source-of-truth.md)

[2026-07-26-plan-feature-3-modal-dialogs-window-types.md](./2026-07-26-plan-feature-3-modal-dialogs-window-types.md)

[2026-07-26-plan-feature-3-one-widget-per-demo-page.md](./2026-07-26-plan-feature-3-one-widget-per-demo-page.md)

[c-code-standard.md](../c-code-standard.md)

[doc-guide.md](../doc-guide.md)

[GTK4 Widget Gallery — visual index](https://docs.gtk.org/gtk4/visual_index.html)

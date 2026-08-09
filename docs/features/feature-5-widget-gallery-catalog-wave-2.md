# Feature 5 Widget Gallery Catalog Wave 2

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Status

**Complete** — two-part feature delivered 2026-08-08:

1. **Part 1 — Deprecated widget separation** (phase 1 and phase 2 **infrastructure**):
   **Complete** — merged to `main` 2026-08-08 ([PR #6](https://github.com/WazzaMo/gtk-widget-demo/pull/6)).

2. **Part 2 — Catalog wave 2** (Display risk spike): **Complete** — **3** new demos
   for **GtkGLArea**, **GtkVideo**, and **GtkPopoverMenu**; **28** total demos.

Part 1 delivers lifecycle metadata, sidebar **Deprecated** subsections, deprecation
banners, replacement-doc links, and comparison API hooks (no comparison builders).
Part 2 adds supported Display demos on top of that baseline. Planning detail is in
[2026-08-05-plan-gallery-deprecated-widget-separation.md](../notes/2026-08-05-plan-gallery-deprecated-widget-separation.md)
and
[2026-08-08-plan-deprecated-widget-delivery-order.md](../notes/2026-08-08-plan-deprecated-widget-delivery-order.md).

# Overview

Feature 4 delivered **25** demos and completed the “straightforward” Display
segment through **GtkTextView**, plus the entire **Entries** category. It also
ships three deprecated demos (**GtkStatusbar**, **GtkInfoBar**,
**GtkMessageDialog**).

Feature 5 **part 1** (on `main`) adds lifecycle metadata, sidebar **Deprecated**
subsections, deprecation banners, replacement-doc links, and comparison API
hooks so developers can distinguish supported from deprecated APIs. Feature 5
**part 2** is the **second catalog expansion wave** and a deliberate **risk
spike**: prove OpenGL, media, and popover Display patterns early, in a small
reviewable milestone, before Feature 6 (wave 3) batches the remaining Display
widgets. Each new demo stays **minimal**; platform or host limitations are
documented in demo descriptions and acceptance notes.

Taxonomy, naming, ordering, and doc links continue to follow
[2026-07-26-plan-feature-3-visual-index-source-of-truth.md](../notes/2026-07-26-plan-feature-3-visual-index-source-of-truth.md).
Wave sizing and sequencing are in
[2026-08-05-plan-widget-gallery-catalog-nine-waves.md](../notes/2026-08-05-plan-widget-gallery-catalog-nine-waves.md).

Feature 5 does not implement **GtkDrawingArea**, **GtkMediaControls**,
**GtkWindowControls**, **GtkPopoverMenuBar**, **GtkCalendar**, or
**GtkEmojiChooser** (Feature 6 / wave 3), migration comparison **content**
(`build_comparison` builders), phase 3 hide-deprecated toggle, or gallery search,
favourites, or live property editing.

# Use cases

## Part 1 — Deprecated widget separation

1. A developer opens **Display widgets** and sees supported demos first, then a
   **Deprecated** subsection containing **GtkStatusbar** and **GtkInfoBar**.

2. A developer opens **Windows** and sees **GtkAboutDialog** in the main list and
   **GtkMessageDialog** under **Deprecated**.

3. A developer selects a deprecated demo and reads the banner **“Deprecated in GTK 4
   — avoid for new designs.”** on the demo page.

4. A developer follows **See replacement API** on **GtkMessageDialog** to the
   **GtkAlertDialog** upstream documentation.

5. A contributor registers a new demo with `GALLERY_DEMO_SUPPORTED` or
   `GALLERY_DEMO_DEPRECATED`; sidebar placement follows lifecycle automatically.

## Part 2 — Catalog wave 2

1. A developer opens **Display widgets** and finds **GtkGLArea**, **GtkVideo**,
   and **GtkPopoverMenu** at their visual-index positions after **GtkScale**
   (unimplemented visual-index entries between them are omitted until Feature 6).

2. A developer runs the **GtkGLArea** demo and sees a minimal OpenGL render
   (for example solid clear colour or simple triangle) inside the gallery page,
   without the app requiring a separate GL toolkit beyond GTK.

3. A developer runs the **GtkVideo** demo and plays a **short bundled** sample
   file with no network access at runtime.

4. A developer runs the **GtkPopoverMenu** demo, opens a popover menu from a
   button, and dismisses it — establishing popover parent and dismiss patterns
   reused by **GtkPopoverMenuBar** (Feature 6) and container **GtkPopover**
   (later wave).

5. A developer enables **View → Inspect widget** and inspects the primary widget
   on each new demo page without gallery-specific introspection changes.

6. A contributor adds each wave 2 demo as a sub-unit under
   `src/gallery/display-demos/`, registers it in `display-demos.c` at the
   correct visual-index position, sets `GALLERY_DEMO_SUPPORTED`, and updates
   gallery smoke tests — without editing `gallery-shell.c` navigation logic.

# Relationship to Feature 4

| Aspect                 | Feature 4 (complete)                   | Feature 5 part 1 (deprecation)                           | Feature 5 part 2 (wave 2) |
| ---------------------- | -------------------------------------- | -------------------------------------------------------- | --- |
| Gallery shell          | Category headers only                  | **Deprecated** subsections per category                  | Unchanged |
| Demo count             | **25**                                 | **25** (unchanged)                                       | **28** (+3) |
| Registry API           | `GalleryDemoEntry` (content fields)    | + lifecycle, replacement URL, comparison hooks           | Unchanged |
| Demo page chrome       | Title, description, doc link, content  | + deprecation banner, replacement link, comparison frame | Unchanged |
| Default selection      | First demo in registry                 | First **supported** demo (**GtkLabel**)                  | Unchanged |
| New deprecated demos   | Three compile with warnings            | Classified; UI separation                                | None (all supported) |
| Code layout            | `display-demos/` sub-units             | `demo-registry`, `demo-page`, `gallery-shell`            | Three new sub-units |

Post–Feature 4 refinements (interactive display demos, bundled SVG assets) remain
in place. Part 1 is on `main`; part 2 extends the lifecycle-aware registry and
demo-page API with three supported Display demos.

# Part 1 — Deprecated widget separation

Scope is phase 1 and phase 2 **infrastructure** from
[2026-08-05-plan-gallery-deprecated-widget-separation.md](../notes/2026-08-05-plan-gallery-deprecated-widget-separation.md).
Phase 2 comparison **content** and phase 3 hide toggle are out of scope.

## Lifecycle classification (Feature 4 baseline)

| Demo             | Lifecycle  | `replacement_doc_url` |
| ---------------- | ---------- | --- |
| GtkStatusbar     | Deprecated | — (no single successor) |
| GtkInfoBar       | Deprecated | — (no single successor) |
| GtkMessageDialog | Deprecated | [GtkAlertDialog](https://docs.gtk.org/gtk4/class.AlertDialog.html) |
| All other demos  | Supported  | — |

## Part 1 deliverables

1. `GalleryDemoLifecycle` enum and extended `GalleryDemoEntry` in
   `include/gallery/demo-registry.h`.

2. Classify all **25** Feature 4 demos (table above).

3. Sidebar **Deprecated** subsections in `gallery-shell.c` (Display + Windows).

4. Deprecation banner and **See replacement API** link in `demo-page.c`.

5. `gallery_demo_page_new(entry, legacy_content, comparison_content)` API.

6. `build_comparison`, `comparison_title`, and `comparison_doc_url` hooks in shell
   and demo page — all callbacks remain `NULL`.

7. `G_GNUC_BEGIN_IGNORE_DEPRECATIONS` / `G_GNUC_END_IGNORE_DEPRECATIONS` in
   deprecated demo sub-units only.

8. Tests: `test/gallery/demo-page.c`, extended `demo-registry.c` and
   `gallery-shell.c`.

## Part 1 acceptance criteria

1. Sidebar shows **Deprecated** under **Display widgets** (Statusbar, InfoBar)
   and **Windows** (MessageDialog).

2. Deprecated demo pages show the standard deprecation banner.

3. **GtkMessageDialog** page shows **See replacement API** linking to AlertDialog
   docs.

4. Default startup selection is **GtkLabel** (first supported demo), not a
   deprecated entry.

5. No demo page shows a **Modern alternative** section (`build_comparison` NULL
   for all entries).

6. `meson test -C build` passes, including deprecation lifecycle and sidebar
   order tests.

# Part 2 — Catalog wave 2 demo set

Three demos in **visual-index order** among implemented Display entries.
Implement demos in any convenient order; register each row at its upstream
position in `display_demos[]`.

Unimplemented visual-index widgets between wave 2 entries (**GtkDrawingArea**,
**GtkMediaControls**, **GtkWindowControls**, **GtkPopoverMenuBar**,
**GtkCalendar**, **GtkEmojiChooser**) are **not** registered until wave 3 — the
sidebar lists only shipped demos, with no placeholder rows.

## Display widgets

Full Display registry order after Feature 5 (existing entries in **bold**; new
entries marked *wave 2*):

| Order | Demo               | Notes |
| ----- | ------------------ | --- |
| 1     | **GtkLabel**       | Feature 3 |
| 2     | **GtkSpinner**     | Feature 3 |
| 3     | **GtkStatusbar**   | Feature 4; deprecated |
| 4     | **GtkLevelBar**    | Feature 4 |
| 5     | **GtkProgressBar** | Feature 3 |
| 6     | **GtkInfoBar**     | Feature 4; deprecated |
| 7     | **GtkScrollbar**   | Feature 4 |
| 8     | **GtkImage**       | Feature 4 |
| 9     | **GtkPicture**     | Feature 4 |
| 10    | **GtkSeparator**   | Feature 4 |
| 11    | **GtkTextView**    | Feature 4 |
| 12    | **GtkScale**       | Feature 3 |
| 13    | GtkGLArea          | *wave 2* — minimal GL clear or triangle; guard compile/runtime where needed |
| 14    | GtkVideo           | *wave 2* — short bundled sample; no network at runtime |
| 15    | GtkPopoverMenu     | *wave 2* — popover menu anchored to a button; establishes dismiss pattern |

Total after Feature 5: **28** demos (Display **15**, Buttons **4**, Entries **5**,
Containers **4**, Windows **2**).

Remaining Display widgets ship in Feature 6 (catalog wave 3) — see
[2026-08-05-plan-widget-gallery-catalog-nine-waves.md](../notes/2026-08-05-plan-widget-gallery-catalog-nine-waves.md).

# Application UI

No shell changes expected beyond new sidebar rows under **Display widgets**.

| Element            | Detail |
| ------------------ | --- |
| File menu          | Unchanged |
| View menu          | Unchanged (**Widget gallery**, **Sample palette**, **Inspect widget**) |
| Help menu          | Unchanged (**About**) |
| Gallery navigation | Three new rows under **Display widgets** |
| Default selection  | Unchanged (first supported display demo — **GtkLabel**) |
| Deprecated UX      | Unchanged from separation feature |

# Acceptance criteria

## Part 1 — Deprecated widget separation

1. [Part 1 acceptance criteria](#part-1-acceptance-criteria) above are met.

## Part 2 — Catalog wave 2

1. On a Linux system with GTK4 development libraries installed, `meson setup build`
   followed by `meson compile -C build` completes without errors, including new
   gallery demo sources and any Meson wiring for bundled media assets.

2. Feature 1–4 behaviour and part 1 deprecation UX are preserved: menu bar,
   content-mode switching, introspection pick mode, Escape, modal window demos,
   and deprecated sidebar subsections.

3. Each demo in the [part 2 demo set](#part-2--catalog-wave-2-demo-set) is present
   in the sidebar under **Display widgets**, in the registry order shown (after
   **GtkScale**, before Feature 6 entries).

4. Selecting each new demo shows a runnable page with the primary widget type
   described in its table row.

5. Each new demo page includes a link to the matching upstream GTK class
   documentation.

6. Pick mode can target the primary widget on each new demo page.

7. New demos that use buttons or interactive controls remain usable alongside
   pick mode (Feature 2 claimed-click behaviour).

8. All three wave 2 demos register as `GALLERY_DEMO_SUPPORTED`.

9. `meson test -C build` passes, including updated registry count expectations
   and non-NULL builder smoke tests for all demos.

10. New source and header files follow [c-code-standard.md](../c-code-standard.md),
    use `include/gtk-version.h` for GTK includes, and carry the project copyright
    notice.

11. Demos do not require network access at runtime.

12. **GtkVideo** uses a bundled media file committed under `data/` (same approach
    as Feature 4 SVG assets); demo description names the file and any optional
    host prerequisites (for example GStreamer plugins).

13. Where OpenGL or media fails at runtime on a given host, the demo page still
    loads and shows a clear inline message rather than crashing the application
    (graceful degradation acceptable for this spike).

## Feature 5 complete

Part 1 and part 2 acceptance criteria are both met; demo count is **28**; Display
category count is **15**.

# Technical acceptance criteria

## Build system

| Requirement     | Detail |
| --------------- | --- |
| Root build file | Extend `meson.build` with three new display sub-units; add bundled video asset path via `GALLERY_DATA_DIR` or equivalent |
| GTK dependency  | Continue `dependency('gtk4', include_type: 'system')` |
| Warnings        | `warning_level=3` on project code |
| Executable      | Still one target (`gtk-widget-demo`) |
| Tests           | Update `test/gallery/` registry counts for Display **15**, total **28** |

Expected contributor workflow:

```bash
meson setup build
meson compile -C build
meson test -C build
./build/gtk-widget-demo
```

## Code layout

### Part 1 — Deprecated widget separation

| Path                                             | Role |
| ------------------------------------------------ | --- |
| `include/gallery/demo-registry.h`                | Lifecycle enum; comparison hooks on `GalleryDemoEntry` |
| `include/gallery/demo-page.h`                    | `gallery_demo_page_new(entry, legacy_content, comparison_content)` |
| `src/gallery/demo-registry.c`                    | `category_has_deprecated`, default demo skips deprecated |
| `src/gallery/gallery-shell.c`                    | Two-pass sidebar iteration; invoke `build_comparison` when set |
| `src/gallery/demo-page.c`                        | Deprecation banner; **Modern alternative** frame when content provided |
| `src/gallery/display-demos.c`                    | Lifecycle on Statusbar, InfoBar entries |
| `src/gallery/window-demos.c`                     | Lifecycle, `replacement_doc_url`, MessageDialog warning isolation |
| `src/gallery/display-demos/gtk-statusbar-demo.c` | Deprecation warning isolation |
| `src/gallery/display-demos/gtk-info-bar-demo.c`  | Deprecation warning isolation |
| `test/gallery/demo-page.c`                       | Banner, replacement link, comparison frame tests |
| `test/gallery/demo-registry.c`                   | Lifecycle, deprecated flags, no builders wired |
| `test/gallery/gallery-shell.c`                   | Subheader count, deprecated sidebar order |
| `test/gallery/demo-builders.c`                   | Invoke `build_comparison` when non-NULL |

### Part 2 — Catalog wave 2

Extend the existing display category per [c-code-standard.md](../c-code-standard.md)
— one sub-unit per demo; parent unit holds the registry table only.

| Path                                                | Role |
| --------------------------------------------------- | --- |
| `src/gallery/display-demos.c`                       | Registry table; insert three entries after **GtkScale** |
| `src/gallery/display-demos/gtk-gl-area-demo.c`      | Minimal **GtkGLArea** render |
| `src/gallery/display-demos/gtk-video-demo.c`        | **GtkVideo** with bundled sample |
| `src/gallery/display-demos/gtk-popover-menu-demo.c` | **GtkPopoverMenu** from button |
| `include/gallery/display-demos/*.h`                 | Builder declarations for new sub-units |
| `data/`                                             | Bundled short video sample (and license/attribution note in demo description) |
| `test/gallery/demo-registry.c`                      | Assert Display **15**, total **28**; display demo order |
| `test/gallery/demo-builders.c`                      | Smoke-test all builders including new demos |

Part 2 does not require further changes to `demo-page.c`, `gallery-shell.c`, or
`demo-registry.c` category structure unless a demo requires a new page pattern
(out of scope).

## Demo implementation rules

Reuse Feature 3–4 conventions:

1. **One primary widget per page** — supporting labels and buttons are incidental
   chrome; see
   [2026-07-26-plan-feature-3-one-widget-per-demo-page.md](../notes/2026-07-26-plan-feature-3-one-widget-per-demo-page.md).

2. **Natural size** — compact controls use `hexpand = FALSE` and sensible
   alignment; see
   [2026-07-30-plan-widget-align-natural-size.md](../notes/2026-07-30-plan-widget-align-natural-size.md).

3. **Lifetime** — GL render callbacks, media files, and popover widgets must
   clean up on page destroy (`g_object_set_data_full()` or weak refs as needed).

4. **Lifecycle** — register all three demos as `GALLERY_DEMO_SUPPORTED`.

### GtkGLArea

Minimal teaching demo: attach a `render` signal handler that clears the colour
buffer or draws a simple triangle. Set a reasonable default size on the GL area.
If GL context creation fails, show a label explaining the failure instead of
asserting or aborting.

### GtkVideo

Bundle a **short** sample (for example a few seconds, small file size) under
`data/`. Load via file URI or `GALLERY_DATA_DIR` path. Autoplay optional;
loop acceptable. Document in the demo description if GStreamer or specific plugins
are required on the host. No runtime download.

### GtkPopoverMenu

Primary widget is **GtkPopoverMenu** (or the popover menu instance opened from
demo chrome — follow one-widget-per-page: the inspect target should be the menu
widget when open, or the menu model surface documented in the demo description).
Use `GMenu` / `GMenuItem` entries; anchor to a **Show menu** or similar button.
Prove dismiss on click-outside and Escape without leaking popover references.

## Tests

| Requirement | Detail |
| ----------- | --- |
| Registry    | Display category count **15**; total demos **28** |
| Order       | `gtk-gl-area`, `gtk-video`, `gtk-popover-menu` after `gtk-scale` in display registry |
| Builders    | Each new builder returns non-NULL root widget |
| Drift       | Avoid brittle GL frame-buffer or video playback assertions; smoke-test types and presence |

Gallery UI for GL, video, and popover behaviour is verified manually on at least
one Linux host; automated tests focus on registry and builder stability as in
Feature 4.

# Design decisions

1. **Wave scope — GL, video, popover spike only:** resolved — three demos per
   [2026-08-05-plan-widget-gallery-catalog-nine-waves.md](../notes/2026-08-05-plan-widget-gallery-catalog-nine-waves.md).
   Remaining Display widgets defer to Feature 6 (wave 3).

2. **Out-of-sequence implementation, in-sequence registration:** resolved —
   implement demos in any order; register each at its visual-index slot in
   `display_demos[]`. Unimplemented upstream entries between wave 2 demos are
   omitted until wave 3 (no empty sidebar rows).

3. **Minimal demos over polish:** resolved — spike validates build and runtime
   patterns; wave 3 reuses video and popover approaches for richer demos.

4. **Framework unchanged:** resolved — no sidebar search, hide-deprecated toggle
   (phase 3), or dynamic title; catalog growth only.

5. **Bundled video asset:** resolved — commit sample under `data/`; no network at
   runtime; document file name and attribution in demo description (and Help →
   About if a third-party asset license requires it).

6. **Graceful degradation:** resolved — GL and media failures show inline fallback
   text on the demo page; build must still succeed on CI hosts without GPU or
   full GStreamer stack where demos compile but runtime may degrade.

7. **Two-part Feature 5:** resolved — part 1 merged to `main` (PR #6, 2026-08-08);
   part 2 (catalog wave 2) proceeds on `wm/feature-5`. See
   [2026-08-08-plan-deprecated-widget-delivery-order.md](../notes/2026-08-08-plan-deprecated-widget-delivery-order.md).

8. **Comparison content deferred:** resolved — `build_comparison` remains NULL
   for all demos in Feature 5; first builders land with eligible deprecated demos
   in Feature 8 (wave 5) per delivery-order note.

# Out of scope

The following belong in later features or waves, not Feature 5:

1. Display widgets **GtkDrawingArea**, **GtkMediaControls**, **GtkWindowControls**,
   **GtkPopoverMenuBar**, **GtkCalendar**, **GtkEmojiChooser** (Feature 6 / wave 3).

2. New demos in **Buttons**, **Entries**, **Containers**, or **Windows**
   categories.

3. Phase 2 migration comparison **content** (`build_comparison` builders).

4. Phase 3 **View → Hide deprecated demos** toggle.

5. Gallery search, favourites, recents, or category collapse.

6. Per-demo curated “type facts” panels; live property editing; signal logging.

7. Automated UI tests driving GL frames or video playback state.

8. Cross-platform CI guarantees for GPU or GStreamer (document manual verification
   instead).

# Risks

| Risk                                      | Mitigation |
| ----------------------------------------- | --- |
| GL context fails on headless CI           | Builder smoke test only; manual verify on GPU host; inline fallback label |
| GStreamer/plugins missing at runtime      | Small bundled sample; document prerequisites; graceful fallback message |
| Popover parent or focus bugs              | Minimal single-button demo; reuse pattern in wave 3/7 notes |
| Scope creep into wave 3 Display batch     | Hold boundary at three demos; list wave 3 widgets in out of scope |
| Large video asset in repo                 | Keep sample short and low resolution |
| Pick mode vs popover menu                 | Verify inspect target when menu open; document primary widget in description |
| Registry test drift                       | Update expected counts and display order in same change |

# References

[feature-4-widget-gallery-catalog-wave-1.md](./feature-4-widget-gallery-catalog-wave-1.md)

[2026-08-05-plan-widget-gallery-catalog-nine-waves.md](../notes/2026-08-05-plan-widget-gallery-catalog-nine-waves.md)

[2026-08-08-plan-deprecated-widget-delivery-order.md](../notes/2026-08-08-plan-deprecated-widget-delivery-order.md)

[2026-08-05-plan-gallery-deprecated-widget-separation.md](../notes/2026-08-05-plan-gallery-deprecated-widget-separation.md)

[2026-07-26-plan-feature-3-visual-index-source-of-truth.md](../notes/2026-07-26-plan-feature-3-visual-index-source-of-truth.md)

[2026-07-26-plan-feature-3-one-widget-per-demo-page.md](../notes/2026-07-26-plan-feature-3-one-widget-per-demo-page.md)

[2026-07-30-plan-widget-align-natural-size.md](../notes/2026-07-30-plan-widget-align-natural-size.md)

[c-code-standard.md](../c-code-standard.md)

[README.md](../../README.md)

[GTK4 Widget Gallery — visual index](https://docs.gtk.org/gtk4/visual_index.html)

[GtkGLArea](https://docs.gtk.org/gtk4/class.GLArea.html)

[GtkVideo](https://docs.gtk.org/gtk4/class.Video.html)

[GtkPopoverMenu](https://docs.gtk.org/gtk4/class.PopoverMenu.html)

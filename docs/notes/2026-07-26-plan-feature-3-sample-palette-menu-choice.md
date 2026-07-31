# Feature 3 Sample Palette Menu Choice

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Context

[Feature 3 Widget Gallery](../features/feature-3-widget-gallery.md) adds navigable
gallery demos. Feature 2 shipped a compact **sample palette** in the main content
area (`src/main/sample-palette.c`) — a single grid of varied controls for trying
**View → Inspect widget** without navigating per-widget demos.

Design decision 3 originally proposed replacing that palette with gallery demos.
This note records a revised decision: keep the palette as an optional view the
user selects from the menu.

# Decision

**Keep the sample palette; let the user choose sample or gallery from the View menu.**

The main content area shows **one mode at a time**. The user switches between:

1. **Widget gallery** — default on startup; navigable visual-index demos.

2. **Sample palette** — the Feature 2 compact control grid
   (`main_sample_palette_new()`).

Expose this as **two mutually exclusive View menu items** (radio group), not a
hidden default with a single optional toggle:

| Menu item          | Content shown |
| ------------------ | --- |
| **Widget gallery** | `gallery-shell` (sidebar + active demo page) |
| **Sample palette** | Feature 2 sample palette grid |

**Widget gallery** is selected on startup. Choosing **Sample palette** shows the
sample; choosing **Widget gallery** again switches back. The user always has an
explicit path to both views.

Gallery demos still cover the same widget types individually; the palette remains
a **compact introspection sandbox**, not a second catalog.

# Rationale

| Benefit                         | Detail |
| ------------------------------- | --- |
| Feature 2 workflow preserved    | Users who learned inspect on the palette keep a one-screen target |
| Quick introspection             | Pick mode across several widget types without changing gallery demos |
| No duplicate maintenance burden | Reuse `main_sample_palette_new()`; do not reimplement the grid in gallery |
| Clear roles                     | Gallery teaches per-widget examples aligned with the visual index; palette teaches multi-widget picking on one page |

Replacing the palette entirely would remove a low-friction entry point for
inspect mode. Deleting `sample-palette.c` is rejected.

Keeping the palette as the **default** would undercut the gallery as the primary
Widget Gallery experience; gallery is default instead.

# Rules

## Menu

| Item      | Detail |
| --------- | --- |
| Location  | **View** menu (alongside **Inspect widget**) |
| Items     | **Widget gallery** and **Sample palette** as a **radio group** |
| Default   | **Widget gallery** selected on startup |
| Behaviour | Selecting one item shows that content mode and deselects the other |

Implementation should use `GSimpleAction` radio state or equivalent so both
choices are visible and the active mode is obvious from the menu. Exact action
names (for example `win.content-mode` with `gallery` / `sample-palette` states)
are an implementation detail.

## Content area

One main content region switches between:

1. **Gallery mode** — `gallery-shell` (sidebar + demo stack).

2. **Sample palette mode** — widget returned by `main_sample_palette_new()`.

Only one mode is visible at a time. Switching modes must not leak widgets or
leave stale pick targets.

## Introspection

Pick mode (**View → Inspect widget**) applies in **both** modes. The pick root
remains the main window content region (menu bar + active content), as in
Feature 2.

When switching from sample palette to gallery (or the reverse), pick mode state
may stay enabled; the pick root must reference widgets that exist in the active
mode.

## Code layout

| Path                          | Detail |
| ----------------------------- | --- |
| `src/main/sample-palette.c`   | **Retained** — no deprecation wrapper |
| `src/main/window-shell.c`     | Owns mode switching and embeds gallery or palette |
| `src/gallery/gallery-shell.c` | Gallery mode only |

Do not register the sample palette as a visual-index gallery demo; it is not a
single-widget page.

## Documentation

[README.md](../../README.md) should document **View → Widget gallery** and
**View → Sample palette**: the user can switch between the visual-index gallery
and the compact inspect sandbox at any time.

# Out of scope for this decision

1. Merging the palette into a gallery category — it is intentionally outside the
   visual index taxonomy.

2. Editing palette widgets from gallery demos — two independent content sources.

3. Showing gallery and palette side by side — mutually exclusive modes only.

# References

[feature-3-widget-gallery.md](../features/feature-3-widget-gallery.md)

[feature-2-gobject-introspection.md](../features/feature-2-gobject-introspection.md)

[2026-07-26-plan-feature-3-framework-first-catalog-later.md](./2026-07-26-plan-feature-3-framework-first-catalog-later.md)

[2026-07-26-plan-feature-3-reuse-introspection.md](./2026-07-26-plan-feature-3-reuse-introspection.md)

[doc-guide.md](../doc-guide.md)

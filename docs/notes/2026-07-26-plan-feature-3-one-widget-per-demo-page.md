# Feature 3 One Primary Widget Per Demo Page

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Context

[Feature 3 Widget Gallery](../features/feature-3-widget-gallery.md) defines a
**demo page pattern**: title, description, upstream doc link, and a widget area
for each visual-index entry.

Design decision 5 asks how many showcased widgets belong on one demo page. This
note compares options, records the agreed **starting point** for Feature 3, and
leaves room to extend later without reworking the gallery shell.

Related: the sample palette (decision 3) already offers a **multi-widget** screen
for inspect practice — see
[2026-07-26-plan-feature-3-sample-palette-menu-choice.md](./2026-07-26-plan-feature-3-sample-palette-menu-choice.md).

# Options

## Option A — One primary widget per demo page

Each gallery page focuses on a **single visual-index widget type**. Supporting
widgets (labels, boxes, frames, buttons that launch dialogs) are allowed only to
present or operate the primary type.

### Benefits

| Benefit | Detail |
|---------|--------|
| Simple UI | One control to study; minimal visual noise for designers and learners |
| Clear doc mapping | Page title, sidebar entry, and upstream class URL align one-to-one |
| Easy inspect | **View → Inspect widget** targets an obvious primary control |
| Fast to implement | Small demo builders; fits the initial 14-demo Feature 3 scope |
| Good starting point | Establishes the demo page pattern and registry before richer pages |

### Trade-offs

Does not show how multiple instances or mixed controls crowd a layout. That
composition story is deferred to Option B, the sample palette, or container demos
that still name one **primary** type.

## Option B — Two or three demo widgets per page

Each page deliberately shows **two or three instances** of the primary type, or
the primary type plus closely related variants (for example two `GtkLabel` rows
with different alignment, or several `GtkButton` styles).

### Benefits

| Benefit | Detail |
|---------|--------|
| UI density teaching | Shows how repeated or grouped controls affect busy-ness and spacing |
| Reusable modules | Shared layout helpers and demo builder functions across pages |
| Richer examples | Closer to real forms and toolbars without a full application screen |
| Composition practice | Exercises container properties while staying on one gallery entry |

### Trade-offs

Harder pick-mode targets (“which widget am I inspecting?”). More code per demo
and more design choices per page before the gallery framework is proven. Better
suited to a **follow-on wave** after Option A is stable.

# Decision

**Start with Option A for Feature 3.** Each demo page has **one primary widget
type** matching the visual-index entry; supporting widgets are incidental chrome
only.

Option B remains a **documented extension**: later demos or stories may add
multi-instance pages using shared modules in `demo-page` or category units, without
changing the one-type-per-sidebar-entry navigation model.

The sample palette continues to satisfy multi-widget inspect and density exploration
outside the per-widget gallery pages.

# Rules (Feature 3)

## Primary widget

| Rule | Detail |
|------|--------|
| Sidebar label | GType name of the primary type (visual-index rule) |
| Widget area | One primary widget instance unless Option B is adopted for that demo in a later wave |
| Supporting widgets | Labels, `GtkBox`, `GtkFrame`, dialog launch buttons — not second catalog entries |
| Inspect | Primary widget should be easy to identify when pick mode is on |

## Container demos

`GtkBox`, `GtkGrid`, `GtkFrame`, and `GtkNotebook` demos may contain child
widgets, but the **primary type under inspection** is still the container — children
illustrate layout, not separate gallery entries on the same page.

## Windows demos

Dialog demos use a primary type (`GtkAboutDialog`, `GtkMessageDialog`) opened from
a supporting button; the page itself is not a second widget catalog.

## Extension to Option B (later)

When adding multi-widget pages:

1. Keep **one sidebar entry** per visual-index widget; density is a presentation
   choice on that entry’s page.

2. Extract repeated layout into `demo-page` or category helpers (for example
   `gallery_demo_page_add_variant_row()`).

3. Document on the page which instance is the “primary” pick target if ambiguous.

4. Prefer Option B for types where spacing and repetition matter (`GtkLabel`,
   `GtkButton`, list rows) — not for every catalog entry at once.

# Out of scope for this decision

1. Full application screens or multi-page flows — not single gallery demos.

2. Merging multiple visual-index entries onto one sidebar row.

3. Replacing the sample palette with multi-widget gallery pages.

# References

[feature-3-widget-gallery.md](../features/feature-3-widget-gallery.md)

[2026-07-26-plan-feature-3-visual-index-source-of-truth.md](./2026-07-26-plan-feature-3-visual-index-source-of-truth.md)

[2026-07-26-plan-feature-3-sample-palette-menu-choice.md](./2026-07-26-plan-feature-3-sample-palette-menu-choice.md)

[doc-guide.md](../doc-guide.md)

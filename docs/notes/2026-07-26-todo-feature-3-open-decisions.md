# Feature 3 Open Decisions Follow Up

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Status

Closed — 2026-07-29. All three items below were resolved during Feature 3
implementation on branch `wm/feature-3`. See [Resolution summary](#resolution-summary).

# Context

[Feature 3 Widget Gallery](../features/feature-3-widget-gallery.md) design
decisions 1–6 are resolved in dated plan notes under `docs/notes/`. Three items
were open before implementation; this **todo** note captured options and
follow-up questions until each was closed at delivery.

Resolved design decisions for reference:

| # | Topic | Note |
|---|-------|------|
| 1 | Visual index taxonomy | [2026-07-26-plan-feature-3-visual-index-source-of-truth.md](./2026-07-26-plan-feature-3-visual-index-source-of-truth.md) |
| 2 | Framework first | [2026-07-26-plan-feature-3-framework-first-catalog-later.md](./2026-07-26-plan-feature-3-framework-first-catalog-later.md) |
| 3 | Sample vs gallery menu | [2026-07-26-plan-feature-3-sample-palette-menu-choice.md](./2026-07-26-plan-feature-3-sample-palette-menu-choice.md) |
| 4 | Reuse introspection | [2026-07-26-plan-feature-3-reuse-introspection.md](./2026-07-26-plan-feature-3-reuse-introspection.md) |
| 5 | One widget per page | [2026-07-26-plan-feature-3-one-widget-per-demo-page.md](./2026-07-26-plan-feature-3-one-widget-per-demo-page.md) |
| 6 | Modal window demos | [2026-07-26-plan-feature-3-modal-dialogs-window-types.md](./2026-07-26-plan-feature-3-modal-dialogs-window-types.md) |

Resolved at delivery (formerly open in this note):

| # | Topic | Resolution |
|---|-------|------------|
| 7 | Window title | Static **GTK Widget Demo** (`window-shell.c`) |
| 8 | Sidebar widget | `GtkListBox` with unselectable category header rows (`gallery-shell.c`) |
| 9 | Implementation stories | Feature spec only; no `docs/stories/` entries |

# Open decision 1 — Window title

## Question

Should the main window title stay fixed or reflect the active gallery demo?

## Options

### Static title — **GTK Widget Demo**

| Benefit | Detail |
|---------|--------|
| Consistency | Matches Feature 1 and Feature 2 today |
| Simplicity | No title updates when switching demos or content modes |
| Platform norms | Many demo and inspector apps use a stable app name |

### Dynamic title — include active demo

Examples: `GTK Widget Demo — GtkLabel`, or `GtkLabel · GTK Widget Demo`.

| Benefit | Detail |
|---------|--------|
| Context | User sees which demo is active without glancing at the sidebar |
| Window lists | Task switcher and screenshot filenames are self-describing |
| Debugging | Support screenshots and bug reports that name the demo |

### Hybrid

Static title for **Sample palette** mode; dynamic suffix only in **Widget gallery**
mode.

| Benefit | Detail |
|---------|--------|
| Balance | App identity preserved; gallery browsing gains context |
| Cost | Slightly more state wiring in `window-shell.c` |

## Resolution

**Static title — GTK Widget Demo.** `gtk_window_set_title()` in `window-shell.c`
sets a fixed title on startup. The title does not change when switching demos or
content modes. Matches the suggested default in the resolution order below.

Dynamic or hybrid titles remain a follow-on UX refinement if user feedback
favours more context in the window list or task switcher.

**Status:** resolved — static title at delivery (2026-07-29).

# Open decision 2 — Sidebar widget choice

## Question

Which GTK widget implements category + demo navigation in `gallery-shell`?

## Options

### `GtkListBox` (flat or grouped rows)

| Benefit | Detail |
|---------|--------|
| Simplicity | Straightforward for ~14 demos and five category headings |
| Accessibility | Familiar list pattern; easy keyboard navigation |
| Fit | Matches “pick a demo from a list” without tree chrome |

Grouped sections can use separators, labels, or unselectable header rows.

### Nested list — category `GtkListBox` + demo `GtkListBox`

| Benefit | Detail |
|---------|--------|
| Clear hierarchy | Category selection filters or expands demo list |
| Scale | Avoids one very long list as catalog grows |

### `GtkColumnView` or `GtkTreeView`

| Benefit | Detail |
|---------|--------|
| Structure | Explicit parent/child category → demo rows |
| Scale | Comfortable for dozens of entries and future metadata columns |

| Trade-off | Detail |
|-----------|--------|
| Complexity | More model and selection code for Feature 3’s first pass |

## Resolution

**`GtkListBox` with category headers.** `gallery-shell.c` builds one flat
`GtkListBox`: unselectable header rows per visual-index category (CSS class
`heading`), then selectable demo rows indented under each header. Demo selection
drives a `GtkStack` of demo pages. No separate plan note was added; the
implementation is the record.

Revisit nested list or tree widgets if the catalog grows large enough that a
single flat list becomes hard to scan.

**Status:** resolved — `GtkListBox` with category headers at delivery (2026-07-29).

# Open decision 3 — Implementation stories

## Question

Split Feature 3 into stories under `docs/stories/` before coding?

[doc-guide.md](../doc-guide.md) recommends stories when breaking a feature into
buildable components. The `docs/stories/` directory is planned but not yet used
in this repository.

## Options

### Write stories before implementation

Example story topics:

- `gallery-shell` + content mode wiring in `window-shell`

- `demo-registry` + `demo-page`

- Category demo units (possibly one story per category or Display+Buttons first)

- `test/gallery/` and README

| Benefit | Detail |
|---------|--------|
| Reviewable slices | Smaller PRs and clearer acceptance per story |
| Parallel work | Contributors can take one category unit at a time |
| Traceability | Links feature acceptance criteria to deliverables |

### Implement from feature spec only (no stories yet)

| Benefit | Detail |
|---------|--------|
| Speed | One less documentation pass before first code |
| Fit | Feature 3 is already detailed with notes for decisions |

| Trade-off | Detail |
|-----------|--------|
| Risk | Single large change set if not disciplined about incremental commits |

### Minimal stories — framework only

One epic plus stories for registry/shell and “initial demo set” without per-category
story files.

| Benefit | Detail |
|---------|--------|
| Balance | Documents the critical path without N story files for N widgets |

## Resolution

**Implement from feature spec only (no stories yet).** Feature 3 shipped from
[feature-3-widget-gallery.md](../features/feature-3-widget-gallery.md) and the
dated plan notes without creating `docs/stories/` entries. Work landed on branch
`wm/feature-3` with incremental commits rather than story-scoped PRs.

Use stories for the next large feature or when multiple contributors need
parallel, reviewable slices; establish the story template from
[doc-guide.md](../doc-guide.md) on first use.

**Status:** resolved — feature spec only at delivery (2026-07-29).

# Resolution summary

All three formerly open decisions were closed during Feature 3 delivery
(2026-07-29):

1. **Window title** — static **GTK Widget Demo** (default suggested before merge).

2. **Sidebar widget** — `GtkListBox` with unselectable category header rows and
   selectable demo rows.

3. **Stories** — no `docs/stories/` split; implementation followed the feature
   spec and plan notes.

Follow-on refinements (dynamic title, tree sidebar, story files for catalog
expansion) are optional and not blockers for Feature 3 acceptance.

Delivery summary:
[2026-07-29-coding-feature-3-widget-gallery.md](./2026-07-29-coding-feature-3-widget-gallery.md).

# References

[feature-3-widget-gallery.md](../features/feature-3-widget-gallery.md)

[2026-07-29-coding-feature-3-widget-gallery.md](./2026-07-29-coding-feature-3-widget-gallery.md)

[doc-guide.md](../doc-guide.md)

[c-code-standard.md](../c-code-standard.md)

# Feature 3 Reuse Introspection

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Context

[Feature 3 Widget Gallery](../features/feature-3-widget-gallery.md) adds
navigable widget demos. [Feature 2](../features/feature-2-gobject-introspection.md)
delivered a read-only **introspection pane** and **View → Inspect widget** pick
mode using the `introspection` code group (`type-ancestry`, `property-list`,
`signal-list`, `inspector-pane`).

Design decision 4 asks whether the gallery needs its own type browser or can
reuse Feature 2. This note records the agreed resolution.

Related: content mode switching is in
[2026-07-26-plan-feature-3-sample-palette-menu-choice.md](./2026-07-26-plan-feature-3-sample-palette-menu-choice.md).

# Decision

**Reuse the Feature 2 introspection pane and algorithms unchanged.**

- Keep the existing **View → Inspect widget** menu item and pick-mode behaviour
  (crosshair cursor, Escape to exit, menu toggle stays in sync).

- Keep the side **introspection pane** populated by the same units: ancestry,
  properties, and signals via upstream GObject APIs — no gallery-specific
  metadata path.

- Do **not** add a second type browser, per-demo inspect panels, or duplicate
  introspection logic under `src/gallery/`.

Gallery and sample-palette widgets are inspect targets only; Feature 3 work wires
content modes and pick roots, not new introspection algorithms.

# Rationale

| Benefit                        | Detail |
| ------------------------------ | --- |
| Single teaching surface        | One inspect workflow for shell, palette, and every gallery demo |
| No duplication                 | `type-ancestry`, `property-list`, and `signal-list` stay the single source |
| Feature 2 investment preserved | Pick mode, `GWeakRef` lifetime, and claimed-click behaviour carry forward |
| Aligns with plan Phase B       | [2026-07-22-plan-gobject-type-exploration.md](./2026-07-22-plan-gobject-type-exploration.md) placed introspection on the main window globally |

Alternatives rejected:

1. **Per-demo type facts panels** — deferred to plan Phase C; not part of Feature 3.

2. **Gallery-specific inspect pane** — duplicates Feature 2 and splits the user model.

3. **Replace menu label or add a second inspect action** — unnecessary; one
   **View → Inspect widget** entry covers all content modes.

# Rules

## Menu and pick mode

| Item      | Detail |
| --------- | --- |
| Menu      | **View → Inspect widget** unchanged from Feature 2 |
| Action    | Existing window action (for example `win.inspect`) |
| Escape    | Exits pick mode; syncs menu state via existing handler |
| Pick mode | Same `GtkGestureClick` capture-phase and crosshair cursor behaviour |

No new View menu entries for introspection in Feature 3.

## Introspection pane

| Item      | Detail |
| --------- | --- |
| Placement | End child of horizontal `GtkPaned` (Feature 2 layout) |
| Display   | Read-only monospace text: type, ancestry, interfaces, properties, signals |
| API       | `introspection_inspector_pane_*` from `include/introspection.h` |
| Editing   | Property values remain read-only (Feature 2 scope) |

## Algorithms (unchanged units)

| Unit             | Role |
| ---------------- | --- |
| `type-ancestry`  | GType name, parent chain, interfaces |
| `property-list`  | `GParamSpec` metadata and formatted values |
| `signal-list`    | Signal names and parameter counts |
| `inspector-pane` | UI assembly, pick mode, selection lifetime (`GWeakRef`) |

Gallery demos must not reimplement these queries locally for display in the demo
page chrome.

## Pick root and content modes

The pick root remains the main window region that contains the menu bar and
active content (gallery or sample palette), as wired in `window-shell.c`.

When the user switches **View → Widget gallery** / **Sample palette**, pick mode
may remain enabled; introspection must target widgets that exist in the active
mode. No gallery code changes the introspection algorithms — only ensures the
pick root covers the visible content.

## Code layout

| Path                      | Feature 3 change |
| ------------------------- | --- |
| `src/introspection/*`     | **No algorithm changes** unless a gallery-exposed bug is found |
| `src/gallery/*`           | **No** introspection units |
| `src/main/window-shell.c` | Retain inspector pane wiring; update pick root when content mode switches if needed |

## Tests

Existing tests under `test/introspection/` remain authoritative for ancestry,
property, and signal listing. Feature 3 adds `test/gallery/` only for registry
and demo builders — not parallel introspection tests per widget.

# Out of scope for this decision

1. Live property editing from the pane.

2. Signal handler connection for debug logging.

3. Per-demo curated type panels (plan Phase C).

4. GTK Inspector duplication (documented in README; external tool).

# References

[feature-3-widget-gallery.md](../features/feature-3-widget-gallery.md)

[feature-2-gobject-introspection.md](../features/feature-2-gobject-introspection.md)

[2026-07-26-plan-feature-3-sample-palette-menu-choice.md](./2026-07-26-plan-feature-3-sample-palette-menu-choice.md)

[2026-07-22-plan-gobject-type-exploration.md](./2026-07-22-plan-gobject-type-exploration.md)

[doc-guide.md](../doc-guide.md)

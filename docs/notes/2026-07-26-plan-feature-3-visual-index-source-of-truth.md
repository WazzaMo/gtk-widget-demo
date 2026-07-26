# Feature 3 Visual Index Source of Truth

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Context

[Feature 3 Widget Gallery](../features/feature-3-widget-gallery.md) introduces
navigable widget demos aligned with the upstream
[GTK4 Widget Gallery](https://docs.gtk.org/gtk4/visual_index.html).

Design decision 1 in that feature spec asks how the in-app gallery names,
groups, and orders demos relative to GTK documentation. This note records the
resolved decision so the feature document stays concise.

# Decision

Use the **GTK4 visual index** as the single source of truth for gallery
taxonomy. The app mirrors upstream structure rather than inventing parallel
categories or naming schemes.

# Rationale

The project README and [AGENTS.md](../../AGENTS.md) already describe the
program as an implementation of the GTK4 Widget Gallery. Feature 2 introspection
surfaces real GType names. Matching the visual index keeps navigation, doc
links, and inspect output on the same vocabulary a developer sees on
[docs.gtk.org](https://docs.gtk.org/gtk4/visual_index.html).

Alternatives such as app-specific categories, a flat global widget list, or
alphabetical ordering were rejected because they diverge from official docs and
add maintenance without teaching value.

# Rules

## Categories

The gallery has exactly five sections, matching the visual index:

| Visual index section | Registry slug (internal) |
|----------------------|--------------------------|
| Display widgets      | `display`                |
| Buttons              | `buttons`                |
| Entries              | `entries`                |
| Containers           | `containers`             |
| Windows              | `windows`                |

Sidebar and other user-visible labels use the **full visual index section
title** (for example **Display widgets**, not **Display**). Internal code and
tests may use the slug column.

## Demo titles and documentation links

Each demo entry is labelled with the **GType name** shown in the visual index
(for example `GtkLabel`, not “Label demo”). Each demo page links to the
matching upstream class page URL from the visual index.

Do not rename widgets to “fix” upstream grouping. When the visual index links
unusually (for example `GtkRadioButton` referencing `GtkCheckButton`
documentation), follow the **visual index entry name and URL**, not a
reconstructed taxonomy.

## Order within a category

Among demos that are implemented, list entries in the **same order they appear
in the visual index** for that section. When new demos are added, insert them at
the visual-index position without reordering unrelated entries.

Alphabetical ordering within a category is out of scope for this decision.

## Scope of the decision

This decision defines **how** widgets are named, grouped, ordered, and linked.
It does **not** require every visual-index widget to ship in Feature 3. The
initial demo set and follow-on catalog are scoped in
[2026-07-26-plan-feature-3-framework-first-catalog-later.md](./2026-07-26-plan-feature-3-framework-first-catalog-later.md)
(design decision 2).

## GTK version drift

If the visual index gains widgets or sections in a future GTK release, add demos
under the existing upstream structure. Restructure categories only when upstream
does. Registry and category units should make adding entries straightforward
without reworking the shell.

# Implementation hints

The demo registry should store, at minimum:

- category slug and display title;

- demo id, GType display title, upstream doc URL;

- demo builder callback.

Gallery shell navigation is populated from the registry so category and demo
labels stay consistent with these rules.

# References

[feature-3-widget-gallery.md](../features/feature-3-widget-gallery.md)

[GTK4 Widget Gallery — visual index](https://docs.gtk.org/gtk4/visual_index.html)

[doc-guide.md](../doc-guide.md)

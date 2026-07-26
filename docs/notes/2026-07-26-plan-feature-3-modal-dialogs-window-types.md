# Feature 3 Modal Dialogs For Window Types

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Context

[Feature 3 Widget Gallery](../features/feature-3-widget-gallery.md) includes a
**Windows** category from the
[GTK4 visual index](https://docs.gtk.org/gtk4/visual_index.html): top-level
windows, dialogs, choosers, and assistants.

Design decision 6 asks how to demo types that are themselves transient windows
rather than embeddable controls. This note records the agreed approach.

Related: demo page scope (one primary widget) is in
[2026-07-26-plan-feature-3-one-widget-per-demo-page.md](./2026-07-26-plan-feature-3-one-widget-per-demo-page.md).

# Decision

**Show window and dialog types modally from the demo page.**

Each Windows-category gallery page stays in the main content stack. The primary
widget (`GtkAboutDialog`, `GtkMessageDialog`, and later choosers and assistants)
is presented **on demand** — typically via a **Show …** button — as a **modal**
transient window parented to the main application window.

Do **not** embed real top-level dialogs inside the gallery `GtkStack` as if they
were ordinary child widgets.

# Rationale

| Benefit | Detail |
|---------|--------|
| Matches GTK usage | Dialogs and choosers are designed to be transient for a parent window |
| Honest demos | Users see real modal presentation, focus, and dismiss behaviour |
| Stable gallery shell | Content area layout stays a single demo page; no nested window chrome |
| Inspect still works | Pick mode targets the demo page button and chrome; opened dialog can be inspected while visible |
| Scales to follow-on widgets | File/font/color choosers reuse the same launch pattern in later waves |

# Alternatives considered

## Embed dialog widget in the demo page

Attempt to pack dialog-like UI inline in the gallery content area.

**Rejected:** top-level types expect window semantics; inline embedding misrepresents
how applications use them and fights GTK4 window/dialog lifecycle.

## Documentation-only pages (link, no runnable dialog)

A page with upstream link but no **Show …** action.

**Rejected as default:** acceptable only when a modal launch is genuinely
impractical on the target platform. Feature 3 initial set (`GtkAboutDialog`,
`GtkMessageDialog`) must be runnable. Prefer modal launch for follow-on Windows
entries where feasible.

# Rules

## Demo page layout

| Element | Detail |
|---------|--------|
| Primary type | Named in title and sidebar (`GtkAboutDialog`, etc.) |
| Description | Short text on when the dialog is used |
| Upstream link | Class page on docs.gtk.org |
| Launch control | **Show about dialog**, **Show message dialog**, or equivalent `GtkButton` |
| Widget area | Page chrome plus launch button — not an embedded top-level window |

Supporting widgets on the page follow the one-primary-widget rule; the dialog
appears only after the user clicks launch.

## Modal presentation

| Rule | Detail |
|------|--------|
| Parent | Transient for `GtkApplicationWindow` (or active window) |
| Modality | Block interaction with parent while open where GTK API supports it |
| APIs | GTK4 patterns: `gtk_window_present`, dialog present helpers, or async dialog APIs as appropriate |
| Dismiss | User closes dialog normally; demo page remains in the stack |

Exact API choice per dialog type is implementation detail; behaviour must match
upstream GTK4 examples.

## Lifetime and shutdown

| Rule | Detail |
|------|--------|
| No zombies | Destroy or dismiss dialogs when closed; do not leak references |
| App exit | Closing main window while a dialog is open must not crash or warn |
| Demo switch | Switching gallery demos or content mode should not leave orphan dialogs |
| Pick mode | Launch buttons use claimed-click behaviour consistent with Feature 2 inspect mode |

## Feature 3 initial demos

| Demo | Launch behaviour |
|------|------------------|
| `GtkAboutDialog` | Button opens about dialog modally with sample app metadata |
| `GtkMessageDialog` | Button opens information or question dialog modally |

## Follow-on Windows category

Apply the same modal-launch pattern to `GtkFileChooserDialog`,
`GtkFontChooserDialog`, `GtkColorChooserDialog`, `GtkAssistant`, and similar
entries in later catalog waves unless platform constraints require a rare
documentation-only exception (document the reason in the demo page).

# Out of scope for this decision

1. Non-modal floating tool windows as gallery demos.

2. Multiple simultaneous dialogs from one demo page (one launch at a time is enough for Feature 3).

3. Custom dialog subclasses or GObject tutorial types.

# References

[feature-3-widget-gallery.md](../features/feature-3-widget-gallery.md)

[2026-07-26-plan-feature-3-one-widget-per-demo-page.md](./2026-07-26-plan-feature-3-one-widget-per-demo-page.md)

[2026-07-26-plan-feature-3-framework-first-catalog-later.md](./2026-07-26-plan-feature-3-framework-first-catalog-later.md)

[GTK4 Widget Gallery — visual index](https://docs.gtk.org/gtk4/visual_index.html)

[doc-guide.md](../doc-guide.md)

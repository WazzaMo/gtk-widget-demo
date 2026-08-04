# Feature 3 Framework First Catalog Later

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Context

[Feature 3 Widget Gallery](../features/feature-3-widget-gallery.md) introduces
the in-app widget gallery. The upstream
[GTK4 visual index](https://docs.gtk.org/gtk4/visual_index.html) lists dozens of
widgets across five categories.

Design decision 2 asks how much of that catalog Feature 3 should ship in one
milestone. This note records the resolved phasing approach so the feature
document stays concise.

Related: design decision 1 (visual index taxonomy) is in
[2026-07-26-plan-feature-3-visual-index-source-of-truth.md](./2026-07-26-plan-feature-3-visual-index-source-of-truth.md).

# Decision

**Framework first, full catalog later.**

Feature 3 delivers a navigable gallery **framework** plus a fixed **initial demo
set** (14 widgets). Remaining visual-index widgets are explicit follow-on work
added incrementally through the same registry and demo page pattern — not in a
single Feature 3 implementation pass.

# Rationale

| Concern       | Why phasing helps |
| ------------- | --- |
| Scope creep   | The full visual index is far larger than one reviewable feature |
| Time to value | Navigation, registry, and demo page pattern unlock all future demos |
| Teaching      | The initial set covers every category; gallery demos mirror palette widgets individually |
| Maintenance   | One registry API avoids rework when each new widget lands |
| Testing       | Smoke tests can target registry counts and demo builders. See below. |

Smoke tests can target registry counts and demo builders without driving the full UI for every widget.

Shipping the entire catalog in Feature 3 would delay the framework, duplicate
Feature 2’s ad hoc sample palette pattern, and mix infrastructure work with
many low-level widget demos that do not share code.

Alternatives rejected:

1. **All widgets in Feature 3** — too large; high risk of incomplete or shallow demos.

2. **No framework; only migrate sample palette** — fails the Widget Gallery vision and forces a second navigation rewrite.

3. **Curated subset with no registry** — each new widget would require shell changes; does not scale to the full visual index.

# What Feature 3 ships (framework)

The framework is the reusable gallery infrastructure:

| Component                   | Role |
| --------------------------- | --- |
| `gallery-shell`             | Category and demo navigation; active demo content area (`GtkStack` or equivalent) |
| `demo-registry`             | Categories, demo metadata, registration and lookup |
| `demo-page`                 | Shared page chrome: title, description, upstream doc link, content slot |
| Category demo units         | `display-demos`, `button-demos`, `entry-demos`, `container-demos`, `window-demos` |
| `window-shell` integration  | Content mode from **View → Widget gallery** / **Sample palette** (gallery default) |
| Tests under `test/gallery/` | Registry counts; non-NULL demo builder smoke tests |

Feature 3 acceptance is met when this framework works end-to-end with the
initial demo set below — not when every visual-index widget has a demo.

# Initial demo set (Feature 3)

Fourteen demos across five categories. Authoritative table and acceptance
wording remain in
[feature-3-widget-gallery.md](../features/feature-3-widget-gallery.md#initial-demo-set).

Summary:

| Category        | Count | Demos |
| --------------- | ----- | --- |
| Display widgets | 4     | `GtkLabel`, `GtkSpinner`, `GtkProgressBar`, `GtkScale` |
| Buttons         | 4     | `GtkButton`, `GtkCheckButton`, `GtkSwitch`, `GtkToggleButton` |
| Entries         | 2     | `GtkEntry`, `GtkSpinButton` |
| Containers      | 4     | `GtkBox`, `GtkGrid`, `GtkFrame`, `GtkNotebook` |
| Windows         | 2     | `GtkAboutDialog`, `GtkMessageDialog` |

These mirror the Feature 2 sample palette widgets as individual demos and add at
least one runnable example per visual-index section. The compact palette remains
available separately; see
[2026-07-26-plan-feature-3-sample-palette-menu-choice.md](./2026-07-26-plan-feature-3-sample-palette-menu-choice.md).

# Follow-on catalog (after Feature 3)

Add the widgets below in later features using the Feature 3 registry
and demo page pattern. Order within each category follows the visual index when
implemented (see the source-of-truth note).

## Display widgets

`GtkStatusbar`, `GtkLevelBar`, `GtkInfoBar`, `GtkScrollbar`, `GtkImage`,
`GtkPicture`, `GtkSeparator`, `GtkTextView`, `GtkGLArea`, `GtkDrawingArea`,
`GtkVideo`, `GtkMediaControls`, `GtkWindowControls`, `GtkPopoverMenuBar`,
`GtkCalendar`, `GtkEmojiChooser`, `GtkPopoverMenu`

## Buttons

`GtkLinkButton`, `GtkRadioButton`, `GtkMenuButton`, `GtkLockButton`,
`GtkVolumeButton`, `GtkComboBox`, `GtkComboBoxText`, `GtkDropDown`,
`GtkColorDialogButton`, `GtkFontDialogButton`, `GtkAppChooserButton`

## Entries

`GtkSearchEntry`, `GtkPasswordEntry`, `GtkEditableLabel`

## Containers

`GtkCenterBox`, `GtkScrolledWindow`, `GtkPaned`, `GtkExpander`,
`GtkSearchBar`, `GtkActionBar`, `GtkHeaderBar`, `GtkListBox`, `GtkFlowBox`,
`GtkTreeView`, `GtkIconView`, `GtkOverlay`, `GtkStack`, `GtkStackSwitcher`,
`GtkStackSidebar`, `GtkPopover`

## Windows

`GtkWindow`, `GtkDialog`, `GtkAssistant`, `GtkColorChooserDialog`,
`GtkFileChooserDialog`, `GtkFontChooserDialog`, `GtkAppChooserDialog`,
`GtkPageSetupUnixDialog`, `GtkPrintUnixDialog`, `GtkShortcutsWindow`

# How to extend after Feature 3

1. Implement a demo builder in the appropriate category unit (or a new sub-unit
   if the file grows large).

2. Register the demo in `demo-registry` with GType title, upstream URL, and
   builder callback.

3. Add or extend smoke tests in `test/gallery/` for the new entry.

4. No changes to `gallery-shell` navigation logic should be required for a
   standard new demo.

Batch follow-on work by category (for example “Display widgets wave 2”) or by
widget complexity (for example file chooser dialogs together) in later feature
specs and plan notes.

# References

[feature-3-widget-gallery.md](../features/feature-3-widget-gallery.md)

[2026-07-26-plan-feature-3-visual-index-source-of-truth.md](./2026-07-26-plan-feature-3-visual-index-source-of-truth.md)

[GTK4 Widget Gallery — visual index](https://docs.gtk.org/gtk4/visual_index.html)

[2026-07-26-plan-feature-3-sample-palette-menu-choice.md](./2026-07-26-plan-feature-3-sample-palette-menu-choice.md)

[doc-guide.md](../doc-guide.md)

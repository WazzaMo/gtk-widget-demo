# Feature 2 GObject Introspection

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Context

Feature 2 adds read-only GObject introspection to the GTK Widget Demo: a sample
widget palette, pick mode, a side introspection pane, unit tests, and README
documentation for the in-app workflow and GTK Inspector.

The feature spec is
[feature-2-gobject-introspection.md](../features/feature-2-gobject-introspection.md).
Planning background is in
[2026-07-22-plan-gobject-type-exploration.md](./2026-07-22-plan-gobject-type-exploration.md).

# Delivered

## Code layout

First code group under `src/` and `include/` per
[c-code-standard.md](../c-code-standard.md):

| Unit | Path | Role |
|------|------|------|
| type-ancestry | `src/introspection/type-ancestry.c` | GType name, ancestry chain, interfaces |
| property-list | `src/introspection/property-list.c` | Property metadata and read-only values |
| signal-list | `src/introspection/signal-list.c` | Signal names and parameter counts |
| inspector-pane | `src/introspection/inspector-pane.c` | Side pane UI, pick mode, object lifetime |

Umbrella header: `include/introspection.h`.

## Application

`src/main.c` composes the Feature 1 shell with:

- **View → Inspect widget** (stateful window action)
- horizontal `GtkPaned` (main content + introspection pane)
- sample palette: `GtkLabel`, `GtkButton`, `GtkEntry`, `GtkSwitch`,
  `GtkScale`, nested `GtkBox` + `GtkCheckButton`

Pick mode uses `gtk_widget_pick()` on the main `GtkBox` (menu bar and content).
The introspection pane holds the selected widget via `GWeakRef` and clears when
the widget is destroyed.

## Build and tests

`meson.build` links the introspection group into `gtk-widget-demo` and adds
`test-introspection` under `test/introspection/`.

Tests cover ancestry for `GObject` and `GtkLabel`, property count for
`GtkLabel`, and formatted instance properties containing `label`.

Verified with:

```bash
meson setup build
meson compile -C build
meson test -C build
./build/gtk-widget-demo
```

# Fixes during implementation

## GType helper macros

Initial code used non-existent macros `G_TYPE_IS_CLASS` and
`G_TYPE_IS_INSTANTIATED`. Replaced with `G_TYPE_IS_CLASSED`, which matches
GLib/GObject public API for classed types such as `GtkLabel`.

## GTK4 entry text API

`gtk_entry_set_text()` is not available in GTK4. Sample palette uses
`gtk_editable_set_text(GTK_EDITABLE(entry), …)` instead.

## Unit test expectations

`g_object_class_list_properties()` on `G_TYPE_OBJECT` returns zero properties;
only inherited types such as `GtkLabel` expose a non-empty list. The test was
narrowed to assert on `GTK_TYPE_LABEL` only.

`gtk_label_new()` returns a floating reference. The instance property test calls
`g_object_ref_sink()` before `g_object_unref()` to avoid a floating-object
warning and abort under GLib debug checks.

## Pick mode consumes clicks

Without claiming the click gesture, buttons and other controls still activated
while pick mode was on. `on_pick_pressed` now calls
`gtk_gesture_set_state(..., GTK_EVENT_SEQUENCE_CLAIMED)` so inspection wins
over normal widget activation.

# Fixes after initial delivery

## Escape exits pick mode

Pick mode could only be toggled off via **View → Inspect widget**. Added
`GtkEventControllerKey` on the pick root: **Escape** exits pick mode and syncs
the menu toggle via `g_action_change_state()` on `win.inspect`.

Documented in the feature spec, README, and application behaviour tables.

## Gtk-CRITICAL on controller removal

Runtime warnings appeared when toggling pick mode:

```
gtk_widget_remove_controller: assertion
'gtk_event_controller_get_widget (controller) == widget' failed
```

Cause: `remove_pick_controllers()` always called `gtk_widget_remove_controller`
even when controllers were not attached — for example when enabling pick mode
(remove-before-add), on startup with pick mode off, and when Escape cleared
pick mode through overlapping code paths.

Fix in `inspector-pane.c`:

1. `detach_controller_if_attached()` — remove only when
   `gtk_event_controller_get_widget()` matches the target widget.

2. `attach_controller_if_detached()` — avoid double-attach when toggling.

3. Escape handler uses `g_action_change_state()` so disabling pick mode goes
   through the same `inspect_change_state` path as the menu toggle.

# References

[feature-2-gobject-introspection.md](../features/feature-2-gobject-introspection.md)

[2026-07-22-plan-gobject-type-exploration.md](./2026-07-22-plan-gobject-type-exploration.md)

[c-code-standard.md](../c-code-standard.md)

[README.md](../../README.md)

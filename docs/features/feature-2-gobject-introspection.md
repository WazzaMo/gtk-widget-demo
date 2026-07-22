# Feature 2 GObject Introspection

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Status

**Planned** — not yet implemented.

This feature implements Phase A and Phase B of
[2026-07-22-plan-gobject-type-exploration.md](../notes/2026-07-22-plan-gobject-type-exploration.md).
When complete, update this section and add an [As built](#as-built) subsection
with implementation specifics.

# Overview

Feature 2 adds read-only exploration of GObject types to the GTK Widget Demo.
A developer can pick a widget in the running application and inspect its GType
name, inheritance chain, GObject properties (metadata and current values), and
signal names — using the same introspection APIs documented in upstream
[GObject](https://docs.gtk.org/gobject/) references.

The feature introduces the first code group under `src/` and `include/` per
[c-code-standard.md](../c-code-standard.md), wires a global introspection pane
into the Feature 1 shell, documents GTK Inspector as a complementary external
tool, and adds the project's first unit tests under `test/`.

It does not implement the Widget Gallery, live property editing, or custom
GObject type tutorials. Those belong in later features.

# Use cases

1. A developer runs `./build/gtk-widget-demo`, chooses **View → Inspect widget**,
   clicks a widget in the window (for example the menu bar or content area), and
   sees the widget's GType ancestry from the concrete type up to `GObject`.

2. A developer selects the same widget and reads a list of GObject properties
   with names, value types, flags, and read-only current values formatted for
   display.

3. A developer selects a widget and sees signal names (and basic metadata such
   as parameter count) defined on the widget's type, without connecting debug
   handlers that could alter application behaviour.

4. A developer reads [README.md](../../README.md) and learns how to use GTK
   Inspector (`GTK_DEBUG=interactive` or Control+Shift+I) alongside the
   in-app introspection pane for full widget-tree and CSS debugging.

5. A contributor adding widget gallery demos in a later feature reuses the
   `introspection` group to inspect demo widgets without duplicating
   introspection logic.

# Acceptance criteria

1. On a Linux system with GTK4 development libraries installed, `meson setup build`
   followed by `meson compile -C build` completes without errors, including the
   new `introspection` sources and test targets.

2. Running the built executable opens the Feature 1 window with an additional
   **View** menu (or equivalent) containing **Inspect widget** that toggles
   widget pick mode.

3. In pick mode, clicking a widget in the main window content updates a
   visible introspection pane with that widget's type information.

4. The introspection pane displays, at minimum:

   - the selected widget's GType name;

   - the inheritance chain from the concrete type to `GObject`;

   - interfaces implemented by the type, when present;

   - GObject properties with pspec metadata and read-only formatted values;

   - signal names with basic metadata (read-only listing; no handlers attached).

5. Property values are read-only in the UI; the feature does not expose live
   `g_object_set()` editing.

6. If the inspected widget is destroyed or replaced while the pane is open, the
   application does not crash or dereference a stale `GObject` pointer.

7. [README.md](../../README.md) documents:

   - GTK Inspector usage (`GTK_DEBUG=interactive`, keyboard shortcuts, link to
     [GTK running and debugging](https://docs.gtk.org/gtk4/running.html));

   - the in-app **View → Inspect widget** workflow.

8. Unit tests under `test/introspection/` pass and cover type ancestry and
   property listing for at least `GObject` and `GtkLabel` against the installed
   GTK version.

9. New source and header files follow [c-code-standard.md](../c-code-standard.md)
   and carry the project copyright notice.

# Technical acceptance criteria

## Build system

| Requirement | Detail |
|-------------|--------|
| Root build file | Extend `meson.build` to compile `introspection` group sources |
| GTK dependency | Continue using `dependency('gtk4', include_type: 'system')` |
| Warnings | `warning_level=3` on project code |
| Executable | Still one target (`gtk-widget-demo`); link introspection objects |
| Tests | Meson test target(s) for `test/introspection/` |

Expected contributor workflow on Linux:

```bash
meson setup build
meson compile -C build
meson test -C build
./build/gtk-widget-demo
```

## Code layout

The `introspection` group follows [c-code-standard.md](../c-code-standard.md).

| Path | Role |
|------|------|
| `include/introspection.h` | Group umbrella header |
| `include/introspection/type-ancestry.h` | Ancestry and interface queries |
| `include/introspection/property-list.h` | Property pspec and value formatting |
| `include/introspection/signal-list.h` | Signal metadata queries |
| `include/introspection/inspector-pane.h` | GTK UI pane and pick-mode integration |
| `src/introspection/type-ancestry.c` | Implementation |
| `src/introspection/property-list.c` | Implementation |
| `src/introspection/signal-list.c` | Implementation |
| `src/introspection/inspector-pane.c` | Implementation |

`src/main.c` remains the entry point. It should delegate introspection UI and
pick-mode wiring to the `introspection` group rather than growing with
introspection logic inline.

## GObject APIs

Implementation should use upstream introspection APIs rather than hard-coded
widget knowledge:

| Concern | Primary APIs | Reference |
|---------|--------------|-----------|
| Type name | `G_OBJECT_TYPE()`, `G_OBJECT_TYPE_NAME()` | [GObject.Object](https://docs.gtk.org/gobject/class.Object.html) |
| Ancestry | `g_type_parent()`, `g_type_is_a()` | [Type System Concepts](https://docs.gtk.org/gobject/concepts.html) |
| Type sizes | `g_type_query()` | [g_type_query](https://docs.gtk.org/gobject/func.type_query.html) |
| Interfaces | `g_type_interfaces()` | [Type System Concepts](https://docs.gtk.org/gobject/concepts.html) |
| Properties | `g_object_class_list_properties()`, `g_object_get()` | [Object.list_properties](https://docs.gtk.org/gobject/class_method.Object.list_properties.html) |
| Property values | `g_strdup_value_contents()` | [GObject index](https://docs.gtk.org/gobject/) |
| Signals | `g_signal_list_ids()`, `g_signal_query()` | [GSignalQuery](https://docs.gtk.org/gobject/struct.SignalQuery.html) |

## Application behaviour

| Requirement | Detail |
|-------------|--------|
| Shell | Extend Feature 1 `GtkApplication` window; preserve **File → Exit** |
| Introspection scope | Global pane on the main window (not per-demo pages) |
| Pick mode | **View → Inspect widget** enables picking widgets in the window |
| Pane placement | Side pane or split view; exact layout is an implementation choice |
| Property editing | Not supported; display only |
| Signal handlers | Not connected for exploration in this feature |
| Object lifetime | Weak references or equivalent when holding the selected widget |

## Documentation

| Requirement | Detail |
|-------------|--------|
| README | GTK Inspector section (environment variable, shortcuts, upstream link) |
| README | In-app inspect workflow |
| Copyright | New source files carry the project copyright notice |

## Tests

| Requirement | Detail |
|-------------|--------|
| Location | `test/introspection/` mirroring group name |
| Ancestry | Assert expected parent chain for `GtkLabel` (or similar) |
| Properties | Assert `g_object_class_list_properties()` returns non-empty for `GtkLabel` |
| Version drift | Tests query installed GTK via pkg-config; avoid brittle property-name lists |
| Runner | Invoked via `meson test -C build` |

# Design decisions

These resolve open questions in
[2026-07-22-plan-gobject-type-exploration.md](../notes/2026-07-22-plan-gobject-type-exploration.md).

1. **Global vs per-demo pane:** introspection lives on the main window so it
   works on Feature 1 widgets immediately and on all future gallery demos
   without duplication.

2. **Live property editing:** out of scope for Feature 2 and this feature spec;
   values are read-only.

3. **Custom GObject tutorial types:** deferred to a later feature; Feature 2
   inspects existing GTK/GObject types only.

# Out of scope

The following belong in later features or plan phases, not Feature 2:

1. Widget Gallery navigation or runnable widget examples from the
   [GTK4 visual index](https://docs.gtk.org/gtk4/visual_index.html).

2. Per-demo curated "type facts" panels (plan Phase C).

3. Live property editing via `g_object_set()` from the introspection UI.

4. Signal emission logging or temporary `g_signal_connect()` debug handlers.

5. Custom GObject type definitions (`G_DEFINE_FINAL_TYPE`, properties, signals)
   as in the [GObject Tutorial](https://docs.gtk.org/gobject/tutorial.html).

6. Command-line type dump tools (plan Option 5), unless used only inside tests.

7. Duplicating GTK Inspector capabilities (full widget tree, CSS editor,
   allocation overlays).

8. Cross-platform CI or Windows/macOS verification (manual Linux success is
   enough for this milestone).

# Risks

1. **Scope creep:** resist building a full property editor; stop at read-only
   metadata and values.

2. **GTK version drift:** tests should validate behaviour against the installed
   type system, not fixed property inventories.

3. **Object lifetime:** picking must not retain strong references to widgets
   that demos may destroy; follow
   [GWeakRef](https://docs.gtk.org/gobject/struct.WeakRef.html) patterns.

4. **Overlap with Inspector:** the in-app pane teaches GObject type metadata;
   README should steer users to Inspector for tree, CSS, and layout debugging.

# As built

Not yet implemented. When Feature 2 is complete, record specifics here (pane
layout, pick API chosen, test command output, any deviations from this spec).

# References

[README.md](../../README.md)

[c-code-standard.md](../c-code-standard.md)

[feature-1-base-application.md](./feature-1-base-application.md)

[2026-07-22-plan-gobject-type-exploration.md](../notes/2026-07-22-plan-gobject-type-exploration.md)

[GObject documentation index](https://docs.gtk.org/gobject/)

[Type System Concepts](https://docs.gtk.org/gobject/concepts.html)

[GObject.Object](https://docs.gtk.org/gobject/class.Object.html)

[g_type_query()](https://docs.gtk.org/gobject/func.type_query.html)

[Object.list_properties](https://docs.gtk.org/gobject/class_method.Object.list_properties.html)

[GParamSpec](https://docs.gtk.org/gobject/class.ParamSpec.html)

[GSignalQuery](https://docs.gtk.org/gobject/struct.SignalQuery.html)

[GTK4 — Running and debugging (GTK Inspector)](https://docs.gtk.org/gtk4/running.html)

[GTK4 Widget Gallery](https://docs.gtk.org/gtk4/visual_index.html)

# Widget Alignment Without Horizontal Scaling

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Context

During gallery and sample-palette review (2026-07-30), **GtkSwitch** controls
appeared horizontally stretched: the track grew wide and the thumb looked oval
instead of a round circle. The widget was being **scaled to fill extra horizontal
space**, not laid out at its natural size.

The same pattern can affect other compact controls when they are placed in
wide containers (demo page frames, grid cells, or stack children that receive
the full content width).

# Root cause

GTK widgets default to `halign = GTK_ALIGN_FILL`. When a parent allocates more
horizontal space than the widget’s natural width, a `FILL`-aligned child
**expands into that space**. For `GtkSwitch`, the control draws to fill the
allocation, which visually stretches the switch rather than centring or
left-aligning it at a fixed size.

This often appears when:

1. Demo content is the sole child of a **GtkFrame** inside a page that spans the
   main content area.

2. A **GtkGrid** cell is wider than the control (for example because another row
   or column, such as a heading with `hexpand`, widens the grid).

3. A parent **GtkStack** gives each child the full stack width even when the
   child’s content is small.

Alignment (`halign`) controls how a widget uses space **within its allocation**;
`hexpand` controls whether the widget **requests** extra horizontal space from
the parent. Compact controls need both considered together.

# Fix pattern

## Prevent stretching

For widgets that should keep a fixed aspect ratio or natural size (switches,
icon buttons, spin buttons, and similar), set `hexpand` to `FALSE` so the
parent does not grow them horizontally:

```c
gtk_widget_set_hexpand(widget, FALSE);
```

Avoid `halign = GTK_ALIGN_FILL` on these controls unless the widget is meant
to grow.

## Align within a wide parent

`halign` only positions a widget **inside the space its parent gives it**. If the
switch is the direct child of a `GtkFrame`, the frame often allocates only the
switch’s natural width. With no spare width, `GTK_ALIGN_CENTER` and
`GTK_ALIGN_START` look the same.

To centre (or end-align) a compact control in a wide demo area:

1. Insert a **full-width wrapper** (`GtkBox` with `halign = FILL` and
   `hexpand = TRUE`) between the frame and the control.

2. Set the control’s `halign` to `CENTER`, `START`, or `END` and keep
   `hexpand = FALSE`.

```c
content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
gtk_widget_set_halign(content_area, GTK_ALIGN_FILL);
gtk_widget_set_hexpand(content_area, TRUE);
gtk_widget_set_halign(switch_widget, GTK_ALIGN_CENTER);
gtk_widget_set_hexpand(switch_widget, FALSE);
gtk_box_append(GTK_BOX(content_area), switch_widget);
```

Do not set `halign` on the control **after** a shared layout helper unless that
helper preserves the value. `gallery_demo_page_new()` applies `hexpand = FALSE`
and only replaces a default `FILL` alignment; explicit `CENTER` / `START` / `END`
from demo builders is kept.

Vertical stacking uses the same idea when needed:

```c
gtk_widget_set_valign(widget, GTK_ALIGN_START);
gtk_widget_set_vexpand(widget, FALSE);
```

# Application in this project

| Location                     | Approach |
| ---------------------------- | --- |
| `src/gallery/demo-page.c`    | Wrap demo `content` in a full-width vertical `GtkBox`; force `hexpand = FALSE` on content; default `halign` to `CENTER` only when still `FILL` |
| `src/gallery/button-demos.c` | `GtkSwitch` demo sets `halign = CENTER` and `hexpand = FALSE` |
| `src/main/sample-palette.c`  | Set `halign` and `hexpand` on the palette `GtkSwitch` so the grid cell does not stretch it |

Gallery demos inherit the demo-page behaviour automatically. Individual demo
builders do not need to repeat the fix unless they introduce **nested** layouts
that expand again (for example a horizontal `GtkBox` with `hexpand` on the
switch).

# Guidance for new demos

When adding gallery or palette widgets:

1. **Prefer natural size** for controls whose GTK drawing assumes fixed
   proportions (`GtkSwitch`, small buttons used as icons, check buttons without
   long labels, spin buttons, etc.).

2. **Allow fill** for widgets that are designed to use available width
   (`GtkEntry`, `GtkScale`, `GtkProgressBar`, multi-line labels with wrap).

3. **Apply at the layout boundary** — set alignment on the widget that sits
   directly in the expanding container, or on a wrapper box if several controls
   share one frame.

4. **Verify visually** in both **Widget gallery** and **Sample palette** modes;
   wide main content makes stretch bugs obvious.

Alternative for toolbars or settings rows: place a spacer widget (for example an
empty label with `hexpand = TRUE`) before a switch that should sit at the
trailing edge, instead of stretching the switch itself.

# References

[Gtk.Widget:halign](https://docs.gtk.org/gtk4/property.Widget.halign.html)

[Gtk.Widget:hexpand](https://docs.gtk.org/gtk4/property.Widget.hexpand.html)

[GtkSwitch](https://docs.gtk.org/gtk4/class.Switch.html)

[c-code-standard.md](../c-code-standard.md)

[feature-3-widget-gallery.md](../features/feature-3-widget-gallery.md)

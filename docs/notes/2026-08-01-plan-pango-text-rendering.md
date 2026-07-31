# Pango And GTK Text Rendering

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Context

Follow-on gallery work adds text-heavy widgets — notably **GtkTextView** in
[feature-4-widget-gallery-catalog-wave-1.md](../features/feature-4-widget-gallery-catalog-wave-1.md)
and editable variants such as **GtkEditableLabel**. Even earlier demos already
use text: **GtkLabel**, **GtkEntry**, progress labels, and inspector pane
output.

GTK does not lay out or render text itself. That work is delegated to
**Pango**, the library GTK uses for internationalized text layout and font
handling. Understanding where Pango sits in the stack helps when choosing demo
APIs and when debugging font or layout behaviour.

# What Pango is

From the GTK architecture overview:

> Pango is a library for laying out and rendering of text, with an emphasis on
> internationalization. Pango can be used anywhere that text layout is needed,
> though most of the work on Pango so far has been done in the context of the
> GTK widget toolkit. **Pango forms the core of text and font handling for GTK.**

Source: [Pango — GTK architecture](https://www.gtk.org/docs/architecture/pango)

The name combines Greek *pan* (“all”) and Japanese *go* (“language”), reflecting
the focus on multilingual text.

# Relevant capabilities

| Area            | Detail |
| --------------- | --- |
| Layout engine   | Modular core; font backends vary by platform (FreeType/fontconfig on Linux, native fonts on Windows and macOS) |
| High-level API  | `PangoLayout` — lay out whole blocks of text |
| Complex scripts | HarfBuzz integration on all platforms |
| GTK integration | Rendering through **Cairo** in typical GTK4 apps |
| Markup          | [Pango markup](https://docs.gtk.org/Pango/pango_markup.html) for styled spans (bold, italic, size) in some widgets |

This project builds against **GTK4** via Meson (`dependency('gtk4')`). Pango is
pulled in as part of the GTK stack; a separate Pango dependency in
`meson.build` is not required for standard widget demos.

# Implications for GTK Widget Demo

## Widget demos usually stay at the GTK layer

Gallery demos should prefer **GTK widget APIs** unless the teaching goal is
explicitly Pango or low-level layout:

| Widget / area                       | Typical API                                 | Pango involvement |
| ----------------------------------- | ------------------------------------------- | --- |
| `GtkLabel`                          | `gtk_label_new()`, `gtk_label_set_markup()` | Markup parsed to Pango attributes internally |
| `GtkEntry`, search/password entries | `gtk_editable_set_text()`                   | Single-line layout via GTK → Pango |
| `GtkTextView`                       | `GtkTextBuffer`, tags, margins              | Multi-line layout and rendering via Pango |
| Inspector pane                      | `GtkTextView` monospace display             | Same stack; no direct Pango calls in app code today |

Demos remain **read-only teaching examples** per Feature 3 scope. Showing
Pango markup in a **GtkLabel** or styled spans in **GtkTextView** is in scope
when it illustrates common app patterns; implementing custom `PangoLayout`
drawing belongs in later work (for example **GtkDrawingArea** demos).

## Internationalization

Pango’s emphasis on i18n matters if demos use:

- mixed-direction text (RTL scripts);
- composed characters or complex shaping;
- translated demo strings loaded at runtime.

The initial gallery uses fixed English strings. If demos later load strings from
gettext or user input, layout correctness depends on Pango + fontconfig (Linux)
without additional project code — but **test with non-ASCII sample text** when
adding `GtkTextView` or editable demos to catch font fallback issues early.

## Feature 4 open decisions

This note informs wave 1 choices in
[feature-4-widget-gallery-catalog-wave-1.md](../features/feature-4-widget-gallery-catalog-wave-1.md):

1. **GtkTextView** — a short plain-text buffer is enough for a minimal demo;
   optional `GtkTextTag` or Pango markup in the buffer can show rich text without
   calling Pango C API directly.

2. **GtkLabel vs GtkTextView** — labels suit single-line static or markup text;
   `GtkTextView` suits multi-line editable or selectable content. Both ultimately
   use Pango.

3. **No new build dependency** — stay on GTK4 public APIs unless a future feature
   explicitly documents direct Pango/Cairo usage (DrawingArea, custom paint).

# Out of scope for this note

1. Bundling fonts or custom `PangoFontDescription` tutorials.

2. Direct `pango_*` calls in gallery demo code for Feature 4.

3. HarfBuzz, Cairo, or Fontconfig architecture notes (separate topics; see GTK
   architecture docs when needed).

# References

[Pango — GTK architecture](https://www.gtk.org/docs/architecture/pango)

[Pango API reference](https://docs.gtk.org/Pango/)

[Pango markup format](https://docs.gtk.org/Pango/pango_markup.html)

[feature-4-widget-gallery-catalog-wave-1.md](../features/feature-4-widget-gallery-catalog-wave-1.md)

[feature-3-widget-gallery.md](../features/feature-3-widget-gallery.md)

[GTK4 Widget Gallery — visual index](https://docs.gtk.org/gtk4/visual_index.html)

[GtkTextView](https://docs.gtk.org/gtk4/class.TextView.html)

[GtkLabel](https://docs.gtk.org/gtk4/class.Label.html)

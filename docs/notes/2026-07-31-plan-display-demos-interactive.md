# Display Demos Interactive Controls

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Context

The **Display widgets** category in `src/gallery/display-demos.c` ships four
demos: `GtkLabel`, `GtkSpinner`, `GtkProgressBar`, and `GtkScale`. Three of
these are largely **static on load**:

- **`GtkSpinner`** — created and `gtk_spinner_start()` called immediately; no
  way to stop or restart.
- **`GtkProgressBar`** — fixed fraction `0.65`; no user-driven updates.
- **`GtkScale`** — slider at `50.0` on range `0–100`; value changes visually
  but nothing reflects the numeric output.
- **`GtkLabel`** — static text; appropriate for a label demo; no change proposed.

[Feature 3](../features/feature-3-widget-gallery.md) allows interaction when it is
inherent to the widget (buttons, switches, scales). The display demos should
exercise the **APIs and signals** a real application would use, not only show a
frozen snapshot. The button demos already follow this pattern — for example
`GtkButton` with click feedback in `src/gallery/button-demos.c`.

Supporting controls (buttons, value labels) remain **incidental chrome** per
[2026-07-26-plan-feature-3-one-widget-per-demo-page.md](./2026-07-26-plan-feature-3-one-widget-per-demo-page.md).
Each page still has one primary widget; the sidebar entry and inspect target stay
the spinner, progress bar, or scale itself.

# Proposed behaviour

## GtkSpinner — start and stop

Replace “always spinning on open” with explicit control over spinner lifecycle,
matching typical use (start when work begins, stop when it finishes).

| Element             | Detail                                                                          |
|---------------------|---------------------------------------------------------------------------------|
| Primary widget      | `GtkSpinner` — not spinning on initial display                                  |
| Supporting controls | **Start spinner** and **Stop spinner** buttons                                  |
| Start               | `gtk_spinner_start(GTK_SPINNER(spinner))`                                       |
| Stop                | `gtk_spinner_stop(GTK_SPINNER(spinner))`                                        |
| Layout              | Vertical `GtkBox`: spinner centred, button row below (horizontal `GtkBox` with two buttons) |

Optional polish: disable **Start** while spinning and **Stop** while idle. Not
required for the first pass.

Teaches `gtk_spinner_start()` / `gtk_spinner_stop()` and the idea that the
spinner reflects application state rather than running unconditionally.

## GtkScale — live value readout

Show the current numeric value as the user drags the slider, wired to the range
value signal a real app would listen to.

| Element             | Detail                                                                          |
|---------------------|---------------------------------------------------------------------------------|
| Primary widget      | `GtkScale` — horizontal, range `0.0–100.0`, step `1.0`, initial value `50.0`   |
| Supporting widget   | `GtkLabel` showing the current value (for example `50` or `50.0`)               |
| Signal              | `value-changed` on the scale (`GtkRange`)                                       |
| Handler             | Read `gtk_range_get_value()`, format with `g_strdup_printf()` or similar, update label text |
| Layout              | Vertical `GtkBox`: scale (width ~240 as today), value label below or beside     |

Teaches `GtkRange:value-changed` and reading the scale value at runtime. Pick
mode should still target the scale easily; the readout label is secondary chrome.

## GtkProgressBar — increment and reset

Drive fraction updates from buttons instead of a fixed `0.65`, simulating task
progress in steps.

| Element             | Detail                                                                          |
|---------------------|---------------------------------------------------------------------------------|
| Primary widget      | `GtkProgressBar` — initial fraction `0.0`                                       |
| Supporting controls | **Add 10%** and **Reset** buttons                                               |
| Add 10%             | Read current fraction, add `0.1`, clamp to `1.0`, `gtk_progress_bar_set_fraction()` |
| Reset               | `gtk_progress_bar_set_fraction(progress, 0.0)`                                  |
| Layout              | Vertical `GtkBox`: progress bar (width ~240), button row below                  |

At `1.0`, **Add 10%** may no-op or stay enabled with no visible change; either
is acceptable. Clamping avoids fractions above `1.0`.

Pulse mode (`gtk_progress_bar_pulse()`) is out of scope for this note; fraction
mode is enough to demonstrate deterministic progress.

# Implementation sketch

All changes stay in `src/gallery/display-demos.c` unless a builder grows large
enough to split per [c-code-standard.md](../c-code-standard.md).

## Shared patterns

1. Return a vertical `GtkBox` as the demo root (same as `GtkButton` in
   `button-demos.c`).

2. Apply alignment for compact children per
   [2026-07-30-plan-widget-align-natural-size.md](./2026-07-30-plan-widget-align-natural-size.md):
   spinner and buttons use `hexpand = FALSE`; scale and progress bar may keep
   a modest `size_request` width while still allowing horizontal fill where
   appropriate.

3. Static click/toggle handlers at file scope; pass the target widget via
   `user_data` (spinner, progress bar, or label for scale).

4. Update demo **description** strings in `display_demos[]` to mention the
   interactive behaviour (one short sentence each).

## GtkLabel

No change — static text remains the right teaching example for labels.

# Acceptance criteria

1. **GtkSpinner** demo: user can start and stop the spinner with labelled buttons;
   spinner is idle when the page first appears.

2. **GtkScale** demo: moving the slider updates a visible numeric readout via
   `value-changed`.

3. **GtkProgressBar** demo: **Add 10%** increases fraction by `0.1` (capped at
   `1.0`); **Reset** sets fraction to `0.0`; initial fraction is `0.0`.

4. Pick mode still works: primary widgets remain identifiable; gallery demos do
   not require network access.

5. `meson test -C build` passes — existing `gallery-demo-builders` smoke test
   still receives non-NULL roots from all display builders.

6. Manual smoke: switch between display demos and content modes; no leaked state
   when leaving a demo page (handlers tied to page lifetime; no static globals).

# Risks

| Risk                       | Mitigation                                                                               |
|----------------------------|------------------------------------------------------------------------------------------|
| Pick mode vs button clicks | Same as button demos — claimed-click behaviour in Feature 2; verify Start/Stop and Add/Reset in inspect mode |
| Progress fraction drift    | Use `double` arithmetic and explicit clamp to `[0.0, 1.0]`                               |
| Scale label churn          | Update label only on `value-changed`; avoid formatting in draw handlers                  |
| Demo page scope creep      | Do not add second catalog widgets; keep one primary type per page                        |

# Out of scope

1. `GtkLabel` interactivity (editable label belongs under Entries follow-on).

2. Progress bar pulse/indeterminate mode.

3. Scale marks, digits, or vertical orientation variants.

4. Automated UI tests driving sliders or buttons (manual gallery verification
   is enough for this wave).

5. Changes to `demo-page.c`, registry, or gallery shell navigation.

# References

[feature-3-widget-gallery.md](../features/feature-3-widget-gallery.md)

[2026-07-26-plan-feature-3-one-widget-per-demo-page.md](./2026-07-26-plan-feature-3-one-widget-per-demo-page.md)

[2026-07-30-plan-widget-align-natural-size.md](./2026-07-30-plan-widget-align-natural-size.md)

[2026-07-29-coding-feature-3-widget-gallery.md](./2026-07-29-coding-feature-3-widget-gallery.md)

[src/gallery/display-demos.c](../../src/gallery/display-demos.c)

[src/gallery/button-demos.c](../../src/gallery/button-demos.c)

[GtkSpinner](https://docs.gtk.org/gtk4/class.Spinner.html)

[GtkProgressBar](https://docs.gtk.org/gtk4/class.ProgressBar.html)

[GtkScale](https://docs.gtk.org/gtk4/class.Scale.html)

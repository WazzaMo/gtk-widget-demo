# Display Demos Interactive And Pulse Mode

## Copyright

(c) Copyright 2026 onwards Warwick Molloy.
Contribution to this project is supported and contributors will be recognised.

# Context

Follow-on work after
[2026-07-29-coding-feature-3-widget-gallery.md](./2026-07-29-coding-feature-3-widget-gallery.md)
to make three **Display widgets** gallery demos interactive and to complete the
`GtkProgressBar` teaching example described in the Feature 3 initial demo table
(fraction and pulse modes).

Planning notes:

- [2026-07-31-plan-display-demos-interactive.md](./2026-07-31-plan-display-demos-interactive.md)
- [2026-07-31-plan-display-demos-pulse-and-spinner-state.md](./2026-07-31-plan-display-demos-pulse-and-spinner-state.md)

# Delivered

## Interactive display demos

`src/gallery/display-demos.c` — three demos extended with supporting chrome;
`GtkLabel` unchanged (static text remains appropriate).

| Demo             | Primary widget                            | Supporting chrome                       | APIs exercised |
| ---------------- | ----------------------------------------- | --------------------------------------- | --- |
| `GtkSpinner`     | `GtkSpinner` — idle on load               | **Start spinner** / **Stop spinner**    | `gtk_spinner_start()`, `gtk_spinner_stop()` |
| `GtkProgressBar` | `GtkProgressBar` — fraction `0.0` on load | **Add 10%** / **Reset** (fraction mode) | `gtk_progress_bar_set_fraction()`, clamped increment |
| `GtkScale`       | `GtkScale` — range `0–100`, initial `50`  | Value `GtkLabel` below slider           | `GtkRange:value-changed`, `gtk_range_get_value()` |

Each demo returns a vertical `GtkBox` root. Compact controls use
`hexpand = FALSE` per
[2026-07-30-plan-widget-align-natural-size.md](./2026-07-30-plan-widget-align-natural-size.md).
Demo **description** strings in `display_demos[]` were updated to mention the
new behaviour.

One primary widget per page is preserved; pick mode still targets the spinner,
progress bar, or scale.

## Progress bar pulse mode and spinner button sensitivity

Second pass on `src/gallery/display-demos.c` per the pulse-and-spinner-state
plan:

### GtkProgressBar — fraction and pulse on one page

| Element       | Detail |
| ------------- | --- |
| Mode selector | Mutually exclusive **Fraction** / **Pulse** toggle buttons; **Fraction** default |
| Fraction mode | **Add 10%** and **Reset** (unchanged from interactive pass) |
| Pulse mode    | **Start pulse** / **Stop pulse**; 100 ms `GTimeoutSource` calling `gtk_progress_bar_pulse()` |
| Mode switch   | Stops active pulse timer; resets fraction to `0.0`; shows/hides the matching action row |
| Lifetime      | `ProgressBarDemoData` on the demo root box via `g_object_set_data_full()`; timeout removed on stop, mode switch, and page destroy |

No second sidebar entry for pulse — fraction and pulse are behaviours of the
same GType on one demo page.

### GtkSpinner — button sensitivity

| State          | **Start spinner** | **Stop spinner** |
| -------------- | ----------------- | --- |
| Idle (initial) | enabled           | disabled |
| Spinning       | disabled          | enabled |

`SpinnerDemoData` (spinner + both buttons) is passed to click handlers via
`g_object_set_data_full()` on the demo root box.

## Application entry point

`src/main.c` — switched to `G_APPLICATION_HANDLES_COMMAND_LINE` with a
`command-line` handler that calls `g_application_activate()`. Ensures a single
activate path when the app is launched with arguments (for example from a
`.desktop` file).

# Build and tests

No new test executables. Existing gallery smoke tests still pass:

```bash
meson compile -C build
meson test -C build
```

| Test                    | Result |
| ----------------------- | --- |
| `gallery-demo-builders` | All display demo builders return non-NULL roots |
| `gallery-demo-registry` | Category and demo counts unchanged (14 demos, 5 categories) |

Manual verification: start/stop spinner; scale value readout; fraction Add/Reset;
pulse Start/Stop; mode switch while pulsing; leave demo page while pulsing (no
lingering timeout).

# References

[2026-07-29-coding-feature-3-widget-gallery.md](./2026-07-29-coding-feature-3-widget-gallery.md)

[2026-07-31-plan-display-demos-interactive.md](./2026-07-31-plan-display-demos-interactive.md)

[2026-07-31-plan-display-demos-pulse-and-spinner-state.md](./2026-07-31-plan-display-demos-pulse-and-spinner-state.md)

[2026-07-30-plan-widget-align-natural-size.md](./2026-07-30-plan-widget-align-natural-size.md)

[feature-3-widget-gallery.md](../features/feature-3-widget-gallery.md)

[src/gallery/display-demos.c](../../src/gallery/display-demos.c)

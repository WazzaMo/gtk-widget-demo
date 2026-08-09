/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/button-demos.h"
#include "gallery/button-demos/gtk-button-demo.h"
#include "gallery/button-demos/gtk-check-button-demo.h"
#include "gallery/button-demos/gtk-link-button-demo.h"
#include "gallery/button-demos/gtk-lock-button-demo.h"
#include "gallery/button-demos/gtk-menu-button-demo.h"
#include "gallery/button-demos/gtk-radio-button-demo.h"
#include "gallery/button-demos/gtk-switch-demo.h"
#include "gallery/button-demos/gtk-toggle-button-demo.h"
#include "gallery/button-demos/gtk-volume-button-demo.h"

static const GalleryDemoEntry button_demos[] =
{
  {
    "gtk-button",
    "GtkButton",
    "Standard push button with a click handler and feedback label.",
    "https://docs.gtk.org/gtk4/class.Button.html",
    gallery_button_gtk_button_demo_build,
  },
  {
    "gtk-toggle-button",
    "GtkToggleButton",
    "Button that stays pressed until clicked again.",
    "https://docs.gtk.org/gtk4/class.ToggleButton.html",
    gallery_button_gtk_toggle_button_demo_build,
  },
  {
    "gtk-link-button",
    "GtkLinkButton",
    "Hyperlink button opening the GTK 4 documentation site.",
    "https://docs.gtk.org/gtk4/class.LinkButton.html",
    gallery_button_gtk_link_button_demo_build,
  },
  {
    "gtk-check-button",
    "GtkCheckButton",
    "Checkbox control for boolean on/off state.",
    "https://docs.gtk.org/gtk4/class.CheckButton.html",
    gallery_button_gtk_check_button_demo_build,
  },
  {
    "gtk-radio-button",
    "GtkRadioButton",
    "Mutually exclusive options using grouped GtkCheckButton controls.",
    "https://docs.gtk.org/gtk4/class.CheckButton.html",
    gallery_button_gtk_radio_button_demo_build,
  },
  {
    "gtk-menu-button",
    "GtkMenuButton",
    "Button that opens a dropdown menu from a GMenu model.",
    "https://docs.gtk.org/gtk4/class.MenuButton.html",
    gallery_button_gtk_menu_button_demo_build,
  },
  {
    "gtk-lock-button",
    "GtkLockButton",
    "Lock control bound to a GPermission with locked state feedback.",
    "https://docs.gtk.org/gtk4/class.LockButton.html",
    gallery_button_gtk_lock_button_demo_build,
  },
  {
    "gtk-volume-button",
    "GtkVolumeButton",
    "Popover volume control with level feedback.",
    "https://docs.gtk.org/gtk4/class.VolumeButton.html",
    gallery_button_gtk_volume_button_demo_build,
  },
  {
    "gtk-switch",
    "GtkSwitch",
    "Compact on/off switch control.",
    "https://docs.gtk.org/gtk4/class.Switch.html",
    gallery_button_gtk_switch_demo_build,
  },
};

const GalleryDemoEntry *
gallery_button_demos_get(gsize *demo_count)
{
  if (demo_count != NULL)
    *demo_count = G_N_ELEMENTS(button_demos);

  return button_demos;
}

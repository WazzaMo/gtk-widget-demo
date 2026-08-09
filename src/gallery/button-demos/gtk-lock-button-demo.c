/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/button-demos/gtk-lock-button-demo.h"

static void
__on_permission_allowed_changed(GObject *object,
                                GParamSpec *pspec,
                                gpointer user_data)
{
  GtkWidget *label = user_data;
  GPermission *permission = G_PERMISSION(object);

  (void) pspec;

  if (g_permission_get_allowed(permission))
    gtk_label_set_text(GTK_LABEL(label), "Unlocked");
  else
    gtk_label_set_text(GTK_LABEL(label), "Locked");
}

GtkWidget *
gallery_button_gtk_lock_button_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *lock_button;
  GtkWidget *label;
  GPermission *permission;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);

  permission = G_PERMISSION(g_simple_permission_new(FALSE));

  label = gtk_label_new("Locked");
  gtk_label_set_xalign(GTK_LABEL(label), 0.0f);

G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  lock_button = gtk_lock_button_new(permission);
G_GNUC_END_IGNORE_DEPRECATIONS

  g_signal_connect(permission, "notify::allowed",
                   G_CALLBACK(__on_permission_allowed_changed), label);

  gtk_box_append(GTK_BOX(box), lock_button);
  gtk_box_append(GTK_BOX(box), label);

  g_object_unref(permission);

  return box;
}

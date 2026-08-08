/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"


#include "gallery/window-demos.h"

typedef struct
{
  GtkWindow *parent_window;
} GalleryDialogLaunchData;

static gboolean
__on_dialog_close_request(GtkWindow *window, gpointer user_data)
{
  (void) user_data;

  gtk_window_destroy(window);
  return TRUE;
}

static void
__on_message_dialog_response(GtkDialog *dialog,
                             int response_id,
                             gpointer user_data)
{
  (void) response_id;
  (void) user_data;

  gtk_window_destroy(GTK_WINDOW(dialog));
}

static void
__on_show_about_clicked(GtkButton *button, gpointer user_data)
{
  GalleryDialogLaunchData *data = user_data;
  GtkWidget *dialog;

  (void) button;

  dialog = gtk_about_dialog_new();
  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), "GTK Widget Demo");
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "0.1.0");
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),
                                "Runnable GTK4 widget gallery demo.");
  gtk_window_set_transient_for(GTK_WINDOW(dialog), data->parent_window);
  gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
  g_signal_connect(dialog, "close-request",
                   G_CALLBACK(__on_dialog_close_request), NULL);
  gtk_window_present(GTK_WINDOW(dialog));
}

static void
__on_show_message_clicked(GtkButton *button, gpointer user_data)
{
  GalleryDialogLaunchData *data = user_data;
  GtkWidget *dialog;

  (void) button;

G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  dialog = gtk_message_dialog_new(data->parent_window,
                                  GTK_DIALOG_MODAL,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_OK,
                                  "Gallery demo message");
  gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog),
                                           "This dialog was opened from the "
                                           "widget gallery demo page.");
G_GNUC_END_IGNORE_DEPRECATIONS
  g_signal_connect(dialog, "response",
                   G_CALLBACK(__on_message_dialog_response), NULL);
  gtk_window_present(GTK_WINDOW(dialog));
}

static GtkWidget *
__build_launch_button_page(GtkWindow *parent_window,
                           const char *label,
                           GCallback clicked_handler)
{
  GtkWidget *button;
  GalleryDialogLaunchData *data;

  data = g_new(GalleryDialogLaunchData, 1);
  data->parent_window = parent_window;

  button = gtk_button_new_with_label(label);
  g_object_set_data_full(G_OBJECT(button), "launch-data", data, g_free);
  g_signal_connect(button, "clicked", clicked_handler, data);

  return button;
}

static GtkWidget *
__build_gtk_about_dialog(GtkWindow *parent_window)
{
  return __build_launch_button_page(parent_window,
                                    "Show about dialog",
                                    G_CALLBACK(__on_show_about_clicked));
}

static GtkWidget *
__build_gtk_message_dialog(GtkWindow *parent_window)
{
  return __build_launch_button_page(parent_window,
                                    "Show message dialog",
                                    G_CALLBACK(__on_show_message_clicked));
}

static const GalleryDemoEntry window_demos[] =
{
  {
    "gtk-about-dialog",
    "GtkAboutDialog",
    "Standard about box with application name and version.",
    "https://docs.gtk.org/gtk4/class.AboutDialog.html",
    __build_gtk_about_dialog,
  },
  {
    "gtk-message-dialog",
    "GtkMessageDialog",
    "Information dialog with primary and secondary text.",
    "https://docs.gtk.org/gtk4/class.MessageDialog.html",
    __build_gtk_message_dialog,
    GALLERY_DEMO_DEPRECATED,
    "https://docs.gtk.org/gtk4/class.AlertDialog.html",
  },
};

const GalleryDemoEntry *
gallery_window_demos_get(gsize *demo_count)
{
  if (demo_count != NULL)
    *demo_count = G_N_ELEMENTS(window_demos);

  return window_demos;
}

/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "main/about-dialog.h"

#define MAIN_APP_PROGRAM_NAME "GTK Widget Demo"
#define MAIN_APP_VERSION "0.1.0"
#define MAIN_APP_COMMENTS \
  "Runnable GTK4 widget gallery aligned with the upstream visual index."
#define MAIN_APP_COPYRIGHT "Copyright © 2026 onwards Warwick Molloy"
#define MAIN_APP_WEBSITE "https://github.com/WazzaMo/gtk-widget-demo"
#define MAIN_APP_WEBSITE_LABEL "GTK Widget Demo on GitHub"

static gboolean
__on_about_dialog_close_request(GtkWindow *window, gpointer user_data)
{
  (void) user_data;

  gtk_window_destroy(window);
  return TRUE;
}

static void
__show_about_dialog(GtkApplication *app)
{
  GtkWindow *parent_window;
  GtkWidget *dialog;
  const char *authors[] = { "Warwick Molloy", NULL };

  parent_window = gtk_application_get_active_window(app);

  dialog = gtk_about_dialog_new();
  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog),
                                    MAIN_APP_PROGRAM_NAME);
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), MAIN_APP_VERSION);
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), MAIN_APP_COMMENTS);
  gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog), authors);
  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), MAIN_APP_COPYRIGHT);
  gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), MAIN_APP_WEBSITE);
  gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(dialog),
                                     MAIN_APP_WEBSITE_LABEL);
  gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(dialog),
                                    GTK_LICENSE_APACHE_2_0);
  gtk_window_set_title(GTK_WINDOW(dialog),
                       "About " MAIN_APP_PROGRAM_NAME);

  if (parent_window != NULL)
    gtk_window_set_transient_for(GTK_WINDOW(dialog), parent_window);

  gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
  g_signal_connect(dialog, "close-request",
                   G_CALLBACK(__on_about_dialog_close_request), NULL);
  gtk_window_present(GTK_WINDOW(dialog));
}

static void
__about_activated(GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
  (void) action;
  (void) parameter;

  __show_about_dialog(GTK_APPLICATION(user_data));
}

void
main_about_dialog_register_action(GtkApplication *app)
{
  GSimpleAction *about_action;

  about_action = g_simple_action_new("about", NULL);
  g_signal_connect(about_action, "activate", G_CALLBACK(__about_activated), app);
  g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(about_action));
  g_object_unref(about_action);
}

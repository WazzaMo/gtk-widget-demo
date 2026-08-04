/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-progress-bar-demo.h"
#include "gallery/display-demos/gtk-spinner-demo.h"
#include "gallery/display-demos/gtk-statusbar-demo.h"

static GtkWidget *
__find_button_by_label(GtkWidget *root, const char *label_text)
{
  GtkWidget *child;

  if (root == NULL || label_text == NULL)
    return NULL;

  if (GTK_IS_BUTTON(root))
    {
      const char *label;

      label = gtk_button_get_label(GTK_BUTTON(root));
      if (label != NULL && g_strcmp0(label, label_text) == 0)
        return root;
    }

  for (child = gtk_widget_get_first_child(root);
       child != NULL;
       child = gtk_widget_get_next_sibling(child))
    {
      GtkWidget *match;

      match = __find_button_by_label(child, label_text);
      if (match != NULL)
        return match;
    }

  return NULL;
}

static void
__click_button(GtkWidget *button)
{
  g_signal_emit_by_name(button, "clicked");
}

static void
__drain_main_context(void)
{
  int iteration;

  for (iteration = 0; iteration < 20; iteration++)
    {
      while (g_main_context_pending(NULL))
        g_main_context_iteration(NULL, FALSE);
      g_usleep(G_USEC_PER_SEC / 20);
    }
}

static void
__test_progress_bar_pulse_cleanup(void)
{
  GtkWidget *content;
  GtkWidget *pulse_mode_button;
  GtkWidget *start_pulse_button;

  content = gallery_display_gtk_progress_bar_demo_build(NULL);
  g_assert_nonnull(content);

  pulse_mode_button = __find_button_by_label(content, "Pulse");
  start_pulse_button = __find_button_by_label(content, "Start pulse");
  g_assert_nonnull(pulse_mode_button);
  g_assert_nonnull(start_pulse_button);

  __click_button(pulse_mode_button);
  __click_button(start_pulse_button);

  g_object_ref_sink(content);
  g_object_unref(content);
  __drain_main_context();
}

static void
__test_spinner_demo_cleanup(void)
{
  GtkWidget *content;
  GtkWidget *start_button;

  content = gallery_display_gtk_spinner_demo_build(NULL);
  g_assert_nonnull(content);

  start_button = __find_button_by_label(content, "Start spinner");
  g_assert_nonnull(start_button);

  __click_button(start_button);
  g_object_ref_sink(content);
  g_object_unref(content);
  __drain_main_context();
}

static void
__test_statusbar_timed_clear_cleanup(void)
{
  GtkWidget *content;
  GtkWidget *timed_button;

  content = gallery_display_gtk_statusbar_demo_build(NULL);
  g_assert_nonnull(content);

  timed_button = __find_button_by_label(content, "Timed clear");
  g_assert_nonnull(timed_button);

  __click_button(timed_button);
  g_object_ref_sink(content);
  g_object_unref(content);
  __drain_main_context();
}

int
main(int argc, char *argv[])
{
  int status;

  gtk_init();
  g_test_init(&argc, &argv, NULL);

  g_test_add_func("/gallery/demo-interactive/progress-bar-pulse-cleanup",
                  __test_progress_bar_pulse_cleanup);
  g_test_add_func("/gallery/demo-interactive/spinner-cleanup",
                  __test_spinner_demo_cleanup);
  g_test_add_func("/gallery/demo-interactive/statusbar-timed-clear-cleanup",
                  __test_statusbar_timed_clear_cleanup);

  status = g_test_run();

  return status;
}

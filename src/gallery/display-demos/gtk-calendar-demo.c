/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-calendar-demo.h"

static void
__on_calendar_day_selected(GtkCalendar *calendar, gpointer user_data)
{
  GtkWidget *label = user_data;
  GDateTime *date;
  char *text;

  date = gtk_calendar_get_date(calendar);
  if (date == NULL)
    return;

  text = g_date_time_format(date, "%Y-%m-%d");
  gtk_label_set_text(GTK_LABEL(label), text);
  g_free(text);
  g_date_time_unref(date);
}

GtkWidget *
gallery_display_gtk_calendar_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *calendar;
  GtkWidget *label;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);

  calendar = gtk_calendar_new();
  gtk_widget_set_hexpand(calendar, FALSE);

  label = gtk_label_new("Select a date on the calendar.");
  gtk_label_set_xalign(GTK_LABEL(label), 0.0f);

  g_signal_connect(calendar,
                   "day-selected",
                   G_CALLBACK(__on_calendar_day_selected),
                   label);

  gtk_box_append(GTK_BOX(box), calendar);
  gtk_box_append(GTK_BOX(box), label);

  return box;
}

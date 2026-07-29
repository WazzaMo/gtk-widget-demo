/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/demo-page.h"

static void
__on_doc_link_clicked(GtkButton *button, gpointer user_data)
{
  const char *doc_url = user_data;
  GtkUriLauncher *launcher;

  (void) button;

  if (doc_url == NULL || doc_url[0] == '\0')
    return;

  launcher = gtk_uri_launcher_new(doc_url);
  gtk_uri_launcher_launch(launcher, NULL, NULL, NULL, NULL);
  g_object_unref(launcher);
}

GtkWidget *
gallery_demo_page_new(const char *title,
                      const char *description,
                      const char *doc_url,
                      GtkWidget *content)
{
  GtkWidget *page;
  GtkWidget *heading;
  GtkWidget *description_label;
  GtkWidget *link_button;
  GtkWidget *content_frame;
  char *heading_markup;

  page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
  gtk_widget_set_margin_start(page, 16);
  gtk_widget_set_margin_end(page, 16);
  gtk_widget_set_margin_top(page, 16);
  gtk_widget_set_margin_bottom(page, 16);
  gtk_widget_set_halign(page, GTK_ALIGN_FILL);
  gtk_widget_set_valign(page, GTK_ALIGN_START);

  heading_markup = g_strdup_printf("<span size=\"large\" weight=\"bold\">%s</span>",
                                   title);
  heading = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(heading), heading_markup);
  g_free(heading_markup);
  gtk_label_set_xalign(GTK_LABEL(heading), 0.0f);
  gtk_box_append(GTK_BOX(page), heading);

  if (description != NULL && description[0] != '\0')
    {
      description_label = gtk_label_new(description);
      gtk_label_set_xalign(GTK_LABEL(description_label), 0.0f);
      gtk_label_set_wrap(GTK_LABEL(description_label), TRUE);
      gtk_widget_set_halign(description_label, GTK_ALIGN_FILL);
      gtk_box_append(GTK_BOX(page), description_label);
    }

  if (doc_url != NULL && doc_url[0] != '\0')
    {
      link_button = gtk_button_new_with_label("Open GTK documentation");
      g_signal_connect(link_button, "clicked",
                       G_CALLBACK(__on_doc_link_clicked),
                       (gpointer) doc_url);
      gtk_box_append(GTK_BOX(page), link_button);
    }

  if (content != NULL)
    {
      GtkWidget *content_area;

      gtk_widget_set_hexpand(content, FALSE);
      gtk_widget_set_vexpand(content, FALSE);
      if (gtk_widget_get_halign(content) == GTK_ALIGN_FILL)
        gtk_widget_set_halign(content, GTK_ALIGN_CENTER);

      content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
      gtk_widget_set_halign(content_area, GTK_ALIGN_FILL);
      gtk_widget_set_hexpand(content_area, TRUE);
      gtk_widget_set_valign(content_area, GTK_ALIGN_START);
      gtk_widget_set_vexpand(content_area, FALSE);
      gtk_box_append(GTK_BOX(content_area), content);

      content_frame = gtk_frame_new(NULL);
      gtk_widget_set_margin_top(content_frame, 8);
      gtk_frame_set_child(GTK_FRAME(content_frame), content_area);
      gtk_box_append(GTK_BOX(page), content_frame);
    }

  return page;
}

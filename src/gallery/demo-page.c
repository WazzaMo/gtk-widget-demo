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

static GtkWidget *
__prepare_demo_content(GtkWidget *content)
{
  GtkWidget *content_area;

  if (content == NULL)
    return NULL;

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

  return content_area;
}

static GtkWidget *
__wrap_demo_content(GtkWidget *content)
{
  GtkWidget *content_area;
  GtkWidget *content_frame;

  content_area = __prepare_demo_content(content);
  if (content_area == NULL)
    return NULL;

  content_frame = gtk_frame_new(NULL);
  gtk_widget_set_margin_top(content_frame, 8);
  gtk_frame_set_child(GTK_FRAME(content_frame), content_area);

  return content_frame;
}

GtkWidget *
gallery_demo_page_new(const GalleryDemoEntry *demo,
                      GtkWidget *legacy_content,
                      GtkWidget *comparison_content)
{
  GtkWidget *page;
  GtkWidget *heading;
  GtkWidget *description_label;
  GtkWidget *link_button;
  GtkWidget *content_widget;
  char *heading_markup;
  const char *banner_text;

  g_return_val_if_fail(demo != NULL, NULL);

  page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
  gtk_widget_set_margin_start(page, 16);
  gtk_widget_set_margin_end(page, 16);
  gtk_widget_set_margin_top(page, 16);
  gtk_widget_set_margin_bottom(page, 16);
  gtk_widget_set_halign(page, GTK_ALIGN_FILL);
  gtk_widget_set_valign(page, GTK_ALIGN_START);

  heading_markup = g_strdup_printf("<span size=\"large\" weight=\"bold\">%s</span>",
                                   demo->title);
  heading = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(heading), heading_markup);
  g_free(heading_markup);
  gtk_label_set_xalign(GTK_LABEL(heading), 0.0f);
  gtk_box_append(GTK_BOX(page), heading);

  if (demo->description != NULL && demo->description[0] != '\0')
    {
      description_label = gtk_label_new(demo->description);
      gtk_label_set_xalign(GTK_LABEL(description_label), 0.0f);
      gtk_label_set_wrap(GTK_LABEL(description_label), TRUE);
      gtk_widget_set_halign(description_label, GTK_ALIGN_FILL);
      gtk_box_append(GTK_BOX(page), description_label);
    }

  if (demo->lifecycle == GALLERY_DEMO_DEPRECATED)
    {
      GtkWidget *banner;

      banner_text = demo->deprecation_note;
      if (banner_text == NULL || banner_text[0] == '\0')
        banner_text = "Deprecated in GTK 4 — avoid for new designs.";

      banner = gtk_label_new(banner_text);
      gtk_label_set_xalign(GTK_LABEL(banner), 0.0f);
      gtk_label_set_wrap(GTK_LABEL(banner), TRUE);
      gtk_widget_add_css_class(banner, "warning");
      gtk_widget_set_halign(banner, GTK_ALIGN_FILL);
      gtk_box_append(GTK_BOX(page), banner);

      if (demo->replacement_doc_url != NULL && demo->replacement_doc_url[0] != '\0')
        {
          link_button = gtk_button_new_with_label("See replacement API");
          g_signal_connect(link_button, "clicked",
                           G_CALLBACK(__on_doc_link_clicked),
                           (gpointer) demo->replacement_doc_url);
          gtk_box_append(GTK_BOX(page), link_button);
        }
    }

  if (demo->doc_url != NULL && demo->doc_url[0] != '\0')
    {
      link_button = gtk_button_new_with_label("Open GTK documentation");
      g_signal_connect(link_button, "clicked",
                       G_CALLBACK(__on_doc_link_clicked),
                       (gpointer) demo->doc_url);
      gtk_box_append(GTK_BOX(page), link_button);
    }

  content_widget = __wrap_demo_content(legacy_content);
  if (content_widget != NULL)
    gtk_box_append(GTK_BOX(page), content_widget);

  if (comparison_content != NULL)
    {
      GtkWidget *comparison_frame;
      const char *comparison_label;

      comparison_label = demo->comparison_title;
      if (comparison_label == NULL || comparison_label[0] == '\0')
        comparison_label = "Modern alternative";

      comparison_frame = gtk_frame_new(comparison_label);
      gtk_widget_set_margin_top(comparison_frame, 8);
      gtk_frame_set_child(GTK_FRAME(comparison_frame),
                          __prepare_demo_content(comparison_content));
      gtk_box_append(GTK_BOX(page), comparison_frame);

      if (demo->comparison_doc_url != NULL && demo->comparison_doc_url[0] != '\0')
        {
          link_button = gtk_button_new_with_label("Open replacement documentation");
          g_signal_connect(link_button, "clicked",
                           G_CALLBACK(__on_doc_link_clicked),
                           (gpointer) demo->comparison_doc_url);
          gtk_box_append(GTK_BOX(page), link_button);
        }
    }

  return page;
}

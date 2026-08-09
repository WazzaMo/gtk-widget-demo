/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-media-controls-demo.h"
#include "gallery/display-demos/gtk-video-demo.h"
#include "gallery/gallery-data-path.h"

typedef struct
{
  GtkWidget *controls;
  GtkWidget *fallback_label;
} GalleryMediaControlsDemo;

static void
__gallery_media_controls_demo_free(gpointer data)
{
  g_free(data);
}

static void
__show_media_controls_error(GalleryMediaControlsDemo *demo,
                            const char *message)
{
  if (demo == NULL || demo->fallback_label == NULL)
    return;

  gtk_label_set_text(GTK_LABEL(demo->fallback_label), message);
  if (demo->controls != NULL)
    gtk_widget_set_visible(demo->controls, FALSE);
  gtk_widget_set_visible(demo->fallback_label, TRUE);
}

static void
__on_media_stream_error_notify(GObject *object,
                               GParamSpec *pspec,
                               gpointer user_data)
{
  GtkMediaStream *stream = GTK_MEDIA_STREAM(object);
  GalleryMediaControlsDemo *demo = user_data;
  const GError *error;

  (void) pspec;

  error = gtk_media_stream_get_error(stream);
  if (error != NULL && error->message != NULL)
    __show_media_controls_error(demo, error->message);
}

GtkWidget *
gallery_display_gtk_media_controls_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *controls;
  GtkWidget *fallback_label;
  GtkMediaStream *stream;
  GalleryMediaControlsDemo *demo;
  char *sample_path;
  char *missing_message;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);

  fallback_label = gtk_label_new(NULL);
  gtk_label_set_wrap(GTK_LABEL(fallback_label), TRUE);
  gtk_widget_set_visible(fallback_label, FALSE);
  gtk_widget_set_halign(fallback_label, GTK_ALIGN_START);

  demo = g_new(GalleryMediaControlsDemo, 1);
  demo->controls = NULL;
  demo->fallback_label = fallback_label;
  g_object_set_data_full(G_OBJECT(box),
                         "media-controls-demo",
                         demo,
                         __gallery_media_controls_demo_free);

  sample_path = g_build_filename(GALLERY_DATA_DIR, DEMO_VIDEO_CLIP, NULL);
  if (!g_file_test(sample_path, G_FILE_TEST_EXISTS))
    {
      missing_message = g_strdup_printf(
        "Bundled %s not found. Rebuild from the repository data/ directory.",
        DEMO_VIDEO_CLIP);
      __show_media_controls_error(demo, missing_message);
      g_free(missing_message);
      g_free(sample_path);
      gtk_box_append(GTK_BOX(box), fallback_label);
      return box;
    }

  stream = gtk_media_file_new_for_filename(sample_path);
  g_free(sample_path);
  gtk_media_stream_set_playing(stream, TRUE);

  controls = gtk_media_controls_new(stream);
  demo->controls = controls;
  gtk_widget_set_hexpand(controls, FALSE);

  g_signal_connect(stream,
                   "notify::error",
                   G_CALLBACK(__on_media_stream_error_notify),
                   demo);
  if (gtk_media_stream_get_error(stream) != NULL)
    __show_media_controls_error(demo,
                                gtk_media_stream_get_error(stream)->message);

  g_object_set_data_full(G_OBJECT(box),
                         "media-stream",
                         stream,
                         g_object_unref);

  gtk_box_append(GTK_BOX(box), controls);
  gtk_box_append(GTK_BOX(box), fallback_label);

  return box;
}

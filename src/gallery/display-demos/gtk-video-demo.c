/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-video-demo.h"
#include "gallery/gallery-data-path.h"

static const char demo_video_filename[] = DEMO_VIDEO_CLIP;

typedef struct
{
  GtkWidget *video;
  GtkWidget *fallback_box;
  GtkWidget *fallback_label;
  GtkWidget *copy_button;
  char *error_message;
} GalleryVideoFallback;

static void
__gallery_video_fallback_free(gpointer data)
{
  GalleryVideoFallback *fallback = data;

  g_free(fallback->error_message);
  g_free(fallback);
}

static void
__on_copy_error_clicked(GtkButton *button, gpointer user_data)
{
  GalleryVideoFallback *fallback = user_data;
  GdkClipboard *clipboard;

  (void) button;

  if (fallback == NULL || fallback->error_message == NULL)
    return;

  clipboard = gtk_widget_get_clipboard(fallback->copy_button);
  gdk_clipboard_set_text(clipboard, fallback->error_message);
}

static GtkWidget *
__build_video_fallback_panel(GalleryVideoFallback **fallback_out)
{
  GtkWidget *fallback_box;
  GtkWidget *fallback_label;
  GtkWidget *copy_button;
  GalleryVideoFallback *fallback;

  fallback_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
  gtk_widget_set_visible(fallback_box, FALSE);
  gtk_widget_set_halign(fallback_box, GTK_ALIGN_START);
  gtk_widget_set_hexpand(fallback_box, FALSE);

  fallback_label = gtk_label_new(NULL);
  gtk_label_set_wrap(GTK_LABEL(fallback_label), TRUE);
  gtk_widget_set_halign(fallback_label, GTK_ALIGN_START);

  copy_button = gtk_button_new_with_label("Copy error message");

  fallback = g_new(GalleryVideoFallback, 1);
  fallback->video = NULL;
  fallback->fallback_box = fallback_box;
  fallback->fallback_label = fallback_label;
  fallback->copy_button = copy_button;
  fallback->error_message = NULL;

  g_signal_connect(copy_button,
                   "clicked",
                   G_CALLBACK(__on_copy_error_clicked),
                   fallback);

  gtk_box_append(GTK_BOX(fallback_box), fallback_label);
  gtk_box_append(GTK_BOX(fallback_box), copy_button);

  *fallback_out = fallback;
  return fallback_box;
}

static void
__show_fallback_message(GalleryVideoFallback *fallback,
                        const char *display_message,
                        const char *clipboard_message)
{
  if (fallback == NULL || fallback->fallback_label == NULL)
    return;

  g_free(fallback->error_message);
  fallback->error_message = g_strdup(clipboard_message);
  gtk_label_set_text(GTK_LABEL(fallback->fallback_label), display_message);

  if (fallback->video != NULL)
    gtk_widget_set_visible(fallback->video, FALSE);
  gtk_widget_set_visible(fallback->fallback_box, TRUE);
}

static gboolean
__error_indicates_missing_gstreamer_plugin(const GError *error)
{
  const char *message;

  if (error == NULL || error->message == NULL)
    return FALSE;

  message = error->message;
  return (strstr(message, "missing a plug-in") != NULL
          || strstr(message, "missing plugin") != NULL
          || strstr(message, "No suitable plugins found") != NULL);
}

static char *
__format_video_error_for_display(const GError *error)
{
  if (__error_indicates_missing_gstreamer_plugin(error))
    {
      return g_strdup_printf(
        "Video playback is unavailable — GStreamer is missing a plug-in "
        "needed to decode %s (H.264).\n\n"
        "On Debian or Ubuntu, install:\n"
        "  sudo apt install gstreamer1.0-plugins-good "
        "gstreamer1.0-plugins-bad gstreamer1.0-libav "
        "libgtk-4-media-gstreamer\n\n"
        "Use \"Copy error message\" for the full GStreamer diagnostic.",
        demo_video_filename);
    }

  if (error != NULL && error->message != NULL && error->message[0] != '\0')
    return g_strdup_printf("Video playback is unavailable — %s.", error->message);

  return g_strdup(
    "Video playback is unavailable — required GStreamer plugins may be "
    "missing on this host.");
}

static void
__show_video_playback_error(GalleryVideoFallback *fallback,
                            const GError *error)
{
  char *display_message;
  char *clipboard_message;

  display_message = __format_video_error_for_display(error);

  if (error != NULL && error->message != NULL && error->message[0] != '\0')
    clipboard_message = g_strdup_printf("%s\n\nGStreamer details:\n%s",
                                        display_message,
                                        error->message);
  else
    clipboard_message = g_strdup(display_message);

  __show_fallback_message(fallback, display_message, clipboard_message);

  g_free(display_message);
  g_free(clipboard_message);
}

static void
__handle_media_stream_error(GtkMediaStream *stream,
                            GalleryVideoFallback *fallback)
{
  const GError *error;

  error = gtk_media_stream_get_error(stream);
  if (error != NULL)
    __show_video_playback_error(fallback, error);
}

static void
__on_media_stream_error_notify(GObject *object,
                               GParamSpec *pspec,
                               gpointer user_data)
{
  (void) pspec;

  __handle_media_stream_error(GTK_MEDIA_STREAM(object), user_data);
}

GtkWidget *
gallery_display_gtk_video_demo_build(GtkWindow *parent_window)
{
  GtkWidget *box;
  GtkWidget *video;
  GtkWidget *fallback_box;
  GtkMediaStream *stream;
  GalleryVideoFallback *fallback;
  char *sample_path;
  char *missing_message;

  (void) parent_window;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
  fallback_box = __build_video_fallback_panel(&fallback);
  g_object_set_data_full(G_OBJECT(box),
                         "video-fallback",
                         fallback,
                         __gallery_video_fallback_free);
  gtk_box_append(GTK_BOX(box), fallback_box);

  sample_path = g_build_filename(GALLERY_DATA_DIR, demo_video_filename, NULL);
  if (!g_file_test(sample_path, G_FILE_TEST_EXISTS))
    {
      missing_message = g_strdup_printf(
        "Bundled %s not found. Rebuild from the repository data/ directory.",
        demo_video_filename);
      __show_fallback_message(fallback, missing_message, missing_message);
      g_free(missing_message);
      g_free(sample_path);
      return box;
    }

  video = gtk_video_new_for_filename(sample_path);
  g_free(sample_path);
  fallback->video = video;
  gtk_video_set_autoplay(GTK_VIDEO(video), TRUE);
  gtk_video_set_loop(GTK_VIDEO(video), TRUE);
  gtk_widget_set_size_request(video, 320, 180);
  gtk_widget_set_hexpand(video, FALSE);

  stream = gtk_video_get_media_stream(GTK_VIDEO(video));
  g_signal_connect(stream,
                   "notify::error",
                   G_CALLBACK(__on_media_stream_error_notify),
                   fallback);
  __handle_media_stream_error(stream, fallback);

  gtk_box_prepend(GTK_BOX(box), video);

  return box;
}

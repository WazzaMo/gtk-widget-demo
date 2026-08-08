/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "gtk-version.h"

#include "gallery/display-demos/gtk-video-demo.h"
#include "gallery/gallery-data-path.h"

GtkWidget *
gallery_display_gtk_video_demo_build(GtkWindow *parent_window)
{
  GtkWidget *video;
  const char *sample_path;

  (void) parent_window;

  sample_path = GALLERY_DATA_PATH("demo-sample.mp4");
  if (!g_file_test(sample_path, G_FILE_TEST_EXISTS))
    {
      return gtk_label_new(
        "Bundled demo-sample.mp4 not found. Rebuild from the repository data/ directory.");
    }

  video = gtk_video_new_for_filename(sample_path);
  gtk_video_set_autoplay(GTK_VIDEO(video), TRUE);
  gtk_video_set_loop(GTK_VIDEO(video), TRUE);
  gtk_widget_set_size_request(video, 320, 180);
  gtk_widget_set_hexpand(video, FALSE);

  return video;
}

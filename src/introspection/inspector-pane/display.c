/*
 * (c) Copyright 2026 onwards Warwick Molloy.
 * Contribution to this project is supported and contributors will be recognised.
 *
 * Licensed under the Apache License, Version 2.0.
 */

#include "introspection/inspector-pane/display.h"

#include "introspection/property-list.h"
#include "introspection/signal-list.h"
#include "introspection/type-ancestry.h"

void
introspection_inspector_pane_display_set_initial_text(
  IntrospectionInspectorPane *pane)
{
  GtkTextBuffer *buffer;

  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pane->text_view));
  gtk_text_buffer_set_text(buffer,
                           "Enable View → Inspect widget, then click a widget "
                           "to inspect its GObject metadata.",
                           -1);
}

void
introspection_inspector_pane_display_update(IntrospectionInspectorPane *pane,
                                            GObject *object)
{
  GtkTextBuffer *buffer;
  GType type;
  gchar *type_name;
  gchar *ancestry;
  gchar *interfaces;
  gchar *properties;
  gchar *signals;
  GString *text;

  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pane->text_view));
  type = G_OBJECT_TYPE(object);
  type_name = introspection_type_name(type);
  ancestry = introspection_format_ancestry(type);
  interfaces = introspection_format_interfaces(type);
  properties = introspection_format_properties(object);
  signals = introspection_format_signals(type);

  text = g_string_new(NULL);
  g_string_append_printf(text, "Type\n%s\n\n", type_name);
  g_string_append_printf(text, "Ancestry\n%s\n\n", ancestry);
  g_string_append_printf(text, "Interfaces\n%s\n\n", interfaces);
  g_string_append_printf(text, "Properties\n%s\n", properties);
  g_string_append_printf(text, "Signals\n%s", signals);

  gtk_text_buffer_set_text(buffer, text->str, (int) text->len);

  g_string_free(text, TRUE);
  g_free(type_name);
  g_free(ancestry);
  g_free(interfaces);
  g_free(properties);
  g_free(signals);
}

void
introspection_inspector_pane_display_show_message(
  IntrospectionInspectorPane *pane,
  const gchar *message)
{
  GtkTextBuffer *buffer;

  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pane->text_view));
  gtk_text_buffer_set_text(buffer, message, -1);
}

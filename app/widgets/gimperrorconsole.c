/* The GIMP -- an image manipulation program
 * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis
 *
 * gimperrorconsole.c
 * Copyright (C) 2003 Michael Natterer <mitch@gimp.org>
 *
 * partly based on errorconsole.c
 * Copyright (C) 1998 Nick Fetchak <nuke@bayside.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "config.h"

#include <glib.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#ifdef G_OS_WIN32
#include <io.h>
#ifndef S_IRUSR
#define S_IRUSR _S_IREAD
#endif
#ifndef S_IWUSR
#define S_IWUSR _S_IWRITE
#endif
#endif

#include <gtk/gtk.h>

#include "libgimpbase/gimpbase.h"
#include "libgimpwidgets/gimpwidgets.h"

#include "widgets-types.h"

#include "core/gimp.h"

#include "gimperrorconsole.h"
#include "gimphelp-ids.h"
#include "gimpmenufactory.h"
#include "gimpwidgets-utils.h"

#include "gimp-intl.h"


static void gimp_error_console_class_init  (GimpErrorConsoleClass *klass);
static void gimp_error_console_init        (GimpErrorConsole      *editor);

static void gimp_error_console_destroy          (GtkObject        *object);
static void gimp_error_console_unmap            (GtkWidget        *widget);

static gboolean gimp_error_console_button_press (GtkWidget        *widget,
                                                 GdkEventButton   *event,
                                                 GimpErrorConsole *console);
static void gimp_error_console_clear_clicked    (GtkWidget        *button,
                                                 GimpErrorConsole *console);
static void gimp_error_console_save_clicked     (GtkWidget        *button,
                                                 GimpErrorConsole *console);
static void gimp_error_console_save_ext_clicked (GtkWidget        *button,
                                                 GdkModifierType   state,
                                                 GimpErrorConsole *console);
static void gimp_error_console_save_response    (GtkWidget        *dialog,
                                                 gint              response_id,
                                                 GimpErrorConsole *console);

static gboolean gimp_error_console_write_file   (GtkTextBuffer    *text_buffer,
                                                 const gchar      *path,
                                                 gboolean          selection_only);


static GimpEditorClass *parent_class = NULL;


GType
gimp_error_console_get_type (void)
{
  static GType view_type = 0;

  if (! view_type)
    {
      static const GTypeInfo view_info =
      {
        sizeof (GimpErrorConsoleClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) gimp_error_console_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (GimpErrorConsole),
        0,              /* n_preallocs */
        (GInstanceInitFunc) gimp_error_console_init,
      };

      view_type = g_type_register_static (GIMP_TYPE_EDITOR,
                                          "GimpErrorConsole",
                                          &view_info, 0);
    }

  return view_type;
}

static void
gimp_error_console_class_init (GimpErrorConsoleClass *klass)
{
  GtkObjectClass *object_class;
  GtkWidgetClass *widget_class;

  object_class = GTK_OBJECT_CLASS (klass);
  widget_class = GTK_WIDGET_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->destroy = gimp_error_console_destroy;
  widget_class->unmap   = gimp_error_console_unmap;
}

static void
gimp_error_console_init (GimpErrorConsole *console)
{
  GtkWidget *scrolled_window;
  gchar     *str;

  console->text_buffer = gtk_text_buffer_new (NULL);

  gtk_text_buffer_create_tag (console->text_buffer, "title",
			      "weight", PANGO_WEIGHT_BOLD,
                              "scale",  PANGO_SCALE_LARGE,
			      NULL);
  gtk_text_buffer_create_tag (console->text_buffer, "message",
			      NULL);

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
				  GTK_POLICY_AUTOMATIC,
				  GTK_POLICY_AUTOMATIC);
  gtk_container_add (GTK_CONTAINER (console), scrolled_window);
  gtk_widget_show (scrolled_window);

  console->text_view = gtk_text_view_new_with_buffer (console->text_buffer);
  g_object_unref (console->text_buffer);

  gtk_text_view_set_editable (GTK_TEXT_VIEW (console->text_view), FALSE);
  gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (console->text_view),
                               GTK_WRAP_WORD);
  gtk_container_add (GTK_CONTAINER (scrolled_window), console->text_view);
  gtk_widget_show (console->text_view);

  g_signal_connect (console->text_view, "button_press_event",
		    G_CALLBACK (gimp_error_console_button_press),
		    console);

  console->clear_button =
    gimp_editor_add_button (GIMP_EDITOR (console),
                            GTK_STOCK_CLEAR, _("Clear errors"),
                            GIMP_HELP_ERRORS_CLEAR,
                            G_CALLBACK (gimp_error_console_clear_clicked),
                            NULL,
                            console);

  str = g_strdup_printf (_("Save all errors\n"
                           "%s  Save selection"),
                         gimp_get_mod_string (GDK_SHIFT_MASK));

  console->save_button =
    gimp_editor_add_button (GIMP_EDITOR (console),
                            GTK_STOCK_SAVE_AS, str,
                            GIMP_HELP_ERRORS_SAVE,
                            G_CALLBACK (gimp_error_console_save_clicked),
                            G_CALLBACK (gimp_error_console_save_ext_clicked),
                            console);

  g_free (str);

  console->file_dialog = NULL;
}

static void
gimp_error_console_destroy (GtkObject *object)
{
  GimpErrorConsole *console = GIMP_ERROR_CONSOLE (object);

  if (console->file_dialog)
    gtk_widget_destroy (console->file_dialog);

  console->gimp->message_handler = GIMP_MESSAGE_BOX;

  GTK_OBJECT_CLASS (parent_class)->destroy (object);
}

static void
gimp_error_console_unmap (GtkWidget *widget)
{
  GimpErrorConsole *console = GIMP_ERROR_CONSOLE (widget);

  if (console->file_dialog)
    gtk_widget_destroy (console->file_dialog);

  GTK_WIDGET_CLASS (parent_class)->unmap (widget);
}

GtkWidget *
gimp_error_console_new (Gimp            *gimp,
                        GimpMenuFactory *menu_factory)
{
  GimpErrorConsole *console;

  g_return_val_if_fail (GIMP_IS_GIMP (gimp), NULL);
  g_return_val_if_fail (GIMP_IS_MENU_FACTORY (menu_factory), NULL);

  console = g_object_new (GIMP_TYPE_ERROR_CONSOLE,
                          "menu-factory",   menu_factory,
                          "menu-identifier", "<ErrorConsole>",
                          "ui-path",        "/error-console-popup",
                          NULL);

  console->gimp = gimp;

  console->gimp->message_handler = GIMP_ERROR_CONSOLE;

  return GTK_WIDGET (console);
}

void
gimp_error_console_add (GimpErrorConsole *console,
                        const gchar      *stock_id,
                        const gchar      *domain,
                        const gchar      *message)
{
  GtkTextIter  end;
  GtkTextMark *end_mark;
  GdkPixbuf   *pixbuf;
  gchar       *str;

  g_return_if_fail (GIMP_IS_ERROR_CONSOLE (console));
  g_return_if_fail (stock_id != NULL);
  g_return_if_fail (domain != NULL);
  g_return_if_fail (message != NULL);

  gtk_text_buffer_get_end_iter (console->text_buffer, &end);

  pixbuf = gtk_widget_render_icon (console->text_view, stock_id,
                                   GTK_ICON_SIZE_MENU, NULL);
  gtk_text_buffer_insert_pixbuf (console->text_buffer, &end, pixbuf);
  g_object_unref (pixbuf);

  gtk_text_buffer_insert (console->text_buffer, &end, "  ", -1);

  str = g_strdup_printf (_("%s Message"), domain);
  gtk_text_buffer_insert_with_tags_by_name (console->text_buffer, &end,
                                            str, -1,
                                            "title",
                                            NULL);
  g_free (str);

  gtk_text_buffer_insert (console->text_buffer, &end, "\n", -1);

  gtk_text_buffer_insert_with_tags_by_name (console->text_buffer, &end,
                                            message, -1,
                                            "message",
                                            NULL);

  gtk_text_buffer_insert (console->text_buffer, &end, "\n\n", -1);

  end_mark = gtk_text_buffer_create_mark (console->text_buffer,
                                          NULL, &end, TRUE);
  gtk_text_view_scroll_to_mark (GTK_TEXT_VIEW (console->text_view), end_mark,
                                FALSE, TRUE, 1.0, 0.0);
  gtk_text_buffer_delete_mark (console->text_buffer, end_mark);
}


/*  private functions  */

static gboolean
gimp_error_console_button_press (GtkWidget        *widget,
                                 GdkEventButton   *bevent,
                                 GimpErrorConsole *console)
{
  if (bevent->button == 3 && bevent->type == GDK_BUTTON_PRESS)
    {
      return gimp_editor_popup_menu (GIMP_EDITOR (console), NULL, NULL);
    }

  return FALSE;
}

static void
gimp_error_console_clear_clicked (GtkWidget        *button,
                                  GimpErrorConsole *console)
{
  GtkTextIter start_iter;
  GtkTextIter end_iter;

  gtk_text_buffer_get_start_iter (console->text_buffer, &start_iter);
  gtk_text_buffer_get_end_iter (console->text_buffer, &end_iter);

  gtk_text_buffer_delete (console->text_buffer, &start_iter, &end_iter);
}

static void
gimp_error_console_save_clicked (GtkWidget        *button,
                                 GimpErrorConsole *console)
{
  gimp_error_console_save_ext_clicked (button, 0, console);
}

static void
gimp_error_console_save_ext_clicked (GtkWidget        *button,
                                     GdkModifierType   state,
                                     GimpErrorConsole *console)
{
  GtkFileChooser *chooser;

  if (! gtk_text_buffer_get_selection_bounds (console->text_buffer,
                                              NULL, NULL) &&
      (state & GDK_SHIFT_MASK))
    {
      g_message (_("Cannot save. Nothing is selected."));
      return;
    }

  if (console->file_dialog)
    {
      gtk_window_present (GTK_WINDOW (console->file_dialog));
      return;
    }

  console->file_dialog =
    gtk_file_chooser_dialog_new (_("Save Error Log to File"), NULL,
                                 GTK_FILE_CHOOSER_ACTION_SAVE,

                                 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                 GTK_STOCK_SAVE,   GTK_RESPONSE_OK,

                                 NULL);

  console->save_selection = (state & GDK_SHIFT_MASK) ? TRUE : FALSE;

  g_object_add_weak_pointer (G_OBJECT (console->file_dialog),
                             (gpointer *) &console->file_dialog);

  chooser = GTK_FILE_CHOOSER (console->file_dialog);

  gtk_window_set_screen (GTK_WINDOW (chooser), gtk_widget_get_screen (button));

  gtk_window_set_position (GTK_WINDOW (chooser), GTK_WIN_POS_MOUSE);
  gtk_window_set_role (GTK_WINDOW (chooser), "gimp-save-errors");

  g_signal_connect (chooser, "response",
		    G_CALLBACK (gimp_error_console_save_response),
		    console);
  g_signal_connect (chooser, "delete_event",
		    G_CALLBACK (gtk_true),
		    NULL);

  gimp_help_connect (GTK_WIDGET (chooser), gimp_standard_help_func,
		     GIMP_HELP_ERRORS_DIALOG, NULL);

  gtk_widget_show (GTK_WIDGET (chooser));
}

static void
gimp_error_console_save_response (GtkWidget        *dialog,
                                  gint              response_id,
                                  GimpErrorConsole *console)
{
  if (response_id == GTK_RESPONSE_OK)
    {
      gchar *filename;

      filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));

      if (! gimp_error_console_write_file (console->text_buffer, filename,
                                           console->save_selection))
        {
          g_message (_("Error writing file '%s':\n%s"),
                     gimp_filename_to_utf8 (filename), g_strerror (errno));
          g_free (filename);
          return;
        }

      g_free (filename);
    }

  gtk_widget_destroy (dialog);
}

static gboolean
gimp_error_console_write_file (GtkTextBuffer *text_buffer,
                               const gchar   *path,
                               gboolean       selection_only)
{
  GtkTextIter  start_iter;
  GtkTextIter  end_iter;
  gint         fd;
  gint         text_length;
  gint         bytes_written;
  gchar	      *text_contents;

  fd = open (path, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);

  if (fd == -1)
    return FALSE;

  if (selection_only)
    gtk_text_buffer_get_selection_bounds (text_buffer, &start_iter, &end_iter);
  else
    gtk_text_buffer_get_bounds (text_buffer, &start_iter, &end_iter);

  text_contents = gtk_text_buffer_get_text (text_buffer,
					    &start_iter, &end_iter, TRUE);

  text_length = strlen (text_contents);

  if (text_contents && (text_length > 0))
    {
      bytes_written = write (fd, text_contents, text_length);

      g_free (text_contents);
      close (fd);

      if (bytes_written != text_length)
        return FALSE;
      else
	return TRUE;
    }

  close (fd);

  return TRUE;
}

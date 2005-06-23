/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball
 *
 * gimpbrowser.c
 * Copyright (C) 2005 Michael Natterer <mitch@gimp.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "config.h"

#include <string.h>

#include <gtk/gtk.h>

#include "gimpwidgetstypes.h"

#include "gimpbrowser.h"
#include "gimpintcombobox.h"
#include "gimpwidgetsmarshal.h"

#include "libgimp/libgimp-intl.h"


enum
{
  SEARCH,
  LAST_SIGNAL
};


static void       gimp_browser_class_init     (GimpBrowserClass *klass);
static void       gimp_browser_init           (GimpBrowser      *browser);

static void       gimp_browser_destroy        (GtkObject        *object);

static void       gimp_browser_entry_changed  (GtkEditable      *editable,
                                               GimpBrowser      *browser);
static gboolean   gimp_browser_search_timeout (gpointer          data);


static GtkHPanedClass *parent_class = NULL;

static guint browser_signals[LAST_SIGNAL] = { 0 };


GType
gimp_browser_get_type (void)
{
  static GType type = 0;

  if (! type)
    {
      static const GTypeInfo info =
      {
        sizeof (GimpBrowserClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) gimp_browser_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (GimpBrowser),
        0,              /* n_preallocs */
        (GInstanceInitFunc) gimp_browser_init,
      };

      type = g_type_register_static (GTK_TYPE_HPANED,
                                     "GimpBrowser",
                                     &info, 0);
    }

  return type;
}

static void
gimp_browser_class_init (GimpBrowserClass *klass)
{
  GtkObjectClass *gtk_object_class = GTK_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  browser_signals[SEARCH] =
    g_signal_new ("search",
                  G_TYPE_FROM_CLASS (klass),
                  G_SIGNAL_RUN_LAST,
                  G_STRUCT_OFFSET (GimpBrowserClass, search),
                  NULL, NULL,
                  _gimp_widgets_marshal_VOID__STRING_INT,
                  G_TYPE_NONE, 2,
                  G_TYPE_STRING,
                  G_TYPE_INT);

  gtk_object_class->destroy = gimp_browser_destroy;

  klass->search             = NULL;
}

static void
gimp_browser_init (GimpBrowser *browser)
{
  GtkWidget *hbox;
  GtkWidget *label;
  GtkWidget *scrolled_window;

  browser->search_type = -1;

  browser->left_vbox = gtk_vbox_new (FALSE, 6);
  gtk_paned_pack1 (GTK_PANED (browser), browser->left_vbox, FALSE, TRUE);
  gtk_widget_show (browser->left_vbox);

  /* search entry */

  hbox = gtk_hbox_new (FALSE, 6);
  gtk_box_pack_start (GTK_BOX (browser->left_vbox), hbox, FALSE, FALSE, 0);
  gtk_widget_show (hbox);

  label = gtk_label_new_with_mnemonic (_("_Search:"));
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);
  gtk_widget_show (label);

  browser->search_entry = gtk_entry_new ();
  gtk_box_pack_start (GTK_BOX (hbox), browser->search_entry, TRUE, TRUE, 0);
  gtk_widget_show (browser->search_entry);

  gtk_label_set_mnemonic_widget (GTK_LABEL (label), browser->search_entry);

  g_signal_connect (browser->search_entry, "changed",
                    G_CALLBACK (gimp_browser_entry_changed),
                    browser);

  /* count label */

  browser->count_label = gtk_label_new ("0 Matches");
  gtk_misc_set_alignment (GTK_MISC (browser->count_label), 0.0, 0.5);
  gtk_box_pack_end (GTK_BOX (browser->left_vbox), browser->count_label,
                    FALSE, FALSE, 0);
  gtk_widget_show (browser->count_label);

  /* scrolled window */

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_AUTOMATIC,
                                  GTK_POLICY_ALWAYS);
  gtk_paned_pack2 (GTK_PANED (browser), scrolled_window, TRUE, TRUE);
  gtk_widget_show (scrolled_window);

  browser->right_vbox = gtk_vbox_new (FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (browser->right_vbox), 12);
  gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window),
                                         browser->right_vbox);
  gtk_widget_show (browser->right_vbox);

  gtk_widget_grab_focus (browser->search_entry);
}

static void
gimp_browser_destroy (GtkObject *object)
{
  GimpBrowser *browser = GIMP_BROWSER (object);

  if (browser->search_timeout_id)
    {
      g_source_remove (browser->search_timeout_id);
      browser->search_timeout_id = 0;
    }

  GTK_OBJECT_CLASS (parent_class)->destroy (object);
}


/*  public functions  */

GtkWidget *
gimp_browser_new (void)
{
  return g_object_new (GIMP_TYPE_BROWSER, NULL);
}

void
gimp_browser_add_search_types (GimpBrowser *browser,
                               const gchar *first_type_label,
                               gint         first_type_id,
                               ...)
{
  g_return_if_fail (GIMP_IS_BROWSER (browser));
  g_return_if_fail (first_type_label != NULL);

  if (! browser->search_type_combo)
    {
      GtkWidget *combo;
      va_list    args;

      va_start (args, first_type_id);
      combo = gimp_int_combo_box_new_valist (first_type_label,
                                             first_type_id,
                                             args);
      va_end (args);

      browser->search_type_combo = combo;
      browser->search_type       = first_type_id;

      gtk_box_pack_end (GTK_BOX (browser->search_entry->parent), combo,
                        FALSE, FALSE, 0);
      gtk_widget_show (combo);

      gimp_int_combo_box_connect (GIMP_INT_COMBO_BOX (combo),
                                  browser->search_type,
                                  G_CALLBACK (gimp_int_combo_box_get_active),
                                  &browser->search_type);

      g_signal_connect (combo, "changed",
                        G_CALLBACK (gimp_browser_entry_changed),
                        browser);
    }
  else
    {
      gimp_int_combo_box_append (GIMP_INT_COMBO_BOX (browser->search_type_combo),
                                 first_type_label, first_type_id,
                                 NULL);
    }
}

void
gimp_browser_set_widget (GimpBrowser *browser,
                         GtkWidget   *widget)
{
  g_return_if_fail (GIMP_IS_BROWSER (browser));
  g_return_if_fail (widget == NULL || GTK_IS_WIDGET (widget));

  if (widget == browser->right_widget)
    return;

  if (browser->right_widget)
    gtk_container_remove (GTK_CONTAINER (browser->right_vbox),
                          browser->right_widget);

  browser->right_widget = widget;

  if (widget)
    {
      gtk_box_pack_start (GTK_BOX (browser->right_vbox), widget,
                          FALSE, FALSE, 0);
      gtk_widget_show (widget);
    }
}

void
gimp_browser_show_message (GimpBrowser *browser,
                           const gchar *message)
{
  g_return_if_fail (GIMP_IS_BROWSER (browser));
  g_return_if_fail (message != NULL);

  if (GTK_IS_LABEL (browser->right_widget))
    {
      gtk_label_set_text (GTK_LABEL (browser->right_widget), message);
    }
  else
    {
      gimp_browser_set_widget (browser, gtk_label_new (message));
    }

  while (gtk_events_pending ())
    gtk_main_iteration ();
}


/*  private functions  */

static void
gimp_browser_entry_changed (GtkEditable *editable,
                            GimpBrowser *browser)
{
  if (browser->search_timeout_id)
    g_source_remove (browser->search_timeout_id);

  browser->search_timeout_id =
    g_timeout_add (100, gimp_browser_search_timeout, browser);
}

static gboolean
gimp_browser_search_timeout (gpointer data)
{
  GimpBrowser *browser = GIMP_BROWSER (data);
  const gchar *search_string;

  GDK_THREADS_ENTER();

  search_string = gtk_entry_get_text (GTK_ENTRY (browser->search_entry));

  if (! search_string)
    search_string = "";

  g_signal_emit (browser, browser_signals[SEARCH], 0,
                 search_string, browser->search_type);

  browser->search_timeout_id = 0;

  GDK_THREADS_LEAVE();

  return FALSE;
}

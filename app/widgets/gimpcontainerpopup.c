/* The GIMP -- an image manipulation program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * gimpcontainerpopup.c
 * Copyright (C) 2003 Michael Natterer <mitch@gimp.org>
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

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "libgimpwidgets/gimpwidgets.h"

#include "widgets-types.h"

#include "core/gimpcontext.h"
#include "core/gimpcontainer.h"
#include "core/gimpmarshal.h"

#include "gimpcontainereditor.h"
#include "gimpcontainerpopup.h"
#include "gimpcontainergridview.h"
#include "gimpcontainertreeview.h"
#include "gimpdialogfactory.h"
#include "gimppreview.h"

#include "gimp-intl.h"


enum
{
  CANCEL,
  CONFIRM,
  LAST_SIGNAL
};


static void     gimp_container_popup_class_init (GimpContainerPopupClass *klass);
static void     gimp_container_popup_init       (GimpContainerPopup      *view);

static void     gimp_container_popup_finalize     (GObject            *object);
static void     gimp_container_popup_map          (GtkWidget          *widget);
static gboolean gimp_container_popup_button_press (GtkWidget          *widget,
                                                   GdkEventButton     *bevent);
static gboolean gimp_container_popup_key_press    (GtkWidget          *widget,
                                                   GdkEventKey        *kevent);
static void     gimp_container_popup_real_cancel  (GimpContainerPopup *popup);
static void     gimp_container_popup_real_confirm (GimpContainerPopup *popup);

static void     gimp_container_popup_create_view  (GimpContainerPopup *popup,
                                                   GimpViewType        view_type);

static void gimp_container_popup_smaller_clicked  (GtkWidget          *button,
                                                   GimpContainerPopup *popup);
static void gimp_container_popup_larger_clicked   (GtkWidget          *button,
                                                   GimpContainerPopup *popup);
static void gimp_container_popup_view_type_toggled(GtkWidget          *button,
                                                   GimpContainerPopup *popup);
static void gimp_container_popup_dialog_clicked   (GtkWidget          *button,
                                                   GimpContainerPopup *popup);


static GtkWindowClass *parent_class = NULL;

static guint popup_signals[LAST_SIGNAL];


GType
gimp_container_popup_get_type (void)
{
  static GType popup_type = 0;

  if (! popup_type)
    {
      static const GTypeInfo popup_info =
      {
        sizeof (GimpContainerPopupClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) gimp_container_popup_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (GimpContainerPopup),
        0,              /* n_preallocs */
        (GInstanceInitFunc) gimp_container_popup_init,
      };

      popup_type = g_type_register_static (GTK_TYPE_WINDOW,
                                           "GimpContainerPopup",
                                           &popup_info, 0);
    }

  return popup_type;
}

static void
gimp_container_popup_class_init (GimpContainerPopupClass *klass)
{
  GObjectClass   *object_class;
  GtkWidgetClass *widget_class;
  GtkBindingSet  *binding_set;

  object_class = G_OBJECT_CLASS (klass);
  widget_class = GTK_WIDGET_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  popup_signals[CANCEL] =
    g_signal_new ("cancel",
                  G_OBJECT_CLASS_TYPE (klass),
                  G_SIGNAL_RUN_LAST | G_SIGNAL_ACTION,
                  G_STRUCT_OFFSET (GimpContainerPopupClass, cancel),
                  NULL, NULL,
                  gimp_marshal_VOID__VOID,
                  G_TYPE_NONE, 0);

  popup_signals[CONFIRM] =
    g_signal_new ("confirm",
                  G_OBJECT_CLASS_TYPE (klass),
                  G_SIGNAL_RUN_LAST | G_SIGNAL_ACTION,
                  G_STRUCT_OFFSET (GimpContainerPopupClass, confirm),
                  NULL, NULL,
                  gimp_marshal_VOID__VOID,
                  G_TYPE_NONE, 0);

  object_class->finalize           = gimp_container_popup_finalize;

  widget_class->map                = gimp_container_popup_map;
  widget_class->button_press_event = gimp_container_popup_button_press;
  widget_class->key_press_event    = gimp_container_popup_key_press;

  klass->cancel                    = gimp_container_popup_real_cancel;
  klass->confirm                   = gimp_container_popup_real_confirm;

  binding_set = gtk_binding_set_by_class (klass);
  
  gtk_binding_entry_add_signal (binding_set, GDK_Escape, 0,
                                "cancel", 0);
  gtk_binding_entry_add_signal (binding_set, GDK_Return, 0,
                                "confirm", 0);
  gtk_binding_entry_add_signal (binding_set, GDK_KP_Enter, 0,
                                "confirm", 0);
  gtk_binding_entry_add_signal (binding_set, GDK_space, 0,
                                "confirm", 0);
}

static void
gimp_container_popup_init (GimpContainerPopup *popup)
{
  popup->frame = gtk_frame_new (NULL);
  gtk_frame_set_shadow_type (GTK_FRAME (popup->frame), GTK_SHADOW_OUT);
  gtk_container_add (GTK_CONTAINER (popup), popup->frame);
  gtk_widget_show (popup->frame);
}

static void
gimp_container_popup_finalize (GObject *object)
{
  GimpContainerPopup *popup;

  popup = GIMP_CONTAINER_POPUP (object);

  if (popup->context)
    {
      g_object_unref (popup->context);
      popup->context = NULL;
    }

  if (popup->dialog_identifier)
    {
      g_free (popup->dialog_identifier);
      popup->dialog_identifier = NULL;
    }

  if (popup->dialog_stock_id)
    {
      g_free (popup->dialog_stock_id);
      popup->dialog_stock_id = NULL;
    }

  if (popup->dialog_tooltip)
    {
      g_free (popup->dialog_tooltip);
      popup->dialog_tooltip = NULL;
    }

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static void
gimp_container_popup_map (GtkWidget *widget)
{
  GTK_WIDGET_CLASS (parent_class)->map (widget);

  /*  grab with owner_events == TRUE so the popup's widgets can
   *  receive events. we filter away events outside this toplevel
   *  away in button_press()
   */
  if (gdk_pointer_grab (widget->window, TRUE,
                        GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK |
                        GDK_POINTER_MOTION_MASK,
                        NULL, NULL, GDK_CURRENT_TIME) == 0)
    {
      if (gdk_keyboard_grab (widget->window, TRUE, GDK_CURRENT_TIME) == 0)
        {
          gtk_grab_add (widget);
          return;
        }
      else
        {
          gdk_display_pointer_ungrab (gdk_drawable_get_display (widget->window),
                                      GDK_CURRENT_TIME);
        }
    }

  /*  if we could not grab, destroy the popup instead of leaving it
   *  around uncloseable.
   */
  g_signal_emit (widget, popup_signals[CANCEL], 0);
}

static gboolean
gimp_container_popup_button_press (GtkWidget      *widget,
                                   GdkEventButton *bevent)
{
  GimpContainerPopup *popup;
  GtkWidget          *event_widget;
  gboolean            cancel = FALSE;

  popup = GIMP_CONTAINER_POPUP (widget);

  event_widget =  gtk_get_event_widget ((GdkEvent *) bevent);

  if (event_widget == widget)
    {
      /*  the event was on the popup, which can either be really on the
       *  popup or outside gimp (owner_events == TRUE, see map())
       */
      if (bevent->x < 0                        ||
          bevent->y < 0                        ||
          bevent->x > widget->allocation.width ||
          bevent->y > widget->allocation.height)
        {
          /*  the event was outsde gimp  */

          cancel = TRUE;
        }
    }
  else if (gtk_widget_get_toplevel (event_widget) != widget)
    {
      /*  the event was on a gimp widget, but not inside the popup  */

      cancel = TRUE;
    }

  if (cancel)
    g_signal_emit (widget, popup_signals[CANCEL], 0);

  return cancel;
}

static gboolean
gimp_container_popup_key_press (GtkWidget   *widget,
                                GdkEventKey *kevent)
{
  GtkBindingSet *binding_set;

  binding_set =
    gtk_binding_set_by_class (GIMP_CONTAINER_POPUP_GET_CLASS (widget));

  /*  invoke the popup's binding entries manually, because otherwise
   *  the focus widget (GtkTreeView e.g.) would consume it
   */
  if (gtk_binding_set_activate (binding_set,
                                kevent->keyval,
                                kevent->state,
                                GTK_OBJECT (widget)))
    {
      return TRUE;
    }

  return GTK_WIDGET_CLASS (parent_class)->key_press_event (widget, kevent);
}

static void
gimp_container_popup_real_cancel (GimpContainerPopup *popup)
{
  GtkWidget *widget;

  widget = GTK_WIDGET (popup);

  if (gtk_grab_get_current () == widget)
    gtk_grab_remove (widget);

  gtk_widget_destroy (widget);
}

static void
gimp_container_popup_real_confirm (GimpContainerPopup *popup)
{
  GtkWidget  *widget;
  GimpObject *object;

  widget = GTK_WIDGET (popup);

  object = gimp_context_get_by_type (popup->context,
                                     popup->container->children_type);
  gimp_context_set_by_type (popup->orig_context,
                            popup->container->children_type,
                            object);

  if (gtk_grab_get_current () == widget)
    gtk_grab_remove (widget);

  gtk_widget_destroy (widget);
}

static void
gimp_container_popup_context_changed (GimpContext        *context,
                                      GimpViewable       *viewable,
                                      GimpContainerPopup *popup)
{
  GdkEvent *current_event;
  gboolean  confirm = FALSE;

  current_event = gtk_get_current_event ();

  if (current_event)
    {
      if (((GdkEventAny *) current_event)->type == GDK_BUTTON_PRESS ||
          ((GdkEventAny *) current_event)->type == GDK_BUTTON_RELEASE)
        confirm = TRUE;

      gdk_event_free (current_event);
    }

  if (confirm)
    g_signal_emit (popup, popup_signals[CONFIRM], 0);
}

GtkWidget *
gimp_container_popup_new (GimpContainer     *container,
                          GimpContext       *context,
                          GimpDialogFactory *dialog_factory,
                          const gchar       *dialog_identifier,
                          const gchar       *dialog_stock_id,
                          const gchar       *dialog_tooltip)
{
  GimpContainerPopup *popup;

  g_return_val_if_fail (GIMP_IS_CONTAINER (container), NULL);
  g_return_val_if_fail (GIMP_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (dialog_factory == NULL ||
                        GIMP_IS_DIALOG_FACTORY (dialog_factory), NULL);
  if (dialog_factory)
    {
      g_return_val_if_fail (dialog_identifier != NULL, NULL);
      g_return_val_if_fail (dialog_stock_id != NULL, NULL);
      g_return_val_if_fail (dialog_tooltip != NULL, NULL);
    }

  popup = g_object_new (GIMP_TYPE_CONTAINER_POPUP,
                        "type", GTK_WINDOW_POPUP,
                        NULL);
  gtk_window_set_resizable (GTK_WINDOW (popup), FALSE);

  popup->container    = container;
  popup->orig_context = context;
  popup->context      = gimp_context_new (context->gimp, "popup", context);

  g_signal_connect (popup->context,
                    gimp_context_type_to_signal_name (container->children_type),
                    G_CALLBACK (gimp_container_popup_context_changed),
                    popup);

  if (dialog_factory)
    {
      popup->dialog_factory    = dialog_factory;
      popup->dialog_identifier = g_strdup (dialog_identifier);
      popup->dialog_stock_id   = g_strdup (dialog_stock_id);
      popup->dialog_tooltip    = g_strdup (dialog_tooltip);
    }

  gimp_container_popup_create_view (popup, GIMP_VIEW_TYPE_LIST);

  return GTK_WIDGET (popup);
}

void
gimp_container_popup_show (GimpContainerPopup *popup,
                           GtkWidget          *widget)
{
  GtkRequisition requisition;
  gint           orig_x;
  gint           orig_y;
  gint           scr_width;
  gint           scr_height;
  gint           x;
  gint           y;

  g_return_if_fail (GIMP_IS_CONTAINER_POPUP (popup));
  g_return_if_fail (GTK_IS_WIDGET (widget));

  gtk_widget_size_request (GTK_WIDGET (popup), &requisition);
  gdk_window_get_origin (widget->window, &orig_x, &orig_y);

  if (GTK_WIDGET_NO_WINDOW (widget))
    {
      orig_x += widget->allocation.x;
      orig_y += widget->allocation.y;
    }

  scr_width  = gdk_screen_width ();
  scr_height = gdk_screen_height ();

  x = orig_x;
  y = orig_y + widget->allocation.height;

  if ((x + requisition.width) > scr_width)
    x += (widget->allocation.width - requisition.width);

  if ((y + requisition.height) > scr_height)
    y = orig_y - requisition.height;

  gtk_window_move (GTK_WINDOW (popup), x, y);

  gtk_widget_show (GTK_WIDGET (popup));
}

static void
gimp_container_popup_create_view (GimpContainerPopup *popup,
                                  GimpViewType        view_type)
{
  GimpEditor *editor;
  GtkWidget  *button;

  popup->editor = g_object_new (GIMP_TYPE_CONTAINER_EDITOR, NULL);
  gimp_container_editor_construct (popup->editor,
                                   view_type,
                                   popup->container,
                                   popup->context,
                                   GIMP_PREVIEW_SIZE_SMALL, 1,
                                   FALSE, /* reorderable */
                                   NULL, NULL);

  gimp_container_view_set_size_request (GIMP_CONTAINER_VIEW (GIMP_CONTAINER_EDITOR (popup->editor)->view),
                                        6 * (GIMP_PREVIEW_SIZE_SMALL + 2),
                                        8 * (GIMP_PREVIEW_SIZE_SMALL + 2));

  if (GIMP_IS_CONTAINER_GRID_VIEW (popup->editor->view))
    gtk_widget_hide (GIMP_CONTAINER_GRID_VIEW (popup->editor->view)->name_label);

  gtk_container_add (GTK_CONTAINER (popup->frame), GTK_WIDGET (popup->editor));
  gtk_widget_show (GTK_WIDGET (popup->editor));

  editor = GIMP_EDITOR (popup->editor->view);

  gimp_editor_add_button (editor, GTK_STOCK_ZOOM_OUT,
                          _("Smaller Previews"), NULL,
                          G_CALLBACK (gimp_container_popup_smaller_clicked),
                          NULL,
                          popup);
  gimp_editor_add_button (editor, GTK_STOCK_ZOOM_IN,
                          _("Larger Previews"), NULL,
                          G_CALLBACK (gimp_container_popup_larger_clicked),
                          NULL,
                          popup);

  button = gimp_editor_add_stock_box (editor, GIMP_TYPE_VIEW_TYPE, "gimp",
                                      G_CALLBACK (gimp_container_popup_view_type_toggled),
                                      popup);
  gimp_radio_group_set_active (GTK_RADIO_BUTTON (button),
                               GINT_TO_POINTER (view_type));

  if (popup->dialog_factory)
    gimp_editor_add_button (editor, popup->dialog_stock_id,
                            popup->dialog_tooltip, NULL,
                            G_CALLBACK (gimp_container_popup_dialog_clicked),
                            NULL,
                            popup);

  gtk_widget_grab_focus (GTK_WIDGET (popup->editor));
}

static void
gimp_container_popup_smaller_clicked (GtkWidget          *button,
                                      GimpContainerPopup *popup)
{
  gint preview_size;

  preview_size = MAX (GIMP_PREVIEW_SIZE_TINY,
                      popup->editor->view->preview_size * 0.8);

  gimp_container_view_set_preview_size (popup->editor->view,
                                        preview_size, 1);
}

static void
gimp_container_popup_larger_clicked (GtkWidget          *button,
                                     GimpContainerPopup *popup)
{
  gint preview_size;

  preview_size = MIN (GIMP_PREVIEW_SIZE_HUGE,
                      popup->editor->view->preview_size * 1.2);

  gimp_container_view_set_preview_size (popup->editor->view,
                                        preview_size, 1);
}

static void
gimp_container_popup_view_type_toggled (GtkWidget          *button,
                                        GimpContainerPopup *popup)
{
  if (GTK_TOGGLE_BUTTON (button)->active)
    {
      GimpViewType view_type;

      view_type = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (button),
                                                      "gimp-item-data"));

      switch (view_type)
        {
        case GIMP_VIEW_TYPE_LIST:
          if (GIMP_IS_CONTAINER_TREE_VIEW (popup->editor->view))
            return;
          break;

        case GIMP_VIEW_TYPE_GRID:
          if (GIMP_IS_CONTAINER_GRID_VIEW (popup->editor->view))
            return;
          break;
        }

      gtk_container_remove (GTK_CONTAINER (popup->frame),
                            GTK_WIDGET (popup->editor));
      gimp_container_popup_create_view (popup, view_type);
    }
}

static void
gimp_container_popup_dialog_clicked (GtkWidget          *button,
                                     GimpContainerPopup *popup)
{
  gimp_dialog_factory_dialog_raise (popup->dialog_factory,
                                    popup->dialog_identifier, -1);
  g_signal_emit (popup, popup_signals[CONFIRM], 0);
}

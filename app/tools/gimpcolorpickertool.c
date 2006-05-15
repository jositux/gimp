/* The GIMP -- an image manipulation program
 * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others
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

#include "libgimpcolor/gimpcolor.h"
#include "libgimpconfig/gimpconfig.h"
#include "libgimpwidgets/gimpwidgets.h"

#include "tools-types.h"

#include "core/gimp.h"
#include "core/gimpdrawable.h"
#include "core/gimpimage.h"
#include "core/gimptoolinfo.h"

#include "widgets/gimpcolorframe.h"
#include "widgets/gimpcolormapeditor.h"
#include "widgets/gimpdialogfactory.h"
#include "widgets/gimpdockable.h"
#include "widgets/gimphelp-ids.h"
#include "widgets/gimppaletteeditor.h"
#include "widgets/gimpsessioninfo.h"
#include "widgets/gimptooldialog.h"
#include "widgets/gimpviewabledialog.h"

#include "display/gimpdisplay.h"

#include "gimpcolorpickeroptions.h"
#include "gimpcolorpickertool.h"
#include "gimptoolcontrol.h"

#include "gimp-intl.h"


/*  local function prototypes  */

static GObject * gimp_color_picker_tool_constructor  (GType            type,
                                                      guint            n_params,
                                                      GObjectConstructParam *params);
static void      gimp_color_picker_tool_finalize     (GObject         *object);

static void      gimp_color_picker_tool_control      (GimpTool        *tool,
                                                      GimpToolAction   action,
                                                      GimpDisplay     *display);
static void      gimp_color_picker_tool_modifier_key (GimpTool        *tool,
                                                      GdkModifierType  key,
                                                      gboolean         press,
                                                      GdkModifierType  state,
                                                      GimpDisplay     *display);
static void      gimp_color_picker_tool_oper_update  (GimpTool        *tool,
                                                      GimpCoords      *coords,
                                                      GdkModifierType  state,
                                                      gboolean         proximity,
                                                      GimpDisplay     *display);

static void      gimp_color_picker_tool_picked       (GimpColorTool   *color_tool,
                                                      GimpColorPickState  pick_state,
                                                      GimpImageType    sample_type,
                                                      GimpRGB         *color,
                                                      gint             color_index);

static void   gimp_color_picker_tool_info_create (GimpColorPickerTool *picker_tool);
static void gimp_color_picker_tool_info_response (GtkWidget           *widget,
                                                  gint                 response_id,
                                                  GimpColorPickerTool *picker_tool);
static void   gimp_color_picker_tool_info_update (GimpColorPickerTool *picker_tool,
                                                  GimpImageType        sample_type,
                                                  GimpRGB             *color,
                                                  gint                 color_index);


G_DEFINE_TYPE (GimpColorPickerTool, gimp_color_picker_tool,
               GIMP_TYPE_COLOR_TOOL)

#define parent_class gimp_color_picker_tool_parent_class


void
gimp_color_picker_tool_register (GimpToolRegisterCallback  callback,
                                 gpointer                  data)
{
  (* callback) (GIMP_TYPE_COLOR_PICKER_TOOL,
                GIMP_TYPE_COLOR_PICKER_OPTIONS,
                gimp_color_picker_options_gui,
                0,
                "gimp-color-picker-tool",
                _("Color Picker"),
                _("Pick colors from the image"),
                N_("C_olor Picker"), "O",
                NULL, GIMP_HELP_TOOL_COLOR_PICKER,
                GIMP_STOCK_TOOL_COLOR_PICKER,
                data);
}

static void
gimp_color_picker_tool_class_init (GimpColorPickerToolClass *klass)
{
  GObjectClass       *object_class     = G_OBJECT_CLASS (klass);
  GimpToolClass      *tool_class       = GIMP_TOOL_CLASS (klass);
  GimpColorToolClass *color_tool_class = GIMP_COLOR_TOOL_CLASS (klass);

  object_class->constructor = gimp_color_picker_tool_constructor;
  object_class->finalize    = gimp_color_picker_tool_finalize;

  tool_class->control       = gimp_color_picker_tool_control;
  tool_class->modifier_key  = gimp_color_picker_tool_modifier_key;
  tool_class->oper_update   = gimp_color_picker_tool_oper_update;

  color_tool_class->picked  = gimp_color_picker_tool_picked;
}

static void
gimp_color_picker_tool_init (GimpColorPickerTool *tool)
{
  GimpColorTool *color_tool = GIMP_COLOR_TOOL (tool);

  color_tool->pick_mode = GIMP_COLOR_PICK_MODE_FOREGROUND;
}

static GObject *
gimp_color_picker_tool_constructor (GType                  type,
                                    guint                  n_params,
                                    GObjectConstructParam *params)
{
  GObject  *object;
  GimpTool *tool;

  object = G_OBJECT_CLASS (parent_class)->constructor (type, n_params, params);

  tool = GIMP_TOOL (object);

  gimp_color_tool_enable (GIMP_COLOR_TOOL (object),
                          GIMP_COLOR_OPTIONS (tool->tool_info->tool_options));

  return object;
}

static void
gimp_color_picker_tool_finalize (GObject *object)
{
  GimpColorPickerTool *picker_tool = GIMP_COLOR_PICKER_TOOL (object);

  if (picker_tool->dialog)
    gimp_color_picker_tool_info_response (NULL, GTK_RESPONSE_CLOSE,
                                          picker_tool);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static void
gimp_color_picker_tool_control (GimpTool       *tool,
                                GimpToolAction  action,
                                GimpDisplay    *display)
{
  GimpColorPickerTool *picker_tool = GIMP_COLOR_PICKER_TOOL (tool);

  switch (action)
    {
    case HALT:
      if (picker_tool->dialog)
        gimp_color_picker_tool_info_response (NULL, GTK_RESPONSE_CLOSE,
                                              picker_tool);
      break;

    default:
      break;
    }

  GIMP_TOOL_CLASS (parent_class)->control (tool, action, display);
}

static void
gimp_color_picker_tool_modifier_key (GimpTool        *tool,
                                     GdkModifierType  key,
                                     gboolean         press,
                                     GdkModifierType  state,
                                     GimpDisplay     *display)
{
  GimpColorPickerOptions *options;

  options = GIMP_COLOR_PICKER_OPTIONS (tool->tool_info->tool_options);

  if (key == GDK_SHIFT_MASK)
    {
      g_object_set (options, "use-info-window", ! options->use_info_window,
                    NULL);
    }
  else if (key == GDK_CONTROL_MASK)
    {
       switch (options->pick_mode)
        {
        case GIMP_COLOR_PICK_MODE_FOREGROUND:
          g_object_set (options, "pick-mode", GIMP_COLOR_PICK_MODE_BACKGROUND,
                        NULL);
          break;

        case GIMP_COLOR_PICK_MODE_BACKGROUND:
          g_object_set (options, "pick-mode", GIMP_COLOR_PICK_MODE_FOREGROUND,
                        NULL);
          break;

        default:
          break;
        }

    }
}

static void
gimp_color_picker_tool_oper_update (GimpTool        *tool,
                                    GimpCoords      *coords,
                                    GdkModifierType  state,
                                    gboolean         proximity,
                                    GimpDisplay     *display)
{
  GimpColorPickerOptions *options;

  options = GIMP_COLOR_PICKER_OPTIONS (tool->tool_info->tool_options);

  GIMP_COLOR_TOOL (tool)->pick_mode = options->pick_mode;

  GIMP_TOOL_CLASS (parent_class)->oper_update (tool, coords, state, proximity,
                                               display);
}

static void
gimp_color_picker_tool_picked (GimpColorTool      *color_tool,
                               GimpColorPickState  pick_state,
                               GimpImageType       sample_type,
                               GimpRGB            *color,
                               gint                color_index)
{
  GimpTool               *tool        = GIMP_TOOL (color_tool);
  GimpColorPickerTool    *picker_tool = GIMP_COLOR_PICKER_TOOL (color_tool);
  GimpColorPickerOptions *options;
  GimpContext            *user_context;

  options = GIMP_COLOR_PICKER_OPTIONS (color_tool->options);

  if (options->use_info_window && ! picker_tool->dialog)
    gimp_color_picker_tool_info_create (picker_tool);

  if (picker_tool->dialog)
    gimp_color_picker_tool_info_update (picker_tool, sample_type,
                                        color, color_index);

  user_context = gimp_get_user_context (tool->display->image->gimp);

  if ((options->pick_mode == GIMP_COLOR_PICK_MODE_FOREGROUND ||
       options->pick_mode == GIMP_COLOR_PICK_MODE_BACKGROUND) &&
      GIMP_IMAGE_TYPE_IS_INDEXED (sample_type))
    {
      GimpDialogFactory *dialog_factory;
      GimpSessionInfo   *info;

      dialog_factory = gimp_dialog_factory_from_name ("dock");
      info = gimp_dialog_factory_find_session_info (dialog_factory,
                                                    "gimp-indexed-palette");

      if (info && info->widget)
        {
          GtkWidget *colormap_editor;

          colormap_editor = gtk_bin_get_child (GTK_BIN (info->widget));

          gtk_adjustment_set_value
            (GIMP_COLORMAP_EDITOR (colormap_editor)->index_adjustment,
             color_index);
        }
    }

  switch (options->pick_mode)
    {
    case GIMP_COLOR_PICK_MODE_NONE:
      break;

    case GIMP_COLOR_PICK_MODE_FOREGROUND:
      gimp_context_set_foreground (user_context, color);
      break;

    case GIMP_COLOR_PICK_MODE_BACKGROUND:
      gimp_context_set_background (user_context, color);
      break;

    case GIMP_COLOR_PICK_MODE_PALETTE:
      {
        GimpDialogFactory *dialog_factory;
        GdkScreen         *screen;
        GtkWidget         *dockable;

        dialog_factory = gimp_dialog_factory_from_name ("dock");
        screen = gtk_widget_get_screen (tool->display->shell);
        dockable = gimp_dialog_factory_dialog_raise (dialog_factory, screen,
                                                     "gimp-palette-editor",
                                                     -1);

        if (dockable)
          {
            GtkWidget *palette_editor;
            GimpData  *data;

            /* don't blink like mad when updating */
            if (pick_state == GIMP_COLOR_PICK_STATE_UPDATE)
              gimp_dockable_blink_cancel (GIMP_DOCKABLE (dockable));

            palette_editor = gtk_bin_get_child (GTK_BIN (dockable));

            data = gimp_data_editor_get_data (GIMP_DATA_EDITOR (palette_editor));

            if (! data)
              {
                data = GIMP_DATA (gimp_context_get_palette (user_context));

                gimp_data_editor_set_data (GIMP_DATA_EDITOR (palette_editor),
                                           data);
              }

            gimp_palette_editor_pick_color (GIMP_PALETTE_EDITOR (palette_editor),
                                            color, pick_state);
          }
      }
      break;
    }
}

static void
gimp_color_picker_tool_info_create (GimpColorPickerTool *picker_tool)
{
  GimpTool  *tool = GIMP_TOOL (picker_tool);
  GtkWidget *hbox;
  GtkWidget *frame;
  GimpRGB    color;

  g_return_if_fail (tool->drawable != NULL);

  picker_tool->dialog = gimp_tool_dialog_new (tool->tool_info,
                                              NULL /* tool->display->shell */,
                                              _("Color Picker Information"),

                                              GTK_STOCK_CLOSE,
                                              GTK_RESPONSE_CLOSE,

                                              NULL);

  gtk_window_set_focus_on_map (GTK_WINDOW (picker_tool->dialog), FALSE);

  gimp_viewable_dialog_set_viewable (GIMP_VIEWABLE_DIALOG (picker_tool->dialog),
                                     GIMP_VIEWABLE (tool->drawable));

  g_signal_connect (picker_tool->dialog, "response",
                    G_CALLBACK (gimp_color_picker_tool_info_response),
                    picker_tool);

  hbox = gtk_hbox_new (FALSE, 6);
  gtk_container_set_border_width (GTK_CONTAINER (hbox), 6);
  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (picker_tool->dialog)->vbox), hbox,
                      FALSE, FALSE, 0);
  gtk_widget_show (hbox);

  picker_tool->color_frame1 = gimp_color_frame_new ();
  gimp_color_frame_set_mode (GIMP_COLOR_FRAME (picker_tool->color_frame1),
                             GIMP_COLOR_FRAME_MODE_PIXEL);
  gtk_box_pack_start (GTK_BOX (hbox), picker_tool->color_frame1,
                      FALSE, FALSE, 0);
  gtk_widget_show (picker_tool->color_frame1);

  picker_tool->color_frame2 = gimp_color_frame_new ();
  gimp_color_frame_set_mode (GIMP_COLOR_FRAME (picker_tool->color_frame2),
                             GIMP_COLOR_FRAME_MODE_RGB);
  gtk_box_pack_start (GTK_BOX (hbox), picker_tool->color_frame2,
                      FALSE, FALSE, 0);
  gtk_widget_show (picker_tool->color_frame2);

  frame = gtk_frame_new (NULL);
  gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
  gtk_box_pack_start (GTK_BOX (hbox), frame, TRUE, TRUE, 0);
  gtk_widget_show (frame);

  gimp_rgba_set (&color, 0.0, 0.0, 0.0, 0.0);
  picker_tool->color_area =
    gimp_color_area_new (&color,
                         gimp_drawable_has_alpha (tool->drawable) ?
                         GIMP_COLOR_AREA_LARGE_CHECKS :
                         GIMP_COLOR_AREA_FLAT,
                         GDK_BUTTON1_MASK | GDK_BUTTON2_MASK);
  gtk_widget_set_size_request (picker_tool->color_area, 48, -1);
  gtk_drag_dest_unset (picker_tool->color_area);
  gtk_container_add (GTK_CONTAINER (frame), picker_tool->color_area);
  gtk_widget_show (picker_tool->color_area);
}

static void
gimp_color_picker_tool_info_response (GtkWidget           *widget,
                                      gint                 response_id,
                                      GimpColorPickerTool *picker_tool)
{
  gtk_widget_destroy (picker_tool->dialog);

  picker_tool->dialog       = NULL;
  picker_tool->color_area   = NULL;
  picker_tool->color_frame1 = NULL;
  picker_tool->color_frame2 = NULL;
}

static void
gimp_color_picker_tool_info_update (GimpColorPickerTool *picker_tool,
                                    GimpImageType        sample_type,
                                    GimpRGB             *color,
                                    gint                 color_index)
{
  gimp_color_area_set_color (GIMP_COLOR_AREA (picker_tool->color_area),
                             color);

  gimp_color_frame_set_color (GIMP_COLOR_FRAME (picker_tool->color_frame1),
                              sample_type, color, color_index);
  gimp_color_frame_set_color (GIMP_COLOR_FRAME (picker_tool->color_frame2),
                              sample_type, color, color_index);

  if (GTK_WIDGET_VISIBLE (picker_tool->dialog))
    gdk_window_show (picker_tool->dialog->window);
  else
    gtk_widget_show (picker_tool->dialog);
}

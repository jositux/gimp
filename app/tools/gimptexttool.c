/* The GIMP -- an image manipulation program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
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

#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>
#include <pango/pangoft2.h>

#include "libgimpwidgets/gimpwidgets.h"

#include "tools-types.h"

#include "paint-funcs/paint-funcs.h"

#include "base/base-types.h"
#include "base/pixel-region.h"
#include "base/tile-manager.h"

#include "core/gimpchannel.h"
#include "core/gimpimage.h"
#include "core/gimpimage-mask.h"
#include "core/gimplayer.h"

#include "widgets/gimpfontselection.h"

#include "gimptexttool.h"
#include "gimptool.h"
#include "tool_manager.h"
#include "tool_options.h"

#include "app_procs.h"
#include "gdisplay.h"
#include "floating_sel.h"
#include "undo_types.h"
#include "undo.h"

#include "libgimp/gimpintl.h"

#define DEFAULT_FONT "sans Normal"


/*  the text tool structures  */

typedef struct _TextOptions TextOptions;

struct _TextOptions
{
  GimpToolOptions  tool_options;
  GtkWidget       *font_selection;
};


static void   gimp_text_tool_class_init      (GimpTextToolClass *klass);
static void   gimp_text_tool_init            (GimpTextTool      *tool);

static void   gimp_text_tool_finalize        (GObject         *object);

static void   text_tool_control              (GimpTool        *tool,
					      ToolAction       tool_action,
					      GDisplay        *gdisp);
static void   text_tool_button_press         (GimpTool        *tool,
					      GdkEventButton  *bevent,
					      GDisplay        *gdisp);
static void   text_tool_button_release       (GimpTool        *tool,
					      GdkEventButton  *bevent,
					      GDisplay        *gdisp);
static void   text_tool_cursor_update        (GimpTool        *tool,
					      GdkEventMotion  *mevent,
					      GDisplay        *gdisp);
static void   text_tool_render               (GimpTextTool    *text_tool);

static TextOptions * text_tool_options_new   (GimpTextTool    *text_tool);
static void          text_tool_options_reset (GimpToolOptions *tool_options);


/*  local variables  */

static TextOptions   *text_tool_options = NULL;
static GimpToolClass *parent_class      = NULL;


/*  functions  */

void
gimp_text_tool_register (Gimp *gimp)
{
  tool_manager_register_tool (gimp,
			      GIMP_TYPE_TEXT_TOOL,
			      FALSE,
			      "gimp:text_tool",
			      _("Text Tool"),
			      _("Add text to the image"),
			      N_("/Tools/Text"), "T",
			      NULL, "tools/text.html",
			      GIMP_STOCK_TOOL_TEXT);
}

GType
gimp_text_tool_get_type (void)
{
  static GType tool_type = 0;

  if (! tool_type)
    {
      static const GTypeInfo tool_info =
      {
        sizeof (GimpTextToolClass),
	(GBaseInitFunc) NULL,
	(GBaseFinalizeFunc) NULL,
	(GClassInitFunc) gimp_text_tool_class_init,
	NULL,		/* class_finalize */
	NULL,		/* class_data     */
	sizeof (GimpTextTool),
	0,              /* n_preallocs    */
	(GInstanceInitFunc) gimp_text_tool_init,
      };

      tool_type = g_type_register_static (GIMP_TYPE_TOOL, "GimpTextTool", 
                                          &tool_info, 0);
    }

  return tool_type;
}

static void
gimp_text_tool_class_init (GimpTextToolClass *klass)
{
  GObjectClass  *object_class;
  GimpToolClass *tool_class;

  object_class = G_OBJECT_CLASS (klass);
  tool_class   = GIMP_TOOL_CLASS (klass);

  parent_class = gtk_type_class (GIMP_TYPE_TOOL);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = gimp_text_tool_finalize;

  tool_class->control        = text_tool_control;
  tool_class->button_press   = text_tool_button_press;
  tool_class->button_release = text_tool_button_release;
  tool_class->cursor_update  = text_tool_cursor_update;
}

static void
gimp_text_tool_init (GimpTextTool *text_tool)
{
  GimpTool *tool;

  tool = GIMP_TOOL (text_tool);
 
  text_tool->pango_context = pango_ft2_get_context ();

  /*  The tool options  */
  if (! text_tool_options)
    {
      text_tool_options = text_tool_options_new (text_tool);

      tool_manager_register_tool_options (GIMP_TYPE_TEXT_TOOL,
					  (GimpToolOptions *) text_tool_options);
    }

  tool->tool_cursor = GIMP_TEXT_TOOL_CURSOR;
  tool->scroll_lock = TRUE;  /* Disallow scrolling */
}

static void
gimp_text_tool_finalize (GObject *object)
{
  GimpTextTool *text_tool;

  text_tool = GIMP_TEXT_TOOL (object);

  if (text_tool->pango_context)
    {
      g_object_unref (text_tool->pango_context);
      text_tool->pango_context = NULL;
    }

  if (G_OBJECT_CLASS (parent_class)->finalize)
    G_OBJECT_CLASS (parent_class)->finalize (object);
}

static void
text_tool_options_reset (GimpToolOptions *tool_options)
{
  TextOptions *options;

  options = (TextOptions *) tool_options;
}

static TextOptions *
text_tool_options_new (GimpTextTool *text_tool)
{
  TextOptions *options;
  GtkWidget   *vbox;

  options = g_new0 (TextOptions, 1);
  tool_options_init ((GimpToolOptions *) options, text_tool_options_reset);

  /*  the main vbox  */
  vbox = options->tool_options.main_vbox;

  options->font_selection = gimp_font_selection_new (text_tool->pango_context);
  gimp_font_selection_set_fontname (GIMP_FONT_SELECTION (options->font_selection), DEFAULT_FONT);
  gtk_box_pack_start (GTK_BOX (vbox), GTK_WIDGET (options->font_selection),
                      FALSE, FALSE, 0);
  gtk_widget_show (options->font_selection);
  
  return options;
}

static void
text_tool_control (GimpTool   *tool,
		   ToolAction  action,
		   GDisplay   *gdisp)
{
  switch (action)
    {
    case PAUSE:
      break;

    case RESUME:
      break;

    case HALT:
      break;

    default:
      break;
    }
}

static void
text_tool_button_press (GimpTool       *tool,
			GdkEventButton *bevent,
			GDisplay       *gdisp)
{
  GimpTextTool *text_tool;

  text_tool = GIMP_TEXT_TOOL (tool);

  text_tool->gdisp = gdisp;

  tool->state = ACTIVE;
  tool->gdisp = gdisp;

  gdisplay_untransform_coords (gdisp, bevent->x, bevent->y,
			       &text_tool->click_x, &text_tool->click_y,
			       TRUE, 0);
}

static void
text_tool_button_release (GimpTool       *tool,
			  GdkEventButton *bevent,
			  GDisplay       *gdisp)
{
  text_tool_render (GIMP_TEXT_TOOL (tool));

  tool->state = INACTIVE;
}

static void
text_tool_cursor_update (GimpTool       *tool,
			 GdkEventMotion *mevent,
			 GDisplay       *gdisp)
{
  gdisplay_install_tool_cursor (gdisp,
				GDK_XTERM,
				GIMP_TEXT_TOOL_CURSOR,
				GIMP_CURSOR_MODIFIER_NONE);
}

static void
text_tool_render (GimpTextTool *text_tool)
{
  GDisplay             *gdisp;
  PangoFontDescription *font_desc;
  gchar                *fontname;
  gchar                *text;

  gdisp = text_tool->gdisp;
  
  font_desc = gimp_font_selection_get_font_desc (GIMP_FONT_SELECTION (text_tool_options->font_selection));
  
  font_desc->size = PANGO_SCALE * 60;  /* FIXME */
  fontname = pango_font_description_to_string (font_desc);
  pango_font_description_free (font_desc);

  text = "gimp";  /* FIXME */

  text_render (gdisp->gimage, gimp_image_active_drawable (gdisp->gimage),
	       text_tool->click_x, text_tool->click_y,
	       fontname, text, 0 /*border*/, TRUE /* antialias */);

  g_free (fontname);

  gdisplays_flush ();
}

GimpLayer *
text_render (GimpImage    *gimage,
	     GimpDrawable *drawable,
	     gint          text_x,
	     gint          text_y,
	     const gchar  *fontname,
	     const gchar  *text,
	     gint          border,
	     gint          antialias)
{
  PangoFontDescription *font_desc;
  PangoContext         *context;
  PangoLayout          *layout;
  PangoRectangle        rect;
  GimpImageType         layer_type;
  GimpLayer            *layer;

  g_return_val_if_fail (fontname != NULL, FALSE);
  g_return_val_if_fail (text != NULL, FALSE);

  /*  determine the layer type  */
  if (drawable)
    layer_type = gimp_drawable_type_with_alpha (drawable);
  else
    layer_type = gimp_image_base_type_with_alpha (gimage);

  font_desc = pango_font_description_from_string (fontname);
  g_return_val_if_fail (font_desc != NULL, NULL);
  if (!font_desc)
    return NULL;
  
  context = pango_ft2_get_context ();
  layout = pango_layout_new (context);
  pango_layout_set_font_description (layout, font_desc);
  pango_font_description_free (font_desc);
  pango_layout_set_text (layout, text, -1);

  pango_layout_get_pixel_extents (layout, &rect, NULL);

  if (rect.width > 0 && rect.height > 0)
    {
      TileManager *mask;
      PixelRegion textPR, maskPR;
      FT_Bitmap   bitmap;
      guchar      color[MAX_CHANNELS];
      gint        y;

      bitmap.width      = rect.width;
      bitmap.rows       = rect.height;
      bitmap.pitch      = rect.width;
      if (bitmap.pitch & 3)
        bitmap.pitch += 4 - (bitmap.pitch & 3);
      bitmap.buffer     = g_malloc0 (bitmap.rows * bitmap.pitch);
      bitmap.num_grays  = 256;
      bitmap.pixel_mode = ft_pixel_mode_grays;
      
      pango_ft2_render_layout (&bitmap, layout, 0, 0);
      
      mask = tile_manager_new (rect.width, rect.height, 1);
      pixel_region_init (&maskPR, mask, 0, 0, rect.width, rect.height, TRUE);

      for (y = 0; y < bitmap.rows; y++)
        pixel_region_set_row (&maskPR, 0, y, bitmap.width, 
                              bitmap.buffer + y * bitmap.pitch);

      g_free (bitmap.buffer);

      layer = gimp_layer_new (gimage, rect.width, rect.height, layer_type,
                              _("Text Layer"), OPAQUE_OPACITY, NORMAL_MODE);

      /*  color the layer buffer  */
      gimp_image_get_foreground (gimage, drawable, color);
      color[GIMP_DRAWABLE (layer)->bytes - 1] = OPAQUE_OPACITY;
      pixel_region_init (&textPR, GIMP_DRAWABLE (layer)->tiles,
			 0, 0,
			 GIMP_DRAWABLE (layer)->width,
			 GIMP_DRAWABLE (layer)->height, TRUE);
      color_region (&textPR, color);

      /*  apply the text mask  */
      pixel_region_init (&textPR, GIMP_DRAWABLE (layer)->tiles,
			 0, 0,
			 GIMP_DRAWABLE (layer)->width,
			 GIMP_DRAWABLE (layer)->height, TRUE);
      pixel_region_init (&maskPR, mask,
			 0, 0,
			 GIMP_DRAWABLE (layer)->width,
			 GIMP_DRAWABLE (layer)->height, FALSE);
      apply_mask_to_region (&textPR, &maskPR, OPAQUE_OPACITY);

      /*  Start a group undo  */
      undo_push_group_start (gimage, TEXT_UNDO);

      /*  Set the layer offsets  */
      GIMP_DRAWABLE (layer)->offset_x = text_x + rect.x;
      GIMP_DRAWABLE (layer)->offset_y = text_y + rect.y;

      /*  If there is a selection mask clear it--
       *  this might not always be desired, but in general,
       *  it seems like the correct behavior.
       */
      if (! gimage_mask_is_empty (gimage))
	gimp_channel_clear (gimp_image_get_mask (gimage));

      /*  If the drawable id is invalid, create a new layer  */
      if (drawable == NULL)
	gimp_image_add_layer (gimage, layer, -1);
      /*  Otherwise, instantiate the text as the new floating selection */
      else
	floating_sel_attach (layer, drawable);

      /*  end the group undo  */
      undo_push_group_end (gimage);

      tile_manager_destroy (mask);
    }

  g_object_unref (layout);
  g_object_unref (context);  

  return NULL;
}

gboolean
text_get_extents (const gchar *fontname,
		  const gchar *text,
		  gint        *width,
		  gint        *height,
		  gint        *ascent,
		  gint        *descent)
{
  PangoFontDescription *font_desc;
  PangoContext         *context;
  PangoLayout          *layout;
  PangoRectangle        rect;

  g_return_val_if_fail (fontname != NULL, FALSE);
  g_return_val_if_fail (text != NULL, FALSE);

  font_desc = pango_font_description_from_string (fontname);
  if (!font_desc)
    return FALSE;
  
  context = pango_ft2_get_context ();
  layout = pango_layout_new (context);
  pango_layout_set_font_description (layout, font_desc);
  pango_font_description_free (font_desc);

  pango_layout_set_text (layout, text, -1);

  pango_layout_get_pixel_extents (layout, &rect, NULL);

  if (width)
    *width = rect.width;
  if (height)
    *height = rect.height;
  if (ascent)
    *ascent = -rect.y;
  if (descent)
    *descent = rect.height + rect.y;

  g_object_unref (layout);
  g_object_unref (context);  

  return TRUE;
}

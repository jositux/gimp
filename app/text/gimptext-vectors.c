/* The GIMP -- an image manipulation program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * GimpText
 * Copyright (C) 2003  Sven Neumann <sven@gimp.org>
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

#include <glib-object.h>
#include <pango/pangoft2.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>

#include "text/text-types.h"

#include "core/gimpimage.h"

#include "vectors/gimpbezierstroke.h"
#include "vectors/gimpvectors.h"
#include "vectors/gimpanchor.h"

#include "gimptext.h"
#include "gimptext-private.h"
#include "gimptext-vectors.h"
#include "gimptextlayout.h"
#include "gimptextlayout-render.h"


/* for compatibility with older freetype versions */
#ifndef FT_GLYPH_FORMAT_OUTLINE
#define FT_GLYPH_FORMAT_OUTLINE ft_glyph_format_outline
#endif

typedef struct _RenderContext  RenderContext;

struct _RenderContext
{
  GimpVectors  *vectors;
  GimpStroke   *stroke;
  GimpAnchor   *anchor;
  gdouble       offset_x;
  gdouble       offset_y;
};


static void  gimp_text_render_vectors (PangoFont     *font,
				       PangoGlyph     glyph,
				       FT_Int32       flags,
				       FT_Matrix     *matrix,
				       gint           x,
				       gint           y,
				       RenderContext *context);


GimpVectors *
gimp_text_vectors_new (GimpImage *image,
		       GimpText  *text)
{
  GimpVectors    *vectors;
  GimpTextLayout *layout;
  RenderContext   context = { 0, };

  g_return_val_if_fail (GIMP_IS_IMAGE (image), NULL);
  g_return_val_if_fail (GIMP_IS_TEXT (text), NULL);

  vectors = gimp_vectors_new (image, NULL);

  if (text->text)
    {
      gimp_object_set_name_safe (GIMP_OBJECT (vectors), text->text);

      layout = gimp_text_layout_new (text, image);

      context.vectors = vectors;

      gimp_text_layout_render (layout,
			       (GimpTextRenderFunc) gimp_text_render_vectors,
			       &context);

      g_object_unref (layout);
    }

  return vectors;
}


static void
gimp_text_vector_coords (RenderContext   *context,
                         const FT_Vector *vector,
                         GimpCoords      *coords)
{
  coords->x        = context->offset_x + (gdouble) vector->x / 64.0;
  coords->y        = context->offset_y - (gdouble) vector->y / 64.0;
  coords->pressure = 1.0;
  coords->xtilt    = 0.5;
  coords->ytilt    = 0.5;
  coords->wheel    = 0.5;
}

static gint
moveto (FT_Vector *to,
	gpointer   data)
{
  RenderContext *context = (RenderContext *) data;
  GimpCoords     coords;

#if TEXT_DEBUG
  g_printerr ("moveto  %f, %f\n", to->x / 64.0, to->y / 64.0);
#endif

  gimp_text_vector_coords (context, to, &coords);

  context->stroke = gimp_bezier_stroke_new ();
  gimp_vectors_stroke_add (context->vectors, context->stroke);
  g_object_unref (context->stroke);

  context->anchor =
    gimp_bezier_stroke_extend (context->stroke,
                               &coords, NULL, EXTEND_SIMPLE);
  context->anchor =
    gimp_bezier_stroke_extend (context->stroke,
			       &coords, context->anchor, EXTEND_SIMPLE);
  context->anchor =
    gimp_bezier_stroke_extend (context->stroke,
			       &coords, context->anchor, EXTEND_SIMPLE);

  return 0;
}

static gint
lineto (FT_Vector *to,
	gpointer   data)
{
  RenderContext *context = (RenderContext *) data;
  GimpCoords     coords;

#if TEXT_DEBUG
  g_printerr ("lineto  %f, %f\n", to->x / 64.0, to->y / 64.0);
#endif

  if (! context->stroke)
    return 0;

  gimp_text_vector_coords (context, to, &coords);

  context->anchor =
    gimp_bezier_stroke_extend (context->stroke,
                               &coords, context->anchor, EXTEND_SIMPLE);
  context->anchor =
    gimp_bezier_stroke_extend (context->stroke,
                               &coords, context->anchor, EXTEND_SIMPLE);
  context->anchor =
    gimp_bezier_stroke_extend (context->stroke,
                               &coords, context->anchor, EXTEND_SIMPLE);

  return 0;
}

static gint
conicto (FT_Vector *ftcontrol,
	 FT_Vector *to,
	 gpointer   data)
{
  RenderContext *context = (RenderContext *) data;
  GimpCoords     coords;
  GimpCoords     control;
  GimpCoords     last;
  GList         *l;

#if TEXT_DEBUG
  g_printerr ("conicto %f, %f\n", to->x / 64.0, to->y / 64.0);
#endif

  if (! context->stroke)
    return 0;
   
  gimp_text_vector_coords (context, ftcontrol, &control);

  last = control;

  /* Find the last endpoint */
  for (l = g_list_last (context->stroke->anchors); l; l = l->prev)
    {
      GimpAnchor *anchor = l->data;

      if (anchor->type == GIMP_ANCHOR_ANCHOR)
	{
	  last = anchor->position;
	  break;
	} 
    }
  
  /* interpolate the cubic control point */
  coords =  last;
  coords.x = (last.x + 2 * control.x) * (1.0 / 3.0);
  coords.y = (last.y + 2 * control.y) * (1.0 / 3.0);
  
  context->anchor->position = coords;

  gimp_text_vector_coords (context, to, &last);

  /* interpolate the cubic control point */
  coords =  last;
  coords.x = (last.x + 2 * control.x) * (1.0 / 3.0);
  coords.y = (last.y + 2 * control.y) * (1.0 / 3.0);
  
  context->anchor =
    gimp_bezier_stroke_extend (context->stroke,
                               &coords, context->anchor, EXTEND_SIMPLE);

  context->anchor =
    gimp_bezier_stroke_extend (context->stroke,
                               &last, context->anchor, EXTEND_SIMPLE);
  context->anchor =
    gimp_bezier_stroke_extend (context->stroke,
                               &last, context->anchor, EXTEND_SIMPLE);

  return 0;
}

static gint
cubicto (FT_Vector *control1,
	 FT_Vector *control2,
	 FT_Vector *to,
	 gpointer   data)
{
  RenderContext *context = (RenderContext *) data;
  GimpCoords     coords;

#if TEXT_DEBUG
  g_printerr ("cubicto %f, %f\n", to->x / 64.0, to->y / 64.0);
#endif

  if (! context->stroke)
    return 0;

  gimp_text_vector_coords (context, control1, &coords);

  context->anchor->position = coords;

  gimp_text_vector_coords (context, control2, &coords);

  context->anchor =
    gimp_bezier_stroke_extend (context->stroke,
                               &coords, context->anchor, EXTEND_SIMPLE);

  gimp_text_vector_coords (context, to, &coords);

  context->anchor =
    gimp_bezier_stroke_extend (context->stroke,
                               &coords, context->anchor, EXTEND_SIMPLE);
  context->anchor =
    gimp_bezier_stroke_extend (context->stroke,
                               &coords, context->anchor, EXTEND_SIMPLE);

  return 0;
}


static void
gimp_text_render_vectors (PangoFont     *font,
			  PangoGlyph     pango_glyph,
			  FT_Int32       flags,
			  FT_Matrix     *trafo,
			  gint           x,
			  gint           y,
			  RenderContext *context)
{
  const FT_Outline_Funcs  outline_funcs =
  {
    moveto,
    lineto,
    conicto,
    cubicto,
    0,
    0
  };

  FT_Face   face;
  FT_Glyph  glyph;

  face = pango_ft2_font_get_face (font);

  FT_Load_Glyph (face, (FT_UInt) pango_glyph, flags);

  FT_Get_Glyph (face->glyph, &glyph);

  if (face->glyph->format == FT_GLYPH_FORMAT_OUTLINE)
    {
      FT_OutlineGlyph outline_glyph = (FT_OutlineGlyph) glyph;

      context->offset_x = (gdouble) x / PANGO_SCALE;
      context->offset_y = (gdouble) y / PANGO_SCALE;

      FT_Outline_Decompose (&outline_glyph->outline, &outline_funcs, context);
    }

  FT_Done_Glyph (glyph);
}

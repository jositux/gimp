/*
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * This is a plug-in for the GIMP.
 *
 * Generates images containing vector type drawings.
 *
 * Copyright (C) 1997 Andy Thomas  alt@picnic.demon.co.uk
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
 * 
 */

#include <math.h>
#include <stdio.h>
#include <string.h>

#include <gtk/gtk.h>

#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>

#include "config.h"
#include "libgimp/stdplugins-intl.h"

#include "gfig.h"
#include "gfig_poly.h"

static Dobject  * d_new_circle            (gint x, gint y);

static void
d_save_circle (Dobject *obj,
	       FILE    *to)
{
  fprintf (to, "<CIRCLE>\n");
  do_save_obj (obj, to);
  fprintf (to, "</CIRCLE>\n");
}

Dobject *
d_load_circle (FILE *from)
{
  Dobject *new_obj = NULL;
  gint     xpnt;
  gint     ypnt;
  gchar    buf[MAX_LOAD_LINE];

  while (get_line (buf, MAX_LOAD_LINE, from, 0))
    {
      if (sscanf (buf, "%d %d", &xpnt, &ypnt) != 2)
	{
	  /* Must be the end */
	  if (strcmp ("</CIRCLE>", buf))
	    {
	      g_warning ("[%d] Internal load error while loading circle",
			 line_no);
	      return NULL;
	    }
	  return new_obj;
	}

      if (!new_obj)
	new_obj = d_new_circle (xpnt, ypnt);
      else
	{
	  new_obj->points->next = new_dobjpoint (xpnt, ypnt);
	}
    }

  g_warning ("[%d] Not enough points for circle", line_no);
  return NULL;
}

static void
d_draw_circle (Dobject * obj)
{
  DobjPoints *center_pnt;
  DobjPoints *edge_pnt;
  gdouble     radius;

  center_pnt = obj->points;

  if (!center_pnt)
    return; /* End-of-line */

  edge_pnt = center_pnt->next;

  if (!edge_pnt)
    {
      g_warning ("Internal error - circle no edge pnt");
    }

  radius = sqrt (((center_pnt->pnt.x - edge_pnt->pnt.x) *
		  (center_pnt->pnt.x - edge_pnt->pnt.x)) +
		 ((center_pnt->pnt.y - edge_pnt->pnt.y) *
		  (center_pnt->pnt.y - edge_pnt->pnt.y)));

  draw_sqr (&center_pnt->pnt);
  draw_sqr (&edge_pnt->pnt);

  if (drawing_pic)
    {
      gdk_draw_arc (pic_preview->window,
		    pic_preview->style->black_gc,
		    0,
		    adjust_pic_coords (center_pnt->pnt.x - radius,
				       preview_width),
		    adjust_pic_coords (center_pnt->pnt.y - radius,
				       preview_height),
		    adjust_pic_coords (radius * 2,
				       preview_width),
		    adjust_pic_coords (radius * 2,
				       preview_height),
		    0,
		    360 * 64);
    }
  else
    {
      gdk_draw_arc (gfig_preview->window,
		    gfig_gc,
		    0,
		    gfig_scale_x (center_pnt->pnt.x - (gint) RINT (radius)),
		    gfig_scale_y (center_pnt->pnt.y - (gint) RINT (radius)),
		    gfig_scale_x ((gint) RINT (radius) * 2),
		    gfig_scale_y ((gint) RINT (radius) * 2),
		    0,
		    360 * 64);
    }
}

static void
d_paint_circle (Dobject *obj)
{
  DobjPoints * center_pnt;
  DobjPoints * edge_pnt;
  gint radius;
  gdouble dpnts[4];

  g_assert (obj != NULL);

  if (selvals.approxcircles)
    {
      obj->type_data = 600;

      d_paint_poly (obj);
      return;
    }      

  /* Drawing circles is hard .
   * 1) select circle
   * 2) stroke it
   */
  center_pnt = obj->points;

  if (!center_pnt)
    return; /* End-of-line */

  edge_pnt = center_pnt->next;

  if (!edge_pnt)
    {
      g_error ("Internal error - circle no edge pnt");
    }

  radius = (gint) sqrt (((center_pnt->pnt.x - edge_pnt->pnt.x) *
			 (center_pnt->pnt.x - edge_pnt->pnt.x)) +
			((center_pnt->pnt.y - edge_pnt->pnt.y) *
			 (center_pnt->pnt.y - edge_pnt->pnt.y)));

  dpnts[0] = (gdouble) center_pnt->pnt.x - radius;
  dpnts[1] = (gdouble) center_pnt->pnt.y - radius;
  dpnts[3] = dpnts[2] = (gdouble) radius * 2;

  /* Scale before drawing */
  if (selvals.scaletoimage)
    scale_to_original_xy (&dpnts[0], 2);
  else
    scale_to_xy (&dpnts[0], 2);

  gimp_ellipse_select (gfig_image,
		       dpnts[0], dpnts[1],
		       dpnts[2], dpnts[3],
		       selopt.type,
		       selopt.antia,
		       selopt.feather,
		       selopt.feather_radius);

  /* Is selection all we need ? */
  if (selvals.painttype == PAINT_SELECTION_TYPE)
    return;

  gimp_edit_stroke (gfig_drawable);

  gimp_selection_clear (gfig_image);
}

static Dobject *
d_copy_circle (Dobject * obj)
{
  Dobject *nc;

  if (!obj)
    return NULL;

  g_assert (obj->type == CIRCLE);

  nc = d_new_circle (obj->points->pnt.x, obj->points->pnt.y);

  nc->points->next = d_copy_dobjpoints (obj->points->next);

  return nc;
}

static Dobject *
d_new_circle (gint x,
	      gint y)
{
  Dobject *nobj;

  nobj = g_new0 (Dobject, 1);

  nobj->type   = CIRCLE;
  nobj->points = new_dobjpoint (x, y);
  nobj->drawfunc  = d_draw_circle;
  nobj->loadfunc  = d_load_circle;
  nobj->savefunc  = d_save_circle;
  nobj->paintfunc = d_paint_circle;
  nobj->copyfunc  = d_copy_circle;

  return nobj;
}

void
d_update_circle (GdkPoint *pnt)
{
  DobjPoints *center_pnt, *edge_pnt;
  gdouble radius;

  /* Undraw last one then draw new one */
  center_pnt = obj_creating->points;

  if (!center_pnt)
    return; /* No points */

  if ((edge_pnt = center_pnt->next))
    {
      /* Undraw current */
      draw_circle (&edge_pnt->pnt);
      radius = sqrt (((center_pnt->pnt.x - edge_pnt->pnt.x) *
		      (center_pnt->pnt.x - edge_pnt->pnt.x)) +
		     ((center_pnt->pnt.y - edge_pnt->pnt.y) *
		      (center_pnt->pnt.y - edge_pnt->pnt.y)));
      
      gdk_draw_arc (gfig_preview->window,
		    gfig_gc,
		    0,
		    center_pnt->pnt.x - (gint) RINT (radius),
		    center_pnt->pnt.y - (gint) RINT (radius),
		    (gint) RINT (radius) * 2,
		    (gint) RINT (radius) * 2,
		    0,
		    360 * 64);
    }

  draw_circle (pnt);

  edge_pnt = new_dobjpoint (pnt->x, pnt->y);

  radius = sqrt (((center_pnt->pnt.x - edge_pnt->pnt.x) *
		  (center_pnt->pnt.x - edge_pnt->pnt.x)) +
		 ((center_pnt->pnt.y - edge_pnt->pnt.y) *
		  (center_pnt->pnt.y - edge_pnt->pnt.y)));

  gdk_draw_arc (gfig_preview->window,
		gfig_gc,
		0,
		center_pnt->pnt.x - (gint) RINT (radius),
		center_pnt->pnt.y - (gint) RINT (radius),
		(gint) RINT (radius) * 2,
		(gint) RINT (radius) * 2,
		0,
		360 * 64);

  center_pnt->next = edge_pnt;
}

void
d_circle_start (GdkPoint *pnt,
		gint      shift_down)
{
  obj_creating = d_new_circle (pnt->x, pnt->y);
}

void
d_circle_end (GdkPoint *pnt,
	      gint      shift_down)
{
  /* Under contrl point */
  if (!obj_creating->points->next)
    {
      /* No circle created */
      free_one_obj (obj_creating);
    }
  else
    {
      draw_circle (pnt);
      add_to_all_obj (current_obj, obj_creating);
    }

  obj_creating = NULL;
}


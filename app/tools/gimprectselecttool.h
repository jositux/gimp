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

#ifndef __GIMP_RECT_SELECT_TOOL_H__
#define __GIMP_RECT_SELECT_TOOL_H__


#include "gimpselectiontool.h"


#define GIMP_TYPE_RECT_SELECT_TOOL            (gimp_rect_select_tool_get_type ())
#define GIMP_RECT_SELECT_TOOL(obj)            (GTK_CHECK_CAST ((obj), GIMP_TYPE_RECT_SELECT_TOOL, GimpRectSelectTool))
#define GIMP_IS_RECT_SELECT_TOOL(obj)         (GTK_CHECK_TYPE ((obj), GIMP_TYPE_RECT_SELECT_TOOL))
#define GIMP_RECT_SELECT_TOOL_CLASS(klass)    (GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_RECT_SELECT_TOOL, GimpRectSelectToolClass))
#define GIMP_IS_RECT_SELECT_TOOL_CLASS(klass) (GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_RECT_SELECT_TOOL))


typedef struct _GimpRectSelectTool      GimpRectSelectTool;
typedef struct _GimpRectSelectToolClass GimpRectSelectToolClass;

struct _GimpRectSelectTool
{
  GimpSelectionTool  parent_instance;

  gint               x, y;        /*  upper left hand coordinate  */
  gint               w, h;        /*  width and height  */
  gint               center;      /*  is the selection being created from the
                                   *  center out?  */

  gint               fixed_size;
  gdouble            fixed_width;
  gdouble            fixed_height;
  guint              context_id;   /*  for the statusbar  */
  
};

struct _GimpRectSelectToolClass
{
  GimpSelectionToolClass parent_class;

  void (* rect_select) (GimpRectSelectTool *rect_tool,
                        gint                x,
                        gint                y,
                        gint                w,
                        gint                h);
};


void       gimp_rect_select_tool_register    (Gimp               *gimp);

GtkType    gimp_rect_select_tool_get_type    (void);

void       gimp_rect_select_tool_rect_select (GimpRectSelectTool *rect_tool,
                                              gint                x,
                                              gint                y,
                                              gint                w,
                                              gint                h);


void       rect_select                       (GimpImage          *gimage,
                                              gint                x,
                                              gint                y,
                                              gint                w,
                                              gint                h,
                                              SelectOps           op,
                                              gboolean            feather,
                                              gdouble             feather_radius);


#endif  /*  __GIMP_RECT_SELECT_TOOL_H__  */

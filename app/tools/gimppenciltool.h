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

#ifndef __GIMP_PENCIL_TOOL_H__
#define __GIMP_PENCIL_TOOL_H__

/* FIXME: This whole tool should probably just be a paintbrush tool that
 *        has an option of hard edge.  It'll give the "pencil tool" all the
 *        flashy stuff the paintbrush tool has, and not duplicate code.
 */

#include "gimppainttool.h"


#define GIMP_TYPE_PENCIL_TOOL            (gimp_pencil_tool_get_type ())
#define GIMP_PENCIL_TOOL(obj)            (GTK_CHECK_CAST ((obj), GIMP_TYPE_PENCIL_TOOL, GimpPencilTool))
#define GIMP_IS_PENCIL_TOOL(obj)         (GTK_CHECK_TYPE ((obj), GIMP_TYPE_PENCIL_TOOL))
#define GIMP_PENCIL_TOOL_CLASS(klass)    (GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PENCIL_TOOL, GimpPencilToolClass))
#define GIMP_IS_PENCIL_TOOL_CLASS(klass) (GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PENCIL_TOOL))

typedef struct _GimpPencilTool      GimpPencilTool;
typedef struct _GimpPencilToolClass GimpPencilToolClass;

struct _GimpPencilTool
{
  GimpPaintTool parent_instance;
};

struct _GimpPencilToolClass
{
  GimpPaintToolClass parent_class;
};


void       gimp_pencil_tool_register (Gimp *gimp);

GtkType    gimp_pencil_tool_get_type (void);

/* FIXME: Get rid of this non_gui stuff someday.  Preferably make
 *        everything use it interally for ease of macro recording.
 */

gboolean   pencil_non_gui    (GimpDrawable *drawable,
			      gint          num_strokes,
			      gdouble      *stroke_array);



#endif  /*  __GIMP_PENCIL_TOOL_H__  */

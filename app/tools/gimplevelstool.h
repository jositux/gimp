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

#ifndef __GIMP_LEVELS_TOOL_H__
#define __GIMP_LEVELS_TOOL_H__


#include "gimpimagemaptool.h"


#define GIMP_TYPE_LEVELS_TOOL            (gimp_levels_tool_get_type ())
#define GIMP_LEVELS_TOOL(obj)            (GTK_CHECK_CAST ((obj), GIMP_TYPE_LEVELS_TOOL, GimpLevelsTool))
#define GIMP_IS_LEVELS_TOOL(obj)         (GTK_CHECK_TYPE ((obj), GIMP_TYPE_LEVELS_TOOL))
#define GIMP_LEVELS_TOOL_CLASS(klass)    (GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LEVELS_TOOL, GimpLevelsToolClass))
#define GIMP_IS_LEVELS_TOOL_CLASS(klass) (GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LEVELS_TOOL))


typedef struct _GimpLevelsTool      GimpLevelsTool;
typedef struct _GimpLevelsToolClass GimpLevelsToolClass;

struct _GimpLevelsTool
{
  GimpImageMapTool  parent_instance;
};

struct _GimpLevelsToolClass
{
  GimpImageMapToolClass  parent_class;
};


void       gimp_levels_tool_register (Gimp *gimp);

GtkType    gimp_levels_tool_get_type (void);


void   levels_dialog_hide (void);
void   levels_free        (void);


#endif  /*  __GIMP_LEVELS_TOOL_H__  */

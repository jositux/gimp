/* The GIMP -- an image manipulation program
 * Copyright (C) 1995-2000 Spencer Kimball and Peter Mattis
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

/* NOTE: This file is autogenerated by pdbgen.pl. */

#include "config.h"

#include <string.h>

#include <gtk/gtk.h>

#include "libgimpbase/gimpbasetypes.h"

#include "core/core-types.h"
#include "procedural_db.h"

#include "base/base-types.h"
#include "base/temp-buf.h"
#include "core/gimp.h"
#include "core/gimpbrush.h"
#include "core/gimpcontext.h"
#include "core/gimpdatafactory.h"
#include "core/gimplist.h"

static ProcRecord brushes_refresh_proc;
static ProcRecord brushes_get_brush_proc;
static ProcRecord brushes_set_brush_proc;
static ProcRecord brushes_get_opacity_proc;
static ProcRecord brushes_set_opacity_proc;
static ProcRecord brushes_get_spacing_proc;
static ProcRecord brushes_set_spacing_proc;
static ProcRecord brushes_get_paint_mode_proc;
static ProcRecord brushes_set_paint_mode_proc;
static ProcRecord brushes_list_proc;
static ProcRecord brushes_get_brush_data_proc;

void
register_brushes_procs (Gimp *gimp)
{
  procedural_db_register (gimp, &brushes_refresh_proc);
  procedural_db_register (gimp, &brushes_get_brush_proc);
  procedural_db_register (gimp, &brushes_set_brush_proc);
  procedural_db_register (gimp, &brushes_get_opacity_proc);
  procedural_db_register (gimp, &brushes_set_opacity_proc);
  procedural_db_register (gimp, &brushes_get_spacing_proc);
  procedural_db_register (gimp, &brushes_set_spacing_proc);
  procedural_db_register (gimp, &brushes_get_paint_mode_proc);
  procedural_db_register (gimp, &brushes_set_paint_mode_proc);
  procedural_db_register (gimp, &brushes_list_proc);
  procedural_db_register (gimp, &brushes_get_brush_data_proc);
}

static Argument *
brushes_refresh_invoker (Gimp     *gimp,
                         Argument *args)
{
  /* FIXME: I've hardcoded success to be 1, because brushes_init() is a 
   *        void function right now.  It'd be nice if it returned a value at 
   *        some future date, so we could tell if things blew up when reparsing
   *        the list (for whatever reason). 
   *                       - Seth "Yes, this is a kludge" Burgess
   *                         <sjburges@gimp.org>
   */

  gimp_data_factory_data_save (gimp->brush_factory);
  gimp_data_factory_data_init (gimp->brush_factory, FALSE);

  return procedural_db_return_args (&brushes_refresh_proc, TRUE);
}

static ProcRecord brushes_refresh_proc =
{
  "gimp_brushes_refresh",
  "Refresh current brushes.",
  "This procedure retrieves all brushes currently in the user's brush path and updates the brush dialog accordingly.",
  "Seth Burgess",
  "Seth Burgess",
  "1997",
  GIMP_INTERNAL,
  0,
  NULL,
  0,
  NULL,
  { { brushes_refresh_invoker } }
};

static Argument *
brushes_get_brush_invoker (Gimp     *gimp,
                           Argument *args)
{
  gboolean success = TRUE;
  Argument *return_args;
  GimpBrush *brush;

  success = (brush = gimp_context_get_brush (gimp_get_current_context (gimp))) != NULL;

  return_args = procedural_db_return_args (&brushes_get_brush_proc, success);

  if (success)
    {
      return_args[1].value.pdb_pointer = g_strdup (GIMP_OBJECT (brush)->name);
      return_args[2].value.pdb_int = brush->mask->width;
      return_args[3].value.pdb_int = brush->mask->height;
      return_args[4].value.pdb_int = brush->spacing;
    }

  return return_args;
}

static ProcArg brushes_get_brush_outargs[] =
{
  {
    GIMP_PDB_STRING,
    "name",
    "The brush name"
  },
  {
    GIMP_PDB_INT32,
    "width",
    "The brush width"
  },
  {
    GIMP_PDB_INT32,
    "height",
    "The brush height"
  },
  {
    GIMP_PDB_INT32,
    "spacing",
    "The brush spacing: 0 <= spacing <= 1000"
  }
};

static ProcRecord brushes_get_brush_proc =
{
  "gimp_brushes_get_brush",
  "Retrieve information about the currently active brush mask.",
  "This procedure retrieves information about the currently active brush mask. This includes the brush name, the width and height, and the brush spacing paramter. All paint operations and stroke operations use this mask to control the application of paint to the image.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  GIMP_INTERNAL,
  0,
  NULL,
  4,
  brushes_get_brush_outargs,
  { { brushes_get_brush_invoker } }
};

static Argument *
brushes_set_brush_invoker (Gimp     *gimp,
                           Argument *args)
{
  gboolean success = TRUE;
  gchar *name;
  GimpObject *object;

  name = (gchar *) args[0].value.pdb_pointer;
  if (name == NULL)
    success = FALSE;

  if (success)
    {
      object = gimp_container_get_child_by_name (gimp->brush_factory->container,
						 name);
    
      if (object)
	gimp_context_set_brush (gimp_get_current_context (gimp),
				GIMP_BRUSH (object));
      else
	success = FALSE;
    }

  return procedural_db_return_args (&brushes_set_brush_proc, success);
}

static ProcArg brushes_set_brush_inargs[] =
{
  {
    GIMP_PDB_STRING,
    "name",
    "The brush name"
  }
};

static ProcRecord brushes_set_brush_proc =
{
  "gimp_brushes_set_brush",
  "Set the specified brush as the active brush.",
  "This procedure allows the active brush mask to be set by specifying its name. The name is simply a string which corresponds to one of the names of the installed brushes. If there is no matching brush found, this procedure will return an error. Otherwise, the specified brush becomes active and will be used in all subsequent paint operations.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  GIMP_INTERNAL,
  1,
  brushes_set_brush_inargs,
  0,
  NULL,
  { { brushes_set_brush_invoker } }
};

static Argument *
brushes_get_opacity_invoker (Gimp     *gimp,
                             Argument *args)
{
  Argument *return_args;

  return_args = procedural_db_return_args (&brushes_get_opacity_proc, TRUE);
  return_args[1].value.pdb_float = gimp_context_get_opacity (gimp_get_current_context (gimp)) * 100.0;

  return return_args;
}

static ProcArg brushes_get_opacity_outargs[] =
{
  {
    GIMP_PDB_FLOAT,
    "opacity",
    "The brush opacity: 0 <= opacity <= 100"
  }
};

static ProcRecord brushes_get_opacity_proc =
{
  "gimp_brushes_get_opacity",
  "Get the brush opacity.",
  "This procedure returns the opacity setting for brushes. This value is set globally and will remain the same even if the brush mask is changed. The return value is a floating point number between 0 and 100.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  GIMP_INTERNAL,
  0,
  NULL,
  1,
  brushes_get_opacity_outargs,
  { { brushes_get_opacity_invoker } }
};

static Argument *
brushes_set_opacity_invoker (Gimp     *gimp,
                             Argument *args)
{
  gboolean success = TRUE;
  gdouble opacity;

  opacity = args[0].value.pdb_float;
  if (opacity < 0.0 || opacity > 100.0)
    success = FALSE;

  if (success)
    gimp_context_set_opacity (gimp_get_current_context (gimp), opacity / 100.0);

  return procedural_db_return_args (&brushes_set_opacity_proc, success);
}

static ProcArg brushes_set_opacity_inargs[] =
{
  {
    GIMP_PDB_FLOAT,
    "opacity",
    "The brush opacity: 0 <= opacity <= 100"
  }
};

static ProcRecord brushes_set_opacity_proc =
{
  "gimp_brushes_set_opacity",
  "Set the brush opacity.",
  "This procedure modifies the opacity setting for brushes. This value is set globally and will remain the same even if the brush mask is changed. The value should be a floating point number between 0 and 100.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  GIMP_INTERNAL,
  1,
  brushes_set_opacity_inargs,
  0,
  NULL,
  { { brushes_set_opacity_invoker } }
};

static Argument *
brushes_get_spacing_invoker (Gimp     *gimp,
                             Argument *args)
{
  Argument *return_args;

  return_args = procedural_db_return_args (&brushes_get_spacing_proc, TRUE);
  return_args[1].value.pdb_int = gimp_brush_get_spacing (gimp_context_get_brush (gimp_get_current_context (gimp)));

  return return_args;
}

static ProcArg brushes_get_spacing_outargs[] =
{
  {
    GIMP_PDB_INT32,
    "spacing",
    "The brush spacing: 0 <= spacing <= 1000"
  }
};

static ProcRecord brushes_get_spacing_proc =
{
  "gimp_brushes_get_spacing",
  "Get the brush spacing.",
  "This procedure returns the spacing setting for brushes. This value is set per brush and will change if a different brush is selected. The return value is an integer between 0 and 1000 which represents percentage of the maximum of the width and height of the mask.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  GIMP_INTERNAL,
  0,
  NULL,
  1,
  brushes_get_spacing_outargs,
  { { brushes_get_spacing_invoker } }
};

static Argument *
brushes_set_spacing_invoker (Gimp     *gimp,
                             Argument *args)
{
  gboolean success = TRUE;
  gint32 spacing;

  spacing = args[0].value.pdb_int;
  if (spacing < 0 || spacing > 1000)
    success = FALSE;

  if (success)
    gimp_brush_set_spacing (gimp_context_get_brush (gimp_get_current_context (gimp)), spacing);

  return procedural_db_return_args (&brushes_set_spacing_proc, success);
}

static ProcArg brushes_set_spacing_inargs[] =
{
  {
    GIMP_PDB_INT32,
    "spacing",
    "The brush spacing: 0 <= spacing <= 1000"
  }
};

static ProcRecord brushes_set_spacing_proc =
{
  "gimp_brushes_set_spacing",
  "Set the brush spacing.",
  "This procedure modifies the spacing setting for the current brush. This value is set on a per-brush basis and will change if a different brush mask is selected. The value should be a integer between 0 and 1000.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  GIMP_INTERNAL,
  1,
  brushes_set_spacing_inargs,
  0,
  NULL,
  { { brushes_set_spacing_invoker } }
};

static Argument *
brushes_get_paint_mode_invoker (Gimp     *gimp,
                                Argument *args)
{
  Argument *return_args;

  return_args = procedural_db_return_args (&brushes_get_paint_mode_proc, TRUE);
  return_args[1].value.pdb_int = gimp_context_get_paint_mode (gimp_get_current_context (gimp));

  return return_args;
}

static ProcArg brushes_get_paint_mode_outargs[] =
{
  {
    GIMP_PDB_INT32,
    "paint_mode",
    "The paint mode: { NORMAL_MODE (0), DISSOLVE_MODE (1), BEHIND_MODE (2), MULTIPLY_MODE (3), SCREEN_MODE (4), OVERLAY_MODE (5), DIFFERENCE_MODE (6), ADDITION_MODE (7), SUBTRACT_MODE (8), DARKEN_ONLY_MODE (9), LIGHTEN_ONLY_MODE (10), HUE_MODE (11), SATURATION_MODE (12), COLOR_MODE (13), VALUE_MODE (14), DIVIDE_MODE (15), DODGE_MODE (16), BURN_MODE (17), HARDLIGHT_MODE (18) }"
  }
};

static ProcRecord brushes_get_paint_mode_proc =
{
  "gimp_brushes_get_paint_mode",
  "Get the brush paint mode.",
  "This procedure returns the paint-mode setting for brushes. This value is set globally and will not change if a different brush is selected. The return value is an integer which corresponds to the values listed in the argument description.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  GIMP_INTERNAL,
  0,
  NULL,
  1,
  brushes_get_paint_mode_outargs,
  { { brushes_get_paint_mode_invoker } }
};

static Argument *
brushes_set_paint_mode_invoker (Gimp     *gimp,
                                Argument *args)
{
  gboolean success = TRUE;
  gint32 paint_mode;

  paint_mode = args[0].value.pdb_int;
  if (paint_mode < NORMAL_MODE || paint_mode > HARDLIGHT_MODE)
    success = FALSE;

  if (success)
    gimp_context_set_paint_mode (gimp_get_current_context (gimp), paint_mode);

  return procedural_db_return_args (&brushes_set_paint_mode_proc, success);
}

static ProcArg brushes_set_paint_mode_inargs[] =
{
  {
    GIMP_PDB_INT32,
    "paint_mode",
    "The paint mode: { NORMAL_MODE (0), DISSOLVE_MODE (1), BEHIND_MODE (2), MULTIPLY_MODE (3), SCREEN_MODE (4), OVERLAY_MODE (5), DIFFERENCE_MODE (6), ADDITION_MODE (7), SUBTRACT_MODE (8), DARKEN_ONLY_MODE (9), LIGHTEN_ONLY_MODE (10), HUE_MODE (11), SATURATION_MODE (12), COLOR_MODE (13), VALUE_MODE (14), DIVIDE_MODE (15), DODGE_MODE (16), BURN_MODE (17), HARDLIGHT_MODE (18) }"
  }
};

static ProcRecord brushes_set_paint_mode_proc =
{
  "gimp_brushes_set_paint_mode",
  "Set the brush paint mode.",
  "This procedure modifies the paint_mode setting for the current brush. This value is set globally and will not change if a different brush mask is selected.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  GIMP_INTERNAL,
  1,
  brushes_set_paint_mode_inargs,
  0,
  NULL,
  { { brushes_set_paint_mode_invoker } }
};

static Argument *
brushes_list_invoker (Gimp     *gimp,
                      Argument *args)
{
  gboolean success = TRUE;
  Argument *return_args;
  gchar **brushes;
  GList *list = NULL;
  int i = 0;

  brushes = g_new (char *, gimp->brush_factory->container->num_children);

  success = (list = GIMP_LIST (gimp->brush_factory->container)->list) != NULL;

  while (list)
    {
      brushes[i++] = g_strdup (GIMP_OBJECT (list->data)->name);
      list = list->next;
    }

  return_args = procedural_db_return_args (&brushes_list_proc, success);

  if (success)
    {
      return_args[1].value.pdb_int = gimp->brush_factory->container->num_children;
      return_args[2].value.pdb_pointer = brushes;
    }

  return return_args;
}

static ProcArg brushes_list_outargs[] =
{
  {
    GIMP_PDB_INT32,
    "num_brushes",
    "The number of brushes in the brush list"
  },
  {
    GIMP_PDB_STRINGARRAY,
    "brush_list",
    "The list of brush names"
  }
};

static ProcRecord brushes_list_proc =
{
  "gimp_brushes_list",
  "Retrieve a complete listing of the available brushes.",
  "This procedure returns a complete listing of available GIMP brushes. Each name returned can be used as input to the 'gimp_brushes_set_brush'.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  GIMP_INTERNAL,
  0,
  NULL,
  2,
  brushes_list_outargs,
  { { brushes_list_invoker } }
};

static Argument *
brushes_get_brush_data_invoker (Gimp     *gimp,
                                Argument *args)
{
  gboolean success = TRUE;
  Argument *return_args;
  gchar *name;
  gint32 length = 0;
  guint8 *mask_data = NULL;
  GimpBrush *brush = NULL;

  name = (gchar *) args[0].value.pdb_pointer;
  if (name == NULL)
    success = FALSE;

  if (success)
    {
      if (strlen (name))
	{
	  GList *list;
    
	  success = FALSE;
    
	  for (list = GIMP_LIST (gimp->brush_factory->container)->list;
	       list;
	       list = g_list_next (list))
	    {
	      brush = (GimpBrush *) list->data;
    
	      if (!strcmp (GIMP_OBJECT (brush)->name, name))
		{
		  success = TRUE;
		  break;
		}
	    }
	}
      else
	success = (brush = gimp_context_get_brush (gimp_get_current_context (gimp))) != NULL;
    
      if (success)
	{
	  length = brush->mask->height * brush->mask->width;
	  mask_data = g_new (guint8, length);
	  g_memmove (mask_data, temp_buf_data (brush->mask), length);
	}
    }

  return_args = procedural_db_return_args (&brushes_get_brush_data_proc, success);

  if (success)
    {
      return_args[1].value.pdb_pointer = g_strdup (GIMP_OBJECT (brush)->name);
      return_args[2].value.pdb_float = 1.0;
      return_args[3].value.pdb_int = brush->spacing;
      return_args[4].value.pdb_int = 0;
      return_args[5].value.pdb_int = brush->mask->width;
      return_args[6].value.pdb_int = brush->mask->height;
      return_args[7].value.pdb_int = length;
      return_args[8].value.pdb_pointer = mask_data;
    }

  return return_args;
}

static ProcArg brushes_get_brush_data_inargs[] =
{
  {
    GIMP_PDB_STRING,
    "name",
    "the brush name (\"\" means current active pattern)"
  }
};

static ProcArg brushes_get_brush_data_outargs[] =
{
  {
    GIMP_PDB_STRING,
    "name",
    "The brush name"
  },
  {
    GIMP_PDB_FLOAT,
    "opacity",
    "The brush opacity: 0 <= opacity <= 100"
  },
  {
    GIMP_PDB_INT32,
    "spacing",
    "The brush spacing: 0 <= spacing <= 1000"
  },
  {
    GIMP_PDB_INT32,
    "paint_mode",
    "The paint mode: { NORMAL_MODE (0), DISSOLVE_MODE (1), BEHIND_MODE (2), MULTIPLY_MODE (3), SCREEN_MODE (4), OVERLAY_MODE (5), DIFFERENCE_MODE (6), ADDITION_MODE (7), SUBTRACT_MODE (8), DARKEN_ONLY_MODE (9), LIGHTEN_ONLY_MODE (10), HUE_MODE (11), SATURATION_MODE (12), COLOR_MODE (13), VALUE_MODE (14), DIVIDE_MODE (15), DODGE_MODE (16), BURN_MODE (17), HARDLIGHT_MODE (18) }"
  },
  {
    GIMP_PDB_INT32,
    "width",
    "The brush width"
  },
  {
    GIMP_PDB_INT32,
    "height",
    "The brush height"
  },
  {
    GIMP_PDB_INT32,
    "length",
    "Length of brush mask data"
  },
  {
    GIMP_PDB_INT8ARRAY,
    "mask_data",
    "The brush mask data"
  }
};

static ProcRecord brushes_get_brush_data_proc =
{
  "gimp_brushes_get_brush_data",
  "Retrieve information about the currently active brush (including data).",
  "This procedure retrieves information about the currently active brush. This includes the brush name, and the brush extents (width and height). It also returns the brush data.",
  "Andy Thomas",
  "Andy Thomas",
  "1998",
  GIMP_INTERNAL,
  1,
  brushes_get_brush_data_inargs,
  8,
  brushes_get_brush_data_outargs,
  { { brushes_get_brush_data_invoker } }
};

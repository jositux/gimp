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


#include <gtk/gtk.h>

#include "libgimpbase/gimpbasetypes.h"

#include "core/core-types.h"
#include "procedural_db.h"

#include "core/gimp.h"
#include "core/gimpcontext.h"
#include "core/gimpdatafactory.h"

#include "libgimpcolor/gimpcolor.h"

static ProcRecord palette_get_foreground_proc;
static ProcRecord palette_get_background_proc;
static ProcRecord palette_set_foreground_proc;
static ProcRecord palette_set_background_proc;
static ProcRecord palette_set_default_colors_proc;
static ProcRecord palette_swap_colors_proc;
static ProcRecord palette_refresh_proc;

void
register_palette_procs (Gimp *gimp)
{
  procedural_db_register (gimp, &palette_get_foreground_proc);
  procedural_db_register (gimp, &palette_get_background_proc);
  procedural_db_register (gimp, &palette_set_foreground_proc);
  procedural_db_register (gimp, &palette_set_background_proc);
  procedural_db_register (gimp, &palette_set_default_colors_proc);
  procedural_db_register (gimp, &palette_swap_colors_proc);
  procedural_db_register (gimp, &palette_refresh_proc);
}

static Argument *
palette_get_foreground_invoker (Gimp     *gimp,
                                Argument *args)
{
  Argument *return_args;
  GimpRGB color;

  gimp_context_get_foreground (gimp_get_current_context (gimp), &color);

  return_args = procedural_db_return_args (&palette_get_foreground_proc, TRUE);
  return_args[1].value.pdb_color = color;

  return return_args;
}

static ProcArg palette_get_foreground_outargs[] =
{
  {
    GIMP_PDB_COLOR,
    "foreground",
    "The foreground color"
  }
};

static ProcRecord palette_get_foreground_proc =
{
  "gimp_palette_get_foreground",
  "Get the current GIMP foreground color.",
  "This procedure retrieves the current GIMP foreground color. The foreground color is used in a variety of tools such as paint tools, blending, and bucket fill.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  GIMP_INTERNAL,
  0,
  NULL,
  1,
  palette_get_foreground_outargs,
  { { palette_get_foreground_invoker } }
};

static Argument *
palette_get_background_invoker (Gimp     *gimp,
                                Argument *args)
{
  Argument *return_args;
  GimpRGB color;

  gimp_context_get_background (gimp_get_current_context (gimp), &color);

  return_args = procedural_db_return_args (&palette_get_background_proc, TRUE);
  return_args[1].value.pdb_color = color;

  return return_args;
}

static ProcArg palette_get_background_outargs[] =
{
  {
    GIMP_PDB_COLOR,
    "background",
    "The background color"
  }
};

static ProcRecord palette_get_background_proc =
{
  "gimp_palette_get_background",
  "Get the current GIMP background color.",
  "This procedure retrieves the current GIMP background color. The background color is used in a variety of tools such as blending, erasing (with non-alpha images), and image filling.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  GIMP_INTERNAL,
  0,
  NULL,
  1,
  palette_get_background_outargs,
  { { palette_get_background_invoker } }
};

static Argument *
palette_set_foreground_invoker (Gimp     *gimp,
                                Argument *args)
{
  GimpRGB color;

  color = args[0].value.pdb_color;

  gimp_rgb_set_alpha (&color, 1.0);
  gimp_context_set_foreground (gimp_get_current_context (gimp), &color);

  return procedural_db_return_args (&palette_set_foreground_proc, TRUE);
}

static ProcArg palette_set_foreground_inargs[] =
{
  {
    GIMP_PDB_COLOR,
    "foreground",
    "The foreground color"
  }
};

static ProcRecord palette_set_foreground_proc =
{
  "gimp_palette_set_foreground",
  "Set the current GIMP foreground color.",
  "This procedure sets the current GIMP foreground color. After this is set, operations which use foreground such as paint tools, blending, and bucket fill will use the new value.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  GIMP_INTERNAL,
  1,
  palette_set_foreground_inargs,
  0,
  NULL,
  { { palette_set_foreground_invoker } }
};

static Argument *
palette_set_background_invoker (Gimp     *gimp,
                                Argument *args)
{
  GimpRGB color;

  color = args[0].value.pdb_color;

  gimp_rgb_set_alpha (&color, 1.0);
  gimp_context_set_background (gimp_get_current_context (gimp), &color);

  return procedural_db_return_args (&palette_set_background_proc, TRUE);
}

static ProcArg palette_set_background_inargs[] =
{
  {
    GIMP_PDB_COLOR,
    "background",
    "The background color"
  }
};

static ProcRecord palette_set_background_proc =
{
  "gimp_palette_set_background",
  "Set the current GIMP background color.",
  "This procedure sets the current GIMP background color. After this is set, operations which use background such as blending, filling images, clearing, and erasing (in non-alpha images) will use the new value.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  GIMP_INTERNAL,
  1,
  palette_set_background_inargs,
  0,
  NULL,
  { { palette_set_background_invoker } }
};

static Argument *
palette_set_default_colors_invoker (Gimp     *gimp,
                                    Argument *args)
{
  gimp_context_set_default_colors (gimp_get_current_context (gimp));
  return procedural_db_return_args (&palette_set_default_colors_proc, TRUE);
}

static ProcRecord palette_set_default_colors_proc =
{
  "gimp_palette_set_default_colors",
  "Set the current GIMP foreground and background colors to black and white.",
  "This procedure sets the current GIMP foreground and background colors to their initial default values, black and white.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  GIMP_INTERNAL,
  0,
  NULL,
  0,
  NULL,
  { { palette_set_default_colors_invoker } }
};

static Argument *
palette_swap_colors_invoker (Gimp     *gimp,
                             Argument *args)
{
  gimp_context_swap_colors (gimp_get_current_context (gimp));
  return procedural_db_return_args (&palette_swap_colors_proc, TRUE);
}

static ProcRecord palette_swap_colors_proc =
{
  "gimp_palette_swap_colors",
  "Swap the current GIMP foreground and background colors.",
  "This procedure swaps the current GIMP foreground and background colors, so that the new foreground color becomes the old background color and vice versa.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  GIMP_INTERNAL,
  0,
  NULL,
  0,
  NULL,
  { { palette_swap_colors_invoker } }
};

static Argument *
palette_refresh_invoker (Gimp     *gimp,
                         Argument *args)
{
  /* FIXME: I've hardcoded success to be TRUE, because brushes_init() is a 
   *        void function right now.  It'd be nice if it returned a value at 
   *        some future date, so we could tell if things blew up when reparsing
   *        the list (for whatever reason). 
   *                       - Seth "Yes, this is a kludge" Burgess
   *                         <sjburges@ou.edu>
   *   -and shamelessly stolen by Adrian Likins for use here...
   */

  gimp_data_factory_data_init (gimp->palette_factory, FALSE);

  return procedural_db_return_args (&palette_refresh_proc, TRUE);
}

static ProcRecord palette_refresh_proc =
{
  "gimp_palette_refresh",
  "Refreshes current palettes.",
  "This procedure incorporates all palettes currently in the users palette path.",
  "Adrian Likins <adrian@gimp.org>",
  "Adrian Likins",
  "1998",
  GIMP_INTERNAL,
  0,
  NULL,
  0,
  NULL,
  { { palette_refresh_invoker } }
};

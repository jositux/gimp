/* The GIMP -- an image manipulation program
 * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis
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


#include <glib-object.h>

#include "pdb-types.h"
#include "procedural_db.h"

#include "core/gimpimage-guides.h"
#include "core/gimpimage-undo-push.h"
#include "core/gimpimage.h"

static ProcRecord image_add_hguide_proc;
static ProcRecord image_add_vguide_proc;
static ProcRecord image_delete_guide_proc;
static ProcRecord image_find_next_guide_proc;
static ProcRecord image_get_guide_orientation_proc;
static ProcRecord image_get_guide_position_proc;

void
register_guides_procs (Gimp *gimp)
{
  procedural_db_register (gimp, &image_add_hguide_proc);
  procedural_db_register (gimp, &image_add_vguide_proc);
  procedural_db_register (gimp, &image_delete_guide_proc);
  procedural_db_register (gimp, &image_find_next_guide_proc);
  procedural_db_register (gimp, &image_get_guide_orientation_proc);
  procedural_db_register (gimp, &image_get_guide_position_proc);
}

static Argument *
image_add_hguide_invoker (Gimp         *gimp,
                          GimpContext  *context,
                          GimpProgress *progress,
                          Argument     *args)
{
  gboolean success = TRUE;
  Argument *return_args;
  GimpImage *gimage;
  gint32 offset;
  gint32 guide_ID = 0;
  GimpGuide *guide;

  gimage = gimp_image_get_by_ID (gimp, args[0].value.pdb_int);
  if (! GIMP_IS_IMAGE (gimage))
    success = FALSE;

  offset = args[1].value.pdb_int;
  if (offset < 0)
    success = FALSE;

  if (success)
    {
      if (offset <= gimage->height)
        {
          guide = gimp_image_add_hguide (gimage, offset, TRUE);
          guide_ID = guide->guide_ID;
        }
      else
        success = FALSE;
    }

  return_args = procedural_db_return_args (&image_add_hguide_proc, success);

  if (success)
    return_args[1].value.pdb_int = guide_ID;

  return return_args;
}

static ProcArg image_add_hguide_inargs[] =
{
  {
    GIMP_PDB_IMAGE,
    "image",
    "The image"
  },
  {
    GIMP_PDB_INT32,
    "yposition",
    "The guide's y-offset from top of image"
  }
};

static ProcArg image_add_hguide_outargs[] =
{
  {
    GIMP_PDB_INT32,
    "guide",
    "The new guide"
  }
};

static ProcRecord image_add_hguide_proc =
{
  "gimp_image_add_hguide",
  "Add a horizontal guide to an image.",
  "This procedure adds a horizontal guide to an image. It takes the input image and the y-position of the new guide as parameters. It returns the guide ID of the new guide.",
  "Adam D. Moss",
  "Adam D. Moss",
  "1998",
  GIMP_INTERNAL,
  2,
  image_add_hguide_inargs,
  1,
  image_add_hguide_outargs,
  { { image_add_hguide_invoker } }
};

static Argument *
image_add_vguide_invoker (Gimp         *gimp,
                          GimpContext  *context,
                          GimpProgress *progress,
                          Argument     *args)
{
  gboolean success = TRUE;
  Argument *return_args;
  GimpImage *gimage;
  gint32 offset;
  gint32 guide_ID = 0;
  GimpGuide *guide;

  gimage = gimp_image_get_by_ID (gimp, args[0].value.pdb_int);
  if (! GIMP_IS_IMAGE (gimage))
    success = FALSE;

  offset = args[1].value.pdb_int;
  if (offset < 0)
    success = FALSE;

  if (success)
    {
      if (offset <= gimage->width)
        {
          guide = gimp_image_add_vguide (gimage, offset, TRUE);
          guide_ID = guide->guide_ID;
        }
      else
        success = FALSE;
    }

  return_args = procedural_db_return_args (&image_add_vguide_proc, success);

  if (success)
    return_args[1].value.pdb_int = guide_ID;

  return return_args;
}

static ProcArg image_add_vguide_inargs[] =
{
  {
    GIMP_PDB_IMAGE,
    "image",
    "The image"
  },
  {
    GIMP_PDB_INT32,
    "xposition",
    "The guide's x-offset from left of image"
  }
};

static ProcArg image_add_vguide_outargs[] =
{
  {
    GIMP_PDB_INT32,
    "guide",
    "The new guide"
  }
};

static ProcRecord image_add_vguide_proc =
{
  "gimp_image_add_vguide",
  "Add a vertical guide to an image.",
  "This procedure adds a vertical guide to an image. It takes the input image and the x-position of the new guide as parameters. It returns the guide ID of the new guide.",
  "Adam D. Moss",
  "Adam D. Moss",
  "1998",
  GIMP_INTERNAL,
  2,
  image_add_vguide_inargs,
  1,
  image_add_vguide_outargs,
  { { image_add_vguide_invoker } }
};

static Argument *
image_delete_guide_invoker (Gimp         *gimp,
                            GimpContext  *context,
                            GimpProgress *progress,
                            Argument     *args)
{
  gboolean success = TRUE;
  GimpImage *gimage;
  gint32 guide;
  GList *guides;

  gimage = gimp_image_get_by_ID (gimp, args[0].value.pdb_int);
  if (! GIMP_IS_IMAGE (gimage))
    success = FALSE;

  guide = args[1].value.pdb_int;

  if (success)
    {
      success = FALSE;

      for (guides = gimage->guides; guides; guides = g_list_next (guides))
        {
          GimpGuide *g = (GimpGuide *) guides->data;

          if ((g->guide_ID == guide) && (g->position >= 0))
            {
              gimp_image_remove_guide (gimage, g, TRUE);
              success = TRUE;
              break;
            }
        }
    }

  return procedural_db_return_args (&image_delete_guide_proc, success);
}

static ProcArg image_delete_guide_inargs[] =
{
  {
    GIMP_PDB_IMAGE,
    "image",
    "The image"
  },
  {
    GIMP_PDB_INT32,
    "guide",
    "The ID of the guide to be removed"
  }
};

static ProcRecord image_delete_guide_proc =
{
  "gimp_image_delete_guide",
  "Deletes a guide from an image.",
  "This procedure takes an image and a guide ID as input and removes the specified guide from the specified image.",
  "Adam D. Moss",
  "Adam D. Moss",
  "1998",
  GIMP_INTERNAL,
  2,
  image_delete_guide_inargs,
  0,
  NULL,
  { { image_delete_guide_invoker } }
};

static Argument *
image_find_next_guide_invoker (Gimp         *gimp,
                               GimpContext  *context,
                               GimpProgress *progress,
                               Argument     *args)
{
  gboolean success = TRUE;
  Argument *return_args;
  GimpImage *gimage;
  gint32 guide;
  gint32 next_guide = 0;
  GList *guides;
  gboolean guide_found;

  gimage = gimp_image_get_by_ID (gimp, args[0].value.pdb_int);
  if (! GIMP_IS_IMAGE (gimage))
    success = FALSE;

  guide = args[1].value.pdb_int;

  if (success)
    {
      if (gimage->guides != NULL)
        {
          success     = FALSE;
          guide_found = FALSE;

          for (guides = gimage->guides; guides; guides = g_list_next (guides))
            {
              GimpGuide *g = (GimpGuide *) guides->data;

              if (g->position < 0)
                continue;

              if (guide == 0)  /* init - Return first guide ID in list */
                {
                  next_guide = g->guide_ID;

                  guide_found = TRUE;
                  break;
                }

              if (! guide_found)
                {
                  if (g->guide_ID == guide)
                    guide_found = TRUE;
                }
              else
                {
                  next_guide = g->guide_ID;
                  break;
                }
            }

          if (guide_found)
            success = TRUE;
        }
    }

  return_args = procedural_db_return_args (&image_find_next_guide_proc, success);

  if (success)
    return_args[1].value.pdb_int = next_guide;

  return return_args;
}

static ProcArg image_find_next_guide_inargs[] =
{
  {
    GIMP_PDB_IMAGE,
    "image",
    "The image"
  },
  {
    GIMP_PDB_INT32,
    "guide",
    "The ID of the current guide (0 if first invocation)"
  }
};

static ProcArg image_find_next_guide_outargs[] =
{
  {
    GIMP_PDB_INT32,
    "next_guide",
    "The next guide's ID"
  }
};

static ProcRecord image_find_next_guide_proc =
{
  "gimp_image_find_next_guide",
  "Find next guide on an image.",
  "This procedure takes an image and a guide ID as input and finds the guide ID of the successor of the given guide ID in the image's guide list. If the supplied guide ID is 0, the procedure will return the first Guide. The procedure will return 0 if given the final guide ID as an argument or the image has no guides.",
  "Adam D. Moss",
  "Adam D. Moss",
  "1998",
  GIMP_INTERNAL,
  2,
  image_find_next_guide_inargs,
  1,
  image_find_next_guide_outargs,
  { { image_find_next_guide_invoker } }
};

static Argument *
image_get_guide_orientation_invoker (Gimp         *gimp,
                                     GimpContext  *context,
                                     GimpProgress *progress,
                                     Argument     *args)
{
  gboolean success = TRUE;
  Argument *return_args;
  GimpImage *gimage;
  gint32 guide;
  gint32 orientation = 0;
  GList *guides;

  gimage = gimp_image_get_by_ID (gimp, args[0].value.pdb_int);
  if (! GIMP_IS_IMAGE (gimage))
    success = FALSE;

  guide = args[1].value.pdb_int;

  if (success)
    {
      success = FALSE;

      for (guides = gimage->guides; guides; guides = g_list_next (guides))
        {
          GimpGuide *g = (GimpGuide *) guides->data;

          if ((g->guide_ID == guide) && (g->position >= 0))
            {
              orientation = g->orientation;

              success = TRUE;
              break;
            }
        }
    }

  return_args = procedural_db_return_args (&image_get_guide_orientation_proc, success);

  if (success)
    return_args[1].value.pdb_int = orientation;

  return return_args;
}

static ProcArg image_get_guide_orientation_inargs[] =
{
  {
    GIMP_PDB_IMAGE,
    "image",
    "The image"
  },
  {
    GIMP_PDB_INT32,
    "guide",
    "The guide"
  }
};

static ProcArg image_get_guide_orientation_outargs[] =
{
  {
    GIMP_PDB_INT32,
    "orientation",
    "The guide's orientation: { GIMP_ORIENTATION_HORIZONTAL (0), GIMP_ORIENTATION_VERTICAL (1) }"
  }
};

static ProcRecord image_get_guide_orientation_proc =
{
  "gimp_image_get_guide_orientation",
  "Get orientation of a guide on an image.",
  "This procedure takes an image and a guide ID as input and returns the orientations of the guide.",
  "Adam D. Moss",
  "Adam D. Moss",
  "1998",
  GIMP_INTERNAL,
  2,
  image_get_guide_orientation_inargs,
  1,
  image_get_guide_orientation_outargs,
  { { image_get_guide_orientation_invoker } }
};

static Argument *
image_get_guide_position_invoker (Gimp         *gimp,
                                  GimpContext  *context,
                                  GimpProgress *progress,
                                  Argument     *args)
{
  gboolean success = TRUE;
  Argument *return_args;
  GimpImage *gimage;
  gint32 guide;
  gint32 position = 0;
  GList *guides;

  gimage = gimp_image_get_by_ID (gimp, args[0].value.pdb_int);
  if (! GIMP_IS_IMAGE (gimage))
    success = FALSE;

  guide = args[1].value.pdb_int;

  if (success)
    {
      success = FALSE;

      for (guides = gimage->guides; guides; guides = g_list_next (guides))
        {
          GimpGuide *g = (GimpGuide *) guides->data;

          if ((g->guide_ID == guide) && (g->position >= 0))
            {
              position = g->position;

              success = TRUE;
              break;
            }
        } 
    }

  return_args = procedural_db_return_args (&image_get_guide_position_proc, success);

  if (success)
    return_args[1].value.pdb_int = position;

  return return_args;
}

static ProcArg image_get_guide_position_inargs[] =
{
  {
    GIMP_PDB_IMAGE,
    "image",
    "The image"
  },
  {
    GIMP_PDB_INT32,
    "guide",
    "The guide"
  }
};

static ProcArg image_get_guide_position_outargs[] =
{
  {
    GIMP_PDB_INT32,
    "position",
    "The guide's position relative to top or left of image"
  }
};

static ProcRecord image_get_guide_position_proc =
{
  "gimp_image_get_guide_position",
  "Get position of a guide on an image.",
  "This procedure takes an image and a guide ID as input and returns the position of the guide relative to the top or left of the image.",
  "Adam D. Moss",
  "Adam D. Moss",
  "1998",
  GIMP_INTERNAL,
  2,
  image_get_guide_position_inargs,
  1,
  image_get_guide_position_outargs,
  { { image_get_guide_position_invoker } }
};

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

#include "libgimpbase/gimpbase.h"

#include "pdb-types.h"
#include "procedural_db.h"

#include "core/gimp-parasites.h"
#include "core/gimpdrawable.h"
#include "core/gimpimage.h"

static ProcRecord parasite_find_proc;
static ProcRecord parasite_attach_proc;
static ProcRecord parasite_detach_proc;
static ProcRecord parasite_list_proc;
static ProcRecord drawable_parasite_find_proc;
static ProcRecord drawable_parasite_attach_proc;
static ProcRecord drawable_parasite_detach_proc;
static ProcRecord drawable_parasite_list_proc;
static ProcRecord image_parasite_find_proc;
static ProcRecord image_parasite_attach_proc;
static ProcRecord image_parasite_detach_proc;
static ProcRecord image_parasite_list_proc;

void
register_parasite_procs (Gimp *gimp)
{
  procedural_db_register (gimp, &parasite_find_proc);
  procedural_db_register (gimp, &parasite_attach_proc);
  procedural_db_register (gimp, &parasite_detach_proc);
  procedural_db_register (gimp, &parasite_list_proc);
  procedural_db_register (gimp, &drawable_parasite_find_proc);
  procedural_db_register (gimp, &drawable_parasite_attach_proc);
  procedural_db_register (gimp, &drawable_parasite_detach_proc);
  procedural_db_register (gimp, &drawable_parasite_list_proc);
  procedural_db_register (gimp, &image_parasite_find_proc);
  procedural_db_register (gimp, &image_parasite_attach_proc);
  procedural_db_register (gimp, &image_parasite_detach_proc);
  procedural_db_register (gimp, &image_parasite_list_proc);
}

static Argument *
parasite_find_invoker (Gimp         *gimp,
                       GimpContext  *context,
                       GimpProgress *progress,
                       Argument     *args)
{
  gboolean success = TRUE;
  Argument *return_args;
  gchar *name;
  GimpParasite *parasite = NULL;

  name = (gchar *) args[0].value.pdb_pointer;
  if (name == NULL || !g_utf8_validate (name, -1, NULL))
    success = FALSE;

  if (success)
    {
      parasite = gimp_parasite_copy (gimp_parasite_find (gimp, name));
      success = parasite != NULL;
    }

  return_args = procedural_db_return_args (&parasite_find_proc, success);

  if (success)
    return_args[1].value.pdb_pointer = parasite;

  return return_args;
}

static ProcArg parasite_find_inargs[] =
{
  {
    GIMP_PDB_STRING,
    "name",
    "The name of the parasite to find"
  }
};

static ProcArg parasite_find_outargs[] =
{
  {
    GIMP_PDB_PARASITE,
    "parasite",
    "The found parasite"
  }
};

static ProcRecord parasite_find_proc =
{
  "gimp_parasite_find",
  "Finds the named parasite.",
  "Finds and returns the named parasite that was previously attached to the gimp.",
  "Jay Cox",
  "Jay Cox",
  "1998",
  GIMP_INTERNAL,
  1,
  parasite_find_inargs,
  1,
  parasite_find_outargs,
  { { parasite_find_invoker } }
};

static Argument *
parasite_attach_invoker (Gimp         *gimp,
                         GimpContext  *context,
                         GimpProgress *progress,
                         Argument     *args)
{
  gboolean success = TRUE;
  GimpParasite *parasite;

  parasite = (GimpParasite *) args[0].value.pdb_pointer;
  if (parasite == NULL || parasite->name == NULL || !g_utf8_validate (parasite->name, -1, NULL))
    success = FALSE;

  if (success)
    gimp_parasite_attach (gimp, parasite);

  return procedural_db_return_args (&parasite_attach_proc, success);
}

static ProcArg parasite_attach_inargs[] =
{
  {
    GIMP_PDB_PARASITE,
    "parasite",
    "The parasite to attach to the gimp"
  }
};

static ProcRecord parasite_attach_proc =
{
  "gimp_parasite_attach",
  "Add a parasite to the gimp.",
  "This procedure attaches a parasite to the gimp. It has no return values.",
  "Jay Cox",
  "Jay Cox",
  "1998",
  GIMP_INTERNAL,
  1,
  parasite_attach_inargs,
  0,
  NULL,
  { { parasite_attach_invoker } }
};

static Argument *
parasite_detach_invoker (Gimp         *gimp,
                         GimpContext  *context,
                         GimpProgress *progress,
                         Argument     *args)
{
  gboolean success = TRUE;
  gchar *name;

  name = (gchar *) args[0].value.pdb_pointer;
  if (name == NULL || !g_utf8_validate (name, -1, NULL))
    success = FALSE;

  if (success)
    gimp_parasite_detach (gimp, name);

  return procedural_db_return_args (&parasite_detach_proc, success);
}

static ProcArg parasite_detach_inargs[] =
{
  {
    GIMP_PDB_STRING,
    "name",
    "The name of the parasite to detach from the gimp."
  }
};

static ProcRecord parasite_detach_proc =
{
  "gimp_parasite_detach",
  "Removes a parasite from the gimp.",
  "This procedure detaches a parasite from the gimp. It has no return values.",
  "Jay Cox",
  "Jay Cox",
  "1998",
  GIMP_INTERNAL,
  1,
  parasite_detach_inargs,
  0,
  NULL,
  { { parasite_detach_invoker } }
};

static Argument *
parasite_list_invoker (Gimp         *gimp,
                       GimpContext  *context,
                       GimpProgress *progress,
                       Argument     *args)
{
  Argument *return_args;
  gint32 num_parasites;
  gchar **parasites;

  parasites = gimp_parasite_list (gimp, &num_parasites);

  return_args = procedural_db_return_args (&parasite_list_proc, TRUE);

  return_args[1].value.pdb_int = num_parasites;
  return_args[2].value.pdb_pointer = parasites;

  return return_args;
}

static ProcArg parasite_list_outargs[] =
{
  {
    GIMP_PDB_INT32,
    "num_parasites",
    "The number of attached parasites"
  },
  {
    GIMP_PDB_STRINGARRAY,
    "parasites",
    "The names of currently attached parasites"
  }
};

static ProcRecord parasite_list_proc =
{
  "gimp_parasite_list",
  "List all parasites.",
  "Returns a list of all currently attached parasites.",
  "Marc Lehmann",
  "Marc Lehmann",
  "1999",
  GIMP_INTERNAL,
  0,
  NULL,
  2,
  parasite_list_outargs,
  { { parasite_list_invoker } }
};

static Argument *
drawable_parasite_find_invoker (Gimp         *gimp,
                                GimpContext  *context,
                                GimpProgress *progress,
                                Argument     *args)
{
  gboolean success = TRUE;
  Argument *return_args;
  GimpDrawable *drawable;
  gchar *name;
  GimpParasite *parasite = NULL;

  drawable = (GimpDrawable *) gimp_item_get_by_ID (gimp, args[0].value.pdb_int);
  if (! (GIMP_IS_DRAWABLE (drawable) && ! gimp_item_is_removed (GIMP_ITEM (drawable))))
    success = FALSE;

  name = (gchar *) args[1].value.pdb_pointer;
  if (name == NULL || !g_utf8_validate (name, -1, NULL))
    success = FALSE;

  if (success)
    {
      parasite = gimp_parasite_copy (gimp_item_parasite_find (GIMP_ITEM (drawable), name));
      success = parasite != NULL;
    }

  return_args = procedural_db_return_args (&drawable_parasite_find_proc, success);

  if (success)
    return_args[1].value.pdb_pointer = parasite;

  return return_args;
}

static ProcArg drawable_parasite_find_inargs[] =
{
  {
    GIMP_PDB_DRAWABLE,
    "drawable",
    "The drawable"
  },
  {
    GIMP_PDB_STRING,
    "name",
    "The name of the parasite to find"
  }
};

static ProcArg drawable_parasite_find_outargs[] =
{
  {
    GIMP_PDB_PARASITE,
    "parasite",
    "The found parasite"
  }
};

static ProcRecord drawable_parasite_find_proc =
{
  "gimp_drawable_parasite_find",
  "Finds the named parasite in a drawable",
  "Finds and returns the named parasite that was previously attached to a drawable.",
  "Jay Cox",
  "Jay Cox",
  "1998",
  GIMP_INTERNAL,
  2,
  drawable_parasite_find_inargs,
  1,
  drawable_parasite_find_outargs,
  { { drawable_parasite_find_invoker } }
};

static Argument *
drawable_parasite_attach_invoker (Gimp         *gimp,
                                  GimpContext  *context,
                                  GimpProgress *progress,
                                  Argument     *args)
{
  gboolean success = TRUE;
  GimpDrawable *drawable;
  GimpParasite *parasite;

  drawable = (GimpDrawable *) gimp_item_get_by_ID (gimp, args[0].value.pdb_int);
  if (! (GIMP_IS_DRAWABLE (drawable) && ! gimp_item_is_removed (GIMP_ITEM (drawable))))
    success = FALSE;

  parasite = (GimpParasite *) args[1].value.pdb_pointer;
  if (parasite == NULL || parasite->name == NULL || !g_utf8_validate (parasite->name, -1, NULL))
    success = FALSE;

  if (success)
    gimp_item_parasite_attach (GIMP_ITEM (drawable), parasite);

  return procedural_db_return_args (&drawable_parasite_attach_proc, success);
}

static ProcArg drawable_parasite_attach_inargs[] =
{
  {
    GIMP_PDB_DRAWABLE,
    "drawable",
    "The drawable"
  },
  {
    GIMP_PDB_PARASITE,
    "parasite",
    "The parasite to attach to a drawable"
  }
};

static ProcRecord drawable_parasite_attach_proc =
{
  "gimp_drawable_parasite_attach",
  "Add a parasite to a drawable.",
  "This procedure attaches a parasite to a drawable. It has no return values.",
  "Jay Cox",
  "Jay Cox",
  "1998",
  GIMP_INTERNAL,
  2,
  drawable_parasite_attach_inargs,
  0,
  NULL,
  { { drawable_parasite_attach_invoker } }
};

static Argument *
drawable_parasite_detach_invoker (Gimp         *gimp,
                                  GimpContext  *context,
                                  GimpProgress *progress,
                                  Argument     *args)
{
  gboolean success = TRUE;
  GimpDrawable *drawable;
  gchar *name;

  drawable = (GimpDrawable *) gimp_item_get_by_ID (gimp, args[0].value.pdb_int);
  if (! (GIMP_IS_DRAWABLE (drawable) && ! gimp_item_is_removed (GIMP_ITEM (drawable))))
    success = FALSE;

  name = (gchar *) args[1].value.pdb_pointer;
  if (name == NULL || !g_utf8_validate (name, -1, NULL))
    success = FALSE;

  if (success)
    gimp_item_parasite_detach (GIMP_ITEM (drawable), name);

  return procedural_db_return_args (&drawable_parasite_detach_proc, success);
}

static ProcArg drawable_parasite_detach_inargs[] =
{
  {
    GIMP_PDB_DRAWABLE,
    "drawable",
    "The drawable"
  },
  {
    GIMP_PDB_STRING,
    "name",
    "The name of the parasite to detach from a drawable."
  }
};

static ProcRecord drawable_parasite_detach_proc =
{
  "gimp_drawable_parasite_detach",
  "Removes a parasite from a drawable.",
  "This procedure detaches a parasite from a drawable. It has no return values.",
  "Jay Cox",
  "Jay Cox",
  "1998",
  GIMP_INTERNAL,
  2,
  drawable_parasite_detach_inargs,
  0,
  NULL,
  { { drawable_parasite_detach_invoker } }
};

static Argument *
drawable_parasite_list_invoker (Gimp         *gimp,
                                GimpContext  *context,
                                GimpProgress *progress,
                                Argument     *args)
{
  gboolean success = TRUE;
  Argument *return_args;
  GimpDrawable *drawable;
  gint32 num_parasites;
  gchar **parasites = NULL;

  drawable = (GimpDrawable *) gimp_item_get_by_ID (gimp, args[0].value.pdb_int);
  if (! (GIMP_IS_DRAWABLE (drawable) && ! gimp_item_is_removed (GIMP_ITEM (drawable))))
    success = FALSE;

  if (success)
    parasites = gimp_item_parasite_list (GIMP_ITEM (drawable), &num_parasites);

  return_args = procedural_db_return_args (&drawable_parasite_list_proc, success);

  if (success)
    {
      return_args[1].value.pdb_int = num_parasites;
      return_args[2].value.pdb_pointer = parasites;
    }

  return return_args;
}

static ProcArg drawable_parasite_list_inargs[] =
{
  {
    GIMP_PDB_DRAWABLE,
    "drawable",
    "The drawable"
  }
};

static ProcArg drawable_parasite_list_outargs[] =
{
  {
    GIMP_PDB_INT32,
    "num_parasites",
    "The number of attached parasites"
  },
  {
    GIMP_PDB_STRINGARRAY,
    "parasites",
    "The names of currently attached parasites"
  }
};

static ProcRecord drawable_parasite_list_proc =
{
  "gimp_drawable_parasite_list",
  "List all parasites.",
  "Returns a list of all currently attached parasites.",
  "Marc Lehmann",
  "Marc Lehmann",
  "1999",
  GIMP_INTERNAL,
  1,
  drawable_parasite_list_inargs,
  2,
  drawable_parasite_list_outargs,
  { { drawable_parasite_list_invoker } }
};

static Argument *
image_parasite_find_invoker (Gimp         *gimp,
                             GimpContext  *context,
                             GimpProgress *progress,
                             Argument     *args)
{
  gboolean success = TRUE;
  Argument *return_args;
  GimpImage *gimage;
  gchar *name;
  GimpParasite *parasite = NULL;

  gimage = gimp_image_get_by_ID (gimp, args[0].value.pdb_int);
  if (! GIMP_IS_IMAGE (gimage))
    success = FALSE;

  name = (gchar *) args[1].value.pdb_pointer;
  if (name == NULL || !g_utf8_validate (name, -1, NULL))
    success = FALSE;

  if (success)
    {
      parasite = gimp_parasite_copy (gimp_image_parasite_find (gimage, name));
      success = parasite != NULL;
    }

  return_args = procedural_db_return_args (&image_parasite_find_proc, success);

  if (success)
    return_args[1].value.pdb_pointer = parasite;

  return return_args;
}

static ProcArg image_parasite_find_inargs[] =
{
  {
    GIMP_PDB_IMAGE,
    "image",
    "The image"
  },
  {
    GIMP_PDB_STRING,
    "name",
    "The name of the parasite to find"
  }
};

static ProcArg image_parasite_find_outargs[] =
{
  {
    GIMP_PDB_PARASITE,
    "parasite",
    "The found parasite"
  }
};

static ProcRecord image_parasite_find_proc =
{
  "gimp_image_parasite_find",
  "Finds the named parasite in an image",
  "Finds and returns the named parasite that was previously attached to an image.",
  "Jay Cox",
  "Jay Cox",
  "1998",
  GIMP_INTERNAL,
  2,
  image_parasite_find_inargs,
  1,
  image_parasite_find_outargs,
  { { image_parasite_find_invoker } }
};

static Argument *
image_parasite_attach_invoker (Gimp         *gimp,
                               GimpContext  *context,
                               GimpProgress *progress,
                               Argument     *args)
{
  gboolean success = TRUE;
  GimpImage *gimage;
  GimpParasite *parasite;

  gimage = gimp_image_get_by_ID (gimp, args[0].value.pdb_int);
  if (! GIMP_IS_IMAGE (gimage))
    success = FALSE;

  parasite = (GimpParasite *) args[1].value.pdb_pointer;
  if (parasite == NULL || parasite->name == NULL || !g_utf8_validate (parasite->name, -1, NULL))
    success = FALSE;

  if (success)
    gimp_image_parasite_attach (gimage, parasite);

  return procedural_db_return_args (&image_parasite_attach_proc, success);
}

static ProcArg image_parasite_attach_inargs[] =
{
  {
    GIMP_PDB_IMAGE,
    "image",
    "The image"
  },
  {
    GIMP_PDB_PARASITE,
    "parasite",
    "The parasite to attach to an image"
  }
};

static ProcRecord image_parasite_attach_proc =
{
  "gimp_image_parasite_attach",
  "Add a parasite to an image.",
  "This procedure attaches a parasite to an image. It has no return values.",
  "Jay Cox",
  "Jay Cox",
  "1998",
  GIMP_INTERNAL,
  2,
  image_parasite_attach_inargs,
  0,
  NULL,
  { { image_parasite_attach_invoker } }
};

static Argument *
image_parasite_detach_invoker (Gimp         *gimp,
                               GimpContext  *context,
                               GimpProgress *progress,
                               Argument     *args)
{
  gboolean success = TRUE;
  GimpImage *gimage;
  gchar *name;

  gimage = gimp_image_get_by_ID (gimp, args[0].value.pdb_int);
  if (! GIMP_IS_IMAGE (gimage))
    success = FALSE;

  name = (gchar *) args[1].value.pdb_pointer;
  if (name == NULL || !g_utf8_validate (name, -1, NULL))
    success = FALSE;

  if (success)
    gimp_image_parasite_detach (gimage, name);

  return procedural_db_return_args (&image_parasite_detach_proc, success);
}

static ProcArg image_parasite_detach_inargs[] =
{
  {
    GIMP_PDB_IMAGE,
    "image",
    "The image"
  },
  {
    GIMP_PDB_STRING,
    "name",
    "The name of the parasite to detach from an image."
  }
};

static ProcRecord image_parasite_detach_proc =
{
  "gimp_image_parasite_detach",
  "Removes a parasite from an image.",
  "This procedure detaches a parasite from an image. It has no return values.",
  "Jay Cox",
  "Jay Cox",
  "1998",
  GIMP_INTERNAL,
  2,
  image_parasite_detach_inargs,
  0,
  NULL,
  { { image_parasite_detach_invoker } }
};

static Argument *
image_parasite_list_invoker (Gimp         *gimp,
                             GimpContext  *context,
                             GimpProgress *progress,
                             Argument     *args)
{
  gboolean success = TRUE;
  Argument *return_args;
  GimpImage *gimage;
  gint32 num_parasites;
  gchar **parasites = NULL;

  gimage = gimp_image_get_by_ID (gimp, args[0].value.pdb_int);
  if (! GIMP_IS_IMAGE (gimage))
    success = FALSE;

  if (success)
    parasites = gimp_image_parasite_list (gimage, &num_parasites);

  return_args = procedural_db_return_args (&image_parasite_list_proc, success);

  if (success)
    {
      return_args[1].value.pdb_int = num_parasites;
      return_args[2].value.pdb_pointer = parasites;
    }

  return return_args;
}

static ProcArg image_parasite_list_inargs[] =
{
  {
    GIMP_PDB_IMAGE,
    "image",
    "The image"
  }
};

static ProcArg image_parasite_list_outargs[] =
{
  {
    GIMP_PDB_INT32,
    "num_parasites",
    "The number of attached parasites"
  },
  {
    GIMP_PDB_STRINGARRAY,
    "parasites",
    "The names of currently attached parasites"
  }
};

static ProcRecord image_parasite_list_proc =
{
  "gimp_image_parasite_list",
  "List all parasites.",
  "Returns a list of all currently attached parasites.",
  "Marc Lehmann",
  "Marc Lehmann",
  "1999",
  GIMP_INTERNAL,
  1,
  image_parasite_list_inargs,
  2,
  image_parasite_list_outargs,
  { { image_parasite_list_invoker } }
};

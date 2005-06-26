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

#include <string.h>

#include <glib-object.h>

#include "libgimpconfig/gimpconfig.h"
#include "libgimpmodule/gimpmodule.h"

#include "pdb-types.h"
#include "procedural_db.h"

#include "config/gimpcoreconfig.h"
#include "config/gimpdisplayconfig.h"
#include "config/gimprc.h"
#include "core/gimp.h"
#include "core/gimptemplate.h"

static ProcRecord gimprc_query_proc;
static ProcRecord gimprc_set_proc;
static ProcRecord get_default_comment_proc;
static ProcRecord get_monitor_resolution_proc;
static ProcRecord get_theme_dir_proc;
static ProcRecord get_color_configuration_proc;
static ProcRecord get_module_load_inhibit_proc;

void
register_gimprc_procs (Gimp *gimp)
{
  procedural_db_register (gimp, &gimprc_query_proc);
  procedural_db_register (gimp, &gimprc_set_proc);
  procedural_db_register (gimp, &get_default_comment_proc);
  procedural_db_register (gimp, &get_monitor_resolution_proc);
  procedural_db_register (gimp, &get_theme_dir_proc);
  procedural_db_register (gimp, &get_color_configuration_proc);
  procedural_db_register (gimp, &get_module_load_inhibit_proc);
}

static Argument *
gimprc_query_invoker (Gimp         *gimp,
                      GimpContext  *context,
                      GimpProgress *progress,
                      Argument     *args)
{
  gboolean success = TRUE;
  Argument *return_args;
  gchar *token;
  gchar *value = NULL;

  token = (gchar *) args[0].value.pdb_pointer;
  if (token == NULL || !g_utf8_validate (token, -1, NULL))
    success = FALSE;

  if (success)
    {
      if (strlen (token))
        {
          /*  use edit_config because unknown tokens are set there  */
          value = gimp_rc_query (GIMP_RC (gimp->edit_config), token);
        }

      success = (value != NULL);
    }

  return_args = procedural_db_return_args (&gimprc_query_proc, success);

  if (success)
    return_args[1].value.pdb_pointer = value;

  return return_args;
}

static ProcArg gimprc_query_inargs[] =
{
  {
    GIMP_PDB_STRING,
    "token",
    "The token to query for"
  }
};

static ProcArg gimprc_query_outargs[] =
{
  {
    GIMP_PDB_STRING,
    "value",
    "The value associated with the queried token"
  }
};

static ProcRecord gimprc_query_proc =
{
  "gimp_gimprc_query",
  "Queries the gimprc file parser for information on a specified token.",
  "This procedure is used to locate additional information contained in the gimprc file considered extraneous to the operation of the GIMP. Plug-ins that need configuration information can expect it will be stored in the user gimprc file and can use this procedure to retrieve it. This query procedure will return the value associated with the specified token. This corresponds _only_ to entries with the format: (<token> <value>). The value must be a string. Entries not corresponding to this format will cause warnings to be issued on gimprc parsing and will not be queryable.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1997",
  NULL,
  GIMP_INTERNAL,
  1,
  gimprc_query_inargs,
  1,
  gimprc_query_outargs,
  { { gimprc_query_invoker } }
};

static Argument *
gimprc_set_invoker (Gimp         *gimp,
                    GimpContext  *context,
                    GimpProgress *progress,
                    Argument     *args)
{
  gboolean success = TRUE;
  gchar *token;
  gchar *value;

  token = (gchar *) args[0].value.pdb_pointer;
  if (token == NULL || !g_utf8_validate (token, -1, NULL))
    success = FALSE;

  value = (gchar *) args[1].value.pdb_pointer;
  if (value == NULL || !g_utf8_validate (value, -1, NULL))
    success = FALSE;

  if (success)
    {
      if (strlen (token))
        {
          /*  use edit_config because that's the one that gets saved  */
          gimp_rc_set_unknown_token (GIMP_RC (gimp->edit_config), token, value);
        }
      else
        success = FALSE;
    }

  return procedural_db_return_args (&gimprc_set_proc, success);
}

static ProcArg gimprc_set_inargs[] =
{
  {
    GIMP_PDB_STRING,
    "token",
    "The token to add or modify"
  },
  {
    GIMP_PDB_STRING,
    "value",
    "The value to set the token to"
  }
};

static ProcRecord gimprc_set_proc =
{
  "gimp_gimprc_set",
  "Sets a gimprc token to a value and saves it in the gimprc.",
  "This procedure is used to add or change additional information in the gimprc file that is considered extraneous to the operation of the GIMP. Plug-ins that need configuration information can use this function to store it, and gimp_gimprc_query to retrieve it. This will accept _only_ string values in UTF-8 encoding.",
  "Seth Burgess",
  "Seth Burgess",
  "1999",
  NULL,
  GIMP_INTERNAL,
  2,
  gimprc_set_inargs,
  0,
  NULL,
  { { gimprc_set_invoker } }
};

static Argument *
get_default_comment_invoker (Gimp         *gimp,
                             GimpContext  *context,
                             GimpProgress *progress,
                             Argument     *args)
{
  Argument *return_args;
  gchar *comment;

  comment = g_strdup (gimp->config->default_image->comment);

  return_args = procedural_db_return_args (&get_default_comment_proc, TRUE);
  return_args[1].value.pdb_pointer = comment;

  return return_args;
}

static ProcArg get_default_comment_outargs[] =
{
  {
    GIMP_PDB_STRING,
    "comment",
    "Default Image Comment"
  }
};

static ProcRecord get_default_comment_proc =
{
  "gimp_get_default_comment",
  "Get the default image comment as specified in the Preferences.",
  "Returns a copy of the default image comment.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  NULL,
  GIMP_INTERNAL,
  0,
  NULL,
  1,
  get_default_comment_outargs,
  { { get_default_comment_invoker } }
};

static Argument *
get_monitor_resolution_invoker (Gimp         *gimp,
                                GimpContext  *context,
                                GimpProgress *progress,
                                Argument     *args)
{
  Argument *return_args;
  gdouble xres;
  gdouble yres;

  xres = GIMP_DISPLAY_CONFIG (gimp->config)->monitor_xres;
  yres = GIMP_DISPLAY_CONFIG (gimp->config)->monitor_yres;

  return_args = procedural_db_return_args (&get_monitor_resolution_proc, TRUE);

  return_args[1].value.pdb_float = xres;
  return_args[2].value.pdb_float = yres;

  return return_args;
}

static ProcArg get_monitor_resolution_outargs[] =
{
  {
    GIMP_PDB_FLOAT,
    "xres",
    "X resolution"
  },
  {
    GIMP_PDB_FLOAT,
    "yres",
    "Y resolution"
  }
};

static ProcRecord get_monitor_resolution_proc =
{
  "gimp_get_monitor_resolution",
  "Get the monitor resolution as specified in the Preferences.",
  "Returns the resolution of the monitor in pixels/inch. This value is taken from the Preferences (or the windowing system if this is set in the Preferences) and there's no guarantee for the value to be reasonable.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  NULL,
  GIMP_INTERNAL,
  0,
  NULL,
  2,
  get_monitor_resolution_outargs,
  { { get_monitor_resolution_invoker } }
};

static Argument *
get_theme_dir_invoker (Gimp         *gimp,
                       GimpContext  *context,
                       GimpProgress *progress,
                       Argument     *args)
{
  Argument *return_args;
  gchar *theme_dir;

  theme_dir = g_strdup (gimp_get_theme_dir (gimp));

  return_args = procedural_db_return_args (&get_theme_dir_proc, TRUE);
  return_args[1].value.pdb_pointer = theme_dir;

  return return_args;
}

static ProcArg get_theme_dir_outargs[] =
{
  {
    GIMP_PDB_STRING,
    "theme_dir",
    "The GUI theme dir"
  }
};

static ProcRecord get_theme_dir_proc =
{
  "gimp_get_theme_dir",
  "Get the directory of the current GUI theme.",
  "Returns a copy of the current GUI theme dir.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  NULL,
  GIMP_INTERNAL,
  0,
  NULL,
  1,
  get_theme_dir_outargs,
  { { get_theme_dir_invoker } }
};

static Argument *
get_color_configuration_invoker (Gimp         *gimp,
                                 GimpContext  *context,
                                 GimpProgress *progress,
                                 Argument     *args)
{
  Argument *return_args;
  gchar *config;

  config = gimp_config_serialize_to_string (GIMP_CONFIG (gimp->config->color_management), NULL);

  return_args = procedural_db_return_args (&get_color_configuration_proc, TRUE);
  return_args[1].value.pdb_pointer = config;

  return return_args;
}

static ProcArg get_color_configuration_outargs[] =
{
  {
    GIMP_PDB_STRING,
    "config",
    "Serialized color management configuration"
  }
};

static ProcRecord get_color_configuration_proc =
{
  "gimp_get_color_configuration",
  "Get a serialized version of the color management configuration.",
  "Returns a string that can be deserialized into a GimpColorConfig object representing the current color management configuration.",
  "Sven Neumann",
  "Sven Neumann",
  "2005",
  NULL,
  GIMP_INTERNAL,
  0,
  NULL,
  1,
  get_color_configuration_outargs,
  { { get_color_configuration_invoker } }
};

static Argument *
get_module_load_inhibit_invoker (Gimp         *gimp,
                                 GimpContext  *context,
                                 GimpProgress *progress,
                                 Argument     *args)
{
  Argument *return_args;
  gchar *load_inhibit;

  load_inhibit = g_strdup (gimp_module_db_get_load_inhibit (gimp->module_db));

  return_args = procedural_db_return_args (&get_module_load_inhibit_proc, TRUE);
  return_args[1].value.pdb_pointer = load_inhibit;

  return return_args;
}

static ProcArg get_module_load_inhibit_outargs[] =
{
  {
    GIMP_PDB_STRING,
    "load_inhibit",
    "The list of modules"
  }
};

static ProcRecord get_module_load_inhibit_proc =
{
  "gimp_get_module_load_inhibit",
  "Get the list of modules which should not be loaded.",
  "Returns a copy of the list of modules which should not be loaded.",
  "Spencer Kimball & Peter Mattis",
  "Spencer Kimball & Peter Mattis",
  "1995-1996",
  NULL,
  GIMP_INTERNAL,
  0,
  NULL,
  1,
  get_module_load_inhibit_outargs,
  { { get_module_load_inhibit_invoker } }
};

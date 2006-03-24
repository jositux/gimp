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

#include <stdlib.h>
#include <string.h>

#include <glib-object.h>

#include "libgimpbase/gimpbase.h"
#include "libgimpbase/gimpprotocol.h"

#include "pdb-types.h"
#include "procedural_db.h"

#include "core/gimp.h"
#include "plug-in/plug-in-def.h"
#include "plug-in/plug-in-params.h"
#include "plug-in/plug-in-proc-def.h"
#include "plug-in/plug-in.h"
#include "plug-in/plug-ins-query.h"
#include "plug-in/plug-ins.h"

static ProcRecord plugins_query_proc;
static ProcRecord plugin_domain_register_proc;
static ProcRecord plugin_help_register_proc;
static ProcRecord plugin_menu_register_proc;
static ProcRecord plugin_menu_branch_register_proc;
static ProcRecord plugin_icon_register_proc;

void
register_plug_in_procs (Gimp *gimp)
{
  procedural_db_register (gimp, &plugins_query_proc);
  procedural_db_register (gimp, &plugin_domain_register_proc);
  procedural_db_register (gimp, &plugin_help_register_proc);
  procedural_db_register (gimp, &plugin_menu_register_proc);
  procedural_db_register (gimp, &plugin_menu_branch_register_proc);
  procedural_db_register (gimp, &plugin_icon_register_proc);
}

static Argument *
plugins_query_invoker (Gimp         *gimp,
                       GimpContext  *context,
                       GimpProgress *progress,
                       Argument     *args)
{
  Argument *return_args;
  gchar *search_string;
  gint32 num_plugins = 0;
  gchar **menu_path = NULL;
  gchar **plugin_accelerator = NULL;
  gchar **plugin_location = NULL;
  gchar **plugin_image_type = NULL;
  gint32 *plugin_install_time = NULL;
  gchar **plugin_real_name = NULL;

  search_string = (gchar *) args[0].value.pdb_pointer;

  num_plugins = plug_ins_query (gimp, search_string,
                                &menu_path,
                                &plugin_accelerator,
                                &plugin_location,
                                &plugin_image_type,
                                &plugin_real_name,
                                &plugin_install_time);

  return_args = procedural_db_return_args (&plugins_query_proc, TRUE);

  return_args[1].value.pdb_int = num_plugins;
  return_args[2].value.pdb_pointer = menu_path;
  return_args[3].value.pdb_int = num_plugins;
  return_args[4].value.pdb_pointer = plugin_accelerator;
  return_args[5].value.pdb_int = num_plugins;
  return_args[6].value.pdb_pointer = plugin_location;
  return_args[7].value.pdb_int = num_plugins;
  return_args[8].value.pdb_pointer = plugin_image_type;
  return_args[9].value.pdb_int = num_plugins;
  return_args[10].value.pdb_pointer = plugin_install_time;
  return_args[11].value.pdb_int = num_plugins;
  return_args[12].value.pdb_pointer = plugin_real_name;

  return return_args;
}

static ProcArg plugins_query_inargs[] =
{
  {
    GIMP_PDB_STRING,
    "search-string",
    "If not an empty string then use this as a search pattern"
  }
};

static ProcArg plugins_query_outargs[] =
{
  {
    GIMP_PDB_INT32,
    "num-plugins",
    "The number of plugins"
  },
  {
    GIMP_PDB_STRINGARRAY,
    "menu-path",
    "The menu path of the plugin"
  },
  {
    GIMP_PDB_INT32,
    "num-plugins",
    "The number of plugins"
  },
  {
    GIMP_PDB_STRINGARRAY,
    "plugin-accelerator",
    "String representing keyboard accelerator (could be empty string)"
  },
  {
    GIMP_PDB_INT32,
    "num-plugins",
    "The number of plugins"
  },
  {
    GIMP_PDB_STRINGARRAY,
    "plugin-location",
    "Location of the plugin program"
  },
  {
    GIMP_PDB_INT32,
    "num-plugins",
    "The number of plugins"
  },
  {
    GIMP_PDB_STRINGARRAY,
    "plugin-image-type",
    "Type of image that this plugin will work on"
  },
  {
    GIMP_PDB_INT32,
    "num-plugins",
    "The number of plugins"
  },
  {
    GIMP_PDB_INT32ARRAY,
    "plugin-install-time",
    "Time that the plugin was installed"
  },
  {
    GIMP_PDB_INT32,
    "num-plugins",
    "The number of plugins"
  },
  {
    GIMP_PDB_STRINGARRAY,
    "plugin-real-name",
    "The internal name of the plugin"
  }
};

static ProcRecord plugins_query_proc =
{
  "gimp-plugins-query",
  "gimp-plugins-query",
  "Queries the plugin database for its contents.",
  "This procedure queries the contents of the plugin database.",
  "Andy Thomas",
  "Andy Thomas",
  "1998",
  NULL,
  GIMP_INTERNAL,
  1,
  plugins_query_inargs,
  12,
  plugins_query_outargs,
  { { plugins_query_invoker } }
};

static Argument *
plugin_domain_register_invoker (Gimp         *gimp,
                                GimpContext  *context,
                                GimpProgress *progress,
                                Argument     *args)
{
  gboolean success = TRUE;
  gchar *domain_name;
  gchar *domain_path;

  domain_name = (gchar *) args[0].value.pdb_pointer;
  if (domain_name == NULL || !g_utf8_validate (domain_name, -1, NULL))
    success = FALSE;

  domain_path = (gchar *) args[1].value.pdb_pointer;

  if (success)
    {
      if (gimp->current_plug_in && gimp->current_plug_in->query)
        {
          plug_in_def_set_locale_domain_name (gimp->current_plug_in->plug_in_def,
                                              domain_name);
          plug_in_def_set_locale_domain_path (gimp->current_plug_in->plug_in_def,
                                              domain_path);
        }
      else
        success = FALSE;
    }

  return procedural_db_return_args (&plugin_domain_register_proc, success);
}

static ProcArg plugin_domain_register_inargs[] =
{
  {
    GIMP_PDB_STRING,
    "domain-name",
    "The name of the textdomain (must be unique)"
  },
  {
    GIMP_PDB_STRING,
    "domain-path",
    "The absolute path to the compiled message catalog (may be NULL)"
  }
};

static ProcRecord plugin_domain_register_proc =
{
  "gimp-plugin-domain-register",
  "gimp-plugin-domain-register",
  "Registers a textdomain for localisation.",
  "This procedure adds a textdomain to the list of domains Gimp searches for strings when translating its menu entries. There is no need to call this function for plug-ins that have their strings included in the gimp-std-plugins domain as that is used by default. If the compiled message catalog is not in the standard location, you may specify an absolute path to another location. This procedure can only be called in the query function of a plug-in and it has to be called before any procedure is installed.",
  "Sven Neumann <sven@gimp.org>",
  "Sven Neumann",
  "2000",
  NULL,
  GIMP_INTERNAL,
  2,
  plugin_domain_register_inargs,
  0,
  NULL,
  { { plugin_domain_register_invoker } }
};

static Argument *
plugin_help_register_invoker (Gimp         *gimp,
                              GimpContext  *context,
                              GimpProgress *progress,
                              Argument     *args)
{
  gboolean success = TRUE;
  gchar *domain_name;
  gchar *domain_uri;

  domain_name = (gchar *) args[0].value.pdb_pointer;
  if (domain_name == NULL || !g_utf8_validate (domain_name, -1, NULL))
    success = FALSE;

  domain_uri = (gchar *) args[1].value.pdb_pointer;
  if (domain_uri == NULL || !g_utf8_validate (domain_uri, -1, NULL))
    success = FALSE;

  if (success)
    {
      if (gimp->current_plug_in && gimp->current_plug_in->query)
        {
          plug_in_def_set_help_domain_name (gimp->current_plug_in->plug_in_def,
                                            domain_name);
          plug_in_def_set_help_domain_uri (gimp->current_plug_in->plug_in_def,
                                           domain_uri);
        }
      else
        success = FALSE;
    }

  return procedural_db_return_args (&plugin_help_register_proc, success);
}

static ProcArg plugin_help_register_inargs[] =
{
  {
    GIMP_PDB_STRING,
    "domain-name",
    "The XML namespace of the plug-in's help pages"
  },
  {
    GIMP_PDB_STRING,
    "domain-uri",
    "The root URI of the plug-in's help pages"
  }
};

static ProcRecord plugin_help_register_proc =
{
  "gimp-plugin-help-register",
  "gimp-plugin-help-register",
  "Register a help path for a plug-in.",
  "This procedure changes the help rootdir for the plug-in which calls it. All subsequent calls of gimp_help from this plug-in will be interpreted relative to this rootdir.",
  "Michael Natterer <mitch@gimp.org>",
  "Michael Natterer",
  "2000",
  NULL,
  GIMP_INTERNAL,
  2,
  plugin_help_register_inargs,
  0,
  NULL,
  { { plugin_help_register_invoker } }
};

static Argument *
plugin_menu_register_invoker (Gimp         *gimp,
                              GimpContext  *context,
                              GimpProgress *progress,
                              Argument     *args)
{
  gboolean success = TRUE;
  gchar *procedure_name;
  gchar *menu_path;

  procedure_name = (gchar *) args[0].value.pdb_pointer;
  if (procedure_name == NULL || !g_utf8_validate (procedure_name, -1, NULL))
    success = FALSE;

  menu_path = (gchar *) args[1].value.pdb_pointer;
  if (menu_path == NULL || !g_utf8_validate (menu_path, -1, NULL))
    success = FALSE;

  if (success)
    {
      if (gimp->current_plug_in)
        {
          gchar *canonical = gimp_canonicalize_identifier (procedure_name);

          success = plug_in_menu_register (gimp->current_plug_in,
                                           canonical, menu_path);
          g_free (canonical);
        }
      else
        {
          success = FALSE;
        }
    }

  return procedural_db_return_args (&plugin_menu_register_proc, success);
}

static ProcArg plugin_menu_register_inargs[] =
{
  {
    GIMP_PDB_STRING,
    "procedure-name",
    "The procedure for which to install the menu path"
  },
  {
    GIMP_PDB_STRING,
    "menu-path",
    "The procedure's additional menu path"
  }
};

static ProcRecord plugin_menu_register_proc =
{
  "gimp-plugin-menu-register",
  "gimp-plugin-menu-register",
  "Register an additional menu path for a plug-in procedure.",
  "This procedure installs an additional menu entry for the given procedure.",
  "Michael Natterer <mitch@gimp.org>",
  "Michael Natterer",
  "2004",
  NULL,
  GIMP_INTERNAL,
  2,
  plugin_menu_register_inargs,
  0,
  NULL,
  { { plugin_menu_register_invoker } }
};

static Argument *
plugin_menu_branch_register_invoker (Gimp         *gimp,
                                     GimpContext  *context,
                                     GimpProgress *progress,
                                     Argument     *args)
{
  gboolean success = TRUE;
  gchar *menu_path;
  gchar *menu_name;

  menu_path = (gchar *) args[0].value.pdb_pointer;
  if (menu_path == NULL || !g_utf8_validate (menu_path, -1, NULL))
    success = FALSE;

  menu_name = (gchar *) args[1].value.pdb_pointer;
  if (menu_name == NULL || !g_utf8_validate (menu_name, -1, NULL))
    success = FALSE;

  if (success)
    {
      if (gimp->current_plug_in)
        {
          plug_ins_menu_branch_add (gimp, gimp->current_plug_in->prog,
                                    menu_path, menu_name);

          if (! gimp->no_interface)
            {
              gimp_menus_create_branch (gimp, gimp->current_plug_in->prog,
                                        menu_path, menu_name);
            }
          else
            success = FALSE;
        }
      else
        success = FALSE;
    }

  return procedural_db_return_args (&plugin_menu_branch_register_proc, success);
}

static ProcArg plugin_menu_branch_register_inargs[] =
{
  {
    GIMP_PDB_STRING,
    "menu-path",
    "The sub-menu's menu path"
  },
  {
    GIMP_PDB_STRING,
    "menu-name",
    "The name of the sub-menu"
  }
};

static ProcRecord plugin_menu_branch_register_proc =
{
  "gimp-plugin-menu-branch-register",
  "gimp-plugin-menu-branch-register",
  "Register a sub-menu.",
  "This procedure installs an sub-menu which does not belong to any procedure.",
  "Michael Natterer <mitch@gimp.org>",
  "Michael Natterer",
  "2005",
  NULL,
  GIMP_INTERNAL,
  2,
  plugin_menu_branch_register_inargs,
  0,
  NULL,
  { { plugin_menu_branch_register_invoker } }
};

static Argument *
plugin_icon_register_invoker (Gimp         *gimp,
                              GimpContext  *context,
                              GimpProgress *progress,
                              Argument     *args)
{
  gboolean success = TRUE;
  gchar *procedure_name;
  gint32 icon_type;
  gint32 icon_data_length;
  guint8 *icon_data;

  procedure_name = (gchar *) args[0].value.pdb_pointer;
  if (procedure_name == NULL || !g_utf8_validate (procedure_name, -1, NULL))
    success = FALSE;

  icon_type = args[1].value.pdb_int;
  if (icon_type < GIMP_ICON_TYPE_STOCK_ID || icon_type > GIMP_ICON_TYPE_IMAGE_FILE)
    success = FALSE;

  icon_data_length = args[2].value.pdb_int;
  if (icon_data_length <= 0)
    success = FALSE;

  icon_data = (guint8 *) args[3].value.pdb_pointer;

  if (success)
    {
      if (gimp->current_plug_in && gimp->current_plug_in->query)
        {
          PlugInProcDef *proc_def;
          gchar         *canonical;

          canonical = gimp_canonicalize_identifier (procedure_name);

          proc_def = plug_in_proc_def_find (gimp->current_plug_in->plug_in_def->proc_defs,
                                            canonical);

          g_free (canonical);

          if (proc_def)
            plug_in_proc_def_set_icon (proc_def, icon_type,
                                       icon_data, icon_data_length);
          else
            success = FALSE;
        }
      else
        success = FALSE;
    }

  return procedural_db_return_args (&plugin_icon_register_proc, success);
}

static ProcArg plugin_icon_register_inargs[] =
{
  {
    GIMP_PDB_STRING,
    "procedure-name",
    "The procedure for which to install the icon"
  },
  {
    GIMP_PDB_INT32,
    "icon-type",
    "The type of the icon: { GIMP_ICON_TYPE_STOCK_ID (0), GIMP_ICON_TYPE_INLINE_PIXBUF (1), GIMP_ICON_TYPE_IMAGE_FILE (2) }"
  },
  {
    GIMP_PDB_INT32,
    "icon-data-length",
    "The length of 'icon_data': 0 < icon_data_length"
  },
  {
    GIMP_PDB_INT8ARRAY,
    "icon-data",
    "The procedure's icon. The format depends on the 'icon_type' parameter"
  }
};

static ProcRecord plugin_icon_register_proc =
{
  "gimp-plugin-icon-register",
  "gimp-plugin-icon-register",
  "Register an icon for a plug-in procedure.",
  "This procedure installs an icon for the given procedure.",
  "Michael Natterer <mitch@gimp.org>",
  "Michael Natterer",
  "2004",
  NULL,
  GIMP_INTERNAL,
  4,
  plugin_icon_register_inargs,
  0,
  NULL,
  { { plugin_icon_register_invoker } }
};

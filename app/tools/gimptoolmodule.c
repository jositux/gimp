/* The GIMP -- an image manipulation program
 * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis and others
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

#include "gimptoolmodule.h"


static void   gimp_tool_module_class_init   (GimpToolModuleClass   *klass);
static void   gimp_tool_module_init         (GimpToolModule        *tool);


static GTypeModuleClass *parent_class = NULL;


static gboolean
gimp_tool_module_load (GTypeModule *gmodule) {
  GimpToolModule *module = GIMP_TOOL_MODULE(gmodule);

  g_return_val_if_fail(module, FALSE);
  g_return_val_if_fail(module->filename, FALSE);
  g_return_val_if_fail(g_module_supported(), FALSE);

  module->module = g_module_open(module->filename, G_MODULE_BIND_LAZY);

  if (!module)
  	return FALSE;

  if (!g_module_symbol (module->module, "gimp_tool_module_register", (gpointer *) &module->register_tool))
    {
      g_warning (g_module_error());
      g_module_close (module->module);

      return FALSE;
    }
                                                                                                                  
  return TRUE;
}

static void
gimp_tool_module_unload (GTypeModule *gmodule) {
  GimpToolModule *module = GIMP_TOOL_MODULE(gmodule);

  g_return_if_fail(module);
  g_return_if_fail(module->module);
  g_return_if_fail(g_module_supported());

  g_module_close(module->module); /* FIXME: error handling */
  module->module=NULL;
}

GType
gimp_tool_module_get_type (void)
{
  static GType tool_module_type = 0;

  if (! tool_module_type)
    {
      static const GTypeInfo tool_module_info =
      {
        sizeof (GimpToolModuleClass),
	(GBaseInitFunc) NULL,
	(GBaseFinalizeFunc) NULL,
	(GClassInitFunc) gimp_tool_module_class_init,
	NULL,           /* class_finalize */
	NULL,           /* class_data     */
	sizeof (GimpToolModule),
	0,              /* n_preallocs    */
	(GInstanceInitFunc) gimp_tool_module_init,
      };

      tool_module_type = g_type_register_static (G_TYPE_TYPE_MODULE,
			        	         "GimpToolModule", 
                                                 &tool_module_info, 0);
    }

  return tool_module_type;
}

static void
gimp_tool_module_class_init (GimpToolModuleClass *klass)
{
  GTypeModuleClass *g_type_module_class = G_TYPE_MODULE_CLASS(klass);
  parent_class = g_type_class_peek_parent (klass);

  g_type_module_class->load = gimp_tool_module_load;
  g_type_module_class->unload = gimp_tool_module_unload;
}

static void
gimp_tool_module_init (GimpToolModule *module)
{
  module->module        = NULL;
  module->filename      = NULL;
  module->register_tool = NULL;
}


GimpToolModule *
gimp_tool_module_new (gchar *filename, Gimp *gimp, GimpToolRegisterCallback callback)
{
  GimpToolModule *module = GIMP_TOOL_MODULE(g_object_new(GIMP_TYPE_TOOL_MODULE, NULL));

  g_return_val_if_fail (filename, NULL);
  g_return_val_if_fail (gimp, NULL);
  g_return_val_if_fail (callback, NULL);

  module->filename = g_strdup(filename);
  gimp_tool_module_load(G_TYPE_MODULE(module)); /* FIXME: check for errors! */
  module->register_tool (gimp, callback, G_TYPE_MODULE(module));
  gimp_tool_module_unload(G_TYPE_MODULE(module));

  return module;
}

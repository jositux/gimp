/* The GIMP -- an image manipulation program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * gimpmoduleinfo.h
 * (C) 1999 Austin Donnelly <austin@gimp.org>
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

#ifndef __GIMP_MODULE_INFO_H__
#define __GIMP_MODULE_INFO_H__


#include "libgimp/gimpmodule.h"

#include "gimpobject.h"


typedef enum
{
  GIMP_MODULE_STATE_ERROR,             /* missing module_load function or other error    */
  GIMP_MODULE_STATE_LOADED_OK,         /* happy and running (normal state of affairs)    */
  GIMP_MODULE_STATE_LOAD_FAILED,       /* module_load returned GIMP_MODULE_UNLOAD        */
  GIMP_MODULE_STATE_UNLOAD_REQUESTED,  /* sent unload request, waiting for callback      */
  GIMP_MODULE_STATE_UNLOADED_OK        /* callback arrived, module not in memory anymore */
} GimpModuleState;


#define GIMP_TYPE_MODULE_INFO            (gimp_module_info_get_type ())
#define GIMP_MODULE_INFO(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_MODULE_INFO, GimpModuleInfoObj))
#define GIMP_MODULE_INFO_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_MODULE_INFO, GimpModuleInfoObjClass))
#define GIMP_IS_MODULE_INFO(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_MODULE_INFO))
#define GIMP_IS_MODULE_INFO_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_MODULE_INFO))
#define GIMP_MODULE_INFO_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_MODULE_INFO, GimpModuleInfoObjClass))


typedef struct _GimpModuleInfoObjClass GimpModuleInfoObjClass;

struct _GimpModuleInfoObj
{
  GimpObject       parent_instance;

  gchar           *fullpath;     /* path to the module                        */
  GimpModuleState  state;        /* what's happened to the module             */
  guint        on_disk : 1;      /* TRUE if file still exists                 */
  guint        load_inhibit : 1; /* user requests not to load at boot time    */

  /* Count of times main gimp is within the module.  Normally, this
   * will be 1, and we assume that the module won't call its
   * unload callback until it is satisfied that it's not in use any
   * more.  refs can be 2 temporarily while we're running the module's
   * unload function, to stop the module attempting to unload
   * itself.
   */
  guint            refs;

  /* stuff from now on may be NULL depending on the state the module is in   */
  GimpModuleInfo  *info;         /* returned values from module_init          */
  GModule         *module;       /* handle on the module                      */
  gchar           *last_module_error;

  GimpModuleInitFunc   init;
  GimpModuleUnloadFunc unload;
};

struct _GimpModuleInfoObjClass
{
  GimpObjectClass  parent_class;

  void (* modified) (GimpModuleInfoObj *module_info);
};


GType               gimp_module_info_get_type         (void) G_GNUC_CONST;

GimpModuleInfoObj * gimp_module_info_new              (const gchar       *filename);

void                gimp_module_info_modified         (GimpModuleInfoObj *module);
void                gimp_module_info_set_load_inhibit (GimpModuleInfoObj *module,
                                                       const gchar       *inhibit_list);

void                gimp_module_info_module_load      (GimpModuleInfoObj *module_info, 
                                                       gboolean           verbose);
void                gimp_module_info_module_unload    (GimpModuleInfoObj *module_info,
                                                       gboolean           verbose);
void                gimp_module_info_module_ref       (GimpModuleInfoObj *module_info);
void                gimp_module_info_module_unref     (GimpModuleInfoObj *module_info);


#endif  /* __GIMP_MODULE_INFO_H__ */

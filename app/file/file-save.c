/* The GIMP -- an image manipulation program
 * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis
 * Copyright (C) 1997 Josh MacDonald
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

#include "config.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <glib-object.h>

#ifdef G_OS_WIN32
#include <io.h>
#define W_OK 2
#define access(f,p) _access(f,p)
#endif

#include "core/core-types.h"

#include "config/gimpcoreconfig.h"

#include "core/gimp.h"
#include "core/gimpcontext.h"
#include "core/gimpdocumentlist.h"
#include "core/gimpdrawable.h"
#include "core/gimpimage.h"
#include "core/gimpimagefile.h"
#include "core/gimpprogress.h"

#include "pdb/procedural_db.h"

#include "plug-in/plug-in.h"
#include "plug-in/plug-in-proc.h"

#include "file-save.h"
#include "file-utils.h"

#include "gimp-intl.h"


/*  public functions  */

GimpPDBStatusType
file_save (GimpImage    *gimage,
           GimpContext  *context,
           GimpProgress *progress,
           GimpRunMode   run_mode,
           GError      **error)
{
  const gchar   *uri;
  PlugInProcDef *file_proc;

  g_return_val_if_fail (GIMP_IS_IMAGE (gimage), GIMP_PDB_CALLING_ERROR);
  g_return_val_if_fail (GIMP_IS_CONTEXT (context), GIMP_PDB_CALLING_ERROR);
  g_return_val_if_fail (progress == NULL || GIMP_IS_PROGRESS (progress),
                        GIMP_PDB_CALLING_ERROR);
  g_return_val_if_fail (error == NULL || *error == NULL,
                        GIMP_PDB_CALLING_ERROR);

  uri = gimp_object_get_name (GIMP_OBJECT (gimage));

  g_return_val_if_fail (uri != NULL, GIMP_PDB_CALLING_ERROR);

  file_proc = gimp_image_get_save_proc (gimage);

  return file_save_as (gimage, context, progress,
                       uri, uri, file_proc, run_mode,
                       FALSE, TRUE, error);
}

GimpPDBStatusType
file_save_as (GimpImage      *gimage,
              GimpContext    *context,
              GimpProgress   *progress,
              const gchar    *uri,
              const gchar    *raw_filename,
              PlugInProcDef  *file_proc,
              GimpRunMode     run_mode,
              gboolean        set_uri_and_proc,
              gboolean        set_image_clean,
              GError        **error)
{
  const ProcRecord  *proc;
  Argument          *args;
  Argument          *return_vals;
  GimpPDBStatusType  status;
  gint               i;
  gchar             *filename;

  g_return_val_if_fail (GIMP_IS_IMAGE (gimage), GIMP_PDB_CALLING_ERROR);
  g_return_val_if_fail (GIMP_IS_CONTEXT (context), GIMP_PDB_CALLING_ERROR);
  g_return_val_if_fail (progress == NULL || GIMP_IS_PROGRESS (progress),
                        GIMP_PDB_CALLING_ERROR);
  g_return_val_if_fail (uri != NULL, GIMP_PDB_CALLING_ERROR);
  g_return_val_if_fail (raw_filename != NULL, GIMP_PDB_CALLING_ERROR);
  g_return_val_if_fail (error == NULL || *error == NULL,
                        GIMP_PDB_CALLING_ERROR);

  if (gimp_image_active_drawable (gimage) == NULL)
    return GIMP_PDB_EXECUTION_ERROR;

  if (! file_proc)
    file_proc = file_utils_find_proc (gimage->gimp->save_procs, raw_filename);

  if (! file_proc)
    {
      g_set_error (error, G_FILE_ERROR, G_FILE_ERROR_FAILED,
                   _("Unknown file type"));
      return GIMP_PDB_CALLING_ERROR;
    }

  filename = g_filename_from_uri (uri, NULL, NULL);

  if (filename)
    {
      /* check if we are saving to a file */
      if (g_file_test (filename, G_FILE_TEST_EXISTS))
        {
          if (! g_file_test (filename, G_FILE_TEST_IS_REGULAR))
            {
              g_set_error (error, G_FILE_ERROR, G_FILE_ERROR_FAILED,
                           _("Not a regular file"));
              g_free (filename);
              return GIMP_PDB_EXECUTION_ERROR;
            }

          if (access (filename, W_OK) != 0)
            {
              g_set_error (error, G_FILE_ERROR, G_FILE_ERROR_ACCES,
                           g_strerror (errno));
              g_free (filename);
              return GIMP_PDB_EXECUTION_ERROR;
            }
        }
    }

  /* ref the image, so it can't get deleted during save */
  g_object_ref (gimage);

  proc = plug_in_proc_def_get_proc (file_proc);

  args = g_new0 (Argument, proc->num_args);

  for (i = 0; i < proc->num_args; i++)
    args[i].arg_type = proc->args[i].arg_type;

  args[0].value.pdb_int     = run_mode;
  args[1].value.pdb_int     = gimp_image_get_ID (gimage);
  args[2].value.pdb_int     = gimp_item_get_ID (GIMP_ITEM (gimp_image_active_drawable (gimage)));
  args[3].value.pdb_pointer = (gpointer) (filename ? filename : uri);
  args[4].value.pdb_pointer = (gpointer) raw_filename;

  return_vals = procedural_db_execute (gimage->gimp, context, progress,
                                       proc->name, args);

  if (filename)
    g_free (filename);

  status = return_vals[0].value.pdb_int;

  if (status == GIMP_PDB_SUCCESS)
    {
      GimpDocumentList *documents;
      GimpImagefile    *imagefile;

      if (set_image_clean)
        {
          /*  set this image to clean  */
          gimp_image_clean_all (gimage);
        }

      documents = GIMP_DOCUMENT_LIST (gimage->gimp->documents);
      imagefile = gimp_document_list_add_uri (documents,
                                              uri, file_proc->mime_type);

      if (set_uri_and_proc)
	{
	  gimp_image_set_uri (gimage, uri);
          gimp_image_set_save_proc (gimage, file_proc);
	}

      /* Write a thumbnail for the saved image */
      if (set_uri_and_proc)
        {
          gimp_imagefile_save_thumbnail (imagefile, gimage);
        }
      else
        {
          gchar *saved_uri;

          saved_uri = GIMP_OBJECT (gimage)->name;
          GIMP_OBJECT (gimage)->name = (gchar *) uri;

          gimp_imagefile_save_thumbnail (imagefile, gimage);

          GIMP_OBJECT (gimage)->name = saved_uri;
	}
    }
  else if (status != GIMP_PDB_CANCEL)
    {
      g_set_error (error, G_FILE_ERROR, G_FILE_ERROR_FAILED,
                   _("Plug-In could not save image"));
    }

  g_free (return_vals);
  g_free (args);

  g_object_unref (gimage);

  return status;
}

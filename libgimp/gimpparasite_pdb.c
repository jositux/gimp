/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpparasite_pdb.c
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/* NOTE: This file is autogenerated by pdbgen.pl */

#include "config.h"

#include "gimp.h"

/**
 * gimp_parasite_find:
 * @name: The name of the parasite to find.
 *
 * Finds the named parasite.
 *
 * Finds and returns the named parasite that was previously attached to
 * the gimp.
 *
 * Returns: The found parasite.
 */
GimpParasite *
gimp_parasite_find (const gchar *name)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  GimpParasite *parasite = NULL;

  return_vals = gimp_run_procedure ("gimp-parasite-find",
                                    &nreturn_vals,
                                    GIMP_PDB_STRING, name,
                                    GIMP_PDB_END);

  if (return_vals[0].data.d_status == GIMP_PDB_SUCCESS)
    parasite = gimp_parasite_copy (&return_vals[1].data.d_parasite);

  gimp_destroy_params (return_vals, nreturn_vals);

  return parasite;
}

/**
 * gimp_parasite_attach:
 * @parasite: The parasite to attach to the gimp.
 *
 * Add a parasite to the gimp.
 *
 * This procedure attaches a parasite to the gimp. It has no return
 * values.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_parasite_attach (const GimpParasite *parasite)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-parasite-attach",
                                    &nreturn_vals,
                                    GIMP_PDB_PARASITE, parasite,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_parasite_detach:
 * @name: The name of the parasite to detach from the gimp.
 *
 * Removes a parasite from the gimp.
 *
 * This procedure detaches a parasite from the gimp. It has no return
 * values.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_parasite_detach (const gchar *name)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-parasite-detach",
                                    &nreturn_vals,
                                    GIMP_PDB_STRING, name,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_parasite_list:
 * @num_parasites: The number of attached parasites.
 * @parasites: The names of currently attached parasites.
 *
 * List all parasites.
 *
 * Returns a list of all currently attached parasites.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_parasite_list (gint    *num_parasites,
                    gchar ***parasites)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;
  gint i;

  return_vals = gimp_run_procedure ("gimp-parasite-list",
                                    &nreturn_vals,
                                    GIMP_PDB_END);

  *num_parasites = 0;
  *parasites = NULL;

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  if (success)
    {
      *num_parasites = return_vals[1].data.d_int32;
      *parasites = g_new (gchar *, *num_parasites);
      for (i = 0; i < *num_parasites; i++)
        (*parasites)[i] = g_strdup (return_vals[2].data.d_stringarray[i]);
    }

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_image_parasite_find:
 * @image_ID: The image.
 * @name: The name of the parasite to find.
 *
 * Finds the named parasite in an image
 *
 * Finds and returns the named parasite that was previously attached to
 * an image.
 *
 * Returns: The found parasite.
 */
GimpParasite *
gimp_image_parasite_find (gint32       image_ID,
                          const gchar *name)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  GimpParasite *parasite = NULL;

  return_vals = gimp_run_procedure ("gimp-image-parasite-find",
                                    &nreturn_vals,
                                    GIMP_PDB_IMAGE, image_ID,
                                    GIMP_PDB_STRING, name,
                                    GIMP_PDB_END);

  if (return_vals[0].data.d_status == GIMP_PDB_SUCCESS)
    parasite = gimp_parasite_copy (&return_vals[1].data.d_parasite);

  gimp_destroy_params (return_vals, nreturn_vals);

  return parasite;
}

/**
 * gimp_image_parasite_attach:
 * @image_ID: The image.
 * @parasite: The parasite to attach to an image.
 *
 * Add a parasite to an image.
 *
 * This procedure attaches a parasite to an image. It has no return
 * values.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_image_parasite_attach (gint32              image_ID,
                            const GimpParasite *parasite)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-image-parasite-attach",
                                    &nreturn_vals,
                                    GIMP_PDB_IMAGE, image_ID,
                                    GIMP_PDB_PARASITE, parasite,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_image_parasite_detach:
 * @image_ID: The image.
 * @name: The name of the parasite to detach from an image.
 *
 * Removes a parasite from an image.
 *
 * This procedure detaches a parasite from an image. It has no return
 * values.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_image_parasite_detach (gint32       image_ID,
                            const gchar *name)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-image-parasite-detach",
                                    &nreturn_vals,
                                    GIMP_PDB_IMAGE, image_ID,
                                    GIMP_PDB_STRING, name,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_image_parasite_list:
 * @image_ID: The image.
 * @num_parasites: The number of attached parasites.
 * @parasites: The names of currently attached parasites.
 *
 * List all parasites.
 *
 * Returns a list of all currently attached parasites.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_image_parasite_list (gint32    image_ID,
                          gint     *num_parasites,
                          gchar  ***parasites)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;
  gint i;

  return_vals = gimp_run_procedure ("gimp-image-parasite-list",
                                    &nreturn_vals,
                                    GIMP_PDB_IMAGE, image_ID,
                                    GIMP_PDB_END);

  *num_parasites = 0;
  *parasites = NULL;

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  if (success)
    {
      *num_parasites = return_vals[1].data.d_int32;
      *parasites = g_new (gchar *, *num_parasites);
      for (i = 0; i < *num_parasites; i++)
        (*parasites)[i] = g_strdup (return_vals[2].data.d_stringarray[i]);
    }

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_drawable_parasite_find:
 * @drawable_ID: The drawable.
 * @name: The name of the parasite to find.
 *
 * Finds the named parasite in a drawable
 *
 * Finds and returns the named parasite that was previously attached to
 * a drawable.
 *
 * Returns: The found parasite.
 */
GimpParasite *
gimp_drawable_parasite_find (gint32       drawable_ID,
                             const gchar *name)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  GimpParasite *parasite = NULL;

  return_vals = gimp_run_procedure ("gimp-drawable-parasite-find",
                                    &nreturn_vals,
                                    GIMP_PDB_DRAWABLE, drawable_ID,
                                    GIMP_PDB_STRING, name,
                                    GIMP_PDB_END);

  if (return_vals[0].data.d_status == GIMP_PDB_SUCCESS)
    parasite = gimp_parasite_copy (&return_vals[1].data.d_parasite);

  gimp_destroy_params (return_vals, nreturn_vals);

  return parasite;
}

/**
 * gimp_drawable_parasite_attach:
 * @drawable_ID: The drawable.
 * @parasite: The parasite to attach to a drawable.
 *
 * Add a parasite to a drawable.
 *
 * This procedure attaches a parasite to a drawable. It has no return
 * values.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_drawable_parasite_attach (gint32              drawable_ID,
                               const GimpParasite *parasite)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-drawable-parasite-attach",
                                    &nreturn_vals,
                                    GIMP_PDB_DRAWABLE, drawable_ID,
                                    GIMP_PDB_PARASITE, parasite,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_drawable_parasite_detach:
 * @drawable_ID: The drawable.
 * @name: The name of the parasite to detach from a drawable.
 *
 * Removes a parasite from a drawable.
 *
 * This procedure detaches a parasite from a drawable. It has no return
 * values.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_drawable_parasite_detach (gint32       drawable_ID,
                               const gchar *name)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-drawable-parasite-detach",
                                    &nreturn_vals,
                                    GIMP_PDB_DRAWABLE, drawable_ID,
                                    GIMP_PDB_STRING, name,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_drawable_parasite_list:
 * @drawable_ID: The drawable.
 * @num_parasites: The number of attached parasites.
 * @parasites: The names of currently attached parasites.
 *
 * List all parasites.
 *
 * Returns a list of all currently attached parasites.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_drawable_parasite_list (gint32    drawable_ID,
                             gint     *num_parasites,
                             gchar  ***parasites)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;
  gint i;

  return_vals = gimp_run_procedure ("gimp-drawable-parasite-list",
                                    &nreturn_vals,
                                    GIMP_PDB_DRAWABLE, drawable_ID,
                                    GIMP_PDB_END);

  *num_parasites = 0;
  *parasites = NULL;

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  if (success)
    {
      *num_parasites = return_vals[1].data.d_int32;
      *parasites = g_new (gchar *, *num_parasites);
      for (i = 0; i < *num_parasites; i++)
        (*parasites)[i] = g_strdup (return_vals[2].data.d_stringarray[i]);
    }

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_vectors_parasite_find:
 * @vectors_ID: The vectors object.
 * @name: The name of the parasite to find.
 *
 * Finds the named parasite in a vectors object
 *
 * Finds and returns the named parasite that was previously attached to
 * a vectors object.
 *
 * Returns: The found parasite.
 *
 * Since: GIMP 2.4
 */
GimpParasite *
gimp_vectors_parasite_find (gint32       vectors_ID,
                            const gchar *name)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  GimpParasite *parasite = NULL;

  return_vals = gimp_run_procedure ("gimp-vectors-parasite-find",
                                    &nreturn_vals,
                                    GIMP_PDB_VECTORS, vectors_ID,
                                    GIMP_PDB_STRING, name,
                                    GIMP_PDB_END);

  if (return_vals[0].data.d_status == GIMP_PDB_SUCCESS)
    parasite = gimp_parasite_copy (&return_vals[1].data.d_parasite);

  gimp_destroy_params (return_vals, nreturn_vals);

  return parasite;
}

/**
 * gimp_vectors_parasite_attach:
 * @vectors_ID: The vectors object.
 * @parasite: The parasite to attach to a vectors object.
 *
 * Add a parasite to a vectors object
 *
 * This procedure attaches a parasite to a vectors object. It has no
 * return values.
 *
 * Returns: TRUE on success.
 *
 * Since: GIMP 2.4
 */
gboolean
gimp_vectors_parasite_attach (gint32              vectors_ID,
                              const GimpParasite *parasite)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-vectors-parasite-attach",
                                    &nreturn_vals,
                                    GIMP_PDB_VECTORS, vectors_ID,
                                    GIMP_PDB_PARASITE, parasite,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_vectors_parasite_detach:
 * @vectors_ID: The vectors object.
 * @name: The name of the parasite to detach from a vectors object.
 *
 * Removes a parasite from a vectors object
 *
 * This procedure detaches a parasite from a vectors object. It has no
 * return values.
 *
 * Returns: TRUE on success.
 *
 * Since: GIMP 2.4
 */
gboolean
gimp_vectors_parasite_detach (gint32       vectors_ID,
                              const gchar *name)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-vectors-parasite-detach",
                                    &nreturn_vals,
                                    GIMP_PDB_VECTORS, vectors_ID,
                                    GIMP_PDB_STRING, name,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_vectors_parasite_list:
 * @vectors_ID: The vectors object.
 * @num_parasites: The number of attached parasites.
 * @parasites: The names of currently attached parasites.
 *
 * List all parasites.
 *
 * Returns a list of all currently attached parasites.
 *
 * Returns: TRUE on success.
 *
 * Since: GIMP 2.4
 */
gboolean
gimp_vectors_parasite_list (gint32    vectors_ID,
                            gint     *num_parasites,
                            gchar  ***parasites)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;
  gint i;

  return_vals = gimp_run_procedure ("gimp-vectors-parasite-list",
                                    &nreturn_vals,
                                    GIMP_PDB_VECTORS, vectors_ID,
                                    GIMP_PDB_END);

  *num_parasites = 0;
  *parasites = NULL;

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  if (success)
    {
      *num_parasites = return_vals[1].data.d_int32;
      *parasites = g_new (gchar *, *num_parasites);
      for (i = 0; i < *num_parasites; i++)
        (*parasites)[i] = g_strdup (return_vals[2].data.d_stringarray[i]);
    }

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpgradients_pdb.c
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

#include <string.h>

#include "gimp.h"

/**
 * gimp_gradients_refresh:
 *
 * Refresh current gradients. This function always succeeds.
 *
 * This procedure retrieves all gradients currently in the user's
 * gradient path and updates the gradient dialogs accordingly.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_gradients_refresh (void)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-gradients-refresh",
                                    &nreturn_vals,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_gradients_get_list:
 * @filter: An optional regular expression used to filter the list.
 * @num_gradients: The number of loaded gradients.
 *
 * Retrieve the list of loaded gradients.
 *
 * This procedure returns a list of the gradients that are currently
 * loaded. You can later use the 'gimp-context-set-gradient' function
 * to set the active gradient.
 *
 * Returns: The list of gradient names.
 */
gchar **
gimp_gradients_get_list (const gchar *filter,
                         gint        *num_gradients)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gchar **gradient_list = NULL;
  gint i;

  return_vals = gimp_run_procedure ("gimp-gradients-get-list",
                                    &nreturn_vals,
                                    GIMP_PDB_STRING, filter,
                                    GIMP_PDB_END);

  *num_gradients = 0;

  if (return_vals[0].data.d_status == GIMP_PDB_SUCCESS)
    {
      *num_gradients = return_vals[1].data.d_int32;
      gradient_list = g_new (gchar *, *num_gradients);
      for (i = 0; i < *num_gradients; i++)
        gradient_list[i] = g_strdup (return_vals[2].data.d_stringarray[i]);
    }

  gimp_destroy_params (return_vals, nreturn_vals);

  return gradient_list;
}

/**
 * gimp_gradients_sample_uniform:
 * @num_samples: The number of samples to take.
 * @reverse: Use the reverse gradient.
 *
 * This procedure is deprecated! Use
 * gimp_gradient_get_uniform_samples() instead.
 *
 * Returns: Color samples: { R1, G1, B1, A1, ..., Rn, Gn, Bn, An }.
 */
gdouble *
gimp_gradients_sample_uniform (gint     num_samples,
                               gboolean reverse)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gdouble *color_samples = NULL;
  gint num_color_samples;

  return_vals = gimp_run_procedure ("gimp-gradients-sample-uniform",
                                    &nreturn_vals,
                                    GIMP_PDB_INT32, num_samples,
                                    GIMP_PDB_INT32, reverse,
                                    GIMP_PDB_END);

  if (return_vals[0].data.d_status == GIMP_PDB_SUCCESS)
    {
      num_color_samples = return_vals[1].data.d_int32;
      color_samples = g_new (gdouble, num_color_samples);
      memcpy (color_samples,
              return_vals[2].data.d_floatarray,
              num_color_samples * sizeof (gdouble));
    }

  gimp_destroy_params (return_vals, nreturn_vals);

  return color_samples;
}

/**
 * gimp_gradients_sample_custom:
 * @num_samples: The number of samples to take.
 * @positions: The list of positions to sample along the gradient.
 * @reverse: Use the reverse gradient.
 *
 * This procedure is deprecated! Use gimp_gradient_get_custom_samples()
 * instead.
 *
 * Returns: Color samples: { R1, G1, B1, A1, ..., Rn, Gn, Bn, An }.
 */
gdouble *
gimp_gradients_sample_custom (gint           num_samples,
                              const gdouble *positions,
                              gboolean       reverse)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gdouble *color_samples = NULL;
  gint num_color_samples;

  return_vals = gimp_run_procedure ("gimp-gradients-sample-custom",
                                    &nreturn_vals,
                                    GIMP_PDB_INT32, num_samples,
                                    GIMP_PDB_FLOATARRAY, positions,
                                    GIMP_PDB_INT32, reverse,
                                    GIMP_PDB_END);

  if (return_vals[0].data.d_status == GIMP_PDB_SUCCESS)
    {
      num_color_samples = return_vals[1].data.d_int32;
      color_samples = g_new (gdouble, num_color_samples);
      memcpy (color_samples,
              return_vals[2].data.d_floatarray,
              num_color_samples * sizeof (gdouble));
    }

  gimp_destroy_params (return_vals, nreturn_vals);

  return color_samples;
}

/**
 * gimp_gradients_get_gradient_data:
 * @name: The gradient name (\"\" means current active gradient).
 * @sample_size: Size of the sample to return when the gradient is changed.
 * @reverse: Use the reverse gradient.
 * @width: The gradient sample width (r,g,b,a).
 * @grad_data: The gradient sample data.
 *
 * This procedure is deprecated! Use
 * gimp_gradient_get_uniform_samples() instead.
 *
 * Returns: The gradient name.
 */
gchar *
gimp_gradients_get_gradient_data (const gchar  *name,
                                  gint          sample_size,
                                  gboolean      reverse,
                                  gint         *width,
                                  gdouble     **grad_data)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gchar *actual_name = NULL;

  return_vals = gimp_run_procedure ("gimp-gradients-get-gradient-data",
                                    &nreturn_vals,
                                    GIMP_PDB_STRING, name,
                                    GIMP_PDB_INT32, sample_size,
                                    GIMP_PDB_INT32, reverse,
                                    GIMP_PDB_END);

  *width = 0;

  if (return_vals[0].data.d_status == GIMP_PDB_SUCCESS)
    {
      actual_name = g_strdup (return_vals[1].data.d_string);
      *width = return_vals[2].data.d_int32;
      *grad_data = g_new (gdouble, *width);
      memcpy (*grad_data,
              return_vals[3].data.d_floatarray,
              *width * sizeof (gdouble));
    }

  gimp_destroy_params (return_vals, nreturn_vals);

  return actual_name;
}

/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimppainttools_pdb.c
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
 * gimp_airbrush:
 * @drawable_ID: The affected drawable.
 * @pressure: The pressure of the airbrush strokes.
 * @num_strokes: Number of stroke control points (count each coordinate as 2 points).
 * @strokes: Array of stroke coordinates: { s1.x, s1.y, s2.x, s2.y, ..., sn.x, sn.y }.
 *
 * Paint in the current brush with varying pressure. Paint application
 * is time-dependent.
 *
 * This tool simulates the use of an airbrush. Paint pressure
 * represents the relative intensity of the paint application. High
 * pressure results in a thicker layer of paint while low pressure
 * results in a thinner layer.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_airbrush (gint32         drawable_ID,
	       gdouble        pressure,
	       gint           num_strokes,
	       const gdouble *strokes)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-airbrush",
				    &nreturn_vals,
				    GIMP_PDB_DRAWABLE, drawable_ID,
				    GIMP_PDB_FLOAT, pressure,
				    GIMP_PDB_INT32, num_strokes,
				    GIMP_PDB_FLOATARRAY, strokes,
				    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_airbrush_default:
 * @drawable_ID: The affected drawable.
 * @num_strokes: Number of stroke control points (count each coordinate as 2 points).
 * @strokes: Array of stroke coordinates: { s1.x, s1.y, s2.x, s2.y, ..., sn.x, sn.y }.
 *
 * Paint in the current brush with varying pressure. Paint application
 * is time-dependent.
 *
 * This tool simulates the use of an airbrush. It is similar to
 * gimp_airbrush except that the pressure is derived from the airbrush
 * tools options box. It the option has not been set the default for
 * the option will be used.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_airbrush_default (gint32         drawable_ID,
		       gint           num_strokes,
		       const gdouble *strokes)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-airbrush-default",
				    &nreturn_vals,
				    GIMP_PDB_DRAWABLE, drawable_ID,
				    GIMP_PDB_INT32, num_strokes,
				    GIMP_PDB_FLOATARRAY, strokes,
				    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_clone:
 * @drawable_ID: The affected drawable.
 * @src_drawable_ID: The source drawable.
 * @clone_type: The type of clone.
 * @src_x: The x coordinate in the source image.
 * @src_y: The y coordinate in the source image.
 * @num_strokes: Number of stroke control points (count each coordinate as 2 points).
 * @strokes: Array of stroke coordinates: { s1.x, s1.y, s2.x, s2.y, ..., sn.x, sn.y }.
 *
 * Clone from the source to the dest drawable using the current brush
 *
 * This tool clones (copies) from the source drawable starting at the
 * specified source coordinates to the dest drawable. If the
 * \"clone_type\" argument is set to PATTERN-CLONE, then the current
 * pattern is used as the source and the \"src_drawable\" argument is
 * ignored. Pattern cloning assumes a tileable pattern and mods the sum
 * of the src coordinates and subsequent stroke offsets with the width
 * and height of the pattern. For image cloning, if the sum of the src
 * coordinates and subsequent stroke offsets exceeds the extents of the
 * src drawable, then no paint is transferred. The clone tool is
 * capable of transforming between any image types including
 * RGB-&gt;Indexed--although converting from any type to indexed is
 * significantly slower.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_clone (gint32         drawable_ID,
	    gint32         src_drawable_ID,
	    GimpCloneType  clone_type,
	    gdouble        src_x,
	    gdouble        src_y,
	    gint           num_strokes,
	    const gdouble *strokes)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-clone",
				    &nreturn_vals,
				    GIMP_PDB_DRAWABLE, drawable_ID,
				    GIMP_PDB_DRAWABLE, src_drawable_ID,
				    GIMP_PDB_INT32, clone_type,
				    GIMP_PDB_FLOAT, src_x,
				    GIMP_PDB_FLOAT, src_y,
				    GIMP_PDB_INT32, num_strokes,
				    GIMP_PDB_FLOATARRAY, strokes,
				    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_clone_default:
 * @drawable_ID: The affected drawable.
 * @num_strokes: Number of stroke control points (count each coordinate as 2 points).
 * @strokes: Array of stroke coordinates: { s1.x, s1.y, s2.x, s2.y, ..., sn.x, sn.y }.
 *
 * Clone from the source to the dest drawable using the current brush
 *
 * This tool clones (copies) from the source drawable starting at the
 * specified source coordinates to the dest drawable. This function
 * performs exactly the same as the gimp_clone function except that the
 * tools arguments are obtained from the clones option dialog. It this
 * dialog has not been activated then the dialogs default values will
 * be used.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_clone_default (gint32         drawable_ID,
		    gint           num_strokes,
		    const gdouble *strokes)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-clone-default",
				    &nreturn_vals,
				    GIMP_PDB_DRAWABLE, drawable_ID,
				    GIMP_PDB_INT32, num_strokes,
				    GIMP_PDB_FLOATARRAY, strokes,
				    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_convolve:
 * @drawable_ID: The affected drawable.
 * @pressure: The pressure.
 * @convolve_type: Convolve type.
 * @num_strokes: Number of stroke control points (count each coordinate as 2 points).
 * @strokes: Array of stroke coordinates: { s1.x, s1.y, s2.x, s2.y, ..., sn.x, sn.y }.
 *
 * Convolve (Blur, Sharpen) using the current brush.
 *
 * This tool convolves the specified drawable with either a sharpening
 * or blurring kernel. The pressure parameter controls the magnitude of
 * the operation. Like the paintbrush, this tool linearly interpolates
 * between the specified stroke coordinates.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_convolve (gint32            drawable_ID,
	       gdouble           pressure,
	       GimpConvolveType  convolve_type,
	       gint              num_strokes,
	       const gdouble    *strokes)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-convolve",
				    &nreturn_vals,
				    GIMP_PDB_DRAWABLE, drawable_ID,
				    GIMP_PDB_FLOAT, pressure,
				    GIMP_PDB_INT32, convolve_type,
				    GIMP_PDB_INT32, num_strokes,
				    GIMP_PDB_FLOATARRAY, strokes,
				    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_convolve_default:
 * @drawable_ID: The affected drawable.
 * @num_strokes: Number of stroke control points (count each coordinate as 2 points).
 * @strokes: Array of stroke coordinates: { s1.x, s1.y, s2.x, s2.y, ..., sn.x, sn.y }.
 *
 * Convolve (Blur, Sharpen) using the current brush.
 *
 * This tool convolves the specified drawable with either a sharpening
 * or blurring kernel. This function performs exactly the same as the
 * gimp_convolve function except that the tools arguments are obtained
 * from the convolve option dialog. It this dialog has not been
 * activated then the dialogs default values will be used.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_convolve_default (gint32         drawable_ID,
		       gint           num_strokes,
		       const gdouble *strokes)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-convolve-default",
				    &nreturn_vals,
				    GIMP_PDB_DRAWABLE, drawable_ID,
				    GIMP_PDB_INT32, num_strokes,
				    GIMP_PDB_FLOATARRAY, strokes,
				    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_dodgeburn:
 * @drawable_ID: The affected drawable.
 * @exposure: The exposure of the strokes.
 * @dodgeburn_type: The type either dodge or burn.
 * @dodgeburn_mode: The mode.
 * @num_strokes: Number of stroke control points (count each coordinate as 2 points).
 * @strokes: Array of stroke coordinates: { s1.x, s1.y, s2.x, s2.y, ..., sn.x, sn.y }.
 *
 * Dodgeburn image with varying exposure.
 *
 * Dodgeburn. More details here later.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_dodgeburn (gint32             drawable_ID,
		gdouble            exposure,
		GimpDodgeBurnType  dodgeburn_type,
		GimpTransferMode   dodgeburn_mode,
		gint               num_strokes,
		const gdouble     *strokes)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-dodgeburn",
				    &nreturn_vals,
				    GIMP_PDB_DRAWABLE, drawable_ID,
				    GIMP_PDB_FLOAT, exposure,
				    GIMP_PDB_INT32, dodgeburn_type,
				    GIMP_PDB_INT32, dodgeburn_mode,
				    GIMP_PDB_INT32, num_strokes,
				    GIMP_PDB_FLOATARRAY, strokes,
				    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_dodgeburn_default:
 * @drawable_ID: The affected drawable.
 * @num_strokes: Number of stroke control points (count each coordinate as 2 points).
 * @strokes: Array of stroke coordinates: { s1.x, s1.y, s2.x, s2.y, ..., sn.x, sn.y }.
 *
 * Dodgeburn image with varying exposure. This is the same as the
 * gimp_dodgeburn function except that the exposure, type and mode are
 * taken from the tools option dialog. If the dialog has not been
 * activated then the defaults as used by the dialog will be used.
 *
 * Dodgeburn. More details here later.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_dodgeburn_default (gint32         drawable_ID,
			gint           num_strokes,
			const gdouble *strokes)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-dodgeburn-default",
				    &nreturn_vals,
				    GIMP_PDB_DRAWABLE, drawable_ID,
				    GIMP_PDB_INT32, num_strokes,
				    GIMP_PDB_FLOATARRAY, strokes,
				    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_eraser:
 * @drawable_ID: The affected drawable.
 * @num_strokes: Number of stroke control points (count each coordinate as 2 points).
 * @strokes: Array of stroke coordinates: { s1.x, s1.y, s2.x, s2.y, ..., sn.x, sn.y }.
 * @hardness: %%desc%%.
 * @method: %%desc%%.
 *
 * Erase using the current brush.
 *
 * This tool erases using the current brush mask. If the specified
 * drawable contains an alpha channel, then the erased pixels will
 * become transparent. Otherwise, the eraser tool replaces the contents
 * of the drawable with the background color. Like paintbrush, this
 * tool linearly interpolates between the specified stroke coordinates.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_eraser (gint32                    drawable_ID,
	     gint                      num_strokes,
	     const gdouble            *strokes,
	     GimpBrushApplicationMode  hardness,
	     GimpPaintApplicationMode  method)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-eraser",
				    &nreturn_vals,
				    GIMP_PDB_DRAWABLE, drawable_ID,
				    GIMP_PDB_INT32, num_strokes,
				    GIMP_PDB_FLOATARRAY, strokes,
				    GIMP_PDB_INT32, hardness,
				    GIMP_PDB_INT32, method,
				    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_eraser_default:
 * @drawable_ID: The affected drawable.
 * @num_strokes: Number of stroke control points (count each coordinate as 2 points).
 * @strokes: Array of stroke coordinates: { s1.x, s1.y, s2.x, s2.y, ..., sn.x, sn.y }.
 *
 * Erase using the current brush.
 *
 * This tool erases using the current brush mask. This function
 * performs exactly the same as the gimp_eraser function except that
 * the tools arguments are obtained from the eraser option dialog. It
 * this dialog has not been activated then the dialogs default values
 * will be used.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_eraser_default (gint32         drawable_ID,
		     gint           num_strokes,
		     const gdouble *strokes)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-eraser-default",
				    &nreturn_vals,
				    GIMP_PDB_DRAWABLE, drawable_ID,
				    GIMP_PDB_INT32, num_strokes,
				    GIMP_PDB_FLOATARRAY, strokes,
				    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_paintbrush:
 * @drawable_ID: The affected drawable.
 * @fade_out: Fade out parameter.
 * @num_strokes: Number of stroke control points (count each coordinate as 2 points).
 * @strokes: Array of stroke coordinates: { s1.x, s1.y, s2.x, s2.y, ..., sn.x, sn.y }.
 * @method: %%desc%%.
 * @gradient_length: Length of gradient to draw.
 *
 * Paint in the current brush with optional fade out parameter and pull
 * colors from a gradient.
 *
 * This tool is the standard paintbrush. It draws linearly interpolated
 * lines through the specified stroke coordinates. It operates on the
 * specified drawable in the foreground color with the active brush.
 * The \"fade_out\" parameter is measured in pixels and allows the
 * brush stroke to linearly fall off. The pressure is set to the
 * maximum at the beginning of the stroke. As the distance of the
 * stroke nears the fade_out value, the pressure will approach zero.
 * The gradient_length is the distance to spread the gradient over. It
 * is measured in pixels. If the gradient_length is 0, no gradient is
 * used.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_paintbrush (gint32                    drawable_ID,
		 gdouble                   fade_out,
		 gint                      num_strokes,
		 const gdouble            *strokes,
		 GimpPaintApplicationMode  method,
		 gdouble                   gradient_length)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-paintbrush",
				    &nreturn_vals,
				    GIMP_PDB_DRAWABLE, drawable_ID,
				    GIMP_PDB_FLOAT, fade_out,
				    GIMP_PDB_INT32, num_strokes,
				    GIMP_PDB_FLOATARRAY, strokes,
				    GIMP_PDB_INT32, method,
				    GIMP_PDB_FLOAT, gradient_length,
				    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_paintbrush_default:
 * @drawable_ID: The affected drawable.
 * @num_strokes: Number of stroke control points (count each coordinate as 2 points).
 * @strokes: Array of stroke coordinates: { s1.x, s1.y, s2.x, s2.y, ..., sn.x, sn.y }.
 *
 * Paint in the current brush. The fade out parameter and pull colors
 * from a gradient parameter are set from the paintbrush options
 * dialog. If this dialog has not been activated then the dialog
 * defaults will be used.
 *
 * This tool is similar to the standard paintbrush. It draws linearly
 * interpolated lines through the specified stroke coordinates. It
 * operates on the specified drawable in the foreground color with the
 * active brush. The \"fade_out\" parameter is measured in pixels and
 * allows the brush stroke to linearly fall off (value obtained from
 * the option dialog). The pressure is set to the maximum at the
 * beginning of the stroke. As the distance of the stroke nears the
 * fade_out value, the pressure will approach zero. The gradient_length
 * (value obtained from the option dialog) is the distance to spread
 * the gradient over. It is measured in pixels. If the gradient_length
 * is 0, no gradient is used.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_paintbrush_default (gint32         drawable_ID,
			 gint           num_strokes,
			 const gdouble *strokes)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-paintbrush-default",
				    &nreturn_vals,
				    GIMP_PDB_DRAWABLE, drawable_ID,
				    GIMP_PDB_INT32, num_strokes,
				    GIMP_PDB_FLOATARRAY, strokes,
				    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_pencil:
 * @drawable_ID: The affected drawable.
 * @num_strokes: Number of stroke control points (count each coordinate as 2 points).
 * @strokes: Array of stroke coordinates: { s1.x, s1.y, s2.x, s2.y, ..., sn.x, sn.y }.
 *
 * Paint in the current brush without sub-pixel sampling.
 *
 * This tool is the standard pencil. It draws linearly interpolated
 * lines through the specified stroke coordinates. It operates on the
 * specified drawable in the foreground color with the active brush.
 * The brush mask is treated as though it contains only black and white
 * values. Any value below half is treated as black; any above half, as
 * white.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_pencil (gint32         drawable_ID,
	     gint           num_strokes,
	     const gdouble *strokes)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-pencil",
				    &nreturn_vals,
				    GIMP_PDB_DRAWABLE, drawable_ID,
				    GIMP_PDB_INT32, num_strokes,
				    GIMP_PDB_FLOATARRAY, strokes,
				    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_smudge:
 * @drawable_ID: The affected drawable.
 * @pressure: The pressure of the smudge strokes.
 * @num_strokes: Number of stroke control points (count each coordinate as 2 points).
 * @strokes: Array of stroke coordinates: { s1.x, s1.y, s2.x, s2.y, ..., sn.x, sn.y }.
 *
 * Smudge image with varying pressure.
 *
 * This tool simulates a smudge using the current brush. High pressure
 * results in a greater smudge of paint while low pressure results in a
 * lesser smudge.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_smudge (gint32         drawable_ID,
	     gdouble        pressure,
	     gint           num_strokes,
	     const gdouble *strokes)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-smudge",
				    &nreturn_vals,
				    GIMP_PDB_DRAWABLE, drawable_ID,
				    GIMP_PDB_FLOAT, pressure,
				    GIMP_PDB_INT32, num_strokes,
				    GIMP_PDB_FLOATARRAY, strokes,
				    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_smudge_default:
 * @drawable_ID: The affected drawable.
 * @num_strokes: Number of stroke control points (count each coordinate as 2 points).
 * @strokes: Array of stroke coordinates: { s1.x, s1.y, s2.x, s2.y, ..., sn.x, sn.y }.
 *
 * Smudge image with varying pressure.
 *
 * This tool simulates a smudge using the current brush. It behaves
 * exactly the same as gimp_smudge except that the pressure value is
 * taken from the smudge tool options or the options default if the
 * tools option dialog has not been activated.
 *
 * Returns: TRUE on success.
 */
gboolean
gimp_smudge_default (gint32         drawable_ID,
		     gint           num_strokes,
		     const gdouble *strokes)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-smudge-default",
				    &nreturn_vals,
				    GIMP_PDB_DRAWABLE, drawable_ID,
				    GIMP_PDB_INT32, num_strokes,
				    GIMP_PDB_FLOATARRAY, strokes,
				    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

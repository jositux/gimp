/* The GIMP -- an image manipulation program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
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

#include <string.h>

#include <glib-object.h>

#include "paint-types.h"

#include "base/brush-scale.h"
#include "base/pixel-region.h"
#include "base/temp-buf.h"

#include "core/gimpbrush.h"
#include "core/gimpdrawable.h"
#include "core/gimpimage.h"
#include "core/gimpmarshal.h"

#include "gimpbrushcore.h"
#include "gimpbrushcore-kernels.h"
#include "gimppaintoptions.h"

#include "gimp-intl.h"


#define EPSILON  0.00001


enum
{
  SET_BRUSH,
  LAST_SIGNAL
};


/*  local function prototypes  */

static void     gimp_brush_core_finalize          (GObject          *object);

static gboolean gimp_brush_core_start             (GimpPaintCore    *core,
                                                   GimpDrawable     *drawable,
                                                   GimpPaintOptions *paint_options,
                                                   GimpCoords       *coords,
                                                   GError          **error);
static gboolean gimp_brush_core_pre_paint         (GimpPaintCore    *core,
                                                   GimpDrawable     *drawable,
                                                   GimpPaintOptions *paint_options,
                                                   GimpPaintState    paint_state,
                                                   guint32           time);
static void     gimp_brush_core_post_paint        (GimpPaintCore    *core,
                                                   GimpDrawable     *drawable,
                                                   GimpPaintOptions *paint_options,
                                                   GimpPaintState    paint_state,
                                                   guint32           time);
static void     gimp_brush_core_interpolate       (GimpPaintCore    *core,
                                                   GimpDrawable     *drawable,
                                                   GimpPaintOptions *paint_options,
                                                   guint32           time);

static TempBuf *gimp_brush_core_get_paint_area    (GimpPaintCore    *paint_core,
                                                   GimpDrawable     *drawable,
                                                   GimpPaintOptions *paint_options);

static void     gimp_brush_core_real_set_brush    (GimpBrushCore    *core,
                                                   GimpBrush        *brush);

static void   gimp_brush_core_calc_brush_size     (GimpBrushCore    *core,
                                                   MaskBuf          *mask,
                                                   gdouble           scale,
                                                   gint             *width,
                                                   gint             *height);
static inline void rotate_pointers                (gulong          **p,
                                                   guint32           n);
static MaskBuf * gimp_brush_core_subsample_mask   (GimpBrushCore    *core,
                                                   MaskBuf          *mask,
                                                   gdouble           x,
                                                   gdouble           y);
static MaskBuf * gimp_brush_core_pressurize_mask  (GimpBrushCore    *core,
                                                   MaskBuf          *brush_mask,
                                                   gdouble           x,
                                                   gdouble           y,
                                                   gdouble           pressure);
static MaskBuf * gimp_brush_core_solidify_mask    (GimpBrushCore    *core,
                                                   MaskBuf          *brush_mask,
                                                   gdouble           x,
                                                   gdouble           y);
static MaskBuf * gimp_brush_core_scale_mask       (GimpBrushCore    *core,
                                                   MaskBuf          *brush_mask,
                                                   gdouble           scale);
static MaskBuf * gimp_brush_core_scale_pixmap     (GimpBrushCore    *core,
                                                   MaskBuf          *brush_mask,
                                                   gdouble           scale);

static MaskBuf * gimp_brush_core_get_brush_mask   (GimpBrushCore    *core,
                                                   GimpBrushApplicationMode  brush_hardness,
                                                   gdouble           scale);
static void      gimp_brush_core_invalidate_cache (GimpBrush        *brush,
                                                   GimpBrushCore    *core);


/*  brush pipe utility functions  */
static void      paint_line_pixmap_mask           (GimpImage        *dest,
                                                   GimpDrawable     *drawable,
                                                   TempBuf          *pixmap_mask,
                                                   TempBuf          *brush_mask,
                                                   guchar           *d,
                                                   gint              x,
                                                   gint              y,
                                                   gint              bytes,
                                                   gint              width,
                                                   GimpBrushApplicationMode  mode);


G_DEFINE_TYPE (GimpBrushCore, gimp_brush_core, GIMP_TYPE_PAINT_CORE)

#define parent_class gimp_brush_core_parent_class

static guint core_signals[LAST_SIGNAL] = { 0, };


static void
gimp_brush_core_class_init (GimpBrushCoreClass *klass)
{
  GObjectClass       *object_class     = G_OBJECT_CLASS (klass);
  GimpPaintCoreClass *paint_core_class = GIMP_PAINT_CORE_CLASS (klass);

  core_signals[SET_BRUSH] =
    g_signal_new ("set-brush",
                  G_TYPE_FROM_CLASS (klass),
                  G_SIGNAL_RUN_LAST,
                  G_STRUCT_OFFSET (GimpBrushCoreClass, set_brush),
                  NULL, NULL,
                  gimp_marshal_VOID__OBJECT,
                  G_TYPE_NONE, 1,
                  GIMP_TYPE_BRUSH);

  object_class->finalize  = gimp_brush_core_finalize;

  paint_core_class->start          = gimp_brush_core_start;
  paint_core_class->pre_paint      = gimp_brush_core_pre_paint;
  paint_core_class->post_paint     = gimp_brush_core_post_paint;
  paint_core_class->interpolate    = gimp_brush_core_interpolate;
  paint_core_class->get_paint_area = gimp_brush_core_get_paint_area;

  klass->handles_changing_brush    = FALSE;
  klass->use_scale                 = TRUE;
  klass->set_brush                 = gimp_brush_core_real_set_brush;
}

static void
gimp_brush_core_init (GimpBrushCore *core)
{
  gint i, j;

  core->main_brush               = NULL;
  core->brush                    = NULL;
  core->spacing                  = 1.0;
  core->scale                    = 1.0;

  core->pressure_brush           = NULL;

  for (i = 0; i < BRUSH_CORE_SOLID_SUBSAMPLE; i++)
    for (j = 0; j < BRUSH_CORE_SOLID_SUBSAMPLE; j++)
      core->solid_brushes[i][j] = NULL;

  core->last_solid_brush         = NULL;
  core->solid_cache_invalid      = FALSE;

  core->scale_brush              = NULL;
  core->last_scale_brush         = NULL;
  core->last_scale_width         = 0;
  core->last_scale_height        = 0;

  core->scale_pixmap             = NULL;
  core->last_scale_pixmap        = NULL;
  core->last_scale_pixmap_width  = 0;
  core->last_scale_pixmap_height = 0;

  g_assert (BRUSH_CORE_SUBSAMPLE == KERNEL_SUBSAMPLE);

  for (i = 0; i < KERNEL_SUBSAMPLE + 1; i++)
    for (j = 0; j < KERNEL_SUBSAMPLE + 1; j++)
      core->kernel_brushes[i][j] = NULL;

  core->last_brush_mask          = NULL;
  core->cache_invalid            = FALSE;

  core->brush_bound_segs         = NULL;
  core->n_brush_bound_segs       = 0;
  core->brush_bound_width        = 0;
  core->brush_bound_height       = 0;
}

static void
gimp_brush_core_finalize (GObject *object)
{
  GimpBrushCore *core = GIMP_BRUSH_CORE (object);
  gint           i, j;

  if (core->pressure_brush)
    {
      temp_buf_free (core->pressure_brush);
      core->pressure_brush = NULL;
    }

  for (i = 0; i < BRUSH_CORE_SOLID_SUBSAMPLE; i++)
    for (j = 0; j < BRUSH_CORE_SOLID_SUBSAMPLE; j++)
      if (core->solid_brushes[i][j])
        {
          temp_buf_free (core->solid_brushes[i][j]);
          core->solid_brushes[i][j] = NULL;
        }

  if (core->scale_brush)
    {
      temp_buf_free (core->scale_brush);
      core->scale_brush = NULL;
    }

  if (core->scale_pixmap)
    {
      temp_buf_free (core->scale_pixmap);
      core->scale_pixmap = NULL;
    }

  for (i = 0; i < KERNEL_SUBSAMPLE + 1; i++)
    for (j = 0; j < KERNEL_SUBSAMPLE + 1; j++)
      if (core->kernel_brushes[i][j])
        {
          temp_buf_free (core->kernel_brushes[i][j]);
          core->kernel_brushes[i][j] = NULL;
        }

  if (core->main_brush)
    {
      g_signal_handlers_disconnect_by_func (core->main_brush,
                                            gimp_brush_core_invalidate_cache,
                                            core);
      g_object_unref (core->main_brush);
      core->main_brush = NULL;
    }

  if (core->brush_bound_segs)
    {
      g_free (core->brush_bound_segs);
      core->brush_bound_segs   = NULL;
      core->n_brush_bound_segs = 0;
      core->brush_bound_width  = 0;
      core->brush_bound_height = 0;
    }

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static gboolean
gimp_brush_core_pre_paint (GimpPaintCore    *paint_core,
                           GimpDrawable     *drawable,
                           GimpPaintOptions *paint_options,
                           GimpPaintState    paint_state,
                           guint32           time)
{
  GimpBrushCore *core = GIMP_BRUSH_CORE (paint_core);

  if (paint_state == GIMP_PAINT_STATE_MOTION)
    {
      /* If we current point == last point, check if the brush
       * wants to be painted in that case. (Direction dependent
       * pixmap brush pipes don't, as they don't know which
       * pixmap to select.)
       */
      if (paint_core->last_coords.x == paint_core->cur_coords.x &&
          paint_core->last_coords.y == paint_core->cur_coords.y &&
          ! gimp_brush_want_null_motion (core->main_brush,
                                         &paint_core->last_coords,
                                         &paint_core->cur_coords))
        {
          return FALSE;
        }

      if (GIMP_BRUSH_CORE_GET_CLASS (paint_core)->handles_changing_brush)
        {
          core->brush = gimp_brush_select_brush (core->main_brush,
                                                 &paint_core->last_coords,
                                                 &paint_core->cur_coords);
        }
    }

  return TRUE;
}

static void
gimp_brush_core_post_paint (GimpPaintCore    *paint_core,
                            GimpDrawable     *drawable,
                            GimpPaintOptions *paint_options,
                            GimpPaintState    paint_state,
                            guint32           time)
{
  GimpBrushCore *core = GIMP_BRUSH_CORE (paint_core);

  if (paint_state == GIMP_PAINT_STATE_MOTION)
    {
      core->brush = core->main_brush;
    }
}

static gboolean
gimp_brush_core_start (GimpPaintCore     *paint_core,
                       GimpDrawable      *drawable,
                       GimpPaintOptions  *paint_options,
                       GimpCoords        *coords,
                       GError           **error)
{
  GimpBrushCore *core = GIMP_BRUSH_CORE (paint_core);
  GimpBrush     *brush;

  brush = gimp_context_get_brush (GIMP_CONTEXT (paint_options));

  if (core->main_brush != brush)
    gimp_brush_core_set_brush (core, brush);

  if (! core->main_brush)
    {
      g_set_error (error, 0, 0,
                   _("No brushes available for use with this tool."));
      return FALSE;
    }

  core->spacing = (gdouble) gimp_brush_get_spacing (core->main_brush) / 100.0;

  core->brush = core->main_brush;

  core->jitter =
    gimp_paint_options_get_jitter (paint_options,
                                   gimp_item_get_image (GIMP_ITEM (drawable)));

  return TRUE;
}

/**
 * gimp_avoid_exact_integer
 * @x: points to a gdouble
 *
 * Adjusts *x such that it is not too close to an integer. This is used
 * for decision algorithms that would be vulnerable to rounding glitches
 * if exact integers were input.
 *
 * Side effects: Changes the value of *x
 **/
static void
gimp_avoid_exact_integer (gdouble *x)
{
  gdouble integral   = floor (*x);
  gdouble fractional = *x - integral;

  if (fractional < EPSILON)
    *x = integral + EPSILON;
  else if (fractional > (1-EPSILON))
    *x = integral + (1-EPSILON);
}

static void
gimp_brush_core_interpolate (GimpPaintCore    *paint_core,
                             GimpDrawable     *drawable,
                             GimpPaintOptions *paint_options,
                             guint32           time)
{
  GimpBrushCore *core = GIMP_BRUSH_CORE (paint_core);
  GimpVector2    delta_vec;
  gdouble        delta_pressure;
  gdouble        delta_xtilt, delta_ytilt;
  gdouble        delta_wheel;
  gint           n, num_points;
  gdouble        t0, dt, tn;
  gdouble        st_factor, st_offset;
  gdouble        initial;
  gdouble        dist;
  gdouble        total;
  gdouble        pixel_dist;
  gdouble        pixel_initial;
  gdouble        xd, yd;
  gdouble        mag;

  gimp_avoid_exact_integer (&paint_core->last_coords.x);
  gimp_avoid_exact_integer (&paint_core->last_coords.y);
  gimp_avoid_exact_integer (&paint_core->cur_coords.x);
  gimp_avoid_exact_integer (&paint_core->cur_coords.y);

  delta_vec.x    = paint_core->cur_coords.x        - paint_core->last_coords.x;
  delta_vec.y    = paint_core->cur_coords.y        - paint_core->last_coords.y;
  delta_pressure = paint_core->cur_coords.pressure - paint_core->last_coords.pressure;
  delta_xtilt    = paint_core->cur_coords.xtilt    - paint_core->last_coords.xtilt;
  delta_ytilt    = paint_core->cur_coords.ytilt    - paint_core->last_coords.ytilt;
  delta_wheel    = paint_core->cur_coords.wheel    - paint_core->last_coords.wheel;

  /*  return if there has been no motion  */
  if (! delta_vec.x    &&
      ! delta_vec.y    &&
      ! delta_pressure &&
      ! delta_xtilt    &&
      ! delta_ytilt    &&
      ! delta_wheel)
    return;

  /* calculate the distance traveled in the coordinate space of the brush */
  mag = gimp_vector2_length (&(core->brush->x_axis));
  xd  = gimp_vector2_inner_product (&delta_vec,
                                    &(core->brush->x_axis)) / (mag * mag);

  mag = gimp_vector2_length (&(core->brush->y_axis));
  yd  = gimp_vector2_inner_product (&delta_vec,
                                    &(core->brush->y_axis)) / (mag * mag);

  dist    = 0.5 * sqrt (xd * xd + yd * yd);
  total   = dist + paint_core->distance;
  initial = paint_core->distance;

  pixel_dist    = gimp_vector2_length (&delta_vec);
  pixel_initial = paint_core->pixel_dist;

  /*  FIXME: need to adapt the spacing to the size                       */
  /*   lastscale = MIN (gimp_paint_tool->lastpressure, 1/256);           */
  /*   curscale = MIN (gimp_paint_tool->curpressure,  1/256);            */
  /*   spacing =                                                         */
  /*     gimp_paint_tool->spacing * sqrt (0.5 * (lastscale + curscale)); */

  /*  Compute spacing parameters such that a brush position will be
   *  made each time the line crosses the *center* of a pixel row or
   *  column, according to whether the line is mostly horizontal or
   *  mostly vertical. The term "stripe" will mean "column" if the
   *  line is horizontalish; "row" if the line is verticalish.
   *
   *  We start by deriving coefficients for a new parameter 's':
   *      s = t * st_factor + st_offset
   *  such that the "nice" brush positions are the ones with *integer*
   *  s values. (Actually the value of s will be 1/2 less than the nice
   *  brush position's x or y coordinate - note that st_factor may
   *  be negative!)
   */

  if (delta_vec.x * delta_vec.x > delta_vec.y * delta_vec.y)
    {
      st_factor = delta_vec.x;
      st_offset = paint_core->last_coords.x - 0.5;
    }
  else
    {
      st_factor = delta_vec.y;
      st_offset = paint_core->last_coords.y - 0.5;
    }

  if (fabs (st_factor) > dist / core->spacing)
    {
      /*  The stripe principle leads to brush positions that are spaced
       *  *closer* than the official brush spacing. Use the official
       *  spacing instead. This is the common case when the brush spacing
       *  is large.
       *  The net effect is then to put a lower bound on the spacing, but
       *  one that varies with the slope of the line. This is suppose to
       *  make thin lines (say, with a 1x1 brush) prettier while leaving
       *  lines with larger brush spacing as they used to look in 1.2.x.
       */

      dt = core->spacing / dist;
      n = (gint) (initial / core->spacing + 1.0 + EPSILON);
      t0 = (n * core->spacing - initial) / dist;
      num_points = 1 + (gint) floor ((1 + EPSILON - t0) / dt);

      /* if we arnt going to paint anything this time and the brush
       * has only moved on one axis return without updating the brush
       * position, distance etc. so that we can more accurately space
       * brush strokes when curves are supplied to us in single pixel
       * chunks.
       */

      if (num_points == 0 && (delta_vec.x == 0 || delta_vec.y == 0))
        return;
    }
  else if (fabs (st_factor) < EPSILON)
    {
      /* Hm, we've hardly moved at all. Don't draw anything, but reset the
       * old coordinates and hope we've gone longer the next time.
       */
      paint_core->cur_coords.x = paint_core->last_coords.x;
      paint_core->cur_coords.y = paint_core->last_coords.y;
      /* ... but go along with the current pressure, tilt and wheel */
      return;
    }
  else
    {
      gint direction = st_factor > 0 ? 1 : -1;
      gint x, y;
      gint s0, sn;

      /*  Choose the first and last stripe to paint.
       *    FIRST PRIORITY is to avoid gaps painting with a 1x1 aliasing
       *  brush when a horizontalish line segment follows a verticalish
       *  one or vice versa - no matter what the angle between the two
       *  lines is. This will also limit the local thinning that a 1x1
       *  subsampled brush may suffer in the same situation.
       *    SECOND PRIORITY is to avoid making free-hand drawings
       *  unpleasantly fat by plotting redundant points.
       *    These are achieved by the following rules, but it is a little
       *  tricky to see just why. Do not change this algorithm unless you
       *  are sure you know what you're doing!
       */

      /*  Basic case: round the beginning and ending point to nearest
       *  stripe center.
       */
      s0 = (gint) floor (st_offset + 0.5);
      sn = (gint) floor (st_offset + st_factor + 0.5);

      t0 = (s0 - st_offset) / st_factor;
      tn = (sn - st_offset) / st_factor;

      x = (gint) floor (paint_core->last_coords.x + t0 * delta_vec.x);
      y = (gint) floor (paint_core->last_coords.y + t0 * delta_vec.y);
      if (t0 < 0.0 && !( x == (gint) floor (paint_core->last_coords.x) &&
                         y == (gint) floor (paint_core->last_coords.y) ))
        {
          /*  Exception A: If the first stripe's brush position is
           *  EXTRApolated into a different pixel square than the
           *  ideal starting point, dont't plot it.
           */
          s0 += direction;
        }
      else if (x == (gint) floor (paint_core->last_paint.x) &&
               y == (gint) floor (paint_core->last_paint.y))
        {
          /*  Exception B: If first stripe's brush position is within the
           *  same pixel square as the last plot of the previous line,
           *  don't plot it either.
           */
          s0 += direction;
        }

      x = (gint) floor (paint_core->last_coords.x + tn * delta_vec.x);
      y = (gint) floor (paint_core->last_coords.y + tn * delta_vec.y);
      if (tn > 1.0 && !( x == (gint) floor (paint_core->cur_coords.x) &&
                         y == (gint) floor (paint_core->cur_coords.y)))
        {
          /*  Exception C: If the last stripe's brush position is
           *  EXTRApolated into a different pixel square than the
           *  ideal ending point, don't plot it.
           */
          sn -= direction;
        }

      t0 = (s0 - st_offset) / st_factor;
      tn = (sn - st_offset) / st_factor;
      dt         =     direction * 1.0 / st_factor;
      num_points = 1 + direction * (sn - s0);

      if (num_points >= 1)
        {
          /*  Hack the reported total distance such that it looks to the
           *  next line as if the the last pixel plotted were at an integer
           *  multiple of the brush spacing. This helps prevent artifacts
           *  for connected lines when the brush spacing is such that some
           *  slopes will use the stripe regime and other slopes will use
           *  the nominal brush spacing.
           */

          if (tn < 1)
            total = initial + tn * dist;

          total = core->spacing * (gint) (total / core->spacing + 0.5);
          total += (1.0 - tn) * dist;
        }
    }

  for (n = 0; n < num_points; n++)
    {
      gdouble t = t0 + n * dt;
      gdouble p = (gdouble) n / num_points;

      paint_core->cur_coords.x        = (paint_core->last_coords.x +
                                         t * delta_vec.x);
      paint_core->cur_coords.y        = (paint_core->last_coords.y +
                                         t * delta_vec.y);
      paint_core->cur_coords.pressure = (paint_core->last_coords.pressure +
                                         p * delta_pressure);
      paint_core->cur_coords.xtilt    = (paint_core->last_coords.xtilt +
                                         p * delta_xtilt);
      paint_core->cur_coords.ytilt    = (paint_core->last_coords.ytilt +
                                         p * delta_ytilt);
      paint_core->cur_coords.wheel    = (paint_core->last_coords.wheel +
                                         p * delta_wheel);

      if (core->jitter > 0.0)
        {
          gdouble jitter_x;
          gdouble jitter_y;

          jitter_x = g_random_double_range (-core->jitter, core->jitter);
          jitter_y = g_random_double_range (-core->jitter, core->jitter);

          paint_core->cur_coords.x += jitter_x * core->brush->x_axis.x;
          paint_core->cur_coords.y += jitter_y * core->brush->y_axis.y;
        }

      paint_core->distance   = initial       + t * dist;
      paint_core->pixel_dist = pixel_initial + t * pixel_dist;

      gimp_paint_core_paint (paint_core, drawable, paint_options,
                             GIMP_PAINT_STATE_MOTION, time);
    }

  paint_core->cur_coords.x        = paint_core->last_coords.x        + delta_vec.x;
  paint_core->cur_coords.y        = paint_core->last_coords.y        + delta_vec.y;
  paint_core->cur_coords.pressure = paint_core->last_coords.pressure + delta_pressure;
  paint_core->cur_coords.xtilt    = paint_core->last_coords.xtilt    + delta_xtilt;
  paint_core->cur_coords.ytilt    = paint_core->last_coords.ytilt    + delta_ytilt;
  paint_core->cur_coords.wheel    = paint_core->last_coords.wheel    + delta_wheel;

  paint_core->distance   = total;
  paint_core->pixel_dist = pixel_initial + pixel_dist;

  paint_core->last_coords = paint_core->cur_coords;
}

static TempBuf *
gimp_brush_core_get_paint_area (GimpPaintCore    *paint_core,
                                GimpDrawable     *drawable,
                                GimpPaintOptions *paint_options)
{
  GimpBrushCore *core = GIMP_BRUSH_CORE (paint_core);
  gint           x, y;
  gint           x1, y1, x2, y2;
  gint           bytes;
  gint           drawable_width, drawable_height;
  gint           brush_width, brush_height;

  bytes = gimp_drawable_bytes_with_alpha (drawable);

  if (GIMP_BRUSH_CORE_GET_CLASS (core)->use_scale)
    {
      GimpPressureOptions *pressure_options = paint_options->pressure_options;

      if (pressure_options->inverse_size)
        core->scale = 1.0 - 0.9 * paint_core->cur_coords.pressure;
      else if (pressure_options->size)
        core->scale = paint_core->cur_coords.pressure;
      else
        core->scale = 1.0;
    }

  gimp_brush_core_calc_brush_size (core, core->brush->mask, core->scale,
                                   &brush_width, &brush_height);

  /*  adjust the x and y coordinates to the upper left corner of the brush  */
  x = (gint) floor (paint_core->cur_coords.x) - (brush_width  >> 1);
  y = (gint) floor (paint_core->cur_coords.y) - (brush_height >> 1);

  drawable_width  = gimp_item_width  (GIMP_ITEM (drawable));
  drawable_height = gimp_item_height (GIMP_ITEM (drawable));

  x1 = CLAMP (x - 1, 0, drawable_width);
  y1 = CLAMP (y - 1, 0, drawable_height);
  x2 = CLAMP (x + brush_width  + 1, 0, drawable_width);
  y2 = CLAMP (y + brush_height + 1, 0, drawable_height);

  /*  configure the canvas buffer  */
  if ((x2 - x1) && (y2 - y1))
    paint_core->canvas_buf = temp_buf_resize (paint_core->canvas_buf, bytes,
                                              x1, y1,
                                              (x2 - x1), (y2 - y1));
  else
    return NULL;

  return paint_core->canvas_buf;
}

static void
gimp_brush_core_real_set_brush (GimpBrushCore *core,
                                GimpBrush     *brush)
{
  if (core->main_brush)
    {
      g_signal_handlers_disconnect_by_func (core->main_brush,
                                            gimp_brush_core_invalidate_cache,
                                            core);
      g_object_unref (core->main_brush);
      core->main_brush = NULL;
    }

  if (core->brush_bound_segs)
    {
      g_free (core->brush_bound_segs);
      core->brush_bound_segs   = NULL;
      core->n_brush_bound_segs = 0;
      core->brush_bound_width  = 0;
      core->brush_bound_height = 0;
    }

  core->main_brush = brush;

  if (core->main_brush)
    {
      g_object_ref (core->main_brush);
      g_signal_connect (core->main_brush, "invalidate-preview",
                        G_CALLBACK (gimp_brush_core_invalidate_cache),
                        core);
    }
}

void
gimp_brush_core_set_brush (GimpBrushCore *core,
                           GimpBrush     *brush)
{
  g_return_if_fail (GIMP_IS_BRUSH_CORE (core));
  g_return_if_fail (brush == NULL || GIMP_IS_BRUSH (brush));

  g_signal_emit (core, core_signals[SET_BRUSH], 0, brush);
}

void
gimp_brush_core_paste_canvas (GimpBrushCore            *core,
                              GimpDrawable             *drawable,
                              gdouble                   brush_opacity,
                              gdouble                   image_opacity,
                              GimpLayerModeEffects      paint_mode,
                              GimpBrushApplicationMode  brush_hardness,
                              GimpPaintApplicationMode  mode)
{
  MaskBuf *brush_mask = gimp_brush_core_get_brush_mask (core,
                                                        brush_hardness,
                                                        core->scale);

  if (brush_mask)
    {
      GimpPaintCore *paint_core = GIMP_PAINT_CORE (core);
      PixelRegion    brush_maskPR;
      gint           x;
      gint           y;
      gint           off_x;
      gint           off_y;

      x = (gint) floor (paint_core->cur_coords.x) - (brush_mask->width  >> 1);
      y = (gint) floor (paint_core->cur_coords.y) - (brush_mask->height >> 1);

      off_x = (x < 0) ? -x : 0;
      off_y = (y < 0) ? -y : 0;

      pixel_region_init_temp_buf (&brush_maskPR, brush_mask,
                                  off_x, off_y,
                                  paint_core->canvas_buf->width,
                                  paint_core->canvas_buf->height);

      gimp_paint_core_paste (paint_core, &brush_maskPR, drawable,
                             brush_opacity,
                             image_opacity, paint_mode,
                             mode);
    }
}

/* Similar to gimp_brush_core_paste_canvas, but replaces the alpha channel
 * rather than using it to composite (i.e. transparent over opaque
 * becomes transparent rather than opauqe.
 */
void
gimp_brush_core_replace_canvas (GimpBrushCore            *core,
                                GimpDrawable             *drawable,
                                gdouble                   brush_opacity,
                                gdouble                   image_opacity,
                                GimpBrushApplicationMode  brush_hardness,
                                GimpPaintApplicationMode  mode)
{
  MaskBuf *brush_mask = gimp_brush_core_get_brush_mask (core,
                                                        brush_hardness,
                                                        core->scale);

  if (brush_mask)
    {
      GimpPaintCore *paint_core = GIMP_PAINT_CORE (core);
      PixelRegion    brush_maskPR;
      gint           x;
      gint           y;
      gint           off_x;
      gint           off_y;

      x = (gint) floor (paint_core->cur_coords.x) - (brush_mask->width  >> 1);
      y = (gint) floor (paint_core->cur_coords.y) - (brush_mask->height >> 1);

      off_x = (x < 0) ? -x : 0;
      off_y = (y < 0) ? -y : 0;

      pixel_region_init_temp_buf (&brush_maskPR, brush_mask,
                                  off_x, off_y,
                                  paint_core->canvas_buf->width,
                                  paint_core->canvas_buf->height);

      gimp_paint_core_replace (paint_core, &brush_maskPR, drawable,
                               brush_opacity,
                               image_opacity,
                               mode);
    }
}


static void
gimp_brush_core_invalidate_cache (GimpBrush     *brush,
                                  GimpBrushCore *core)
{
  /* Make sure we don't cache data for a brush that has changed */

  core->cache_invalid       = TRUE;
  core->solid_cache_invalid = TRUE;

  /* Set the same brush again so the "set-brush" signal is emitted */

  gimp_brush_core_set_brush (core, brush);
}

/************************************************************
 *             LOCAL FUNCTION DEFINITIONS                   *
 ************************************************************/

static void
gimp_brush_core_calc_brush_size (GimpBrushCore *core,
                                 MaskBuf       *mask,
                                 gdouble        scale,
                                 gint          *width,
                                 gint          *height)
{
  scale = CLAMP (scale, 0.0, 1.0);

  if (! GIMP_PAINT_CORE (core)->use_pressure)
    {
      *width  = mask->width;
      *height = mask->height;
    }
  else
    {
      gdouble ratio;

      if (scale < 1 / 256)
        ratio = 1 / 16;
      else
        ratio = sqrt (scale);

      *width  = MAX ((gint) (mask->width  * ratio + 0.5), 1);
      *height = MAX ((gint) (mask->height * ratio + 0.5), 1);
    }
}

static inline void
rotate_pointers (gulong  **p,
                 guint32   n)
{
  guint32  i;
  gulong  *tmp;

  tmp = p[0];
  for (i = 0; i < n-1; i++)
    {
      p[i] = p[i+1];
    }
  p[i] = tmp;
}

static MaskBuf *
gimp_brush_core_subsample_mask (GimpBrushCore *core,
                                MaskBuf       *mask,
                                gdouble        x,
                                gdouble        y)
{
  MaskBuf    *dest;
  gdouble     left;
  guchar     *m;
  guchar     *d;
  const gint *k;
  gint        index1;
  gint        index2;
  gint        dest_offset_x = 0;
  gint        dest_offset_y = 0;
  const gint *kernel;
  gint        i, j;
  gint        r, s;
  gulong     *accum[KERNEL_HEIGHT];
  gint        offs;

  while (x < 0)
    x += mask->width;

  left = x - floor (x);
  index1 = (gint) (left * (gdouble) (KERNEL_SUBSAMPLE + 1));

  while (y < 0)
    y += mask->height;

  left = y - floor (y);
  index2 = (gint) (left * (gdouble) (KERNEL_SUBSAMPLE + 1));


  if ((mask->width % 2) == 0)
    {
      index1 += KERNEL_SUBSAMPLE >> 1;

      if (index1 > KERNEL_SUBSAMPLE)
        {
          index1 -= KERNEL_SUBSAMPLE + 1;
          dest_offset_x = 1;
        }
    }

  if ((mask->height % 2) == 0)
    {
      index2 += KERNEL_SUBSAMPLE >> 1;

      if (index2 > KERNEL_SUBSAMPLE)
        {
          index2 -= KERNEL_SUBSAMPLE + 1;
          dest_offset_y = 1;
        }
    }


  kernel = subsample[index2][index1];

  if (mask == core->last_brush_mask && ! core->cache_invalid)
    {
      if (core->kernel_brushes[index2][index1])
        return core->kernel_brushes[index2][index1];
    }
  else
    {
      for (i = 0; i < KERNEL_SUBSAMPLE + 1; i++)
        for (j = 0; j < KERNEL_SUBSAMPLE + 1; j++)
          if (core->kernel_brushes[i][j])
            {
              mask_buf_free (core->kernel_brushes[i][j]);
              core->kernel_brushes[i][j] = NULL;
            }

      core->last_brush_mask = mask;
      core->cache_invalid   = FALSE;
    }

  dest = mask_buf_new (mask->width  + 2,
                       mask->height + 2);

  /* Allocate and initialize the accum buffer */
  for (i = 0; i < KERNEL_HEIGHT ; i++)
    accum[i] = g_new0 (gulong, dest->width + 1);

  core->kernel_brushes[index2][index1] = dest;

  m = mask_buf_data (mask);
  for (i = 0; i < mask->height; i++)
    {
      for (j = 0; j < mask->width; j++)
        {
          k = kernel;
          for (r = 0; r < KERNEL_HEIGHT; r++)
            {
              offs = j + dest_offset_x;
              s = KERNEL_WIDTH;
              while (s--)
                accum[r][offs++] += *m * *k++;
            }
          m++;
        }

      /* store the accum buffer into the destination mask */
      d = mask_buf_data (dest) + (i + dest_offset_y) * dest->width;
      for (j = 0; j < dest->width; j++)
        *d++ = (accum[0][j] + 127) / KERNEL_SUM;

      rotate_pointers (accum, KERNEL_HEIGHT);

      memset (accum[KERNEL_HEIGHT - 1], 0, sizeof (gulong) * dest->width);
    }

  /* store the rest of the accum buffer into the dest mask */
  while (i + dest_offset_y < dest->height)
    {
      d = mask_buf_data (dest) + (i + dest_offset_y) * dest->width;
      for (j = 0; j < dest->width; j++)
        *d++ = (accum[0][j] + (KERNEL_SUM / 2)) / KERNEL_SUM;

      rotate_pointers (accum, KERNEL_HEIGHT);
      i++;
    }

  for (i = 0; i < KERNEL_HEIGHT ; i++)
    g_free (accum[i]);

  return dest;
}

/* #define FANCY_PRESSURE */

static MaskBuf *
gimp_brush_core_pressurize_mask (GimpBrushCore *core,
                                 MaskBuf       *brush_mask,
                                 gdouble        x,
                                 gdouble        y,
                                 gdouble        pressure)
{
  static guchar  mapi[256];
  guchar        *source;
  guchar        *dest;
  MaskBuf       *subsample_mask;
  gint           i;

  /* Get the raw subsampled mask */
  subsample_mask = gimp_brush_core_subsample_mask (core,
                                                   brush_mask,
                                                   x, y);

  /* Special case pressure = 0.5 */
  if ((gint) (pressure * 100 + 0.5) == 50)
    return subsample_mask;

  if (core->pressure_brush)
    mask_buf_free (core->pressure_brush);

  core->pressure_brush = mask_buf_new (brush_mask->width  + 2,
                                       brush_mask->height + 2);

#ifdef FANCY_PRESSURE
  /* Create the pressure profile
   *
   * It is: I'(I) = tanh (20 * (pressure - 0.5) * I)           : pressure > 0.5
   *        I'(I) = 1 - tanh (20 * (0.5 - pressure) * (1 - I)) : pressure < 0.5
   *
   * It looks like:
   *
   *    low pressure      medium pressure     high pressure
   *
   *         |                   /                 --
   *         |                    /                 /
   *        /                    /                 |
   *      --                  /                         |
   */
  {
    static gdouble  map[256];
    gdouble         ds, s, c;

    ds = (pressure - 0.5) * (20.0 / 256.0);
    s  = 0;
    c  = 1.0;

    if (ds > 0)
      {
        for (i = 0; i < 256; i++)
          {
            map[i] = s / c;
            s += c * ds;
            c += s * ds;
          }

        for (i = 0; i < 256; i++)
          mapi[i] = (gint) (255 * map[i] / map[255]);
      }
    else
      {
        ds = -ds;

        for (i = 255; i >= 0; i--)
          {
            map[i] = s / c;
            s += c * ds;
            c += s * ds;
        }

        for (i = 0; i < 256; i++)
          mapi[i] = (gint) (255 * (1 - map[i] / map[0]));
      }
#else /* ! FANCY_PRESSURE */

  {
    gdouble j, k;

    j = pressure + pressure;
    k = 0;

    for (i = 0; i < 256; i++)
      {
        if (k > 255)
          mapi[i] = 255;
        else
          mapi[i] = (guchar) k;

        k += j;
      }
  }

#endif /* FANCY_PRESSURE */

  /* Now convert the brush */

  source = mask_buf_data (subsample_mask);
  dest   = mask_buf_data (core->pressure_brush);

  i = subsample_mask->width * subsample_mask->height;
  while (i--)
    *dest++ = mapi[(*source++)];

  return core->pressure_brush;
}

static MaskBuf *
gimp_brush_core_solidify_mask (GimpBrushCore *core,
                               MaskBuf       *brush_mask,
                               gdouble        x,
                               gdouble        y)
{
  MaskBuf *dest;
  guchar  *m;
  guchar  *d;
  gint     dest_offset_x = 0;
  gint     dest_offset_y = 0;
  gint     i, j;

  if ((brush_mask->width % 2) == 0)
    {
      while (x < 0)
        x += brush_mask->width;

      if ((x - floor (x)) >= 0.5)
        dest_offset_x++;
    }

  if ((brush_mask->height % 2) == 0)
    {
      while (y < 0)
        y += brush_mask->height;

      if ((y - floor (y)) >= 0.5)
        dest_offset_y++;
    }

  if (! core->solid_cache_invalid &&
      brush_mask == core->last_solid_brush)
    {
      if (core->solid_brushes[dest_offset_y][dest_offset_x])
        return core->solid_brushes[dest_offset_y][dest_offset_x];
    }
  else
    {
      for (i = 0; i < BRUSH_CORE_SOLID_SUBSAMPLE; i++)
        for (j = 0; j < BRUSH_CORE_SOLID_SUBSAMPLE; j++)
          if (core->solid_brushes[i][j])
            {
              mask_buf_free (core->solid_brushes[i][j]);
              core->solid_brushes[i][j] = NULL;
            }

      core->last_solid_brush    = brush_mask;
      core->solid_cache_invalid = FALSE;
    }

  dest = mask_buf_new (brush_mask->width  + 2,
                       brush_mask->height + 2);

  core->solid_brushes[dest_offset_y][dest_offset_x] = dest;

  m = mask_buf_data (brush_mask);
  d = (mask_buf_data (dest) +
       (dest_offset_y + 1) * dest->width +
       (dest_offset_x + 1));

  for (i = 0; i < brush_mask->height; i++)
    {
      for (j = 0; j < brush_mask->width; j++)
        *d++ = (*m++) ? OPAQUE_OPACITY : TRANSPARENT_OPACITY;

      d += 2;
    }

  return dest;
}

static MaskBuf *
gimp_brush_core_scale_mask (GimpBrushCore *core,
                            MaskBuf       *brush_mask,
                            gdouble        scale)
{
  gint dest_width;
  gint dest_height;

  scale = CLAMP (scale, 0.0, 1.0);

  if (scale == 0.0)
    return NULL;

  if (scale == 1.0)
    return brush_mask;

  gimp_brush_core_calc_brush_size (core, brush_mask, scale,
                                   &dest_width, &dest_height);

  if (! core->cache_invalid                 &&
      brush_mask == core->last_scale_brush  &&
      core->scale_brush                     &&
      dest_width  == core->last_scale_width &&
      dest_height == core->last_scale_height)
    {
      return core->scale_brush;
    }

  core->last_scale_brush  = brush_mask;
  core->last_scale_width  = dest_width;
  core->last_scale_height = dest_height;

  if (core->scale_brush)
    mask_buf_free (core->scale_brush);

  core->scale_brush = brush_scale_mask (brush_mask,
                                        dest_width, dest_height);

  core->cache_invalid       = TRUE;
  core->solid_cache_invalid = TRUE;

  return core->scale_brush;
}

static MaskBuf *
gimp_brush_core_scale_pixmap (GimpBrushCore *core,
                              MaskBuf       *brush_mask,
                              gdouble        scale)
{
  gint dest_width;
  gint dest_height;

  scale = CLAMP (scale, 0.0, 1.0);

  if (scale == 0.0)
    return NULL;

  if (scale == 1.0)
    return brush_mask;

  gimp_brush_core_calc_brush_size (core, brush_mask, scale,
                                   &dest_width, &dest_height);

  if (! core->cache_invalid                        &&
      brush_mask == core->last_scale_pixmap        &&
      core->scale_pixmap                           &&
      dest_width  == core->last_scale_pixmap_width &&
      dest_height == core->last_scale_pixmap_height)
    {
      return core->scale_pixmap;
    }

  core->last_scale_pixmap        = brush_mask;
  core->last_scale_pixmap_width  = dest_width;
  core->last_scale_pixmap_height = dest_height;

  if (core->scale_pixmap)
    mask_buf_free (core->scale_pixmap);

  core->scale_pixmap = brush_scale_pixmap (brush_mask,
                                           dest_width, dest_height);

  core->cache_invalid = TRUE;

  return core->scale_pixmap;
}

static MaskBuf *
gimp_brush_core_get_brush_mask (GimpBrushCore            *core,
                                GimpBrushApplicationMode  brush_hardness,
                                gdouble                   scale)
{
  GimpPaintCore *paint_core = GIMP_PAINT_CORE (core);
  MaskBuf       *mask;

  if (paint_core->use_pressure)
    mask = gimp_brush_core_scale_mask (core, core->brush->mask, scale);
  else
    mask = core->brush->mask;

  if (! mask)
    return NULL;

  switch (brush_hardness)
    {
    case GIMP_BRUSH_SOFT:
      mask = gimp_brush_core_subsample_mask (core, mask,
                                             paint_core->cur_coords.x,
                                             paint_core->cur_coords.y);
      break;

    case GIMP_BRUSH_HARD:
      mask = gimp_brush_core_solidify_mask (core, mask,
                                            paint_core->cur_coords.x,
                                            paint_core->cur_coords.y);
      break;

    case GIMP_BRUSH_PRESSURE:
      if (paint_core->use_pressure)
        mask = gimp_brush_core_pressurize_mask (core, mask,
                                                paint_core->cur_coords.x,
                                                paint_core->cur_coords.y,
                                                paint_core->cur_coords.pressure);
      else
        mask = gimp_brush_core_subsample_mask (core, mask,
                                               paint_core->cur_coords.x,
                                               paint_core->cur_coords.y);
      break;

    default:
      break;
    }

  return mask;
}


/**************************************************/
/*  Brush pipe utility functions                  */
/**************************************************/

void
gimp_brush_core_color_area_with_pixmap (GimpBrushCore            *core,
                                        GimpImage                *dest,
                                        GimpDrawable             *drawable,
                                        TempBuf                  *area,
                                        gdouble                   scale,
                                        GimpBrushApplicationMode  mode)
{
  GimpPaintCore *paint_core = GIMP_PAINT_CORE (core);
  PixelRegion    destPR;
  void          *pr;
  guchar        *d;
  gint           ulx;
  gint           uly;
  gint           offsetx;
  gint           offsety;
  gint           y;
  TempBuf       *pixmap_mask;
  TempBuf       *brush_mask;
  gdouble        X           = paint_core->cur_coords.x;
  gdouble        Y           = paint_core->cur_coords.y;

  g_return_if_fail (GIMP_IS_BRUSH (core->brush));
  g_return_if_fail (core->brush->pixmap != NULL);

  /*  scale the brushes  */
  pixmap_mask = gimp_brush_core_scale_pixmap (core,
                                              core->brush->pixmap,
                                              scale);
  if (! pixmap_mask)
    return;

  if (mode != GIMP_BRUSH_HARD)
    brush_mask = gimp_brush_core_scale_mask (core,
                                             core->brush->mask,
                                             scale);
  else
    brush_mask = NULL;

  pixel_region_init_temp_buf (&destPR, area,
                              0, 0, area->width, area->height);

  pr = pixel_regions_register (1, &destPR);

  /*  Calculate upper left corner of brush as in
   *  gimp_paint_core_get_paint_area.  Ugly to have to do this here, too.
   */
  ulx = (gint) floor (X) - (pixmap_mask->width  >> 1);
  uly = (gint) floor (Y) - (pixmap_mask->height  >> 1);

  /*  Not sure why this is necessary, but empirically the code does
   *  not work without it for even-sided brushes.  See bug #166622.
   */
  if (pixmap_mask->width %2 == 0)
    ulx += ROUND (X) - floor (X);
  if (pixmap_mask->height %2 == 0)
    uly += ROUND (Y) - floor (Y);

  offsetx = area->x - ulx;
  offsety = area->y - uly;

  for (; pr != NULL; pr = pixel_regions_process (pr))
    {
      d = destPR.data;

      for (y = 0; y < destPR.h; y++)
        {
          paint_line_pixmap_mask (dest, drawable, pixmap_mask, brush_mask,
                                  d, offsetx, y + offsety,
                                  destPR.bytes, destPR.w, mode);
          d += destPR.rowstride;
        }
    }
}

static void
paint_line_pixmap_mask (GimpImage                *dest,
                        GimpDrawable             *drawable,
                        TempBuf                  *pixmap_mask,
                        TempBuf                  *brush_mask,
                        guchar                   *d,
                        gint                      x,
                        gint                      y,
                        gint                      bytes,
                        gint                      width,
                        GimpBrushApplicationMode  mode)
{
  guchar  *b;
  guchar  *p;
  guchar  *mask;
  gdouble  alpha;
  gdouble  factor = 0.00392156986;  /*  1.0 / 255.0  */
  gint     x_index;
  gint     i,byte_loop;

  /*  Make sure x, y are positive  */
  while (x < 0)
    x += pixmap_mask->width;
  while (y < 0)
    y += pixmap_mask->height;

  /* Point to the approriate scanline */
  b = (temp_buf_data (pixmap_mask) +
       (y % pixmap_mask->height) * pixmap_mask->width * pixmap_mask->bytes);

  if (mode == GIMP_BRUSH_SOFT && brush_mask)
    {
      /*  ditto, except for the brush mask, so we can pre-multiply the
       *  alpha value
       */
      mask = (temp_buf_data (brush_mask) +
              (y % brush_mask->height) * brush_mask->width);

      for (i = 0; i < width; i++)
        {
          /* attempt to avoid doing this calc twice in the loop */
          x_index = ((i + x) % pixmap_mask->width);
          p = b + x_index * pixmap_mask->bytes;
          d[bytes - 1] = mask[x_index];

          /* multiply alpha into the pixmap data
           * maybe we could do this at tool creation or brush switch time?
           * and compute it for the whole brush at once and cache it?
           */
          alpha = d[bytes - 1] * factor;
          if (alpha)
            for (byte_loop = 0; byte_loop < bytes - 1; byte_loop++)
              d[byte_loop] *= alpha;

          gimp_image_transform_color (dest, drawable, d, GIMP_RGB, p);
          d += bytes;
        }
    }
  else
    {
      for (i = 0; i < width; i++)
        {
          /* attempt to avoid doing this calc twice in the loop */
          x_index = ((i + x) % pixmap_mask->width);
          p = b + x_index * pixmap_mask->bytes;
          d[bytes - 1] = 255;

          /* multiply alpha into the pixmap data
           * maybe we could do this at tool creation or brush switch time?
           * and compute it for the whole brush at once and cache it?
           */
          gimp_image_transform_color (dest, drawable, d, GIMP_RGB, p);
          d += bytes;
        }
    }
}

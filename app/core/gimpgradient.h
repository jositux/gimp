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

#ifndef __GIMP_GRADIENT_H__
#define __GIMP_GRADIENT_H__


#include "gimpdata.h"


#define GIMP_GRADIENT_FILE_EXTENSION ".ggr"

#define GIMP_GRADIENT_DEFAULT_SAMPLE_SIZE 40


struct _GimpGradientSegment
{
  gdouble                  left, middle, right;
  GimpRGB                  left_color;
  GimpRGB                  right_color;
  GimpGradientSegmentType  type;          /*  Segment's blending function  */
  GimpGradientSegmentColor color;         /*  Segment's coloring type      */

  GimpGradientSegment     *prev;
  GimpGradientSegment     *next;
};


#define GIMP_TYPE_GRADIENT            (gimp_gradient_get_type ())
#define GIMP_GRADIENT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_GRADIENT, GimpGradient))
#define GIMP_GRADIENT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_GRADIENT, GimpGradientClass))
#define GIMP_IS_GRADIENT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_GRADIENT))
#define GIMP_IS_GRADIENT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_GRADIENT))
#define GIMP_GRADIENT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_GRADIENT, GimpGradientClass))


typedef struct _GimpGradientClass GimpGradientClass;

struct _GimpGradient
{
  GimpData             parent_instance;

  GimpGradientSegment *segments;

  /*< private >*/
  GimpGradientSegment *last_visited;
  gint                 freeze_count;
};

struct _GimpGradientClass
{
  GimpDataClass  parent_class;
};


GType                 gimp_gradient_get_type         (void) G_GNUC_CONST;

GimpData            * gimp_gradient_new              (const gchar   *name,
                                                      gboolean       stingy_memory_use);
GimpData            * gimp_gradient_get_standard     (void);
GimpData            * gimp_gradient_load             (const gchar   *filename,
                                                      gboolean       stingy_memory_use,
                                                      GError       **error);

gboolean              gimp_gradient_save_as_pov      (GimpGradient  *gradient,
                                                      const gchar   *filename,
                                                      GError       **error);

void                  gimp_gradient_get_color_at     (GimpGradient  *gradient,
						      gdouble        pos,
                                                      gboolean       reverse,
						      GimpRGB       *color);
GimpGradientSegment * gimp_gradient_get_segment_at   (GimpGradient  *grad,
						      gdouble        pos);

void                  gimp_gradient_freeze           (GimpGradient  *gradient);
void                  gimp_gradient_thaw             (GimpGradient  *gradient);



/*  gradient segment functions  */

GimpGradientSegment * gimp_gradient_segment_new       (void);
GimpGradientSegment * gimp_gradient_segment_get_last  (GimpGradientSegment *seg);
GimpGradientSegment * gimp_gradient_segment_get_first (GimpGradientSegment *seg);
GimpGradientSegment * gimp_gradient_segment_get_nth   (GimpGradientSegment *seg,
                                                       gint                 index);

void                  gimp_gradient_segment_free      (GimpGradientSegment *seg);
void                  gimp_gradient_segments_free     (GimpGradientSegment *seg);

void    gimp_gradient_segment_split_midpoint  (GimpGradient         *gradient,
                                               GimpGradientSegment  *lseg,
                                               GimpGradientSegment **newl,
                                               GimpGradientSegment **newr);
void    gimp_gradient_segment_split_uniform   (GimpGradient         *gradient,
                                               GimpGradientSegment  *lseg,
                                               gint                  parts,
                                               GimpGradientSegment **newl,
                                               GimpGradientSegment **newr);

/* Colors Setting/Getting Routines */
void    gimp_gradient_segment_get_left_color  (GimpGradient         *gradient,
                                               GimpGradientSegment  *seg,
                                               GimpRGB              *color);

void    gimp_gradient_segment_set_left_color  (GimpGradient         *gradient,
                                               GimpGradientSegment  *seg,
                                               const GimpRGB        *color);


void    gimp_gradient_segment_get_right_color (GimpGradient         *gradient,
                                               GimpGradientSegment  *seg,
                                               GimpRGB              *color);

void    gimp_gradient_segment_set_right_color (GimpGradient         *gradient,
                                               GimpGradientSegment  *seg,
                                               const GimpRGB        *color);

/* Position Setting/Getting Routines */
/* (Setters return the position after it was set) */
gdouble gimp_gradient_segment_get_left_pos    (GimpGradient         *gradient,
                                               GimpGradientSegment  *seg);
gdouble gimp_gradient_segment_set_left_pos    (GimpGradient         *gradient,
                                               GimpGradientSegment  *seg,
                                               gdouble               pos);

gdouble gimp_gradient_segment_get_right_pos   (GimpGradient         *gradient,
                                               GimpGradientSegment  *seg);
gdouble gimp_gradient_segment_set_right_pos   (GimpGradient         *gradient,
                                               GimpGradientSegment  *seg,
                                               gdouble               pos);

gdouble gimp_gradient_segment_get_middle_pos  (GimpGradient         *gradient,
                                               GimpGradientSegment  *seg);
gdouble gimp_gradient_segment_set_middle_pos  (GimpGradient         *gradient,
                                               GimpGradientSegment  *seg,
                                               gdouble               pos);

/* Getting/Setting the Blending Function/Coloring Type */
GimpGradientSegmentType
gimp_gradient_segment_get_blending_function   (GimpGradient         *gradient,
                                               GimpGradientSegment  *seg);
GimpGradientSegmentColor
gimp_gradient_segment_get_coloring_type       (GimpGradient         *gradient,
                                               GimpGradientSegment  *seg);

/*
 * If the second segment is NULL, these functions will process
 * until the end of the string.
 * */
void    gimp_gradient_segment_range_compress  (GimpGradient         *gradient,
                                               GimpGradientSegment  *range_l,
                                               GimpGradientSegment  *range_r,
                                               gdouble               new_l,
                                               gdouble               new_r);
void    gimp_gradient_segment_range_blend     (GimpGradient         *gradient,
                                               GimpGradientSegment  *lseg,
                                               GimpGradientSegment  *rseg,
                                               const GimpRGB        *rgb1,
                                               const GimpRGB        *rgb2,
                                               gboolean              blend_colors,
                                               gboolean              blend_opacity);

void    gimp_gradient_segment_range_set_blending_function
                                              (GimpGradient         *gradient,
                                               GimpGradientSegment  *start_seg,
                                               GimpGradientSegment  *end_seg,
                                               GimpGradientSegmentType new_type);

void    gimp_gradient_segment_range_set_coloring_type
                                              (GimpGradient         *gradient,
                                               GimpGradientSegment  *start_seg,
                                               GimpGradientSegment  *end_seg,
                                               GimpGradientSegmentColor new_color);

void    gimp_gradient_segment_range_flip      (GimpGradient         *gradient,
                                               GimpGradientSegment  *start_seg,
                                               GimpGradientSegment  *end_seg,
                                               GimpGradientSegment **final_start_seg,
                                               GimpGradientSegment **final_end_seg);

void    gimp_gradient_segment_range_replicate (GimpGradient         *gradient,
                                               GimpGradientSegment  *start_seg,
                                               GimpGradientSegment  *end_seg,
                                               gint                  replicate_times,
                                               GimpGradientSegment **final_start_seg,
                                               GimpGradientSegment **final_end_seg);

void    gimp_gradient_segment_range_split_midpoint
                                              (GimpGradient         *gradient,
                                               GimpGradientSegment  *start_seg,
                                               GimpGradientSegment  *end_seg,
                                               GimpGradientSegment **final_start_seg,
                                               GimpGradientSegment **final_end_seg);

void    gimp_gradient_segment_range_split_uniform
                                              (GimpGradient         *gradient,
                                               GimpGradientSegment  *start_seg,
                                               GimpGradientSegment  *end_seg,
                                               gint                  parts,
                                               GimpGradientSegment **final_start_seg,
                                               GimpGradientSegment **final_end_seg);

void    gimp_gradient_segment_range_delete    (GimpGradient         *gradient,
                                               GimpGradientSegment  *start_seg,
                                               GimpGradientSegment  *end_seg,
                                               GimpGradientSegment **final_start_seg,
                                               GimpGradientSegment **final_end_seg);

void    gimp_gradient_segment_range_recenter_handles
                                              (GimpGradient         *gradient,
                                               GimpGradientSegment  *start_seg,
                                               GimpGradientSegment  *end_seg);
void    gimp_gradient_segment_range_redistribute_handles
                                              (GimpGradient         *gradient,
                                               GimpGradientSegment  *start_seg,
                                               GimpGradientSegment  *end_seg);

gdouble gimp_gradient_segment_range_move      (GimpGradient         *gradient,
                                               GimpGradientSegment  *range_l,
                                               GimpGradientSegment  *range_r,
                                               gdouble               delta,
                                               gboolean              control_compress);


#endif /* __GIMP_GRADIENT_H__ */

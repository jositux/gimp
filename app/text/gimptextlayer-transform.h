/* The GIMP -- an image manipulation program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * GimpTextLayer
 * Copyright (C) 2002-2003  Sven Neumann <sven@gimp.org>
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

#ifndef __GIMP_TEXT_LAYER_TRANSFORM_H__
#define __GIMP_TEXT_LAYER_TRANSFORM_H__


void  gimp_text_layer_scale     (GimpItem               *item,
                                 gint                    new_width,
                                 gint                    new_height,
                                 gint                    new_offset_x,
                                 gint                    new_offset_y,
                                 GimpInterpolationType   interpolation_type,
                                 GimpProgressFunc        progress_callback,
                                 gpointer                progress_data);
void  gimp_text_layer_flip      (GimpItem               *item,
                                 GimpContext            *context,
                                 GimpOrientationType     flip_type,
                                 gdouble                 axis,
                                 gboolean                clip_result);
void  gimp_text_layer_rotate    (GimpItem               *item,
                                 GimpContext            *context,
                                 GimpRotationType        rotate_type,
                                 gdouble                 center_x,
                                 gdouble                 center_y,
                                 gboolean                clip_result);
void  gimp_text_layer_transform (GimpItem               *item,
                                 GimpContext            *context,
                                 const GimpMatrix3      *matrix,
                                 GimpTransformDirection  direction,
                                 GimpInterpolationType   interpolation_type,
                                 gboolean                supersample,
                                 gint                    recursion_level,
                                 gboolean                clip_result,
                                 GimpProgressFunc        progress_callback,
                                 gpointer                progress_data);


#endif /* __GIMP_TEXT_LAYER_TRANSFORM_H__ */

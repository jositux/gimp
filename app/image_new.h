/* The GIMP -- an image manipulation program
 * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis
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

#ifndef __IMAGE_NEW_H__
#define __IMAGE_NEW_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  GimpImageBaseType  type;
  gchar             *name;
} GimpImageBaseTypeName;

typedef struct
{
  GimpFillType  type;
  gchar        *name;
} GimpFillTypeName;

struct _GimpImageNewValues
{
  gint               width;
  gint               height;
  GimpUnit           unit;

  gdouble            xresolution;
  gdouble            yresolution;
  GimpUnit           res_unit;
  
  GimpImageBaseType  type;
  GimpFillType       fill_type;
};

GList * image_new_get_fill_type_names       (void);
GList * image_new_get_image_base_type_names (void);

void image_new_create_window        (const GimpImageNewValues *values, 
				     const GimpImage          *image);
void image_new_set_default_values   (const GimpImageNewValues *values);

GimpImageNewValues * image_new_values_new  (const GimpImageNewValues *src_vals);
void                 image_new_values_free (GimpImageNewValues       *values);

void      image_new_create_image    (const GimpImageNewValues *values);

gdouble   image_new_calculate_size  (GimpImageNewValues       *values);
gchar   * image_new_get_size_string (gdouble                   size);

void      image_new_reset_current_cut_buffer (void);

#ifdef __cplusplus
}
#endif

#endif /* __IMAGE_NEW__ */

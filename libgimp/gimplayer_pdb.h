/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimplayer_pdb.h
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

#ifndef __GIMP_LAYER_PDB_H__
#define __GIMP_LAYER_PDB_H__

G_BEGIN_DECLS

/* For information look into the C source or the html documentation */


gint32               _gimp_layer_new                 (gint32                image_ID,
						      gint                  width,
						      gint                  height,
						      GimpImageType         type,
						      const gchar          *name,
						      gdouble               opacity,
						      GimpLayerModeEffects  mode);
gint32               gimp_layer_new_from_drawable    (gint32                drawable_ID,
						      gint32                dest_image_ID);
gint32               _gimp_layer_copy                (gint32                layer_ID,
						      gboolean              add_alpha);
gboolean             gimp_layer_add_alpha            (gint32                layer_ID);
gboolean             gimp_layer_scale                (gint32                layer_ID,
						      gint                  new_width,
						      gint                  new_height,
						      gboolean              local_origin);
gboolean             gimp_layer_resize               (gint32                layer_ID,
						      gint                  new_width,
						      gint                  new_height,
						      gint                  offx,
						      gint                  offy);
gboolean             gimp_layer_resize_to_image_size (gint32                layer_ID);
gboolean             gimp_layer_translate            (gint32                layer_ID,
						      gint                  offx,
						      gint                  offy);
gboolean             gimp_layer_set_offsets          (gint32                layer_ID,
						      gint                  offx,
						      gint                  offy);
gint32               gimp_layer_create_mask          (gint32                layer_ID,
						      GimpAddMaskType       mask_type);
gint32               gimp_layer_get_mask             (gint32                layer_ID);
gint32               gimp_layer_from_mask            (gint32                mask_ID);
gboolean             gimp_layer_add_mask             (gint32                layer_ID,
						      gint32                mask_ID);
gboolean             gimp_layer_remove_mask          (gint32                layer_ID,
						      GimpMaskApplyMode     mode);
gboolean             gimp_layer_is_floating_sel      (gint32                layer_ID);
gboolean             gimp_layer_get_lock_alpha       (gint32                layer_ID);
gboolean             gimp_layer_set_lock_alpha       (gint32                layer_ID,
						      gboolean              lock_alpha);
gboolean             gimp_layer_get_apply_mask       (gint32                layer_ID);
gboolean             gimp_layer_set_apply_mask       (gint32                layer_ID,
						      gboolean              apply_mask);
gboolean             gimp_layer_get_show_mask        (gint32                layer_ID);
gboolean             gimp_layer_set_show_mask        (gint32                layer_ID,
						      gboolean              show_mask);
gboolean             gimp_layer_get_edit_mask        (gint32                layer_ID);
gboolean             gimp_layer_set_edit_mask        (gint32                layer_ID,
						      gboolean              edit_mask);
gdouble              gimp_layer_get_opacity          (gint32                layer_ID);
gboolean             gimp_layer_set_opacity          (gint32                layer_ID,
						      gdouble               opacity);
GimpLayerModeEffects gimp_layer_get_mode             (gint32                layer_ID);
gboolean             gimp_layer_set_mode             (gint32                layer_ID,
						      GimpLayerModeEffects  mode);


G_END_DECLS

#endif /* __GIMP_LAYER_PDB_H__ */

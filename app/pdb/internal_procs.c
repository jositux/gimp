/* The GIMP -- an image manipulation program
 * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis
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

/* NOTE: This file is autogenerated by pdbgen.pl. */

#include "config.h"

#include <glib-object.h>

#include "pdb-types.h"

#include "core/gimp.h"

/* Forward declarations for registering PDB procs */

void register_brush_procs              (Gimp *gimp);
void register_brush_select_procs       (Gimp *gimp);
void register_brushes_procs            (Gimp *gimp);
void register_buffer_procs             (Gimp *gimp);
void register_channel_procs            (Gimp *gimp);
void register_color_procs              (Gimp *gimp);
void register_context_procs            (Gimp *gimp);
void register_convert_procs            (Gimp *gimp);
void register_display_procs            (Gimp *gimp);
void register_drawable_procs           (Gimp *gimp);
void register_drawable_transform_procs (Gimp *gimp);
void register_edit_procs               (Gimp *gimp);
void register_fileops_procs            (Gimp *gimp);
void register_floating_sel_procs       (Gimp *gimp);
void register_font_select_procs        (Gimp *gimp);
void register_fonts_procs              (Gimp *gimp);
void register_gimprc_procs             (Gimp *gimp);
void register_gradient_procs           (Gimp *gimp);
void register_gradient_select_procs    (Gimp *gimp);
void register_gradients_procs          (Gimp *gimp);
void register_grid_procs               (Gimp *gimp);
void register_guides_procs             (Gimp *gimp);
void register_help_procs               (Gimp *gimp);
void register_image_procs              (Gimp *gimp);
void register_layer_procs              (Gimp *gimp);
void register_message_procs            (Gimp *gimp);
void register_misc_procs               (Gimp *gimp);
void register_paint_tools_procs        (Gimp *gimp);
void register_palette_procs            (Gimp *gimp);
void register_palette_select_procs     (Gimp *gimp);
void register_palettes_procs           (Gimp *gimp);
void register_parasite_procs           (Gimp *gimp);
void register_paths_procs              (Gimp *gimp);
void register_pattern_procs            (Gimp *gimp);
void register_pattern_select_procs     (Gimp *gimp);
void register_patterns_procs           (Gimp *gimp);
void register_plug_in_procs            (Gimp *gimp);
void register_procedural_db_procs      (Gimp *gimp);
void register_progress_procs           (Gimp *gimp);
void register_selection_procs          (Gimp *gimp);
void register_selection_tools_procs    (Gimp *gimp);
void register_text_tool_procs          (Gimp *gimp);
void register_transform_tools_procs    (Gimp *gimp);
void register_undo_procs               (Gimp *gimp);
void register_unit_procs               (Gimp *gimp);
void register_vectors_procs            (Gimp *gimp);

/* 525 procedures registered total */

void
internal_procs_init (Gimp *gimp)
{
  g_return_if_fail (GIMP_IS_GIMP (gimp));

  register_brush_procs (gimp);
  register_brush_select_procs (gimp);
  register_brushes_procs (gimp);
  register_buffer_procs (gimp);
  register_channel_procs (gimp);
  register_color_procs (gimp);
  register_context_procs (gimp);
  register_convert_procs (gimp);
  register_display_procs (gimp);
  register_drawable_procs (gimp);
  register_drawable_transform_procs (gimp);
  register_edit_procs (gimp);
  register_fileops_procs (gimp);
  register_floating_sel_procs (gimp);
  register_font_select_procs (gimp);
  register_fonts_procs (gimp);
  register_gimprc_procs (gimp);
  register_gradient_procs (gimp);
  register_gradient_select_procs (gimp);
  register_gradients_procs (gimp);
  register_grid_procs (gimp);
  register_guides_procs (gimp);
  register_help_procs (gimp);
  register_image_procs (gimp);
  register_layer_procs (gimp);
  register_message_procs (gimp);
  register_misc_procs (gimp);
  register_paint_tools_procs (gimp);
  register_palette_procs (gimp);
  register_palette_select_procs (gimp);
  register_palettes_procs (gimp);
  register_parasite_procs (gimp);
  register_paths_procs (gimp);
  register_pattern_procs (gimp);
  register_pattern_select_procs (gimp);
  register_patterns_procs (gimp);
  register_plug_in_procs (gimp);
  register_procedural_db_procs (gimp);
  register_progress_procs (gimp);
  register_selection_procs (gimp);
  register_selection_tools_procs (gimp);
  register_text_tool_procs (gimp);
  register_transform_tools_procs (gimp);
  register_undo_procs (gimp);
  register_unit_procs (gimp);
  register_vectors_procs (gimp);
}

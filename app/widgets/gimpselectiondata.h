/* The GIMP -- an image manipulation program
 * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis
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

#ifndef __GIMP_SELECTION_DATA_H__
#define __GIMP_SELECTION_DATA_H__


/*  uri list  */

void            gimp_selection_data_set_uris      (GtkSelectionData *selection,
                                                   GdkAtom           atom,
                                                   GList            *uris);
GList         * gimp_selection_data_get_uris      (GtkSelectionData *selection);


/*  color  */

void            gimp_selection_data_set_color     (GtkSelectionData *selection,
                                                   GdkAtom           atom,
                                                   const GimpRGB    *color);
gboolean        gimp_selection_data_get_color     (GtkSelectionData *selection,
                                                   GimpRGB          *color);


/*  svg  */

void            gimp_selection_data_set_svg       (GtkSelectionData *selection,
                                                   GdkAtom           atom,
                                                   const gchar      *svg_data,
                                                   gint              svg_data_length);
const gchar   * gimp_selection_data_get_svg       (GtkSelectionData *selection,
                                                   gint             *svg_data_length);


/*  image  */

void            gimp_selection_data_set_image     (GtkSelectionData *selection,
                                                   GdkAtom           atom,
                                                   GimpImage        *gimage);
GimpImage     * gimp_selection_data_get_image     (GtkSelectionData *selection,
                                                   Gimp             *gimp);


/*  item  */

void            gimp_selection_data_set_item      (GtkSelectionData *selection,
                                                   GdkAtom           atom,
                                                   GimpItem         *item);
GimpItem      * gimp_selection_data_get_item      (GtkSelectionData *selection,
                                                   Gimp             *gimp);


/*  various data  */

void            gimp_selection_data_set_viewable  (GtkSelectionData *selection,
                                                   GdkAtom           atom,
                                                   GimpViewable     *viewable);

GimpBrush     * gimp_selection_data_get_brush     (GtkSelectionData *selection,
                                                   Gimp             *gimp);
GimpPattern   * gimp_selection_data_get_pattern   (GtkSelectionData *selection,
                                                   Gimp             *gimp);
GimpGradient  * gimp_selection_data_get_gradient  (GtkSelectionData *selection,
                                                   Gimp             *gimp);
GimpPalette   * gimp_selection_data_get_palette   (GtkSelectionData *selection,
                                                   Gimp             *gimp);
GimpFont      * gimp_selection_data_get_font      (GtkSelectionData *selection,
                                                   Gimp             *gimp);
GimpBuffer    * gimp_selection_data_get_buffer    (GtkSelectionData *selection,
                                                   Gimp             *gimp);
GimpImagefile * gimp_selection_data_get_imagefile (GtkSelectionData *selection,
                                                   Gimp             *gimp);
GimpTemplate  * gimp_selection_data_get_template  (GtkSelectionData *selection,
                                                   Gimp             *gimp);
GimpToolInfo  * gimp_selection_data_get_tool      (GtkSelectionData *selection,
                                                   Gimp             *gimp);


#endif /* __GIMP_SELECTION_DATA_H__ */

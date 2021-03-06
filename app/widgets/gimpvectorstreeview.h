/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * gimpvectorstreeview.h
 * Copyright (C) 2001-2003 Michael Natterer <mitch@gimp.org>
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

#ifndef __GIMP_VECTORS_TREE_VIEW_H__
#define __GIMP_VECTORS_TREE_VIEW_H__


#include "gimpitemtreeview.h"


#define GIMP_TYPE_VECTORS_TREE_VIEW            (gimp_vectors_tree_view_get_type ())
#define GIMP_VECTORS_TREE_VIEW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_VECTORS_TREE_VIEW, GimpVectorsTreeView))
#define GIMP_VECTORS_TREE_VIEW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_VECTORS_TREE_VIEW, GimpVectorsTreeViewClass))
#define GIMP_IS_VECTORS_TREE_VIEW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_VECTORS_TREE_VIEW))
#define GIMP_IS_VECTORS_TREE_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_VECTORS_TREE_VIEW))
#define GIMP_VECTORS_TREE_VIEW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_VECTORS_TREE_VIEW, GimpVectorsTreeViewClass))


typedef struct _GimpVectorsTreeViewClass  GimpVectorsTreeViewClass;

struct _GimpVectorsTreeView
{
  GimpItemTreeView  parent_instance;

  GtkWidget        *toselection_button;
  GtkWidget        *tovectors_button;
  GtkWidget        *stroke_button;
};

struct _GimpVectorsTreeViewClass
{
  GimpItemTreeViewClass  parent_class;
};


GType   gimp_vectors_tree_view_get_type (void) G_GNUC_CONST;


#endif  /*  __GIMP_VECTORS_TREE_VIEW_H__  */

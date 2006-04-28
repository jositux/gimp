/* The GIMP -- an image manipulation program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * gimppluginmanager-data.h
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

#ifndef __GIMP_PLUG_IN_MANAGER_DATA_H__
#define __GIMP_PLUG_IN_MANAGER_DATA_H__


void           gimp_plug_in_manager_data_free (GimpPlugInManager *manager);

void           gimp_plug_in_manager_set_data  (GimpPlugInManager *manager,
                                               const gchar       *identifier,
                                               gint32             bytes,
                                               const guint8      *data);
const guint8 * gimp_plug_in_manager_get_data  (GimpPlugInManager *manager,
                                               const gchar       *identifier,
                                               gint32            *bytes);


#endif  /*  __GIMP_PLUG_IN_MANAGER_DATA_H__  */

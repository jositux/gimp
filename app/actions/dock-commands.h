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

#ifndef __DOCK_COMMANDS_H__
#define __DOCK_COMMANDS_H__


void   dock_close_cmd_callback             (GtkAction *action,
                                            gpointer   data);
void   dock_change_screen_cmd_callback     (GtkAction *action,
                                            gpointer   data);

void   dock_toggle_image_menu_cmd_callback (GtkAction *action,
                                            gpointer   data);
void   dock_toggle_auto_cmd_callback       (GtkAction *action,
                                            gpointer   data);


#endif /* __DOCK_COMMANDS_H__ */

/*
 * This is a plug-in for the GIMP.
 *
 * Generates clickable image maps.
 *
 * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl
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
 *
 */

#ifndef _IMAP_GRID_H
#define _IMAP_GRID_H

#include "imap_default_dialog.h"

typedef struct {
   DefaultDialog_t *dialog;
   GtkWidget *type_frame;
   GtkWidget *granularity_frame;
   GtkWidget *offset_frame;
   GtkWidget *snap;
   GtkWidget *width;
   GtkWidget *height;
   GtkWidget *left;
   GtkWidget *top;
   GtkWidget *hidden;
   GtkWidget *lines;
   GtkWidget *crosses;
   GtkWidget *preview;

   gboolean   enable_preview;
} GridDialog_t;

void do_grid_settings_dialog();
void draw_grid(GtkWidget *preview);
gboolean toggle_grid();
void round_to_grid(gint *x, gint *y);

gboolean grid_near_x(gint x);
gboolean grid_near_y(gint y);

#endif /* _IMAP_GRID_H */

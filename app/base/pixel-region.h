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

#ifndef __PIXEL_REGION_H__
#define __PIXEL_REGION_H__


struct _PixelRegion
{
  guchar      *data;           /*  pointer to region data        */
  TileManager *tiles;          /*  pointer to tiles              */
  Tile        *curtile;        /*  current tile                  */
  gint         offx;           /*  tile offsets                  */
  gint         offy;           /*  tile offsets                  */
  guint        rowstride;      /*  bytes per pixel row           */
  gint         x;              /*  origin                        */
  gint         y;              /*  origin                        */
  guint        w;              /*  width of region               */
  guint        h;              /*  height of region              */
  guint        bytes;          /*  bytes per pixel               */
  guint        dirty : 1;      /*  will this region be dirtied?  */
  guint        process_count;  /*  used internally               */
};

struct _PixelRegionHolder
{
  PixelRegion *PR;
  guchar      *original_data;
  gint         startx;
  gint         starty;
  guint        count;
};

struct _PixelRegionIterator
{
  GSList *pixel_regions;
  guint   dirty_tiles;
  guint   region_width;
  guint   region_height;
  guint   portion_width;
  guint   portion_height;
  guint   process_count;
};


/*  PixelRegion functions  */

void     pixel_region_init          (PixelRegion         *PR, 
				     TileManager         *tiles, 
				     gint                 x, 
				     gint                 y, 
				     gint                 w, 
				     gint                 h, 
				     gboolean             dirty);
void     pixel_region_resize        (PixelRegion         *PR, 
				     gint                 x, 
				     gint                 y, 
				     gint                 w, 
				     gint                 h);
void     pixel_region_get_async     (PixelRegion         *PR, 
				     gint                 ulx, 
				     gint                 uly, 
				     gint                 lrx, 
				     gint                 lry);
void     pixel_region_get_row       (PixelRegion         *PR, 
				     gint                 x, 
				     gint                 y, 
				     gint                 w, 
				     guchar              *data, 
				     gint                 subsample);
void     pixel_region_set_row       (PixelRegion         *PR, 
				     gint                 x, 
				     gint                 y, 
				     gint                 w, 
				     guchar              *data);
void     pixel_region_get_col       (PixelRegion         *PR, 
				     gint                 x, 
				     gint                 y, 
				     gint                 h, 
				     guchar              *data, 
				     gint                 subsample);
void     pixel_region_set_col       (PixelRegion         *PR, 
				     gint                 x, 
				     gint                 y, 
				     gint                 h, 
				     guchar              *data);
gboolean pixel_region_has_alpha     (PixelRegion         *PR);

gpointer pixel_regions_register     (gint                 num_regions, 
				     ...);
gpointer pixel_regions_process      (PixelRegionIterator *PRI);
void     pixel_regions_process_stop (PixelRegionIterator *PRI);


#endif /* __PIXEL_REGION_H__ */

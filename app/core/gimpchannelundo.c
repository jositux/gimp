/* GIMP - The GNU Image Manipulation Program
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

#include "config.h"

#include <glib-object.h>

#include "libgimpbase/gimpbase.h"

#include "core-types.h"

#include "base/pixel-region.h"
#include "base/tile-manager.h"

#include "paint-funcs/paint-funcs.h"

#include "gimpimage.h"
#include "gimpchannel.h"
#include "gimpchannelundo.h"


static GObject * gimp_channel_undo_constructor (GType                  type,
                                                guint                  n_params,
                                                GObjectConstructParam *params);

static void      gimp_channel_undo_pop         (GimpUndo              *undo,
                                                GimpUndoMode           undo_mode,
                                                GimpUndoAccumulator   *accum);
static void      gimp_channel_undo_free        (GimpUndo              *undo,
                                                GimpUndoMode           undo_mode);


G_DEFINE_TYPE (GimpChannelUndo, gimp_channel_undo, GIMP_TYPE_ITEM_UNDO)

#define parent_class gimp_channel_undo_parent_class


static void
gimp_channel_undo_class_init (GimpChannelUndoClass *klass)
{
  GObjectClass  *object_class = G_OBJECT_CLASS (klass);
  GimpUndoClass *undo_class   = GIMP_UNDO_CLASS (klass);

  object_class->constructor = gimp_channel_undo_constructor;

  undo_class->pop           = gimp_channel_undo_pop;
  undo_class->free          = gimp_channel_undo_free;
}

static void
gimp_channel_undo_init (GimpChannelUndo *undo)
{
}

static GObject *
gimp_channel_undo_constructor (GType                  type,
                               guint                  n_params,
                               GObjectConstructParam *params)
{
  GObject         *object;
  GimpChannelUndo *channel_undo;
  GimpChannel     *channel;
  gint             x1, y1, x2, y2;

  object = G_OBJECT_CLASS (parent_class)->constructor (type, n_params, params);

  channel_undo = GIMP_CHANNEL_UNDO (object);

  g_assert (GIMP_IS_CHANNEL (GIMP_ITEM_UNDO (object)->item));

  channel = GIMP_CHANNEL (GIMP_ITEM_UNDO (object)->item);

  if (gimp_channel_bounds (channel, &x1, &y1, &x2, &y2))
    {
      GimpDrawable *drawable = GIMP_DRAWABLE (channel);
      PixelRegion   srcPR, destPR;

      channel_undo->tiles = tile_manager_new (x2 - x1, y2 - y1,
                                              gimp_drawable_bytes (drawable));
      channel_undo->x = x1;
      channel_undo->y = y1;

      pixel_region_init (&srcPR, gimp_drawable_get_tiles (drawable),
                         x1, y1, x2 - x1, y2 - y1, FALSE);
      pixel_region_init (&destPR, channel_undo->tiles,
                         0, 0, x2 - x1, y2 - y1, TRUE);

      copy_region (&srcPR, &destPR);

      GIMP_UNDO (object)->size +=
        tile_manager_get_memsize (channel_undo->tiles, FALSE);
    }

  return object;
}

static void
gimp_channel_undo_pop (GimpUndo            *undo,
                       GimpUndoMode         undo_mode,
                       GimpUndoAccumulator *accum)
{
  GimpChannelUndo *channel_undo = GIMP_CHANNEL_UNDO (undo);
  GimpChannel     *channel      = GIMP_CHANNEL (GIMP_ITEM_UNDO (undo)->item);
  TileManager     *new_tiles;
  PixelRegion      srcPR, destPR;
  gint             x1, y1, x2, y2;
  gint             width  = 0;
  gint             height = 0;

  GIMP_UNDO_CLASS (parent_class)->pop (undo, undo_mode, accum);

  if (channel_undo->tiles)
    undo->size -= tile_manager_get_memsize (channel_undo->tiles, FALSE);

  if (gimp_channel_bounds (channel, &x1, &y1, &x2, &y2))
    {
      guchar empty = 0;

      new_tiles = tile_manager_new (x2 - x1, y2 - y1, 1);

      pixel_region_init (&srcPR, GIMP_DRAWABLE (channel)->tiles,
                         x1, y1, x2 - x1, y2 - y1, FALSE);
      pixel_region_init (&destPR, new_tiles,
                         0, 0, x2 - x1, y2 - y1, TRUE);

      copy_region (&srcPR, &destPR);

      pixel_region_init (&srcPR, GIMP_DRAWABLE (channel)->tiles,
                         x1, y1, x2 - x1, y2 - y1, TRUE);

      color_region (&srcPR, &empty);
    }
  else
    {
      new_tiles = NULL;
    }

  if (channel_undo->tiles)
    {
      width  = tile_manager_width  (channel_undo->tiles);
      height = tile_manager_height (channel_undo->tiles);

      pixel_region_init (&srcPR, channel_undo->tiles,
                         0, 0, width, height, FALSE);
      pixel_region_init (&destPR, GIMP_DRAWABLE (channel)->tiles,
                         channel_undo->x, channel_undo->y, width, height, TRUE);

      copy_region (&srcPR, &destPR);

      tile_manager_unref (channel_undo->tiles);
    }

  /* invalidate the current bounds and boundary of the mask */
  gimp_drawable_invalidate_boundary (GIMP_DRAWABLE (channel));

  if (channel_undo->tiles)
    {
      channel->empty = FALSE;
      channel->x1    = channel_undo->x;
      channel->y1    = channel_undo->y;
      channel->x2    = channel_undo->x + width;
      channel->y2    = channel_undo->y + height;
    }
  else
    {
      channel->empty = TRUE;
      channel->x1    = 0;
      channel->y1    = 0;
      channel->x2    = GIMP_ITEM (channel)->width;
      channel->y2    = GIMP_ITEM (channel)->height;
    }

  /* we know the bounds */
  channel->bounds_known = TRUE;

  /*  set the new mask undo parameters  */
  channel_undo->tiles = new_tiles;
  channel_undo->x     = x1;
  channel_undo->y     = y1;

  gimp_drawable_update (GIMP_DRAWABLE (channel),
                        0, 0,
                        GIMP_ITEM (channel)->width,
                        GIMP_ITEM (channel)->height);

  if (channel_undo->tiles)
    undo->size += tile_manager_get_memsize (channel_undo->tiles, FALSE);
}

static void
gimp_channel_undo_free (GimpUndo     *undo,
                        GimpUndoMode  undo_mode)
{
  GimpChannelUndo *channel_undo = GIMP_CHANNEL_UNDO (undo);

  if (channel_undo->tiles)
    {
      tile_manager_unref (channel_undo->tiles);
      channel_undo->tiles = NULL;
    }

  GIMP_UNDO_CLASS (parent_class)->free (undo, undo_mode);
}

/* The GIMP -- an image manipulation program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * gimpfontlist.c
 * Copyright (C) 2003 Michael Natterer <mitch@gimp.org>
 *                    Sven Neumann <sven@gimp.org>
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

#include <string.h>

#include <glib-object.h>

#include "text-types.h"

#include "gimpfont.h"
#include "gimpfontlist.h"

#include "gimp-intl.h"


static void   gimp_font_list_class_init        (GimpFontListClass *klass);
static void   gimp_font_list_init              (GimpFontList      *list);

static void   gimp_font_list_add               (GimpContainer     *container,
                                                GimpObject        *object);
static gint   gimp_font_list_font_compare_func (gconstpointer      first,
                                                gconstpointer      second);


static GimpListClass *parent_class = NULL;


GType
gimp_font_list_get_type (void)
{
  static GType list_type = 0;

  if (! list_type)
    {
      static const GTypeInfo list_info =
      {
        sizeof (GimpFontListClass),
	(GBaseInitFunc) NULL,
	(GBaseFinalizeFunc) NULL,
	(GClassInitFunc) gimp_font_list_class_init,
	NULL,           /* class_finalize */
	NULL,           /* class_font     */
	sizeof (GimpFontList),
	0,              /* n_preallocs    */
	(GInstanceInitFunc) gimp_font_list_init,
      };

      list_type = g_type_register_static (GIMP_TYPE_LIST,
					  "GimpFontList", 
					  &list_info, 0);
    }

  return list_type;
}

static void
gimp_font_list_class_init (GimpFontListClass *klass)
{
  GimpContainerClass *container_class;
  
  container_class = GIMP_CONTAINER_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  container_class->add = gimp_font_list_add;
}

static void
gimp_font_list_init (GimpFontList *list)
{
}

static void
gimp_font_list_add (GimpContainer *container,
		    GimpObject    *object)
{
  GimpList *list;

  list = GIMP_LIST (container);

  list->list = g_list_insert_sorted (list->list, object,
				     gimp_font_list_font_compare_func);
}

GimpContainer *
gimp_font_list_new (void)
{
  GimpFontList *list;

  list = g_object_new (GIMP_TYPE_FONT_LIST,
                       "children_type", GIMP_TYPE_FONT,
                       "policy",        GIMP_CONTAINER_POLICY_STRONG,
                       NULL);

  return GIMP_CONTAINER (list);
}

static gint
gimp_font_list_font_compare_func (gconstpointer first,
				  gconstpointer second)
{
  return strcmp (((const GimpObject *) first)->name,
		 ((const GimpObject *) second)->name);
}

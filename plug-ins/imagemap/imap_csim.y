%{
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

#include <stdlib.h>
#include <strings.h>

#include "gtk/gtk.h"

#include "imap_circle.h"
#include "imap_file.h"
#include "imap_main.h"
#include "imap_polygon.h"
#include "imap_rectangle.h"
#include "imap_string.h"

extern int csim_lex();
extern int csim_restart();
static void csim_error(char* s);

static enum {UNDEFINED, RECTANGLE, CIRCLE, POLYGON} current_type;
static Object_t *current_object;
static MapInfo_t *_map_info;

%}

%union {
   int val;
   double value;
   char id[256];
}

%token<val> IMG SRC WIDTH HEIGHT BORDER USEMAP
%token<val> START_MAP END_MAP NAME AREA SHAPE COORDS ALT HREF NOHREF
%token<val> TARGET ONMOUSEOVER ONMOUSEOUT ONFOCUS ONBLUR
%token<val> AUTHOR DESCRIPTION BEGIN_COMMENT END_COMMENT
%token<value> FLOAT
%token<id> STRING

%%

csim_file	: image start_map comment_lines area_list end_map
		;

image		: '<' IMG SRC '=' STRING image_tags '>'
		{
		   g_strreplace(&_map_info->image_name, $5);
		}
		;

image_tags	: /* Empty */
		| image_tags image_tag
		;

image_tag	: image_width
		| image_height
		| BORDER '=' FLOAT {}
		| USEMAP '=' STRING {}
		| ALT '=' STRING {}
		;

image_width	: WIDTH '=' FLOAT 
		{
		   _map_info->old_image_width = (gint) $3;
		}
		;

image_height	: HEIGHT '=' FLOAT 
		{
		   _map_info->old_image_height = (gint) $3;
		}
		;

start_map	: '<' START_MAP NAME '=' STRING '>'
		{
		   g_strreplace(&_map_info->title, $5);
		}
		;

comment_lines	: /* empty */
		| comment_lines comment_line
		;

comment_line	: author_line
		| description_line
		| real_comment
		;

real_comment	: BEGIN_COMMENT STRING END_COMMENT
		{
		}
		;

author_line	: AUTHOR STRING END_COMMENT
		{
		   g_strreplace(&_map_info->author, $2);

		}
		;

description_line: DESCRIPTION STRING END_COMMENT
		{
		   gchar *description;

		   description = g_strconcat(_map_info->description, $2, "\n", 
					     NULL);
		   g_strreplace(&_map_info->description, description);
		}
		;

area_list	: /* empty */
		| area_list area
		;

area		: '<' AREA tag_list '>'
		{
		   if (current_type != UNDEFINED)
		      add_shape(current_object);
		}
		;

tag_list	: /* Empty */
		| tag_list tag
		;

tag		: shape_tag
		| coords_tag
		| href_tag
		| nohref_tag
		| alt_tag
		| target_tag
		| onmouseover_tag
		| onmouseout_tag
		| onfocus_tag
		| onblur_tag
		;

shape_tag	: SHAPE '=' STRING
		{
		   if (!g_strcasecmp($3, "RECT")) {
		      current_object = create_rectangle(0, 0, 0, 0);
		      current_type = RECTANGLE;
		   } else if (!g_strcasecmp($3, "CIRCLE")) {
		      current_object = create_circle(0, 0, 0);
		      current_type = CIRCLE;
		   } else if (!g_strcasecmp($3, "POLY")) {
		      current_object = create_polygon(NULL);
		      current_type = POLYGON;
		   } else if (!g_strcasecmp($3, "DEFAULT")) {
		      current_type = UNDEFINED;
		   }
		}
		;

coords_tag	: COORDS '=' STRING
		{
		   char *p;
		   if (current_type == RECTANGLE) {
		      Rectangle_t *rectangle;

		      rectangle = ObjectToRectangle(current_object);
		      p = strtok($3, ",");
		      rectangle->x = atoi(p);
		      p = strtok(NULL, ",");
		      rectangle->y = atoi(p);
		      p = strtok(NULL, ",");
		      rectangle->width = atoi(p) - rectangle->x;
		      p = strtok(NULL, ",");
		      rectangle->height = atoi(p) - rectangle->y;
		   } else if (current_type == CIRCLE) {
		      Circle_t *circle;

		      circle = ObjectToCircle(current_object);
		      p = strtok($3, ",");
		      circle->x = atoi(p);
		      p = strtok(NULL, ",");
		      circle->y = atoi(p);
		      p = strtok(NULL, ",");
		      circle->r = atoi(p);
		   } else if (current_type == POLYGON) {
		      Polygon_t *polygon = ObjectToPolygon(current_object);
		      GList *points;
		      GdkPoint *point, *first;
		      gint x, y;

		      p = strtok($3, ",");
		      x = atoi(p);
		      p = strtok(NULL, ",");
		      y = atoi(p);
		      point = new_point(x, y);
		      points = g_list_append(NULL, (gpointer) point);

		      while(1) {
			 p = strtok(NULL, ",");
			 if (!p)
			    break;
			 x = atoi(p);
			 p = strtok(NULL, ",");
			 y = atoi(p);
			 point = new_point(x, y);
			 g_list_append(points, (gpointer) point);
		      }
		      /* Remove last point if duplicate */
		      first = (GdkPoint*) points->data;
		      if (first->x == point->x && first->y == point->y)
			 polygon_remove_last_point(polygon);
		      polygon->points = points;
		   }
		}
		;

href_tag	: HREF '=' STRING
		{
		   if (current_type == UNDEFINED) {
		      g_strreplace(&_map_info->default_url, $3);
		   } else {
		      object_set_url(current_object, $3);
		   }
		}
		;

nohref_tag	: NOHREF
		{
		}
		;

alt_tag		: ALT '=' STRING
		{
		   object_set_comment(current_object, $3);
		}
		;

target_tag	: TARGET '=' STRING
		{
		   object_set_target(current_object, $3);
		}
		;

onmouseover_tag	: ONMOUSEOVER '=' STRING
		{
		   object_set_mouse_over(current_object, $3);
		}
		;

onmouseout_tag	: ONMOUSEOUT '=' STRING
		{
		   object_set_mouse_out(current_object, $3);
		}
		;

onfocus_tag	: ONFOCUS '=' STRING
		{
		   object_set_focus(current_object, $3);
		}
		;

onblur_tag	: ONBLUR '=' STRING
		{
		   object_set_blur(current_object, $3);
		}
		;

end_map		: '<' END_MAP '>'
		;

%%

static void 
csim_error(char* s)
{
   extern FILE *csim_in;
   csim_restart(csim_in);
}

gboolean
load_csim(const char* filename)
{
   gboolean status;
   extern FILE *csim_in;
   csim_in = fopen(filename, "r");
   if (csim_in) {
      _map_info = get_map_info();
      status = !csim_parse();
      fclose(csim_in);
   } else {
      status = FALSE;
   }
   return status;
}

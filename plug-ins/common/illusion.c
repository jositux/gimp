/*******************************************************************************

  illusion.c  -- This is a plug-in for the GIMP 1.0

  Copyright (C) 1997  Hirotsuna Mizuno
                      s1041150@u-aizu.ac.jp

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the Free
  Software Foundation; either version 2 of the License, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc.,
  59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

*******************************************************************************/

#include "config.h"

#include <stdio.h>
#include <stdlib.h>

#include <gtk/gtk.h>

#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>

#include "libgimp/stdplugins-intl.h"

#define PLUG_IN_NAME    "plug_in_illusion"
#define PLUG_IN_VERSION "v0.7 (Dec. 25 1997)"


/******************************************************************************/

static void query  (void);
static void run    (gchar   *name,
		    gint     nparam,
		    GParam  *param,
		    gint    *nreturn_vals,
		    GParam **return_vals);

static void filter (GDrawable *drawable);
static int  dialog (void);

/******************************************************************************/

typedef struct
{
  gint32 division;
} parameter_t;

/******************************************************************************/

GPlugInInfo PLUG_IN_INFO =
{
  NULL,  /* init_proc  */
  NULL,  /* quit_proc  */
  query, /* query_proc */
  run,   /* run_proc   */
};

static parameter_t parameters =
{
  8
};

static gint    image_width;
static gint    image_height;
static gint    image_bpp;
static gint    image_has_alpha;
static gint    select_x1;
static gint    select_y1;
static gint    select_x2;
static gint    select_y2;
static gint    select_width;
static gint    select_height;
static gdouble center_x;
static gdouble center_y;

/******************************************************************************/

MAIN ()

/******************************************************************************/

static void
query (void)
{
  static int nargs = 4;
  static GParamDef args[] =
  {
    { PARAM_INT32,    "run_mode",  "interactive / non-interactive" },
    { PARAM_IMAGE,    "image",     "input image" },
    { PARAM_DRAWABLE, "drawable",  "input drawable" },
    { PARAM_INT32,    "division",  "the number of divisions" }
  };
  static int nreturn_vals = 0;
  static GParamDef *return_vals = NULL;

  INIT_I18N();

  gimp_install_procedure (PLUG_IN_NAME,
			  "produce illusion",
			  "produce illusion",
			  "Hirotsuna Mizuno <s1041150@u-aizu.ac.jp>",
			  "Hirotsuna Mizuno",
			  PLUG_IN_VERSION,
			  N_("<Image>/Filters/Map/Illusion..."),
			  "RGB*, GRAY*",
			  PROC_PLUG_IN,
			  nargs,
			  nreturn_vals,
			  args,
			  return_vals);
}

/******************************************************************************/

static void
run (gchar   *name,
     gint     nparams,
     GParam  *params,
     gint    *nreturn_vals,
     GParam **return_vals)
{
  GDrawable     *drawable;
  GRunModeType   run_mode;
  static GParam  returnv[1];
  GStatusType    status = STATUS_SUCCESS;

  run_mode = params[0].data.d_int32;
  drawable = gimp_drawable_get (params[2].data.d_drawable);
  *nreturn_vals = 1;
  *return_vals  = returnv;

  /* get the drawable info */
  image_width     = gimp_drawable_width (drawable->id);
  image_height    = gimp_drawable_height (drawable->id);
  image_bpp       = gimp_drawable_bpp (drawable->id);
  image_has_alpha = gimp_drawable_has_alpha (drawable->id);
  gimp_drawable_mask_bounds (drawable->id,
			     &select_x1, &select_y1, &select_x2, &select_y2);
  select_width    = select_x2 - select_x1;
  select_height   = select_y2 - select_y1;
  center_x        = select_x1 + (gdouble)select_width / 2;
  center_y        = select_y1 + (gdouble)select_height / 2;

  /* switch the run mode */
  switch (run_mode)
    {
    case RUN_INTERACTIVE:
      INIT_I18N_UI();
      gimp_get_data (PLUG_IN_NAME, &parameters);
      if (! dialog())
	return;
      gimp_set_data (PLUG_IN_NAME, &parameters, sizeof (parameter_t));
      break;

    case RUN_NONINTERACTIVE:
      if (nparams != 4)
	{
	  status = STATUS_CALLING_ERROR;
	}
      else
	{
	  parameters.division = params[3].data.d_int32;
	}
      break;

    case RUN_WITH_LAST_VALS:
      gimp_get_data (PLUG_IN_NAME, &parameters);
      break;
    }

  if (status == STATUS_SUCCESS)
    {
      if (gimp_drawable_is_rgb (drawable->id) || 
	  gimp_drawable_is_gray (drawable->id))
	{
	  gimp_tile_cache_ntiles (2 * (drawable->width / gimp_tile_width() + 1));
	  filter (drawable);
	  if (run_mode != RUN_NONINTERACTIVE)
	    gimp_displays_flush ();
	}
      else
	{
	  status = STATUS_EXECUTION_ERROR;
	}
    }

  returnv[0].type          = PARAM_STATUS;
  returnv[0].data.d_status = status;

  gimp_drawable_detach (drawable);
}

/******************************************************************************/

static void
filter (GDrawable *drawable)
{
  GPixelRgn srcPR, destPR;
  guchar  **pixels;
  guchar  **destpixels;
  gint      x, y, b;
  gint      xx, yy;
  gdouble   scale, radius, cx, cy, angle, offset;
  
  gimp_pixel_rgn_init (&srcPR, drawable,
		       0, 0, image_width, image_height, FALSE, FALSE);
  gimp_pixel_rgn_init (&destPR, drawable,
		       0, 0, image_width, image_height, TRUE, TRUE);

  pixels = (guchar **) g_malloc (image_height * sizeof (guchar *));
  destpixels = (guchar **) g_malloc (image_height * sizeof (guchar *));
  for (y = 0; y < image_height; y++)
    {
      pixels[y] = (guchar *) g_malloc (image_width * image_bpp);
      destpixels[y] = (guchar *) g_malloc (image_width * image_bpp);
      gimp_pixel_rgn_get_row (&srcPR, pixels[y], 0, y, image_width);
    }

  /*
    for( y = select_y1; y < select_y2; y++ ){
    for( x = select_x1; x < select_x2; x++ ){
    for( b = 0; b < image_bpp; b++ ){
    destpixels[y][x*image_bpp+b] = 0;
    }
    }
    }
  */

  gimp_progress_init (PLUG_IN_NAME);

  scale = sqrt (select_width * select_width + select_height * select_height) / 2;
  offset = (gint) (scale / 2);

  for (y = select_y1; y < select_y2; y++)
    {
      cy = ((gdouble)y - center_y) / scale; 
      for (x = select_x1; x < select_x2; x++)
	{
	  cx = ((gdouble)x - center_x) / scale;
	  angle = floor (atan2 (cy, cx) * parameters.division / G_PI_2)
	    * G_PI_2 / parameters.division + (G_PI / parameters.division);
	  radius = sqrt ((gdouble) (cx * cx + cy * cy));
	  xx = x - offset * cos (angle);
	  yy = y - offset * sin (angle);
	  if (xx < 0) xx = 0;
	  else if (image_width <= xx) xx = image_width - 1;
	  if (yy < 0) yy = 0;
	  else if (image_height <= yy) yy = image_height - 1;
	  for (b = 0; b < image_bpp; b++)
	    destpixels[y][x*image_bpp+b] =
	      (1-radius) * pixels[y][x * image_bpp + b] 
	      + radius * pixels[yy][xx * image_bpp + b];
	}
      gimp_pixel_rgn_set_row (&destPR, destpixels[y], 0, y, image_width);
      gimp_progress_update ((double) (y - select_y1) / (double) select_height);
    }

  gimp_drawable_flush (drawable);
  gimp_drawable_merge_shadow (drawable->id, TRUE);
  gimp_drawable_update (drawable->id,
			select_x1, select_y1, select_width, select_height);

  for (y = select_y1; y < select_y2; y++) g_free (pixels[y-select_y1]);
  g_free (pixels);
  for (y = select_y1; y < select_y2; y++) g_free (destpixels[y-select_y1]);
  g_free (destpixels);
}

/******************************************************************************/

static int dialog_status = FALSE;

static void
dialog_ok_handler (GtkWidget *widget,
		   gpointer   data)
{
  dialog_status = TRUE;

  gtk_widget_destroy (GTK_WIDGET (data));
}

/******************************************************************************/

static int
dialog (void)
{
  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *table;
  GtkWidget *spinbutton;
  GtkObject *adj;

  gint    argc = 1;
  gchar **argv = g_new (gchar *, 1);

  argv[0] = g_strdup ("illusion");

  gtk_init (&argc, &argv);
  gtk_rc_parse (gimp_gtkrc ());

  /* dialog window */
  window = gimp_dialog_new (_("Illusion"), "illusion",
			    gimp_plugin_help_func, "filters/illusion.html",
			    GTK_WIN_POS_MOUSE,
			    FALSE, TRUE, FALSE,

			    _("OK"), dialog_ok_handler,
			    NULL, NULL, NULL, TRUE, FALSE,
			    _("Cancel"), gtk_widget_destroy,
			    NULL, 1, NULL, FALSE, TRUE,

			    NULL);

  gtk_signal_connect (GTK_OBJECT (window), "destroy",
		      GTK_SIGNAL_FUNC (gtk_main_quit),
		      NULL);

  frame = gtk_frame_new (_("Parameter Settings"));
  gtk_container_set_border_width (GTK_CONTAINER (frame), 6);
  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window)->vbox), frame,
		      FALSE, FALSE, 0 );
  gtk_widget_show (frame);

  table = gtk_table_new (1, 2, FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (table), 4);
  gtk_table_set_row_spacings (GTK_TABLE (table), 2);
  gtk_table_set_col_spacings (GTK_TABLE (table), 4);
  gtk_container_add (GTK_CONTAINER (frame), table);
  gtk_widget_show (table);

  spinbutton = gimp_spin_button_new (&adj, parameters.division,
				     G_MININT, G_MAXINT, 1, 10, 0, 1, 0);
  gimp_table_attach_aligned (GTK_TABLE (table), 0, 0,
			     _("Division:"), 1.0, 0.5,
			     spinbutton, 1, TRUE);
  gtk_signal_connect (GTK_OBJECT (adj), "value_changed",
		      GTK_SIGNAL_FUNC (gimp_int_adjustment_update),
		      &parameters.division);

  gtk_widget_show (window);

  gtk_main ();
  gdk_flush ();

  return dialog_status;
}

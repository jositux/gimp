/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <stdio.h>

#include <glib.h>

#include "gimpbasetypes.h"

#include "gimpparasite.h"
#include "gimpprotocol.h"
#include "gimpwire.h"


static void _gp_quit_read                (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_quit_write               (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_quit_destroy             (WireMessage  *msg);

static void _gp_config_read              (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_config_write             (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_config_destroy           (WireMessage  *msg);

static void _gp_tile_req_read            (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_tile_req_write           (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_tile_req_destroy         (WireMessage  *msg);

static void _gp_tile_ack_read            (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_tile_ack_write           (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_tile_ack_destroy         (WireMessage  *msg);

static void _gp_tile_data_read           (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_tile_data_write          (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_tile_data_destroy        (WireMessage  *msg);

static void _gp_proc_run_read            (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_proc_run_write           (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_proc_run_destroy         (WireMessage  *msg);

static void _gp_proc_return_read         (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_proc_return_write        (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_proc_return_destroy      (WireMessage  *msg);

static void _gp_temp_proc_run_read       (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_temp_proc_run_write      (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_temp_proc_run_destroy    (WireMessage  *msg);

static void _gp_temp_proc_return_read    (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_temp_proc_return_write   (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_temp_proc_return_destroy (WireMessage  *msg);

static void _gp_proc_install_read        (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_proc_install_write       (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_proc_install_destroy     (WireMessage  *msg);

static void _gp_proc_uninstall_read      (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_proc_uninstall_write     (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_proc_uninstall_destroy   (WireMessage  *msg);

static void _gp_extension_ack_read       (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_extension_ack_write      (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_extension_ack_destroy    (WireMessage  *msg);

static void _gp_params_read              (GIOChannel   *channel,
					  GPParam     **params,
					  guint        *nparams,
                                          gpointer      user_data);
static void _gp_params_write             (GIOChannel   *channel,
					  GPParam      *params,
					  gint          nparams,
                                          gpointer      user_data);

/* used by gimp.c:gimp_destroy_params() */
void        _gp_params_destroy           (GPParam      *params,
					  gint          nparams);

static void _gp_has_init_read            (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_has_init_write           (GIOChannel   *channel,
					  WireMessage  *msg,
                                          gpointer      user_data);
static void _gp_has_init_destroy         (WireMessage  *msg);



void
gp_init (void)
{
  wire_register (GP_QUIT,
		 _gp_quit_read,
		 _gp_quit_write,
		 _gp_quit_destroy);
  wire_register (GP_CONFIG,
		 _gp_config_read,
		 _gp_config_write,
		 _gp_config_destroy);
  wire_register (GP_TILE_REQ,
		 _gp_tile_req_read,
		 _gp_tile_req_write,
		 _gp_tile_req_destroy);
  wire_register (GP_TILE_ACK,
		 _gp_tile_ack_read,
		 _gp_tile_ack_write,
		 _gp_tile_ack_destroy);
  wire_register (GP_TILE_DATA,
		 _gp_tile_data_read,
		 _gp_tile_data_write,
		 _gp_tile_data_destroy);
  wire_register (GP_PROC_RUN,
		 _gp_proc_run_read,
		 _gp_proc_run_write,
		 _gp_proc_run_destroy);
  wire_register (GP_PROC_RETURN,
		 _gp_proc_return_read,
		 _gp_proc_return_write,
		 _gp_proc_return_destroy);
  wire_register (GP_TEMP_PROC_RUN,
		 _gp_temp_proc_run_read,
		 _gp_temp_proc_run_write,
		 _gp_temp_proc_run_destroy);
  wire_register (GP_TEMP_PROC_RETURN,
		 _gp_temp_proc_return_read,
		 _gp_temp_proc_return_write,
		 _gp_temp_proc_return_destroy);
  wire_register (GP_PROC_INSTALL,
		 _gp_proc_install_read,
		 _gp_proc_install_write,
		 _gp_proc_install_destroy);
  wire_register (GP_PROC_UNINSTALL,
		 _gp_proc_uninstall_read,
		 _gp_proc_uninstall_write,
		 _gp_proc_uninstall_destroy);
  wire_register (GP_EXTENSION_ACK,
		 _gp_extension_ack_read,
		 _gp_extension_ack_write,
		 _gp_extension_ack_destroy);
  wire_register (GP_HAS_INIT,
		 _gp_has_init_read,
		 _gp_has_init_write,
		 _gp_has_init_destroy);
}

gboolean
gp_quit_write (GIOChannel *channel,
               gpointer    user_data)
{
  WireMessage msg;

  msg.type = GP_QUIT;
  msg.data = NULL;

  if (! wire_write_msg (channel, &msg, user_data))
    return FALSE;
  if (! wire_flush (channel, user_data))
    return FALSE;
  return TRUE;
}

gboolean
gp_config_write (GIOChannel *channel,
		 GPConfig   *config,
                 gpointer    user_data)
{
  WireMessage msg;

  msg.type = GP_CONFIG;
  msg.data = config;

  if (! wire_write_msg (channel, &msg, user_data))
    return FALSE;
  if (! wire_flush (channel, user_data))
    return FALSE;
  return TRUE;
}

gboolean
gp_tile_req_write (GIOChannel *channel,
		   GPTileReq  *tile_req,
                   gpointer    user_data)
{
  WireMessage msg;

  msg.type = GP_TILE_REQ;
  msg.data = tile_req;

  if (! wire_write_msg (channel, &msg, user_data))
    return FALSE;
  if (! wire_flush (channel, user_data))
    return FALSE;
  return TRUE;
}

gboolean
gp_tile_ack_write (GIOChannel *channel,
                   gpointer    user_data)
{
  WireMessage msg;

  msg.type = GP_TILE_ACK;
  msg.data = NULL;

  if (! wire_write_msg (channel, &msg, user_data))
    return FALSE;
  if (! wire_flush (channel, user_data))
    return FALSE;
  return TRUE;
}

gboolean
gp_tile_data_write (GIOChannel *channel,
		    GPTileData *tile_data,
                    gpointer    user_data)
{
  WireMessage msg;

  msg.type = GP_TILE_DATA;
  msg.data = tile_data;

  if (! wire_write_msg (channel, &msg, user_data))
    return FALSE;
  if (! wire_flush (channel, user_data))
    return FALSE;
  return TRUE;
}

gboolean
gp_proc_run_write (GIOChannel *channel,
		   GPProcRun  *proc_run,
                   gpointer    user_data)
{
  WireMessage msg;

  msg.type = GP_PROC_RUN;
  msg.data = proc_run;

  if (! wire_write_msg (channel, &msg, user_data))
    return FALSE;
  if (! wire_flush (channel, user_data))
    return FALSE;
  return TRUE;
}

gboolean
gp_proc_return_write (GIOChannel   *channel,
		      GPProcReturn *proc_return,
                      gpointer      user_data)
{
  WireMessage msg;

  msg.type = GP_PROC_RETURN;
  msg.data = proc_return;

  if (! wire_write_msg (channel, &msg, user_data))
    return FALSE;
  if (! wire_flush (channel, user_data))
    return FALSE;
  return TRUE;
}

gboolean
gp_temp_proc_run_write (GIOChannel *channel,
			GPProcRun  *proc_run,
                        gpointer    user_data)
{
  WireMessage msg;

  msg.type = GP_TEMP_PROC_RUN;
  msg.data = proc_run;

  if (! wire_write_msg (channel, &msg, user_data))
    return FALSE;
  if (! wire_flush (channel, user_data))
    return FALSE;
  return TRUE;
}

gboolean
gp_temp_proc_return_write (GIOChannel   *channel,
			   GPProcReturn *proc_return,
                           gpointer      user_data)
{
  WireMessage msg;

  msg.type = GP_TEMP_PROC_RETURN;
  msg.data = proc_return;

  if (! wire_write_msg (channel, &msg, user_data))
    return FALSE;
  if (! wire_flush (channel, user_data))
    return FALSE;
  return TRUE;
}

gboolean
gp_proc_install_write (GIOChannel    *channel,
		       GPProcInstall *proc_install,
                       gpointer       user_data)
{
  WireMessage msg;

  msg.type = GP_PROC_INSTALL;
  msg.data = proc_install;

  if (! wire_write_msg (channel, &msg, user_data))
    return FALSE;
  if (! wire_flush (channel, user_data))
    return FALSE;
  return TRUE;
}

gboolean
gp_proc_uninstall_write (GIOChannel      *channel,
			 GPProcUninstall *proc_uninstall,
                         gpointer         user_data)
{
  WireMessage msg;

  msg.type = GP_PROC_UNINSTALL;
  msg.data = proc_uninstall;

  if (! wire_write_msg (channel, &msg, user_data))
    return FALSE;
  if (! wire_flush (channel, user_data))
    return FALSE;
  return TRUE;
}

gboolean
gp_extension_ack_write (GIOChannel *channel,
                        gpointer    user_data)
{
  WireMessage msg;

  msg.type = GP_EXTENSION_ACK;
  msg.data = NULL;

  if (! wire_write_msg (channel, &msg, user_data))
    return FALSE;
  if (! wire_flush (channel, user_data))
    return FALSE;
  return TRUE;
}

gboolean
gp_has_init_write (GIOChannel *channel,
                   gpointer    user_data)
{
  WireMessage msg;

  msg.type = GP_HAS_INIT;
  msg.data = NULL;

  if (! wire_write_msg (channel, &msg, user_data))
    return FALSE;
  if (! wire_flush (channel, user_data))
    return FALSE;
  return TRUE;
}

/*  quit  */

static void
_gp_quit_read (GIOChannel  *channel,
	       WireMessage *msg,
               gpointer     user_data)
{
}

static void
_gp_quit_write (GIOChannel  *channel,
		WireMessage *msg,
                gpointer     user_data)
{
}

static void
_gp_quit_destroy (WireMessage *msg)
{
}

/*  config  */

static void
_gp_config_read (GIOChannel  *channel,
		 WireMessage *msg,
                 gpointer     user_data)
{
  GPConfig *config;

  config = g_new (GPConfig, 1);

  if (! wire_read_int32 (channel, &config->version, 1, user_data))
    goto cleanup;
  if (! wire_read_int32 (channel, &config->tile_width, 1, user_data))
    goto cleanup;
  if (! wire_read_int32 (channel, &config->tile_height, 1, user_data))
    goto cleanup;
  if (! wire_read_int32 (channel, (guint32*) &config->shm_ID, 1, user_data))
    goto cleanup;
  if (! wire_read_double (channel, &config->gamma, 1, user_data))
    goto cleanup;
  if (! wire_read_int8 (channel, (guint8*) &config->install_cmap, 1, user_data))
    goto cleanup;
  if (! wire_read_int8 (channel, (guint8*) &config->unused, 1, user_data))
    goto cleanup;
  if (! wire_read_int32 (channel, (guint32*) &config->min_colors, 1, user_data))
    goto cleanup;
  if (! wire_read_int32 (channel, (guint32*) &config->gdisp_ID, 1, user_data))
    goto cleanup;

  msg->data = config;
  return;

 cleanup:
  g_free (config);
}

static void
_gp_config_write (GIOChannel  *channel,
		  WireMessage *msg,
                  gpointer     user_data)
{
  GPConfig *config;

  config = msg->data;
  if (! wire_write_int32 (channel, &config->version, 1, user_data))
    return;
  if (! wire_write_int32 (channel, &config->tile_width, 1, user_data))
    return;
  if (! wire_write_int32 (channel, &config->tile_height, 1, user_data))
    return;
  if (! wire_write_int32 (channel, (guint32*) &config->shm_ID, 1, user_data))
    return;
  if (! wire_write_double (channel, &config->gamma, 1, user_data))
    return;
  if (! wire_write_int8 (channel, (guint8*) &config->install_cmap, 1, user_data))
    return;
  if (! wire_write_int8 (channel, (guint8*) &config->unused, 1, user_data))
    return;
  if (! wire_write_int32 (channel, (guint32*) &config->min_colors, 1, user_data))
    return;
  if (! wire_write_int32 (channel, (guint32*) &config->gdisp_ID, 1, user_data))
    return;
}

static void
_gp_config_destroy (WireMessage *msg)
{
  g_free (msg->data);
}

/*  tile_req  */

static void
_gp_tile_req_read (GIOChannel  *channel,
		   WireMessage *msg,
                   gpointer     user_data)
{
  GPTileReq *tile_req;

  tile_req = g_new (GPTileReq, 1);

  if (! wire_read_int32 (channel, (guint32*) &tile_req->drawable_ID, 1,
                         user_data))
    goto cleanup;
  if (! wire_read_int32 (channel, &tile_req->tile_num, 1, user_data))
    goto cleanup;
  if (! wire_read_int32 (channel, &tile_req->shadow, 1, user_data))
    goto cleanup;

  msg->data = tile_req;
  return;

 cleanup:
  g_free (tile_req);
}

static void
_gp_tile_req_write (GIOChannel  *channel,
		    WireMessage *msg,
                    gpointer     user_data)
{
  GPTileReq *tile_req;

  tile_req = msg->data;
  if (! wire_write_int32 (channel, (guint32*) &tile_req->drawable_ID, 1,
                          user_data))
    return;
  if (! wire_write_int32 (channel, &tile_req->tile_num, 1, user_data))
    return;
  if (! wire_write_int32 (channel, &tile_req->shadow, 1, user_data))
    return;
}

static void
_gp_tile_req_destroy (WireMessage *msg)
{
  g_free (msg->data);
}

/*  tile_ack  */

static void
_gp_tile_ack_read (GIOChannel  *channel,
		   WireMessage *msg,
                   gpointer     user_data)
{
}

static void
_gp_tile_ack_write (GIOChannel  *channel,
		    WireMessage *msg,
                    gpointer     user_data)
{
}

static void
_gp_tile_ack_destroy (WireMessage *msg)
{
}

/*  tile_data  */

static void
_gp_tile_data_read (GIOChannel  *channel,
		    WireMessage *msg,
                    gpointer     user_data)
{
  GPTileData *tile_data;
  guint length;

  tile_data = g_new0 (GPTileData, 1);

  if (! wire_read_int32 (channel, (guint32*) &tile_data->drawable_ID, 1,
                         user_data))
    goto cleanup;
  if (! wire_read_int32 (channel, &tile_data->tile_num, 1, user_data))
    goto cleanup;
  if (! wire_read_int32 (channel, &tile_data->shadow, 1, user_data))
    goto cleanup;
  if (! wire_read_int32 (channel, &tile_data->bpp, 1, user_data))
    goto cleanup;
  if (! wire_read_int32 (channel, &tile_data->width, 1, user_data))
    goto cleanup;
  if (! wire_read_int32 (channel, &tile_data->height, 1, user_data))
    goto cleanup;
  if (! wire_read_int32 (channel, &tile_data->use_shm, 1, user_data))
    goto cleanup;

  if (!tile_data->use_shm)
    {
      length = tile_data->width * tile_data->height * tile_data->bpp;
      tile_data->data = g_new (guchar, length);

      if (! wire_read_int8 (channel, (guint8*) tile_data->data, length,
                            user_data))
	goto cleanup;
    }

  msg->data = tile_data;
  return;

 cleanup:
  g_free (tile_data->data);
  g_free (tile_data);
}

static void
_gp_tile_data_write (GIOChannel  *channel,
		     WireMessage *msg,
                     gpointer     user_data)
{
  GPTileData *tile_data;
  guint length;

  tile_data = msg->data;
  if (! wire_write_int32 (channel, (guint32*) &tile_data->drawable_ID, 1,
                          user_data))
    return;
  if (! wire_write_int32 (channel, &tile_data->tile_num, 1, user_data))
    return;
  if (! wire_write_int32 (channel, &tile_data->shadow, 1, user_data))
    return;
  if (! wire_write_int32 (channel, &tile_data->bpp, 1, user_data))
    return;
  if (! wire_write_int32 (channel, &tile_data->width, 1, user_data))
    return;
  if (! wire_write_int32 (channel, &tile_data->height, 1, user_data))
    return;
  if (! wire_write_int32 (channel, &tile_data->use_shm, 1, user_data))
    return;

  if (!tile_data->use_shm)
    {
      length = tile_data->width * tile_data->height * tile_data->bpp;
      if (! wire_write_int8 (channel, (guint8*) tile_data->data, length,
                             user_data))
	return;
    }
}

static void
_gp_tile_data_destroy (WireMessage *msg)
{
  GPTileData *tile_data;

  tile_data = msg->data;

  g_free (tile_data->data);
  g_free (tile_data);
}

/*  proc_run  */

static void
_gp_proc_run_read (GIOChannel  *channel,
		   WireMessage *msg,
                   gpointer     user_data)
{
  GPProcRun *proc_run;

  proc_run = g_new (GPProcRun, 1);

  if (! wire_read_string (channel, &proc_run->name, 1, user_data))
    goto cleanup;

  _gp_params_read (channel,
                   &proc_run->params, (guint*) &proc_run->nparams,
                   user_data);

  msg->data = proc_run;
  return;

 cleanup:
  g_free (proc_run);
}

static void
_gp_proc_run_write (GIOChannel  *channel,
		    WireMessage *msg,
                    gpointer     user_data)
{
  GPProcRun *proc_run;

  proc_run = msg->data;

  if (! wire_write_string (channel, &proc_run->name, 1, user_data))
    return;

  _gp_params_write (channel, proc_run->params, proc_run->nparams, user_data);
}

static void
_gp_proc_run_destroy (WireMessage *msg)
{
  GPProcRun *proc_run;

  proc_run = msg->data;
  _gp_params_destroy (proc_run->params, proc_run->nparams);

  g_free (proc_run->name);
  g_free (proc_run);
}

/*  proc_return  */

static void
_gp_proc_return_read (GIOChannel  *channel,
		      WireMessage *msg,
                      gpointer     user_data)
{
  GPProcReturn *proc_return;

  proc_return = g_new (GPProcReturn, 1);

  if (! wire_read_string (channel, &proc_return->name, 1, user_data))
    goto cleanup;

  _gp_params_read (channel,
                   &proc_return->params, (guint*) &proc_return->nparams,
                   user_data);

  msg->data = proc_return;
  return;

 cleanup:
  g_free (proc_return);
}

static void
_gp_proc_return_write (GIOChannel  *channel,
		       WireMessage *msg,
                       gpointer     user_data)
{
  GPProcReturn *proc_return;

  proc_return = msg->data;

  if (! wire_write_string (channel, &proc_return->name, 1, user_data))
    return;

  _gp_params_write (channel, proc_return->params, proc_return->nparams,
                    user_data);
}

static void
_gp_proc_return_destroy (WireMessage *msg)
{
  GPProcReturn *proc_return;

  proc_return = msg->data;
  _gp_params_destroy (proc_return->params, proc_return->nparams);

  g_free (proc_return->name);
  g_free (proc_return);
}

/*  temp_proc_run  */

static void
_gp_temp_proc_run_read (GIOChannel  *channel,
			WireMessage *msg,
                        gpointer     user_data)
{
  _gp_proc_run_read (channel, msg, user_data);
}

static void
_gp_temp_proc_run_write (GIOChannel  *channel,
			 WireMessage *msg,
                         gpointer     user_data)
{
  _gp_proc_run_write (channel, msg, user_data);
}

static void
_gp_temp_proc_run_destroy (WireMessage *msg)
{
  _gp_proc_run_destroy (msg);
}

/*  temp_proc_return  */

static void
_gp_temp_proc_return_read (GIOChannel  *channel,
			   WireMessage *msg,
                           gpointer     user_data)
{
  _gp_proc_return_read (channel, msg, user_data);
}

static void
_gp_temp_proc_return_write (GIOChannel  *channel,
			    WireMessage *msg,
                            gpointer     user_data)
{
  _gp_proc_return_write (channel, msg, user_data);
}

static void
_gp_temp_proc_return_destroy (WireMessage *msg)
{
  _gp_proc_return_destroy (msg);
}

/*  proc_install  */

static void
_gp_proc_install_read (GIOChannel  *channel,
		       WireMessage *msg,
                       gpointer     user_data)
{
  GPProcInstall *proc_install;
  gint i;

  proc_install = g_new0 (GPProcInstall, 1);

  if (! wire_read_string (channel, &proc_install->name, 1, user_data))
    goto cleanup;
  if (! wire_read_string (channel, &proc_install->blurb, 1, user_data))
    goto cleanup;
  if (! wire_read_string (channel, &proc_install->help, 1, user_data))
    goto cleanup;
  if (! wire_read_string (channel, &proc_install->author, 1, user_data))
    goto cleanup;
  if (! wire_read_string (channel, &proc_install->copyright, 1, user_data))
    goto cleanup;
  if (! wire_read_string (channel, &proc_install->date, 1, user_data))
    goto cleanup;
  if (! wire_read_string (channel, &proc_install->menu_path, 1, user_data))
    goto cleanup;
  if (! wire_read_string (channel, &proc_install->image_types, 1, user_data))
    goto cleanup;

  if (! wire_read_int32 (channel, &proc_install->type, 1, user_data))
    goto cleanup;
  if (! wire_read_int32 (channel, &proc_install->nparams, 1, user_data))
    goto cleanup;
  if (! wire_read_int32 (channel, &proc_install->nreturn_vals, 1, user_data))
    goto cleanup;

  proc_install->params = g_new0 (GPParamDef, proc_install->nparams);

  for (i = 0; i < proc_install->nparams; i++)
    {
      if (! wire_read_int32 (channel,
                             (guint32*) &proc_install->params[i].type, 1,
                             user_data))
	goto cleanup;
      if (! wire_read_string (channel,
                              &proc_install->params[i].name, 1,
                              user_data))
	goto cleanup;
      if (! wire_read_string (channel,
                              &proc_install->params[i].description, 1,
                              user_data))
	goto cleanup;
    }

  proc_install->return_vals = g_new0 (GPParamDef, proc_install->nreturn_vals);

  for (i = 0; i < proc_install->nreturn_vals; i++)
    {
      if (! wire_read_int32 (channel,
                             (guint32*) &proc_install->return_vals[i].type, 1,
                             user_data))
	goto cleanup;
      if (! wire_read_string (channel,
                              &proc_install->return_vals[i].name, 1,
                              user_data))
	goto cleanup;
      if (! wire_read_string (channel,
                              &proc_install->return_vals[i].description, 1,
                              user_data))
	goto cleanup;
    }

  msg->data = proc_install;
  return;

 cleanup:
  g_free (proc_install->name);
  g_free (proc_install->blurb);
  g_free (proc_install->help);
  g_free (proc_install->author);
  g_free (proc_install->copyright);
  g_free (proc_install->date);
  g_free (proc_install->menu_path);
  g_free (proc_install->image_types);

  if (proc_install->params)
    {
      for (i = 0; i < proc_install->nparams; i++)
	{
	  if (!proc_install->params[i].name)
	    break;

	  g_free (proc_install->params[i].name);
	  g_free (proc_install->params[i].description);
	}

      g_free (proc_install->params);
    }

  if (proc_install->return_vals)
    {
      for (i = 0; i < proc_install->nreturn_vals; i++)
	{
	  if (!proc_install->return_vals[i].name)
	    break;

	  g_free (proc_install->return_vals[i].name);
	  g_free (proc_install->return_vals[i].description);
	}

      g_free (proc_install->return_vals);
    }

  g_free (proc_install);
}

static void
_gp_proc_install_write (GIOChannel  *channel,
			WireMessage *msg,
                        gpointer     user_data)
{
  GPProcInstall *proc_install;
  gint i;

  proc_install = msg->data;

  if (! wire_write_string (channel, &proc_install->name, 1, user_data))
    return;
  if (! wire_write_string (channel, &proc_install->blurb, 1, user_data))
    return;
  if (! wire_write_string (channel, &proc_install->help, 1, user_data))
    return;
  if (! wire_write_string (channel, &proc_install->author, 1, user_data))
    return;
  if (! wire_write_string (channel, &proc_install->copyright, 1, user_data))
    return;
  if (! wire_write_string (channel, &proc_install->date, 1, user_data))
    return;
  if (! wire_write_string (channel, &proc_install->menu_path, 1, user_data))
    return;
  if (! wire_write_string (channel, &proc_install->image_types, 1, user_data))
    return;

  if (! wire_write_int32 (channel, &proc_install->type, 1, user_data))
    return;
  if (! wire_write_int32 (channel, &proc_install->nparams, 1, user_data))
    return;
  if (! wire_write_int32 (channel, &proc_install->nreturn_vals, 1, user_data))
    return;

  for (i = 0; i < proc_install->nparams; i++)
    {
      if (! wire_write_int32 (channel,
                              (guint32*) &proc_install->params[i].type, 1,
                              user_data))
	return;
      if (! wire_write_string (channel,
                               &proc_install->params[i].name, 1,
                               user_data))
	return;
      if (! wire_write_string (channel,
                               &proc_install->params[i].description, 1,
                               user_data))
	return;
    }

  for (i = 0; i < proc_install->nreturn_vals; i++)
    {
      if (! wire_write_int32 (channel,
                              (guint32*) &proc_install->return_vals[i].type, 1,
                              user_data))
	return;
      if (! wire_write_string (channel,
                               &proc_install->return_vals[i].name, 1,
                               user_data))
	return;
      if (! wire_write_string (channel,
                               &proc_install->return_vals[i].description, 1,
                               user_data))
	return;
    }
}

static void
_gp_proc_install_destroy (WireMessage *msg)
{
  GPProcInstall *proc_install;
  gint i;

  proc_install = msg->data;

  g_free (proc_install->name);
  g_free (proc_install->blurb);
  g_free (proc_install->help);
  g_free (proc_install->author);
  g_free (proc_install->copyright);
  g_free (proc_install->date);
  g_free (proc_install->menu_path);
  g_free (proc_install->image_types);

  for (i = 0; i < proc_install->nparams; i++)
    {
      g_free (proc_install->params[i].name);
      g_free (proc_install->params[i].description);
    }

  for (i = 0; i < proc_install->nreturn_vals; i++)
    {
      g_free (proc_install->return_vals[i].name);
      g_free (proc_install->return_vals[i].description);
    }

  g_free (proc_install->params);
  g_free (proc_install->return_vals);
  g_free (proc_install);
}

/*  proc_uninstall  */

static void
_gp_proc_uninstall_read (GIOChannel  *channel,
			 WireMessage *msg,
                         gpointer     user_data)
{
  GPProcUninstall *proc_uninstall;

  proc_uninstall = g_new (GPProcUninstall, 1);

  if (! wire_read_string (channel, &proc_uninstall->name, 1, user_data))
    goto cleanup;

  msg->data = proc_uninstall;
  return;

 cleanup:
  g_free (proc_uninstall);
}

static void
_gp_proc_uninstall_write (GIOChannel  *channel,
                          WireMessage *msg,
                          gpointer     user_data)
{
  GPProcUninstall *proc_uninstall;

  proc_uninstall = msg->data;

  if (! wire_write_string (channel, &proc_uninstall->name, 1, user_data))
    return;
}

static void
_gp_proc_uninstall_destroy (WireMessage *msg)
{
  GPProcUninstall *proc_uninstall;

  proc_uninstall = msg->data;

  g_free (proc_uninstall->name);
  g_free (proc_uninstall);
}

/*  extension_ack  */

static void
_gp_extension_ack_read (GIOChannel  *channel,
			WireMessage *msg,
                        gpointer     user_data)
{
}

static void
_gp_extension_ack_write (GIOChannel  *channel,
			 WireMessage *msg,
                         gpointer     user_data)
{
}

static void
_gp_extension_ack_destroy (WireMessage *msg)
{
}

/*  params  */

static void
_gp_params_read (GIOChannel  *channel,
		 GPParam    **params,
		 guint       *nparams,
                 gpointer     user_data)
{
  gint i, j;

  if (! wire_read_int32 (channel, (guint32*) nparams, 1, user_data))
    return;

  if (*nparams == 0)
    {
      *params = NULL;
      return;
    }

  *params = g_new (GPParam, *nparams);

  for (i = 0; i < *nparams; i++)
    {
      if (! wire_read_int32 (channel,
                             (guint32*) &(*params)[i].type, 1,
                             user_data))
	goto cleanup;

      switch ((*params)[i].type)
	{
	case GIMP_PDB_INT32:
	  if (! wire_read_int32 (channel,
                                 (guint32*) &(*params)[i].data.d_int32, 1,
                                 user_data))
	    goto cleanup;
	  break;

	case GIMP_PDB_INT16:
	  if (! wire_read_int16 (channel,
                                 (guint16*) &(*params)[i].data.d_int16, 1,
                                 user_data))
	    goto cleanup;
	  break;

	case GIMP_PDB_INT8:
	  if (! wire_read_int8 (channel,
                                (guint8*) &(*params)[i].data.d_int8, 1,
                                user_data))
	    goto cleanup;
	  break;

        case GIMP_PDB_FLOAT:
	  if (! wire_read_double (channel,
                                  &(*params)[i].data.d_float, 1,
                                  user_data))
	    goto cleanup;
          break;

        case GIMP_PDB_STRING:
	  if (! wire_read_string (channel,
                                  &(*params)[i].data.d_string, 1,
                                  user_data))
	    goto cleanup;
          break;

        case GIMP_PDB_INT32ARRAY:
	  (*params)[i].data.d_int32array =
	    g_new (gint32, (*params)[i-1].data.d_int32);
	  if (! wire_read_int32 (channel,
                                 (guint32*) (*params)[i].data.d_int32array,
                                 (*params)[i-1].data.d_int32,
                                 user_data))
	    {
	      g_free ((*params)[i].data.d_int32array);
	      goto cleanup;
	    }
          break;

        case GIMP_PDB_INT16ARRAY:
	  (*params)[i].data.d_int16array =
	    g_new (gint16, (*params)[i-1].data.d_int32);
	  if (! wire_read_int16 (channel,
                                 (guint16*) (*params)[i].data.d_int16array,
                                 (*params)[i-1].data.d_int32,
                                 user_data))
	    {
	      g_free ((*params)[i].data.d_int16array);
	      goto cleanup;
	    }
          break;

        case GIMP_PDB_INT8ARRAY:
	  (*params)[i].data.d_int8array =
	    g_new (gint8, (*params)[i-1].data.d_int32);
	  if (! wire_read_int8 (channel,
                                (guint8*) (*params)[i].data.d_int8array,
                                (*params)[i-1].data.d_int32,
                                user_data))
	    {
	      g_free ((*params)[i].data.d_int8array);
	      goto cleanup;
	    }
          break;

        case GIMP_PDB_FLOATARRAY:
	  (*params)[i].data.d_floatarray =
	    g_new (gdouble, (*params)[i-1].data.d_int32);
	  if (! wire_read_double (channel,
                                  (*params)[i].data.d_floatarray,
                                  (*params)[i-1].data.d_int32,
                                  user_data))
	    {
	      g_free ((*params)[i].data.d_floatarray);
	      goto cleanup;
	    }
          break;

        case GIMP_PDB_STRINGARRAY:
	  (*params)[i].data.d_stringarray =
	    g_new0 (gchar*, (*params)[i-1].data.d_int32);
	  if (! wire_read_string (channel,
                                  (*params)[i].data.d_stringarray,
                                  (*params)[i-1].data.d_int32,
                                  user_data))
	    {
	      for (j = 0; j < (*params)[i-1].data.d_int32; j++)
		g_free (((*params)[i].data.d_stringarray)[j]);
	      g_free ((*params)[i].data.d_stringarray);
	      goto cleanup;
	    }
          break;

        case GIMP_PDB_COLOR:
	  if (! wire_read_double (channel,
                                  &(*params)[i].data.d_color.r, 1,
                                  user_data))
	    goto cleanup;
	  if (! wire_read_double (channel,
                                  &(*params)[i].data.d_color.g, 1,
                                  user_data))
	    goto cleanup;
	  if (! wire_read_double (channel,
                                  &(*params)[i].data.d_color.b, 1,
                                  user_data))
	    goto cleanup;
	  if (! wire_read_double (channel,
                                  &(*params)[i].data.d_color.a, 1,
                                  user_data))
	    goto cleanup;
	  break;

        case GIMP_PDB_REGION:
          break;

        case GIMP_PDB_DISPLAY:
	  if (! wire_read_int32 (channel,
                                 (guint32*) &(*params)[i].data.d_display, 1,
                                 user_data))
	    goto cleanup;
          break;

        case GIMP_PDB_IMAGE:
	  if (! wire_read_int32 (channel,
                                 (guint32*) &(*params)[i].data.d_image, 1,
                                 user_data))
	    goto cleanup;
          break;

        case GIMP_PDB_LAYER:
	  if (! wire_read_int32 (channel,
                                 (guint32*) &(*params)[i].data.d_layer, 1,
                                 user_data))
	    goto cleanup;
          break;

        case GIMP_PDB_CHANNEL:
	  if (! wire_read_int32 (channel,
                                 (guint32*) &(*params)[i].data.d_channel, 1,
                                 user_data))
	    goto cleanup;
          break;

        case GIMP_PDB_DRAWABLE:
	  if (! wire_read_int32 (channel,
                                 (guint32*) &(*params)[i].data.d_drawable, 1,
                                 user_data))
	    goto cleanup;
          break;

        case GIMP_PDB_SELECTION:
	  if (! wire_read_int32 (channel,
                                 (guint32*) &(*params)[i].data.d_selection, 1,
                                 user_data))
	    goto cleanup;
          break;

        case GIMP_PDB_BOUNDARY:
	  if (! wire_read_int32 (channel,
                                 (guint32*) &(*params)[i].data.d_boundary, 1,
                                 user_data))
	    goto cleanup;
          break;

        case GIMP_PDB_PATH:
	  if (! wire_read_int32 (channel,
                                 (guint32*) &(*params)[i].data.d_path, 1,
                                 user_data))
	    goto cleanup;
          break;

        case GIMP_PDB_PARASITE:
	  if (! wire_read_string (channel,
                                  &(*params)[i].data.d_parasite.name, 1,
                                  user_data))
	    goto cleanup;
	  if ((*params)[i].data.d_parasite.name == NULL)
	    {
	      /* we have a null parasite */
	      (*params)[i].data.d_parasite.data = NULL;
	      break;
	    }
	  if (! wire_read_int32 (channel,
                                 &((*params)[i].data.d_parasite.flags), 1,
                                 user_data))
	    goto cleanup;
	  if (! wire_read_int32 (channel,
                                 &((*params)[i].data.d_parasite.size), 1,
                                 user_data))
	    goto cleanup;
	  if ((*params)[i].data.d_parasite.size > 0)
	    {
	      (*params)[i].data.d_parasite.data = g_malloc ((*params)[i].data.d_parasite.size);
	      if (! wire_read_int8 (channel,
                                    (*params)[i].data.d_parasite.data,
                                    (*params)[i].data.d_parasite.size,
                                    user_data))
		{
		  g_free ((*params)[i].data.d_parasite.data);
		  goto cleanup;
		}
	    }
	  else
	    (*params)[i].data.d_parasite.data = NULL;
	  break;

        case GIMP_PDB_STATUS:
	  if (! wire_read_int32 (channel,
                                 (guint32*) &(*params)[i].data.d_status, 1,
                                 user_data))
	    goto cleanup;
          break;

	case GIMP_PDB_END:
	  break;
	}
    }

  return;

 cleanup:
  *nparams = 0;
  g_free (*params);
  *params = NULL;
}

static void
_gp_params_write (GIOChannel *channel,
		  GPParam    *params,
		  gint        nparams,
                  gpointer    user_data)
{
  gint i;

  if (! wire_write_int32 (channel, (guint32*) &nparams, 1, user_data))
    return;

  for (i = 0; i < nparams; i++)
    {
      if (! wire_write_int32 (channel,
                              (guint32*) &params[i].type, 1,
                              user_data))
	return;

      switch (params[i].type)
	{
	case GIMP_PDB_INT32:
	  if (! wire_write_int32 (channel,
                                  (guint32*) &params[i].data.d_int32, 1,
                                  user_data))
	    return;
	  break;

	case GIMP_PDB_INT16:
	  if (! wire_write_int16 (channel,
                                  (guint16*) &params[i].data.d_int16, 1,
                                  user_data))
	    return;
	  break;

	case GIMP_PDB_INT8:
	  if (! wire_write_int8 (channel,
                                 (guint8*) &params[i].data.d_int8, 1,
                                 user_data))
	    return;
	  break;

        case GIMP_PDB_FLOAT:
	  if (! wire_write_double (channel,
                                   &params[i].data.d_float, 1,
                                   user_data))
	    return;
          break;

        case GIMP_PDB_STRING:
	  if (! wire_write_string (channel,
                                   &params[i].data.d_string, 1,
                                   user_data))
	    return;
          break;

        case GIMP_PDB_INT32ARRAY:
	  if (! wire_write_int32 (channel,
                                  (guint32*) params[i].data.d_int32array,
                                  params[i-1].data.d_int32,
                                  user_data))
	    return;
          break;

        case GIMP_PDB_INT16ARRAY:
	  if (! wire_write_int16 (channel,
                                  (guint16*) params[i].data.d_int16array,
                                  params[i-1].data.d_int32,
                                  user_data))
	    return;
          break;

        case GIMP_PDB_INT8ARRAY:
	  if (! wire_write_int8 (channel,
                                 (guint8*) params[i].data.d_int8array,
                                 params[i-1].data.d_int32,
                                 user_data))
	    return;
          break;

        case GIMP_PDB_FLOATARRAY:
	  if (! wire_write_double (channel,
                                   params[i].data.d_floatarray,
                                   params[i-1].data.d_int32,
                                   user_data))
	    return;
          break;

        case GIMP_PDB_STRINGARRAY:
	  if (! wire_write_string (channel,
                                   params[i].data.d_stringarray,
                                   params[i-1].data.d_int32,
                                   user_data))
	    return;
          break;

        case GIMP_PDB_COLOR:
	  {
	    GimpRGB *color = (GimpRGB *) &params[i].data.d_color;
	    if (! wire_write_double (channel, &color->r, 1, user_data))
	      return;
	    if (! wire_write_double (channel, &color->g, 1, user_data))
	      return;
	    if (! wire_write_double (channel, &color->b, 1, user_data))
	      return;
	    if (! wire_write_double (channel, &color->a, 1, user_data))
	      return;
	  }
          break;

        case GIMP_PDB_REGION:
          break;

        case GIMP_PDB_DISPLAY:
	  if (! wire_write_int32 (channel,
                                  (guint32*) &params[i].data.d_display, 1,
                                  user_data))
	    return;
          break;

        case GIMP_PDB_IMAGE:
	  if (! wire_write_int32 (channel,
                                  (guint32*) &params[i].data.d_image, 1,
                                  user_data))
	    return;
          break;

        case GIMP_PDB_LAYER:
	  if (! wire_write_int32 (channel,
                                  (guint32*) &params[i].data.d_layer, 1,
                                  user_data))
	    return;
          break;

        case GIMP_PDB_CHANNEL:
	  if (! wire_write_int32 (channel,
                                  (guint32*) &params[i].data.d_channel, 1,
                                  user_data))
	    return;
          break;

        case GIMP_PDB_DRAWABLE:
	  if (! wire_write_int32 (channel,
                                  (guint32*) &params[i].data.d_drawable, 1,
                                  user_data))
	    return;
          break;

        case GIMP_PDB_SELECTION:
	  if (! wire_write_int32 (channel,
                                  (guint32*) &params[i].data.d_selection, 1,
                                  user_data))
	    return;
          break;

        case GIMP_PDB_BOUNDARY:
	  if (! wire_write_int32 (channel,
                                  (guint32*) &params[i].data.d_boundary, 1,
                                  user_data))
	    return;
          break;

        case GIMP_PDB_PATH:
	  if (! wire_write_int32 (channel,
                                  (guint32*) &params[i].data.d_path, 1,
                                  user_data))
	    return;
          break;

        case GIMP_PDB_PARASITE:
	  {
	    GimpParasite *p = (GimpParasite *) &params[i].data.d_parasite;
	    if (p->name == NULL)
	      {
		/* write a null string to signifly a null parasite */
		wire_write_string (channel,  &p->name, 1, user_data);
		break;
	      }
	    if (! wire_write_string (channel, &p->name, 1, user_data))
	      return;
	    if (! wire_write_int32 (channel, &p->flags, 1, user_data))
	      return;
	    if (! wire_write_int32 (channel, &p->size, 1, user_data))
	      return;
	    if (p->size > 0)
	      {
		if (! wire_write_int8 (channel, p->data, p->size, user_data))
		  return;
	      }
	  }
	  break;

        case GIMP_PDB_STATUS:
	  if (! wire_write_int32 (channel,
                                  (guint32*) &params[i].data.d_status, 1,
                                  user_data))
	    return;
          break;

	case GIMP_PDB_END:
	  break;
	}
    }
}

void
_gp_params_destroy (GPParam *params,
		    gint     nparams)
{
  gint count;
  gint i, j;

  for (i = 0; i < nparams; i++)
    {
      switch (params[i].type)
	{
	case GIMP_PDB_INT32:
	case GIMP_PDB_INT16:
	case GIMP_PDB_INT8:
	case GIMP_PDB_FLOAT:
	case GIMP_PDB_COLOR:
	case GIMP_PDB_REGION:
	case GIMP_PDB_DISPLAY:
	case GIMP_PDB_IMAGE:
	case GIMP_PDB_LAYER:
	case GIMP_PDB_CHANNEL:
	case GIMP_PDB_DRAWABLE:
	case GIMP_PDB_SELECTION:
	case GIMP_PDB_BOUNDARY:
	case GIMP_PDB_PATH:
	case GIMP_PDB_STATUS:
	  break;

	case GIMP_PDB_STRING:
	  g_free (params[i].data.d_string);
	  break;

	case GIMP_PDB_INT32ARRAY:
	  g_free (params[i].data.d_int32array);
	  break;

	case GIMP_PDB_INT16ARRAY:
	  g_free (params[i].data.d_int16array);
	  break;

	case GIMP_PDB_INT8ARRAY:
	  g_free (params[i].data.d_int8array);
	  break;

	case GIMP_PDB_FLOATARRAY:
	  g_free (params[i].data.d_floatarray);
	  break;

	case GIMP_PDB_STRINGARRAY:
	  if ((i > 0) && (params[i-1].type == GIMP_PDB_INT32))
	    {
	      count = params[i-1].data.d_int32;
	      for (j = 0; j < count; j++)
		g_free (params[i].data.d_stringarray[j]);
	      g_free (params[i].data.d_stringarray);
	    }
	  break;

	case GIMP_PDB_PARASITE:
	  if (params[i].data.d_parasite.name)
	    g_free(params[i].data.d_parasite.name);
	  if (params[i].data.d_parasite.data)
	    g_free(params[i].data.d_parasite.data);
	  break;

	case GIMP_PDB_END:
	  break;
	}
    }

  g_free (params);
}

/* has_init */

static void
_gp_has_init_read (GIOChannel  *channel,
	           WireMessage *msg,
                   gpointer     user_data)
{
}

static void
_gp_has_init_write (GIOChannel  *channel,
	     	    WireMessage *msg,
                    gpointer     user_data)
{
}

static void
_gp_has_init_destroy (WireMessage *msg)
{
}


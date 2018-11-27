/*
 *  Copyright (C) 2017-2018 Emmanuel Fleury <emmanuel.fleury@u-bordeaux.fr>
 *
 * This source file is part of Gtk-boilerplate.
 *
 * Gtk-boilerplate is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Gtk-boilerplate is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Gtk-boilerplate. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "config.h"
#include "main_window.h"

/* Global variables */
GSList *cmd_line_file_list;

/* Call-back to handle a local option on command line */
static gint
handle_local_options (GApplication __unused * app, GVariantDict * options)
{
  /* Handling the '--version'/'-V' option */
  if (g_variant_dict_contains (options, "version"))
    {
      fprintf (stdout, "%s - Version %s\n", PROG_NAME, PROG_VERSION);
      return RETURN_SUCCESS;
    }

  return RETURN_FAILURE;
}

/* Call-back to setup application when run by the Desktop environment */
static void
activate_main_window (GApplication * app)
{
  GtkWidget * window = main_window_new (app);
  /* Display the window and its content */
  gtk_widget_show_all (window);
}

/* Call-back to open a file from a file browser */
static void
open_cmdline (GtkApplication __unused * app)
{
  g_print ("Open\n");
}

int
main (int argc, char **argv)
{
  /* Create a non-unique application */
  GtkApplication *app =
    gtk_application_new ("com.github.perror.gtk-boilerplate",
			 G_APPLICATION_NON_UNIQUE |
			 G_APPLICATION_HANDLES_OPEN);

  /* Connect call-backs on signals */
  g_signal_connect (G_APPLICATION (app), "activate",
		    G_CALLBACK (activate_main_window), NULL);
  g_signal_connect (G_APPLICATION (app), "handle-local-options",
		    G_CALLBACK (handle_local_options), NULL);
  g_signal_connect (G_APPLICATION(app), "open",
		    G_CALLBACK (open_cmdline), NULL);

  /* Adding custom options to command-line */
  const GOptionEntry options[] = {
    {"version", 'V', 0, G_OPTION_ARG_NONE, NULL,
     "Show application's version", NULL},
    {NULL}
  };
  g_application_add_main_option_entries (G_APPLICATION (app), options);

  /* Starting the application */
  int status = g_application_run (G_APPLICATION (app), argc, argv);

  /* Free memory on quit */
  g_object_unref (app);

  return status;
}

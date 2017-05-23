/*
 *  Copyright (C) 2017 Emmanuel Fleury <emmanuel.fleury@u-bordeaux.fr>
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

/* Global variables */
GSList *cmd_line_file_list;

/* Call-back to handle a local option on command line */
static gint
handle_local_options (GApplication __unused *app,
		      GVariantDict *options)
{
  /* Handling the '--version' option */
  if (g_variant_dict_contains (options, "version"))
    {
      fprintf (stdout, "%s - Version %s\n", PROG_NAME, PROG_VERSION);
      return RETURN_SUCCESS;
    }

  return RETURN_FAILURE;
}

/* Call-back to quit the application */
static void
quit (GtkApplication __unused * app)
{
  g_print("Quit\n");
}

/* Call-back to call the 'about' modal window of the application */
static void
about (GtkApplication __unused * app)
{
  g_print("About\n");
}

/* Call-back to setup application when run by the Desktop environment */
static void
activate (GApplication * app)
{
  /* Initializing the main window */
  GtkWidget *window = gtk_application_window_new (GTK_APPLICATION (app));
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  /* Setting main box */
  GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window), main_box);

  /* Adding a menubar to the main window */
  GtkWidget *menubar = gtk_menu_bar_new();
  gtk_box_pack_start(GTK_BOX(main_box), menubar, FALSE, FALSE, 0);

  /* Adding a 'File' menu */
  GtkWidget *file_menu = gtk_menu_new();
  GtkWidget *file_menu_content = gtk_menu_item_new_with_label("File");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_content), file_menu);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_menu_content);

  /* Adding a 'File->Open' submenu */
  GtkWidget *file_menu_open = gtk_menu_item_new_with_label("Open");
  gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_menu_open);

  /* Adding a 'File->Preferences' submenu */
  GtkWidget *file_menu_prefs = gtk_menu_item_new_with_label("Preferences");
  gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_menu_prefs);

  /* Adding a separator in the menu */
  GtkWidget *file_menu_sep = gtk_separator_menu_item_new();
  gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_menu_sep);

  /* Adding a 'File->Quit' submenu */
  GtkWidget *file_menu_quit = gtk_menu_item_new_with_label("Quit");
  gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_menu_quit);
  g_signal_connect (file_menu_quit, "activate", G_CALLBACK (quit), app);

  /* Adding a 'Help' menu */
  GtkWidget *help_menu = gtk_menu_new();
  GtkWidget *help_menu_content = gtk_menu_item_new_with_label("Help");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_menu_content), help_menu);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help_menu_content);

  /* Adding a 'Help->About' submenu */
  GtkWidget *help_menu_quit = gtk_menu_item_new_with_label("About");
  gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), help_menu_quit);
  g_signal_connect (help_menu_quit, "activate", G_CALLBACK (about), app);


  /* Display the window and its content */
  gtk_widget_show_all (window);
}

/* Call-back to open a file from a file browser */
static void
open (GtkApplication __unused * app)
{
  g_print("Open\n");
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
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  g_signal_connect (app, "handle-local-options",
		    G_CALLBACK (handle_local_options), NULL);
  g_signal_connect (app, "open", G_CALLBACK (open), NULL);

  /* Adding custom options to command-line */
  const GOptionEntry options[] =
    {
      {
	"version", 'V', 0, G_OPTION_ARG_NONE, NULL,
	"Show application's version", NULL
      },
      { NULL }
    };

  g_application_add_main_option_entries (G_APPLICATION (app), options);

  /* Starting the application */
  int status = g_application_run (G_APPLICATION (app), argc, argv);

  /* Free memory on quit */
  g_object_unref (app);

  return status;
}

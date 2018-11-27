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

#include "main_window.h"

#include "config.h"

static GtkWidget * main_window;


/* Call-back to quit the application */
static void
quit (GtkWidget __unused * gtk_menu_item, GApplication * app)
{
  /* Setting the quit dialog window */
  GtkWidget *quit_dialog = gtk_dialog_new();
  gtk_window_set_transient_for (GTK_WINDOW(quit_dialog),
				GTK_WINDOW(main_window));
  gtk_window_set_title (GTK_WINDOW (quit_dialog), "Closing Confirmation");
  gtk_window_set_modal (GTK_WINDOW (quit_dialog), TRUE);
  gtk_window_set_destroy_with_parent (GTK_WINDOW (quit_dialog), TRUE);
  gtk_dialog_add_button (GTK_DIALOG (quit_dialog),
			 "Close", GTK_RESPONSE_ACCEPT);
  gtk_dialog_add_button (GTK_DIALOG (quit_dialog),
			 "Cancel", GTK_RESPONSE_REJECT);

  GtkWidget * content_area =
    gtk_dialog_get_content_area (GTK_DIALOG (quit_dialog));
  GtkWidget * label = gtk_label_new ("Would you like to close ?");
  gtk_container_add (GTK_CONTAINER (content_area), label);
  gtk_box_set_spacing (GTK_BOX(content_area), 10);
  gtk_widget_show_all (quit_dialog);

  gint result = gtk_dialog_run (GTK_DIALOG (quit_dialog));
  switch (result)
    {
      /* Confirm closing */
    case GTK_RESPONSE_ACCEPT:
      g_application_quit (G_APPLICATION(app));
      break;

    case GTK_RESPONSE_REJECT:
    default:
      /* Cancel closing, do nothing */
      break;
    }

  gtk_widget_destroy(quit_dialog);
  //  g_application_quit (app);
}

/* Call-back to call the 'about' modal window of the application */
static void
about (GtkApplication __unused * app)
{
  g_print ("About\n");
}

GtkWidget *
main_window_new (GApplication * app)
{
    /* Initializing the main window */
  main_window = gtk_application_window_new (GTK_APPLICATION (app));
  gtk_window_set_title (GTK_WINDOW (main_window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (main_window), 200, 200);

  /* Setting main box */
  GtkWidget *main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER (main_window), main_box);

  /* Adding a menubar to the main window */
  GtkWidget *menubar = gtk_menu_bar_new ();
  gtk_box_pack_start (GTK_BOX (main_box), menubar, FALSE, FALSE, 0);

  /* Adding a 'File' menu */
  GtkWidget *file_menu = gtk_menu_new ();
  GtkWidget *file_menu_content = gtk_menu_item_new_with_label ("File");
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (file_menu_content), file_menu);
  gtk_menu_shell_append (GTK_MENU_SHELL (menubar), file_menu_content);

  /* Adding a 'File->Open' submenu */
  GtkWidget *file_menu_open = gtk_menu_item_new_with_label ("Open");
  gtk_menu_shell_append (GTK_MENU_SHELL (file_menu), file_menu_open);

  /* Adding a 'File->Preferences' submenu */
  GtkWidget *file_menu_prefs = gtk_menu_item_new_with_label ("Preferences");
  gtk_menu_shell_append (GTK_MENU_SHELL (file_menu), file_menu_prefs);

  /* Adding a separator in the menu */
  GtkWidget *file_menu_sep = gtk_separator_menu_item_new ();
  gtk_menu_shell_append (GTK_MENU_SHELL (file_menu), file_menu_sep);

  /* Adding a 'File->Quit' submenu */
  GtkWidget *file_menu_quit = gtk_menu_item_new_with_label ("Quit");
  gtk_menu_shell_append (GTK_MENU_SHELL (file_menu), file_menu_quit);
  g_signal_connect (file_menu_quit, "activate", G_CALLBACK (quit), app);

  /* Adding a 'Help' menu */
  GtkWidget *help_menu = gtk_menu_new ();
  GtkWidget *help_menu_content = gtk_menu_item_new_with_label ("Help");
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (help_menu_content), help_menu);
  gtk_menu_shell_append (GTK_MENU_SHELL (menubar), help_menu_content);

  /* Adding a 'Help->About' submenu */
  GtkWidget *help_menu_about = gtk_menu_item_new_with_label ("About");
  gtk_menu_shell_append (GTK_MENU_SHELL (help_menu), help_menu_about);
  g_signal_connect (help_menu_about, "activate", G_CALLBACK (about), app);

  return main_window;
}

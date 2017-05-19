#
# Copyright (C) 2017 Emmanuel Fleury <emmanuel.fleury@u-bordeaux.fr>
#
# This CMake file is part of Gtk-boilerplate.
#
# Gtk-boilerplate is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# Gtk-boilerplate is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Gtk-boilerplate. If not, see <http://www.gnu.org/licenses/>.

# Setup the main executable
set(SRC_LIST gtk-boilerplate.c)
add_executable(gtk-boilerplate ${SRC_LIST})

# Link the main target
target_link_libraries(gtk-boilerplate ${GLIB_LIBRARY_DIRS} ${GTK3_LIBRARIES})


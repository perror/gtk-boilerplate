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

# Configuration file
configure_file(config.h.in config.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Main executable
set(EXEC gtk-boilerplate)

# Setup the main executable
set(SRC_LIST
  gtk-boilerplate.c
  main_window.c)
add_executable(${EXEC} ${SRC_LIST})

# Link the main target
target_link_libraries(${EXEC} ${GLIB_LIBRARY_DIRS} ${GTK3_LIBRARIES})

# Copy final executable in build root directory
add_custom_command(TARGET ${EXEC}
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E
		   copy $<TARGET_FILE:${EXEC}> ${PROJECT_BINARY_DIR})
# Cleaning it
set_property(DIRECTORY PROPERTY
             ADDITIONAL_MAKE_CLEAN_FILES ${PROJECT_BINARY_DIR}/gtk-boilerplate)

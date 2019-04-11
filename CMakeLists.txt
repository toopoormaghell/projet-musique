cmake_minimum_required(VERSION 3.13.4)

##
## PROJECT
##
project(projet-musique VERSION 0.0.1 LANGUAGES CXX)

##
## PARAMETERS
##
# Set a cache variable with the path to Qt5 root directory
set(QT_ROOT_DIRECTORY "C:/Qt/5.12.2/mingw73_64" CACHE PATH "Root directory for Qt" FORCE)
# Define the output directories for binaries (.exe and .dll on Windows, binaries on Linux)
include(GNUInstallDirs)
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/stage/${CMAKE_INSTALL_BINDIR})
endif()
# Define the output directories for libraries (.lib on Windows, .so on Linux)
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/stage/${CMAKE_INSTALL_LIBDIR})
endif()
# Define the output directories for archives (.a on Linux)
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/stage/${CMAKE_INSTALL_LIBDIR})
endif()

##
## EXTERNAL SOURCES
##
add_subdirectory(external)

##
## INTERNAL SOURCES
##
add_subdirectory(src)

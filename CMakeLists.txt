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
##
## EXTERNAL SOURCES
##
add_subdirectory(external)

##
## INTERNAL SOURCES
##
add_subdirectory(src)

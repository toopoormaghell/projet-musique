cmake_minimum_required(VERSION 3.13.4)

##
## PROJECT
##
project(projet-musique VERSION 0.0.1 LANGUAGES CXX)

##
## EXTERNAL SOURCES
##
add_subdirectory(external)

##
## INTERNAL SOURCES
##
add_subdirectory(src)

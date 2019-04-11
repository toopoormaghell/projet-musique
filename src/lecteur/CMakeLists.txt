##
## List all headers of the library
##
set(HEADERS_LIST dialogcontroles.h
                 mainwindowlecteur.h
                 playermanager.h)

##
## List all source files of the library
##
set(SOURCES_LIST dialogcontroles.cpp
                 mainwindowlecteur.cpp
                 playermanager.cpp)

##
## List all form files of the library
##
set(FORMS_LIST dialogcontroles.ui
               playermanager.ui
               mainwindowlecteur.ui)

##
## List all resource files of the library
##
set(RESOURCES_LIST iconeslecteur.qrc)

##
## Set options to process files with moc, uic or rcc automatically
## In order to find generated moc_* or ui_* file, current directory
## must be in the list of include directories.
##
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

##
## Create the target for the library
##
add_library(lecteur SHARED ${SOURCES_LIST} ${HEADERS_LIST} ${FORMS_LIST} ${RESOURCES_LIST})

##
## Add current directory to the list of included directories
##
target_include_directories(lecteur PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

##
## Add necessary dependencies
##
list(APPEND CMAKE_PREFIX_PATH ${QT_ROOT_DIRECTORY}/lib/cmake)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Multimedia Widgets)
target_link_libraries(lecteur PUBLIC taglib Qt5::Core Qt5::Gui Qt5::Multimedia Qt5::Widgets)

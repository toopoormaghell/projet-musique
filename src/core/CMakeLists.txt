##
## List all headers of the library
##
set(HEADERS_LIST bddafficherartiste.h
                 bddafficherliste.h
                 bddaffichermp3.h
                 bddafficherphys.h
                 bddgestionmp3.h
                 bddgestionphys.h
                 bddlecteur.h
                 DialogAjouterPhys.h
                 DialogAjoutTitre.h
                 dialogalbumssmp3.h
                 dialogchoixpochette.h
                 dialogconfigactu.h
                 DialogModifierAlbum.h
                 DialogModifierArtiste.h
                 dialogverifications.h
                 DialogVidageBDD.h
                 mainwindow.h
                 mp3remover.h
                 ongletartiste.h
                 ongleterreurs.h
                 ongletliste.h
                 ongletmp3.h
                 ongletphys.h
                 ongletrech.h
                 ongletstats.h)

##
## List all source files of the library
##
set(SOURCES_LIST bddafficherartiste.cpp
                 bddafficherliste.cpp
                 bddaffichermp3.cpp
                 bddafficherphys.cpp
                 bddgestionmp3.cpp
                 bddgestionphys.cpp
                 bddlecteur.cpp
                 DialogAjouterPhys.cpp
                 DialogAjoutTitre.cpp
                 dialogalbumssmp3.cpp
                 dialogchoixpochette.cpp
                 dialogconfigactu.cpp
                 DialogModifierAlbum.cpp
                 DialogModifierArtiste.cpp
                 dialogverifications.cpp
                 DialogVidageBDD.cpp
                 main.cpp
                 mainwindow.cpp
                 mp3remover.cpp
                 ongletartiste.cpp
                 ongleterreurs.cpp
                 ongletliste.cpp
                 ongletmp3.cpp
                 ongletphys.cpp
                 ongletrech.cpp
                 ongletstats.cpp)

##
## List all form files of the library
##
set(FORMS_LIST DialogAjouterPhys.ui
               DialogAjoutTitre.ui
               dialogalbumssmp3.ui
               DialogChoixAlbumPhys.ui
               dialogchoixpochette.ui
               dialogconfigactu.ui
               DialogModifierAlbum.ui
               DialogModifierArtiste.ui
               dialogverifications.ui
               DialogVidageBDD.ui
               mainwindow.ui
               ongletartiste.ui
               ongleterreurs.ui
               ongletliste.ui
               ongletmp3.ui
               ongletphys.ui
               ongletrech.ui
               ongletstats.ui)

##
## List all resource files of the library
##
set(RESOURCES_LIST IconesMenu.qrc)

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
add_executable(core ${SOURCES_LIST} ${HEADERS_LIST} ${FORMS_LIST} ${RESOURCES_LIST})

##
## Add current directory to the list of included directories
##
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

##
## Add necessary dependencies
##
list(APPEND CMAKE_PREFIX_PATH C:/Qt/5.12.1/mingw73_64/lib/cmake)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Multimedia Network Sql Widgets WinExtras)
target_link_libraries(core PUBLIC bdd
                                  helpers
                                  lecteur
                                  qawswrapper
                                  taglib
                                  Qt5::Core
                                  Qt5::Gui
                                  Qt5::Multimedia
                                  Qt5::Network
                                  Qt5::Sql
                                  Qt5::Widgets
                                  Qt5::WinExtras)

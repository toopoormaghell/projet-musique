##
## List all headers of the library
##
set(HEADERS_LIST bdd_global.h
                 bddalbum.h
                 bddartiste.h
                 bddconfig.h
                 bdderreurs.h
                 bddmp3.h
                 bddphys.h
                 bddpoch.h
                 bddrech.h
                 bddrelation.h
                 bddsingleton.h
                 bddstats.h
                 bddsupport.h
                 bddtitre.h
                 bddtype.h
                 changementversion.h
                 gestionverifications.h
                 idowner.h
                 meta_album.h
                 meta_artiste.h
                 meta_titre.h
                 outilsbdd.h
                 tags.h)

##
## List all source files of the library
##
set(SOURCES_LIST bddalbum.cpp
                 bddartiste.cpp
                 bddconfig.cpp
                 bdderreurs.cpp
                 bddmp3.cpp
                 bddphys.cpp
                 bddpoch.cpp
                 bddrech.cpp
                 bddrelation.cpp
                 bddsingleton.cpp
                 bddstats.cpp
                 bddsupport.cpp
                 bddtitre.cpp
                 bddtype.cpp
                 changementversion.cpp
                 gestionverifications.cpp
                 idowner.cpp
                 meta_album.cpp
                 meta_artiste.cpp
                 meta_titre.cpp
                 outilsbdd.cpp
                 tags.cpp)

##
## Set options to process files with moc, uic or rcc automatically
## In order to find generated moc_* or ui_* file, current directory
## must be in the list of include directories.
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

##
## Create the target for the library
##
add_library(bdd SHARED ${SOURCES_LIST} ${HEADERS_LIST})

##
## Define some preprocessor definitions
##
target_compile_definitions(bdd PRIVATE BDD_LIBRARY)

##
## Add current directory to the list of included directories
##
target_include_directories(bdd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

##
## Add necessary dependencies
##
list(APPEND CMAKE_PREFIX_PATH C:/Qt/5.12.1/mingw73_64/lib/cmake)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Sql Widgets)
target_link_libraries(bdd PUBLIC helpers taglib Qt5::Core Qt5::Gui Qt5::Sql Qt5::Widgets)

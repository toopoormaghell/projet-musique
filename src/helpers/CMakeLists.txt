##
## List all headers of the library
##
set(HEADERS_LIST handable.h
                 handle.h
                 handle_impl.h
                 helpers_global.h
                 util.h)

##
## List all source files of the library
##
set(SOURCES_LIST handable.cpp
                 util.cpp)

##
## Create the target for the library
##
add_library(helpers SHARED ${SOURCES_LIST} ${HEADERS_LIST})

##
## Define some preprocessor definitions
##
target_compile_definitions(helpers PRIVATE HELPERS_LIBRARY)

##
## Add current directory to the list of included directories
##
target_include_directories(helpers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

##
## Add necessary dependencies
##
list(APPEND CMAKE_PREFIX_PATH C:/Qt/5.12.1/mingw73_64/lib/cmake)
find_package(Qt5 REQUIRED COMPONENTS Core Gui)
target_link_libraries(helpers PUBLIC Qt5::Core Qt5::Gui)

##
## Initiate a testing environment
##
enable_testing()

##
## List all headers of the library
##
set(HEADERS_LIST "")

##
## List all source files of the library
##
set(SOURCES_LIST DiscogsTests.cpp)

##
## List all form files of the library
##
set(FORMS_LIST "")

##
## List all resource files of the library
##
set(RESOURCES_LIST "")

##
## Set options to process files with moc, uic or rcc automatically
## In order to find generated moc_* or ui_* file, current directory
## must be in the list of include directories.
##
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)

##
## Create the target for the executable
##
add_executable(discinfotests ${SOURCES_LIST} ${HEADERS_LIST} ${FORMS_LIST} ${RESOURCES_LIST})
add_test(discinfotests discinfotests)

##
## Generate export header file for symbols visibility
##
#include(GenerateExportHeader)
#generate_export_header(discinfo)

##
## Add current directory to the list of included directories
##
#target_include_directories(discinfo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

##
## Add necessary dependencies
##
list(APPEND CMAKE_PREFIX_PATH ${QT_ROOT_DIRECTORY}/lib/cmake)
find_package(Qt5 REQUIRED COMPONENTS Test)
target_link_libraries(discinfotests PUBLIC discinfo
                                           Qt5::Test)

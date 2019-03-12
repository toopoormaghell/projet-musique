##
## List all headers of the library
##
set(HEADERS_LIST QAWSGlobalInfo.h
                 QAWSWrapper.h
                 QAWSWrapper_global.h
                 QAWSWrapperNotifier.h)

##
## List all source files of the library
##
set(SOURCES_LIST QAWSWrapper.cpp
                 QAWSWrapperNotifier.cpp)

##
## Set options to process files with moc, uic or rcc automatically
## In order to find generated moc_* or ui_* file, current directory
## must be in the list of include directories.
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

##
## Create the target for the library
##
add_library(qawswrapper SHARED ${SOURCES_LIST} ${HEADERS_LIST})

##
## Define some preprocessor definitions
##
target_compile_definitions(qawswrapper PRIVATE QAWSWRAPPER_LIBRARY)

##
## Add current directory to the list of included directories
##
target_include_directories(qawswrapper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

##
## Add necessary dependencies
##
list(APPEND CMAKE_PREFIX_PATH C:/Qt/5.12.1/mingw73_64/lib/cmake)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Network)
target_link_libraries(qawswrapper PUBLIC bdd helpers Qt5::Core Qt5::Gui Qt5::Network)

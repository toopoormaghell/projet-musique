# Install script for directory: H:/MUSIQUE/taglib-1.8/taglib

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/taglib")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files (x86)/taglib/lib/libtag.dll.a")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "C:/Program Files (x86)/taglib/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "H:/MUSIQUE/taglib-1.8/taglib/libtag.dll.a")
  IF(EXISTS "$ENV{DESTDIR}/C:/Program Files (x86)/taglib/lib/libtag.dll.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/C:/Program Files (x86)/taglib/lib/libtag.dll.a")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "c:/MinGW/bin/strip.exe" "$ENV{DESTDIR}/C:/Program Files (x86)/taglib/lib/libtag.dll.a")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files (x86)/taglib/bin/libtag.dll")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "C:/Program Files (x86)/taglib/bin" TYPE SHARED_LIBRARY FILES "H:/MUSIQUE/taglib-1.8/taglib/libtag.dll")
  IF(EXISTS "$ENV{DESTDIR}/C:/Program Files (x86)/taglib/bin/libtag.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/C:/Program Files (x86)/taglib/bin/libtag.dll")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "c:/MinGW/bin/strip.exe" "$ENV{DESTDIR}/C:/Program Files (x86)/taglib/bin/libtag.dll")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files (x86)/taglib/include/taglib/tag.h;C:/Program Files (x86)/taglib/include/taglib/fileref.h;C:/Program Files (x86)/taglib/include/taglib/audioproperties.h;C:/Program Files (x86)/taglib/include/taglib/taglib_export.h;C:/Program Files (x86)/taglib/include/taglib/taglib_config.h;C:/Program Files (x86)/taglib/include/taglib/taglib.h;C:/Program Files (x86)/taglib/include/taglib/tstring.h;C:/Program Files (x86)/taglib/include/taglib/tlist.h;C:/Program Files (x86)/taglib/include/taglib/tlist.tcc;C:/Program Files (x86)/taglib/include/taglib/tstringlist.h;C:/Program Files (x86)/taglib/include/taglib/tbytevector.h;C:/Program Files (x86)/taglib/include/taglib/tbytevectorlist.h;C:/Program Files (x86)/taglib/include/taglib/tbytevectorstream.h;C:/Program Files (x86)/taglib/include/taglib/tiostream.h;C:/Program Files (x86)/taglib/include/taglib/tfile.h;C:/Program Files (x86)/taglib/include/taglib/tfilestream.h;C:/Program Files (x86)/taglib/include/taglib/tmap.h;C:/Program Files (x86)/taglib/include/taglib/tmap.tcc;C:/Program Files (x86)/taglib/include/taglib/tpropertymap.h;C:/Program Files (x86)/taglib/include/taglib/mpegfile.h;C:/Program Files (x86)/taglib/include/taglib/mpegproperties.h;C:/Program Files (x86)/taglib/include/taglib/mpegheader.h;C:/Program Files (x86)/taglib/include/taglib/xingheader.h;C:/Program Files (x86)/taglib/include/taglib/id3v1tag.h;C:/Program Files (x86)/taglib/include/taglib/id3v1genres.h;C:/Program Files (x86)/taglib/include/taglib/id3v2extendedheader.h;C:/Program Files (x86)/taglib/include/taglib/id3v2frame.h;C:/Program Files (x86)/taglib/include/taglib/id3v2header.h;C:/Program Files (x86)/taglib/include/taglib/id3v2synchdata.h;C:/Program Files (x86)/taglib/include/taglib/id3v2footer.h;C:/Program Files (x86)/taglib/include/taglib/id3v2framefactory.h;C:/Program Files (x86)/taglib/include/taglib/id3v2tag.h;C:/Program Files (x86)/taglib/include/taglib/attachedpictureframe.h;C:/Program Files (x86)/taglib/include/taglib/commentsframe.h;C:/Program Files (x86)/taglib/include/taglib/generalencapsulatedobjectframe.h;C:/Program Files (x86)/taglib/include/taglib/ownershipframe.h;C:/Program Files (x86)/taglib/include/taglib/popularimeterframe.h;C:/Program Files (x86)/taglib/include/taglib/privateframe.h;C:/Program Files (x86)/taglib/include/taglib/relativevolumeframe.h;C:/Program Files (x86)/taglib/include/taglib/textidentificationframe.h;C:/Program Files (x86)/taglib/include/taglib/uniquefileidentifierframe.h;C:/Program Files (x86)/taglib/include/taglib/unknownframe.h;C:/Program Files (x86)/taglib/include/taglib/unsynchronizedlyricsframe.h;C:/Program Files (x86)/taglib/include/taglib/urllinkframe.h;C:/Program Files (x86)/taglib/include/taglib/oggfile.h;C:/Program Files (x86)/taglib/include/taglib/oggpage.h;C:/Program Files (x86)/taglib/include/taglib/oggpageheader.h;C:/Program Files (x86)/taglib/include/taglib/xiphcomment.h;C:/Program Files (x86)/taglib/include/taglib/vorbisfile.h;C:/Program Files (x86)/taglib/include/taglib/vorbisproperties.h;C:/Program Files (x86)/taglib/include/taglib/oggflacfile.h;C:/Program Files (x86)/taglib/include/taglib/speexfile.h;C:/Program Files (x86)/taglib/include/taglib/speexproperties.h;C:/Program Files (x86)/taglib/include/taglib/flacfile.h;C:/Program Files (x86)/taglib/include/taglib/flacpicture.h;C:/Program Files (x86)/taglib/include/taglib/flacproperties.h;C:/Program Files (x86)/taglib/include/taglib/flacmetadatablock.h;C:/Program Files (x86)/taglib/include/taglib/apefile.h;C:/Program Files (x86)/taglib/include/taglib/apeproperties.h;C:/Program Files (x86)/taglib/include/taglib/apetag.h;C:/Program Files (x86)/taglib/include/taglib/apefooter.h;C:/Program Files (x86)/taglib/include/taglib/apeitem.h;C:/Program Files (x86)/taglib/include/taglib/mpcfile.h;C:/Program Files (x86)/taglib/include/taglib/mpcproperties.h;C:/Program Files (x86)/taglib/include/taglib/wavpackfile.h;C:/Program Files (x86)/taglib/include/taglib/wavpackproperties.h;C:/Program Files (x86)/taglib/include/taglib/trueaudiofile.h;C:/Program Files (x86)/taglib/include/taglib/trueaudioproperties.h;C:/Program Files (x86)/taglib/include/taglib/rifffile.h;C:/Program Files (x86)/taglib/include/taglib/aifffile.h;C:/Program Files (x86)/taglib/include/taglib/aiffproperties.h;C:/Program Files (x86)/taglib/include/taglib/wavfile.h;C:/Program Files (x86)/taglib/include/taglib/wavproperties.h;C:/Program Files (x86)/taglib/include/taglib/asffile.h;C:/Program Files (x86)/taglib/include/taglib/asfproperties.h;C:/Program Files (x86)/taglib/include/taglib/asftag.h;C:/Program Files (x86)/taglib/include/taglib/asfattribute.h;C:/Program Files (x86)/taglib/include/taglib/asfpicture.h;C:/Program Files (x86)/taglib/include/taglib/mp4file.h;C:/Program Files (x86)/taglib/include/taglib/mp4atom.h;C:/Program Files (x86)/taglib/include/taglib/mp4tag.h;C:/Program Files (x86)/taglib/include/taglib/mp4item.h;C:/Program Files (x86)/taglib/include/taglib/mp4properties.h;C:/Program Files (x86)/taglib/include/taglib/mp4coverart.h;C:/Program Files (x86)/taglib/include/taglib/modfilebase.h;C:/Program Files (x86)/taglib/include/taglib/modfile.h;C:/Program Files (x86)/taglib/include/taglib/modtag.h;C:/Program Files (x86)/taglib/include/taglib/modproperties.h;C:/Program Files (x86)/taglib/include/taglib/itfile.h;C:/Program Files (x86)/taglib/include/taglib/itproperties.h;C:/Program Files (x86)/taglib/include/taglib/s3mfile.h;C:/Program Files (x86)/taglib/include/taglib/s3mproperties.h;C:/Program Files (x86)/taglib/include/taglib/xmfile.h;C:/Program Files (x86)/taglib/include/taglib/xmproperties.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "C:/Program Files (x86)/taglib/include/taglib" TYPE FILE FILES
    "H:/MUSIQUE/taglib-1.8/taglib/tag.h"
    "H:/MUSIQUE/taglib-1.8/taglib/fileref.h"
    "H:/MUSIQUE/taglib-1.8/taglib/audioproperties.h"
    "H:/MUSIQUE/taglib-1.8/taglib/taglib_export.h"
    "H:/MUSIQUE/taglib-1.8/taglib_config.h"
    "H:/MUSIQUE/taglib-1.8/taglib/toolkit/taglib.h"
    "H:/MUSIQUE/taglib-1.8/taglib/toolkit/tstring.h"
    "H:/MUSIQUE/taglib-1.8/taglib/toolkit/tlist.h"
    "H:/MUSIQUE/taglib-1.8/taglib/toolkit/tlist.tcc"
    "H:/MUSIQUE/taglib-1.8/taglib/toolkit/tstringlist.h"
    "H:/MUSIQUE/taglib-1.8/taglib/toolkit/tbytevector.h"
    "H:/MUSIQUE/taglib-1.8/taglib/toolkit/tbytevectorlist.h"
    "H:/MUSIQUE/taglib-1.8/taglib/toolkit/tbytevectorstream.h"
    "H:/MUSIQUE/taglib-1.8/taglib/toolkit/tiostream.h"
    "H:/MUSIQUE/taglib-1.8/taglib/toolkit/tfile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/toolkit/tfilestream.h"
    "H:/MUSIQUE/taglib-1.8/taglib/toolkit/tmap.h"
    "H:/MUSIQUE/taglib-1.8/taglib/toolkit/tmap.tcc"
    "H:/MUSIQUE/taglib-1.8/taglib/toolkit/tpropertymap.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/mpegfile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/mpegproperties.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/mpegheader.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/xingheader.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v1/id3v1tag.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v1/id3v1genres.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/id3v2extendedheader.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/id3v2frame.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/id3v2header.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/id3v2synchdata.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/id3v2footer.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/id3v2framefactory.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/id3v2tag.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/frames/attachedpictureframe.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/frames/commentsframe.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/frames/generalencapsulatedobjectframe.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/frames/ownershipframe.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/frames/popularimeterframe.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/frames/privateframe.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/frames/relativevolumeframe.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/frames/textidentificationframe.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/frames/uniquefileidentifierframe.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/frames/unknownframe.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpeg/id3v2/frames/urllinkframe.h"
    "H:/MUSIQUE/taglib-1.8/taglib/ogg/oggfile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/ogg/oggpage.h"
    "H:/MUSIQUE/taglib-1.8/taglib/ogg/oggpageheader.h"
    "H:/MUSIQUE/taglib-1.8/taglib/ogg/xiphcomment.h"
    "H:/MUSIQUE/taglib-1.8/taglib/ogg/vorbis/vorbisfile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/ogg/vorbis/vorbisproperties.h"
    "H:/MUSIQUE/taglib-1.8/taglib/ogg/flac/oggflacfile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/ogg/speex/speexfile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/ogg/speex/speexproperties.h"
    "H:/MUSIQUE/taglib-1.8/taglib/flac/flacfile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/flac/flacpicture.h"
    "H:/MUSIQUE/taglib-1.8/taglib/flac/flacproperties.h"
    "H:/MUSIQUE/taglib-1.8/taglib/flac/flacmetadatablock.h"
    "H:/MUSIQUE/taglib-1.8/taglib/ape/apefile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/ape/apeproperties.h"
    "H:/MUSIQUE/taglib-1.8/taglib/ape/apetag.h"
    "H:/MUSIQUE/taglib-1.8/taglib/ape/apefooter.h"
    "H:/MUSIQUE/taglib-1.8/taglib/ape/apeitem.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpc/mpcfile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mpc/mpcproperties.h"
    "H:/MUSIQUE/taglib-1.8/taglib/wavpack/wavpackfile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/wavpack/wavpackproperties.h"
    "H:/MUSIQUE/taglib-1.8/taglib/trueaudio/trueaudiofile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/trueaudio/trueaudioproperties.h"
    "H:/MUSIQUE/taglib-1.8/taglib/riff/rifffile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/riff/aiff/aifffile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/riff/aiff/aiffproperties.h"
    "H:/MUSIQUE/taglib-1.8/taglib/riff/wav/wavfile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/riff/wav/wavproperties.h"
    "H:/MUSIQUE/taglib-1.8/taglib/asf/asffile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/asf/asfproperties.h"
    "H:/MUSIQUE/taglib-1.8/taglib/asf/asftag.h"
    "H:/MUSIQUE/taglib-1.8/taglib/asf/asfattribute.h"
    "H:/MUSIQUE/taglib-1.8/taglib/asf/asfpicture.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mp4/mp4file.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mp4/mp4atom.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mp4/mp4tag.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mp4/mp4item.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mp4/mp4properties.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mp4/mp4coverart.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mod/modfilebase.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mod/modfile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mod/modtag.h"
    "H:/MUSIQUE/taglib-1.8/taglib/mod/modproperties.h"
    "H:/MUSIQUE/taglib-1.8/taglib/it/itfile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/it/itproperties.h"
    "H:/MUSIQUE/taglib-1.8/taglib/s3m/s3mfile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/s3m/s3mproperties.h"
    "H:/MUSIQUE/taglib-1.8/taglib/xm/xmfile.h"
    "H:/MUSIQUE/taglib-1.8/taglib/xm/xmproperties.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")


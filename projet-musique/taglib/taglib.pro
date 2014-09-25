#-------------------------------------------------
#
# Project created by QtCreator 2014-09-25T23:08:12
#
#-------------------------------------------------

QT       -= core gui

TARGET = taglib
TEMPLATE = lib

DEFINES += MAKE_TAGLIB_LIB
DEFINES += WITH_ASF
DEFINES += WITH_MP4

CONFIG += dll

SOURCES += \
    audioproperties.cpp \
    fileref.cpp \
    tag.cpp \
    tagunion.cpp \
    ape/apefile.cpp \
    ape/apefooter.cpp \
    ape/apeitem.cpp \
    ape/apeproperties.cpp \
    ape/apetag.cpp \
    asf/asfattribute.cpp \
    asf/asffile.cpp \
    asf/asfpicture.cpp \
    asf/asfproperties.cpp \
    asf/asftag.cpp \
    flac/flacfile.cpp \
    flac/flacmetadatablock.cpp \
    flac/flacpicture.cpp \
    flac/flacproperties.cpp \
    flac/flacunknownmetadatablock.cpp \
    it/itfile.cpp \
    it/itproperties.cpp \
    mod/modfile.cpp \
    mod/modfilebase.cpp \
    mod/modproperties.cpp \
    mod/modtag.cpp \
    mp4/mp4atom.cpp \
    mp4/mp4coverart.cpp \
    mp4/mp4file.cpp \
    mp4/mp4item.cpp \
    mp4/mp4properties.cpp \
    mp4/mp4tag.cpp \
    mpc/mpcfile.cpp \
    mpc/mpcproperties.cpp \
    mpeg/id3v1/id3v1genres.cpp \
    mpeg/id3v1/id3v1tag.cpp \
    mpeg/id3v2/frames/attachedpictureframe.cpp \
    mpeg/id3v2/frames/commentsframe.cpp \
    mpeg/id3v2/frames/generalencapsulatedobjectframe.cpp \
    mpeg/id3v2/frames/ownershipframe.cpp \
    mpeg/id3v2/frames/popularimeterframe.cpp \
    mpeg/id3v2/frames/privateframe.cpp \
    mpeg/id3v2/frames/relativevolumeframe.cpp \
    mpeg/id3v2/frames/textidentificationframe.cpp \
    mpeg/id3v2/frames/uniquefileidentifierframe.cpp \
    mpeg/id3v2/frames/unknownframe.cpp \
    mpeg/id3v2/frames/unsynchronizedlyricsframe.cpp \
    mpeg/id3v2/frames/urllinkframe.cpp \
    mpeg/id3v2/id3v2extendedheader.cpp \
    mpeg/id3v2/id3v2footer.cpp \
    mpeg/id3v2/id3v2frame.cpp \
    mpeg/id3v2/id3v2framefactory.cpp \
    mpeg/id3v2/id3v2header.cpp \
    mpeg/id3v2/id3v2synchdata.cpp \
    mpeg/id3v2/id3v2tag.cpp \
    mpeg/mpegfile.cpp \
    mpeg/mpegheader.cpp \
    mpeg/mpegproperties.cpp \
    mpeg/xingheader.cpp \
    ogg/flac/oggflacfile.cpp \
    ogg/speex/speexfile.cpp \
    ogg/speex/speexproperties.cpp \
    ogg/vorbis/vorbisfile.cpp \
    ogg/vorbis/vorbisproperties.cpp \
    ogg/oggfile.cpp \
    ogg/oggpage.cpp \
    ogg/oggpageheader.cpp \
    ogg/xiphcomment.cpp \
    riff/aiff/aifffile.cpp \
    riff/aiff/aiffproperties.cpp \
    riff/wav/wavfile.cpp \
    riff/wav/wavproperties.cpp \
    riff/rifffile.cpp \
    s3m/s3mfile.cpp \
    s3m/s3mproperties.cpp \
    toolkit/tbytevector.cpp \
    toolkit/tbytevectorlist.cpp \
    toolkit/tbytevectorstream.cpp \
    toolkit/tdebug.cpp \
    toolkit/tfile.cpp \
    toolkit/tfilestream.cpp \
    toolkit/tiostream.cpp \
    toolkit/tpropertymap.cpp \
    toolkit/tstring.cpp \
    toolkit/tstringlist.cpp \
    toolkit/unicode.cpp \
    trueaudio/trueaudiofile.cpp \
    trueaudio/trueaudioproperties.cpp \
    wavpack/wavpackfile.cpp \
    wavpack/wavpackproperties.cpp \
    xm/xmfile.cpp \
    xm/xmproperties.cpp

HEADERS += \
    audioproperties.h \
    fileref.h \
    tag.h \
    taglib_export.h \
    tagunion.h \
    taglib_config.h \
    ape/apefile.h \
    ape/apefooter.h \
    ape/apeitem.h \
    ape/apeproperties.h \
    ape/apetag.h \
    asf/asfattribute.h \
    asf/asffile.h \
    asf/asfpicture.h \
    asf/asfproperties.h \
    asf/asftag.h \
    flac/flacfile.h \
    flac/flacmetadatablock.h \
    flac/flacpicture.h \
    flac/flacproperties.h \
    flac/flacunknownmetadatablock.h \
    it/itfile.h \
    it/itproperties.h \
    mod/modfile.h \
    mod/modfilebase.h \
    mod/modfileprivate.h \
    mod/modproperties.h \
    mod/modtag.h \
    mp4/mp4atom.h \
    mp4/mp4coverart.h \
    mp4/mp4file.h \
    mp4/mp4item.h \
    mp4/mp4properties.h \
    mp4/mp4tag.h \
    mpc/mpcfile.h \
    mpc/mpcproperties.h \
    mpeg/id3v1/id3v1genres.h \
    mpeg/id3v1/id3v1tag.h \
    mpeg/id3v2/frames/attachedpictureframe.h \
    mpeg/id3v2/frames/commentsframe.h \
    mpeg/id3v2/frames/generalencapsulatedobjectframe.h \
    mpeg/id3v2/frames/ownershipframe.h \
    mpeg/id3v2/frames/popularimeterframe.h \
    mpeg/id3v2/frames/privateframe.h \
    mpeg/id3v2/frames/relativevolumeframe.h \
    mpeg/id3v2/frames/textidentificationframe.h \
    mpeg/id3v2/frames/uniquefileidentifierframe.h \
    mpeg/id3v2/frames/unknownframe.h \
    mpeg/id3v2/frames/unsynchronizedlyricsframe.h \
    mpeg/id3v2/frames/urllinkframe.h \
    mpeg/id3v2/id3v2extendedheader.h \
    mpeg/id3v2/id3v2footer.h \
    mpeg/id3v2/id3v2frame.h \
    mpeg/id3v2/id3v2framefactory.h \
    mpeg/id3v2/id3v2header.h \
    mpeg/id3v2/id3v2synchdata.h \
    mpeg/id3v2/id3v2tag.h \
    mpeg/mpegfile.h \
    mpeg/mpegheader.h \
    mpeg/mpegproperties.h \
    mpeg/xingheader.h \
    ogg/flac/oggflacfile.h \
    ogg/speex/speexfile.h \
    ogg/speex/speexproperties.h \
    ogg/vorbis/vorbisfile.h \
    ogg/vorbis/vorbisproperties.h \
    ogg/oggfile.h \
    ogg/oggpage.h \
    ogg/oggpageheader.h \
    ogg/xiphcomment.h \
    riff/aiff/aifffile.h \
    riff/aiff/aiffproperties.h \
    riff/wav/wavfile.h \
    riff/wav/wavproperties.h \
    riff/rifffile.h \
    s3m/s3mfile.h \
    s3m/s3mproperties.h \
    toolkit/taglib.h \
    toolkit/tbytevector.h \
    toolkit/tbytevectorlist.h \
    toolkit/tbytevectorstream.h \
    toolkit/tdebug.h \
    toolkit/tfile.h \
    toolkit/tfilestream.h \
    toolkit/tiostream.h \
    toolkit/tlist.h \
    toolkit/tmap.h \
    toolkit/tpropertymap.h \
    toolkit/tstring.h \
    toolkit/tstringlist.h \
    toolkit/unicode.h \
    trueaudio/trueaudiofile.h \
    trueaudio/trueaudioproperties.h \
    wavpack/wavpackfile.h \
    wavpack/wavpackproperties.h \
    xm/xmfile.h \
    xm/xmproperties.h

INCLUDEPATH += ape \
               asf \
               flac \
               it \
               mod \
               mp4 \
               mpc \
               mpeg \
               mpeg/id3v1 \
               mpeg/id3v2 \
               mpeg/id3v2/frames \
               ogg \
               ogg/flac \
               ogg/speex \
               ogg/vorbis \
               riff \
               riff/aiff \
               riff/wav \
               s3m \
               toolkit \
               trueaudio \
               wavpack \
               xm

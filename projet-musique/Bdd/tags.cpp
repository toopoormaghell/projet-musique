#include "tags.h"

#include <iostream>
#include <stdexcept>
#include <QImage>
#include<tbytevector.h>//ByteVector
#include<id3v2frame.h>//frame
#include <id3v2/frames/attachedpictureframe.h>
#include <id3v2/id3v2tag.h>
#include <mpegfile.h>
#include <QFile>
#include <mpegfile.h>
#include <id3v2tag.h>
#include <frames/attachedpictureframe.h>

Tags::Tags(const QString& nomFichier)
{
    QByteArray arrFileName = QFile::encodeName( nomFichier );
    const char* encodedName = arrFileName.constData();
    m_file = new TagLib::FileRef( encodedName );

    //si il n'est pas possible d'identifier le fichier
    if(m_file->isNull())
    {
        delete m_file;
        throw std::runtime_error("Erreur d'ouverture du fichier");
    }
}

Tags::~Tags()
{
    delete m_file;
}

bool Tags::save()
{
    return m_file->save();
}

QString Tags::getTitle() const
{

    return  TStringToQString( m_file->tag()->title() );
}

QString Tags::getArtist() const
{
    return TStringToQString ( m_file->tag()->artist() );
}

QString Tags::getAlbum() const
{
    return TStringToQString( m_file->tag()->album() );
}
int Tags::getYear() const
{
    return m_file->tag()->year();
}

int Tags::getTrack() const
{
    return m_file->tag()->track();
}

int Tags::getDuree() const
{
    return m_file->audioProperties()->length();
}
QImage Tags::getPoch() const
{
    QImage Image;
    TagLib::ID3v2::Tag Tag ( m_file->file() , 0 );
    TagLib::ID3v2::FrameList Liste = Tag.frameListMap()["APIC"];
    TagLib::ID3v2::AttachedPictureFrame* Pic = static_cast<TagLib::ID3v2::AttachedPictureFrame*>( Liste.front() );

    if ( ( Pic == NULL ) || Pic->picture().isEmpty() )
    {
        Image.fromData( "./Pochettes/def.jpg" );

    }
    else
    {
        Image.loadFromData( ( const uchar* ) Pic->picture().data(), Pic->picture().size() );
    }

    return Image;
}

void Tags::setTitle(const QString& title)
{
    m_file->tag()->setTitle( title.toStdString() );
}

void Tags::setArtist(const QString &artist)
{
    m_file->tag()->setArtist( artist.toStdString() );
}

void Tags::setAlbum(const QString& album)
{
    m_file->tag()->setAlbum( album.toStdString() );
}

void Tags::setYear(const int year)
{
    m_file->tag()->setYear(year);
}
void Tags::setTrack(const int track)
{
    m_file->tag()->setTrack( track );
}
void Tags::fermerTag()
{
    delete m_file;
    m_file = NULL;
}

void Tags::setPoch(const QString& Poch, const QString& Chemin)
{
    ImageFile imageFile( Poch.toStdString().c_str() );
    TagLib::ByteVector imageData = imageFile.data();
    TagLib::MPEG::File audioFile( TagLib::FileName ( Chemin.toStdString().c_str() ) );
    TagLib::ID3v2::Tag *tag = audioFile.ID3v2Tag(true);
    tag->removeFrames( "APIC" );

    TagLib::ID3v2::AttachedPictureFrame *frame = new TagLib::ID3v2::AttachedPictureFrame;

    frame->setMimeType( "image/jpeg" );
    frame->setType(TagLib::ID3v2::AttachedPictureFrame::FrontCover);
    frame->setPicture( imageData );

    tag->addFrame( frame );
    audioFile.save( TagLib::MPEG::File::AllTags,true, 3 );


}

int Tags::getBitRate() const
{
    return m_file->audioProperties()->bitrate();
}

int Tags::getSampleRate() const
{
    return m_file->audioProperties()->sampleRate();
}

int Tags::getChannels() const
{
    return m_file->audioProperties()->channels();
}

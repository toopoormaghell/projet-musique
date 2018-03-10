#ifndef TAGS_H
#define TAGS_H
#include <fileref.h> //pour la classe qui gere le fichier
#include <tag.h> //pour manipuler les tags
#include <QString>
#include "bdd_global.h"
class ImageFile : public TagLib::File
{
public:
    ImageFile(const char *file) : TagLib::File(file)
    {

    }

    TagLib::ByteVector data()
    {
        return readBlock(length());
    }


private:
    virtual TagLib::Tag *tag() const { return 0; }
    virtual TagLib::AudioProperties *audioProperties() const { return 0; }
    virtual bool save() { return false; }
};
class QImage;

/////////////////////////////////////////////////////////////////////////////////
///\class Tags
///\brief Gere les tags d'un fichier son
///\author boli
///\date mercredi 4 mars 2009
/// Simple encapsulation de classe de gestion des tags, écriture, lecture, et tout ce qui est en rapport avec les tags
/// d'un fichier independement de son extension.
/// Dependances: La bibliotheque C++ taglib (-ltags) sous GNU/Linux
///////////////////////////////////////////////////////////////////////////////////

class BDDSHARED_EXPORT Tags
{
public:
    //leve une exception uniquement pour indiquer que le type de fichier ne peut etre traité.
    //ou eventuellement un problème lors du new
    Tags(const QString &nomFichier);
    ~Tags();

    bool save(); //sauve les modifications de tags et autres.

    //récuperation des informations sur le morceau
    QString getTitle() const;
    QString getArtist() const;
    QString getAlbum() const;
    int getYear() const;
    int getTrack() const;
    int getDuree() const;
    QImage getPoch() const;

    //modification des informations
    void setTitle(const QString &title);
    void setArtist(const QString& artist);
    void setAlbum(const QString &album);
    void setYear(const  int year);
    void setTrack(const int track);
    static void setPoch(const QString &Poch, const QString &Chemin);

    //recuperation des proprietes audio
    int getBitRate() const;
    int getSampleRate() const;
    int getChannels() const;



    void fermerTag();
private:
    TagLib::FileRef *m_file;
};

#endif // TAGS_H

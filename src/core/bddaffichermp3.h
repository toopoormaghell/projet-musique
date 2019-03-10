#ifndef BDDAFFICHERMP3_H
#define BDDAFFICHERMP3_H

#include <QObject>
#include "bddsingleton.h"


class BDDAfficherMp3 : public QObject
{
    Q_OBJECT

public:
    explicit BDDAfficherMp3( QObject* parent = nullptr );
    QList<int> ListeArtiste( QString type );
    QStringList listeTitresAlbumMp3(QString Id_Album, QString Categorie );
    QStringList MP3Artiste( QString id_artiste );
    QList<int> listeAlbums( QString Id_Artiste, QString Categorie );
    QStringList RecupererListeTypes();


    QList<int> RecupererSimilaires(const int id);
};

#endif // BDDAFFICHERMP3_H

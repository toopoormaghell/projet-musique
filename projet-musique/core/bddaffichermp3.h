#ifndef BDDAFFICHERMP3_H
#define BDDAFFICHERMP3_H

#include <QObject>
#include "bddsingleton.h"

class BDDAfficherMp3 : public QObject
{
    Q_OBJECT
public:
    explicit BDDAfficherMp3(QObject *parent = 0);
QList<int> ListeArtiste();
QStringList listeTitresAlbumMp3(QString Album);



QList<int> listeAlbums(QString Id_Artiste);
QStringList RecupererListeTypes(const QString categorie);
};

#endif // BDDAFFICHERMP3_H

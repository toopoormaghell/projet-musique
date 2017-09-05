#ifndef BDDRECH_H
#define BDDRECH_H

#include <QObject>
#include "bddsingleton.h"
class BDDRech : public QObject
{
public:
    explicit BDDRech( QObject* parent );

    QList<int> RechTitres( QString rech );
    QList<int> RechAlb( QString rech );
    QList<int> RechArt( QString rech );

    QList<int> TitresPourAlb (QString rech);
    QList<int> TitresPourArt (QString rech);
    QList<int> AlbumsPourArt (QString rech);
    QList<int> AlbPourTitre(QString rech);
};

#endif // BDDRECH_H

#ifndef BDDGESTIONPHYS_H
#define BDDGESTIONPHYS_H

#include <QObject>
#include <QImage>
#include "util.h";

class BDDGestionPhys : public QObject
{
    Q_OBJECT
public:
    explicit BDDGestionPhys(QObject *parent = 0);
void ajouterAlbum(QImage Poch, QString Album, QString Artiste, QString ean, int Annee, QList<TitresPhys> titres, int Type);


};

#endif // BDDGESTIONPHYS_H
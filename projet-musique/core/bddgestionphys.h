#ifndef BDDGESTIONPHYS_H
#define BDDGESTIONPHYS_H

#include <QObject>
#include <QImage>
#include "util.h"
#include "meta_titre.h"

class BDDGestionPhys : public QObject
{
    Q_OBJECT

public:
    explicit BDDGestionPhys( QObject* parent = nullptr );
    void SupprimerenBDDPhys( int Id );
//    void modifierAlbum(QString Album, QString Artiste, QString ean, int Annee, QList<TitresPhys> titres, int Type, int Id_Poch, int Id_Album, QString Commentaires, int Support);

};

#endif // BDDGESTIONPHYS_H

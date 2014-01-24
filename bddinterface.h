#ifndef BDDINTERFACE_H
#define BDDINTERFACE_H

#include <QObject>
#include "BDDcommun.h"
#include "BDDmp3.h"
#include "BDDphys.h"
#include "util.h"
class BarreAvancement;

class BDDInterface: public QObject
{
    Q_OBJECT
public:
    explicit BDDInterface(QObject *parent=0);
    void actualiserMP3();
    void ViderBDD();

    void enregistrerObservateur( BarreAvancement* obs );
    void desenregistrerObservateur( BarreAvancement* obs );


    QStringList listeArtistesMp3(QString Categorie);
    QString afficherPochette(const QString &Album, const QString &Type);
    QStringList listeCategoriesMp3();
    QStringList listeAlbumsMp3(QString Id_Artiste);
    QStringList listeTitresAlbumMp3(QString Id_Album);
    void ajouterAlbumPhysique(AlbumGestion album);
private:
    BDDCommun myCommun;
    BDDMp3 myMp3;
    BDDPhys myPhys;
};

#endif // BDDINTERFACE_H

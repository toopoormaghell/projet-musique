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

    void enregistrerObservateur( BarreAvancement* obs );
    void desenregistrerObservateur( BarreAvancement* obs );

    //Mp3
    QStringList listeArtistesMp3(QString Categorie);
    void actualiserMP3();
    QString getPathFromIdMp3( const QString& mp3Id );
    QStringList listeCategoriesMp3();
    QStringList listeAlbumsMp3(QString Id_Artiste);
    QStringList listeTitresAlbumMp3(QString Id_Album);

    //Phys
    QStringList listeArtistesPhys(QString Categorie);
    QStringList listeCategoriesPhys();
    QStringList listeAlbumsPhys(QString Id_Artiste, QString Categorie);
    QList<TitreGestion> listeTitresAlbumPhys(QString Id_Album);
    AlbumGestion InfosAlbumPhys(QString Id_Album);
    void ajouterAlbumPhysique(AlbumGestion album);
    void ExporterHTML(QString Type);
    void SauvegarderAlbums();

    //Commun
    void ViderBDD();
    QStringList ListeArtistes();
    QStringList ListeArtistesInvers();
    QImage afficherPochette(const QString &Album, const QString &Type);


private:
    BDDCommun myCommun;
    BDDMp3 myMp3;
    BDDPhys myPhys;
};

#endif // BDDINTERFACE_H

#include "bddinterface.h"
#include "BDDcommun.h"
#include "BDDmp3.h"
#include "BDDphys.h"
#include <QDebug>

BDDInterface::BDDInterface(QObject *parent) : QObject(parent),
    myCommun(),
    myMp3(),
    myPhys()
{
}
//Actualise la liste MP3
void BDDInterface::actualiserMP3()
{
    myMp3.actualiserMp3("Album");
}
void BDDInterface::ViderBDD()
{
    myCommun.viderBDD();
}
void BDDInterface::enregistrerObservateur(BarreAvancement *obs)
{
    myCommun.enregistrerObservateur( obs );
    myMp3.enregistrerObservateur( obs );
}
void BDDInterface::desenregistrerObservateur(BarreAvancement *obs)
{
    myCommun.desenregistrerObservateur( obs );
    myMp3.desenregistrerObservateur( obs );
}
QStringList BDDInterface::listeArtistesMp3(QString Categorie)
{
    QStringList liste;
    liste=myMp3.listeArtistes(Categorie);
    return liste;
}
QImage BDDInterface::afficherPochette(const QString &Album,const QString &Type)
{
    QImage image=myCommun.afficherPochette(Album,Type);
    return image;
}
QStringList BDDInterface::listeCategoriesMp3()
{
    QStringList list;
    list=myMp3.listeCategories();
    return list;
}
QStringList BDDInterface::listeAlbumsMp3(QString Id_Artiste)
{
    QStringList list;
    list=myMp3.listeAlbums(Id_Artiste);
    return list;
}
QStringList BDDInterface::listeTitresAlbumMp3(QString Id_Album)
{
    QStringList list;
    list=myMp3.listeTitresAlbum(Id_Album);
    return list;
}
void BDDInterface::ajouterAlbumPhysique(AlbumGestion album)
{
    myPhys.AjouterAlbum(album);
}
QStringList BDDInterface::listeArtistesPhys(QString Categorie)
{
    QStringList liste;
    liste=myPhys.listeArtistes(Categorie);
    return liste;
}
QStringList BDDInterface::listeCategoriesPhys()
{
    QStringList list;
    list=myPhys.listeCategories();
    return list;
}
QStringList BDDInterface::listeAlbumsPhys(QString Id_Artiste,QString Categorie)
{
    QStringList list;
    list=myPhys.listeAlbums(Id_Artiste,Categorie);
    return list;
}
QList<TitreGestion> BDDInterface::listeTitresAlbumPhys(QString Id_Album)
{
    QList<TitreGestion> list;
    list=myPhys.listeTitresAlbum(Id_Album);
    return list;
}
AlbumGestion BDDInterface::InfosAlbumPhys(QString Id_Album)
{
    AlbumGestion album=myPhys.InfosAlbum(Id_Album);
    return album;
}
void BDDInterface::ExporterHTML(QString Type)
{
    myPhys.ExporterHTML(Type);
}
QStringList BDDInterface::ListeArtistes()
{
    QStringList temp=myCommun.ListeArtistes();
    return temp;
}
QStringList BDDInterface::ListeArtistesInvers()
{
    QStringList temp=myCommun.ListeArtistesInvers();
    return temp;
}

QString BDDInterface::getPathFromIdMp3(const QString &mp3Id)
{
    return myMp3.getPathFromIdMp3( mp3Id );
}
void BDDInterface::SauvegarderAlbums()
{
    myPhys.SauvegarderAlbums();
}
QString BDDInterface::getjetonAcces()
{
    return myPhys.getjetonAcces();
}
QString BDDInterface::getjetonSecret()
{
    return myPhys.getjetonSecret();
}

void BDDInterface::changerjetonSecret(QString jeton)
{
    myPhys.changerjetonSecret(jeton);
}

void BDDInterface::changerjetonAcces(QString jeton)
{
    myPhys.changerjetonAcces(jeton);
}


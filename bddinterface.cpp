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
void BDDInterface::actualiserMP3()
{
    if (ActualiserAlbums())
    {
        myMp3.actualiserMp3("Albums");
    }
    if (ActualiserCompil())
    {
        myMp3.actualiserMp3("Compil");
    }
    if (ActualiserLives())
    {
        myMp3.actualiserMp3("Lives");
    }
}
QStringList BDDInterface::listeArtistesMp3(QString Categorie)
{
    return myMp3.listeArtistes(Categorie);
}
QStringList BDDInterface::listeCategoriesMp3()
{
    return myMp3.listeCategories();
}
QStringList BDDInterface::listeAlbumsMp3(QString Id_Artiste)
{
    return myMp3.listeAlbums(Id_Artiste);
}
QStringList BDDInterface::listeTitresAlbumMp3(QString Id_Album)
{
    return myMp3.listeTitresAlbum(Id_Album);
}
MP3Gestion BDDInterface::RecupererInfosMp3(int Id_Titre)
{
    return myMp3.RecupererInfosMp3(Id_Titre);
}
bool BDDInterface::ActualiserAlbums()
{
    return myMp3.ActualiserAlbums();
}
bool BDDInterface::ActualiserCompil()
{
    return myMp3.ActualiserCompil();
}
bool BDDInterface::ActualiserLives()
{
    return myMp3.ActualiserLives();
}
QList<int> BDDInterface::ListeMp3Compil(QString annee)
{
    return myMp3.ListeMp3Compil(annee);
}

void BDDInterface::ViderMp3(QString Type)
{
    myMp3.ViderMp3(Type);
}
void BDDInterface::EnregistrerActuAlbums(bool check)
{
    myMp3.EnregistrerActuAlbums(check);
}
void BDDInterface::EnregistrerActuCompil(bool check)
{
    myMp3.EnregistrerActuCompil(check);
}
void BDDInterface::EnregistrerActuLives(bool check)
{
    myMp3.EnregistrerActuLives(check);
}
QMap<int, MP3Gestion> BDDInterface::similaires(QString Id)
{
    return myMp3.similaires(Id);
}
void BDDInterface::ajouterAlbumPhysique(AlbumGestion album)
{
    myPhys.AjouterAlbum(album);
}
QStringList BDDInterface::listeArtistesPhys(QString Categorie)
{
    return myPhys.listeArtistes(Categorie);
}
QStringList BDDInterface::listeCategoriesPhys()
{
    return myPhys.listeCategories();
}
QStringList BDDInterface::listeAlbumsPhys(QString Id_Artiste,QString Categorie)
{
    return myPhys.listeAlbums(Id_Artiste,Categorie);
}
QList<TitreGestion> BDDInterface::listeTitresAlbumPhys(QString Id_Album)
{
    return myPhys.listeTitresAlbum(Id_Album);
}
AlbumGestion BDDInterface::InfosAlbumPhys(QString Id_Album)
{
    return myPhys.InfosAlbum(Id_Album);
}
void BDDInterface::ExporterHTML(QString Type)
{
    myPhys.ExporterHTML(Type);
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
QImage BDDInterface::afficherPochette(const QString &Album,const QString &Type)
{
    return myCommun.afficherPochette(Album,Type);
}
QStringList BDDInterface::ListeArtistes()
{
    return myCommun.ListeArtistes();
}
QStringList BDDInterface::ListeArtistesInvers()
{
    return myCommun.ListeArtistesInvers();
}
QString BDDInterface::getPathFromIdMp3(const QString &mp3Id)
{
    return myMp3.getPathFromIdMp3( mp3Id );
}
void BDDInterface::SauvegarderAlbums()
{
    myPhys.SauvegarderAlbums();
}
QString BDDInterface::getdossierpardef()
{
    return myCommun.getdossierpardef();
}
void BDDInterface::EnregistrerDossierParDef(QString doss)
{
    myCommun.EnregistrerDossierParDef(doss);
}
void BDDInterface::CopierBDD()
{
    myCommun.CopierBDD();
}
void BDDInterface::ChargerBDD()
{
    myCommun.ChargerBDD();
}
void BDDInterface::EchangerArtiste(QString Artiste, QString Id_Artiste)
{
    return myCommun.EchangerArtistes(Artiste,Id_Artiste);
}
PlaylistGestion BDDInterface::RecupererInfosPlaylist(QString Id)
{
    return myPlay.RecupererInfosPlaylist(Id);
}
QList<PlaylistGestion> BDDInterface::ListesPlaylist()
{
    return myPlay.ListesPlaylist();
}
QString BDDInterface::CreerPlaylist(PlaylistGestion play)
{
    return myPlay.CreerPlaylist(play);
}
void BDDInterface::AjouterMP3dansPlaylist(int IdMp3, int IdPlay)
{
    myPlay.AjouterMP3dansPlaylist(IdMp3,IdPlay);
}
QList<Pochette> BDDInterface::ListePochettes()
{
    return myCommun.ListePochettes();
}
QStringList BDDInterface::listePlaylistMp3(QString Id)
{
    return myPlay.listePlaylistMP3(Id);
}

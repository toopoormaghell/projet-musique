#ifndef BDDINTERFACE_H
#define BDDINTERFACE_H

#include <QObject>
#include "BDDcommun.h"
#include "BDDmp3.h"
#include "BDDphys.h"
#include "bddplaylist.h"
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
    QMap<int, MP3Gestion> similaires(QString Id);
    MP3Gestion RecupererInfosMp3(int Id_Titre);
    QList<int> ListeMp3Compil(QString annee);
    void ViderMp3(QString Type);

    //Configuration du projet
    bool ActualiserAlbums();
    bool ActualiserCompil();
    bool ActualiserLives();
    void EnregistrerActuAlbums(bool check);
    void EnregistrerActuCompil(bool check);
    void EnregistrerActuLives(bool check);
    QString getdossierpardef();
    void EnregistrerDossierParDef(QString doss);
    void CopierBDD();
    void ChargerBDD();

    //Playlist
    PlaylistGestion RecupererInfosPlaylist(QString Id);
    QList<PlaylistGestion> ListesPlaylist();
    QString CreerPlaylist(PlaylistGestion play);
    void AjouterMP3dansPlaylist(int IdMp3, int IdPlay);
    QStringList listePlaylistMp3(QString Id);

    //Phys
    QStringList listeArtistesPhys(QString Categorie);
    QStringList listeCategoriesPhys();
    QStringList listeAlbumsPhys(QString Id_Artiste, QString Categorie);
    QList<TitreGestion> listeTitresAlbumPhys(QString Id_Album);
    AlbumGestion InfosAlbumPhys(QString Id_Album);
    void ajouterAlbumPhysique(AlbumGestion album);
    void ExporterHTML(QString Type);
    void SauvegarderAlbums();
    QString getjetonAcces();
    QString getjetonSecret();
    void changerjetonSecret(QString jeton);
    void changerjetonAcces(QString jeton);
    void SupprimerAlbumPhys(QString Id_Album);
    void ajouterCompilPhysique(CompilGestion compil);
    void ModifierAlbumPhys(AlbumGestion album);
    QStringList listeCompilPhys(QString Annee);

    //Commun
    void ViderBDD();
    QStringList ListeArtistes();
    QStringList ListeArtistesInvers();
    QImage afficherPochette(const QString &Id, const QString &Type);
    void EchangerArtiste(QString Artiste, QString Id_Artiste);
    QList<Pochette> ListePochettes();
    bool VerifPoch(QString &ArtAlb);
    int lireIDPoch(const QString &ArtAlb);
void VerifierBDD();

    CompilGestion InfosCompilPhys(QString Id_Album);
    void SupprimerCompilPhys(QString Id_Album);
    int NombreAlbumsPhys();
    int NombreMP3();
private:
    BDDCommun myCommun;
    BDDMp3 myMp3;
    BDDPhys myPhys;
    BDDPlaylist myPlay;
};

#endif // BDDINTERFACE_H

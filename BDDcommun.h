#ifndef BDDCOMMUN_H
#define BDDCOMMUN_H

#include <QObject>
#include <QString>
#include <QSet>
#include "util.h"
class BarreAvancement;

class BDDCommun : public QObject
{
public:
    explicit BDDCommun( QObject* parent = 0 );

    void viderBDD();

    bool removeDir(const QString& dirPath, const bool remove = true, const QString fichier = "def.jpg");

    int lireIDPoch(const QString &ArtAlb);
    int lireIDArtiste( const QString &Artiste,const int &IdPoch);
    int lireIDAlbum( const QString &Album, int Id_Poch, int Id_Artiste, QString Annee, QString Type);
    int lireIDTitre( const QString &Titre, int IdAlb, int IdArtiste, int IdPoch,int NumPiste, QString Duree);

    bool supprimerArtiste(const int &Id_Artiste, const QString artiste);
    bool supprimerAlbum(const int &Id_Alb, const QString &Chemin);
    bool supprimerTitre(const int Id_Titre);
    void supprimerPoch(const int &IdPoch);

    void enregistrerObservateur( BarreAvancement* obs );
    void desenregistrerObservateur( BarreAvancement* obs );

    QImage afficherPochette(const QString &Id, const QString &Type);
    bool verifierTitreMp3Phys(int Id_Titre);

    QString AjouterPochette(MP3Gestion mp3);
    QString AjouterPochette(AlbumGestion album);
    QString AjouterPochette(QString Type, QString Nom, QImage Image);

    bool supprimerTitre(const int Id_Album, const int Id_Titre);
    QStringList ListeArtistes();
    QStringList Artistea2mots(QStringList Artistes);
    QStringList ListeArtistesInvers();
    QString getdossierpardef();
    void EnregistrerDossierParDef(QString doss);
    void CopierBDD();
    void ChargerBDD();
    QList<Pochette> ListePochettes();

    void EchangerArtistes(QString Artiste, QString Id_Artiste);
protected:
    void notifierObservateurs( const QString& chemin, const float pourcentage );

private:
    QSet<BarreAvancement*> m_observateurs;
};

#endif // BDDCOMMUN_H

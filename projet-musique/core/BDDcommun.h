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
    int lireIDRelation(const int &Id_Alb, const int &Id_Artiste, const int &Id_Titre, const int &Id_Pochette );

    bool supprimerArtiste(const int &Id_Artiste);
    bool supprimerAlbum(const int &Id_Alb);
    bool supprimerTitredePhys(const int &Id_Titre,const int &Id_Relation);
    void supprimerPoch(const int &IdPoch, const QString Artiste, const QString Album);
    bool supprimerTitredeMp3(const int Id_Album, const int Id_Titre,const int Id_Relation);
    void supprimerRelation(const int &Id_Relation);

    void enregistrerObservateur( BarreAvancement* obs );
    void desenregistrerObservateur( BarreAvancement* obs );

    bool verifierTitreMp3Phys(int Id_Titre);

    QImage afficherPochette(const QString &Id, const QString &Type);
    QString AjouterPochette(MP3Gestion mp3);
    QString AjouterPochette(AlbumGestion album);
    QString AjouterPochette(QString Type, QString Nom, QImage Image);
    QList<Pochette> ListePochettes();

    //Artistes
    QStringList ListeArtistes();
    QStringList Artistea2mots(QStringList Artistes);
    QStringList ListeArtistesInvers();
    void EchangerArtistes(QString Artiste, QString Id_Artiste);


    //Confguration du projet
    QString getdossierpardef();
    void EnregistrerDossierParDef(QString doss);
    void CopierBDD();
    void ChargerBDD();


    QString AjouterPochette(CompilGestion album);
protected:
    void notifierObservateurs( const QString& chemin, const float pourcentage );
private:
    QSet<BarreAvancement*> m_observateurs;
};

#endif // BDDCOMMUN_H
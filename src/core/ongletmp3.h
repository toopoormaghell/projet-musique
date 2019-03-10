#ifndef ONGLETMP3_H
#define ONGLETMP3_H

#include <QWidget>
#include "bddaffichermp3.h"
#include <QAbstractButton>
#include <QTableWidgetItem>
#include "bddlecteur.h"
#include "meta_titre.h"

namespace Ui
{
class OngletMP3;
}

class OngletMP3 : public QWidget
{
    Q_OBJECT

public:
    explicit OngletMP3( QWidget* parent = nullptr );
    ~OngletMP3();

    //Concerne seulement l'affichage
    void afficherListeType();
    void affichageartistes();
    void afficherListeAnnees();
    void afficheralbumsettitres();
    void afficherTitresAlbum(QList<Meta_Titre*> titres, int Cate, int row );
    void afficherInfosTitre();
    void Similaires( int id );
    void vider( QString Type );
    void afficherAlbumSelectionne();

    void ActualiserOnglet();
    QStringList m_PlaylistLecteur;
    QString m_fichierlu;

public slots:
    void suppplaylist(QStringList temp);
signals:
    void EnvoyerTexte();
    void modifplaylist( QStringList index);

private slots:
    void on_AlbumsTitres_doubleClicked( const QModelIndex& index );
    void on_buttonBox_clicked( QAbstractButton* button );
    void on_ArtistesAnnees_doubleClicked( const QModelIndex& index );
    void on_Categories_clicked( const QModelIndex& index );
    void on_ArtistesAnnees_clicked( const QModelIndex& index );
    void on_AlbumsTitres_clicked( const QModelIndex& index );
    void on_Similaires_clicked(const QModelIndex &index);
    void on_LireMP3_clicked();
    void on_CopierMP3_clicked();
    void on_LireArtiste_clicked();
    void on_LireAlbum_clicked();
    void on_LireAnnee_clicked();
    void on_DialogueLecteurAnnee_clicked();

    void on_ModifierArtiste_clicked();

private:
    Ui::OngletMP3* ui;
    BDDAfficherMp3 m_bddInterface; //Permet de récupérer les infos de la BDD
    int m_lignestitres;
    BDDLecteur* m_lecteur;

    int m_colonnetitre;
    int m_ajoutlignes;

    //Concerne la récupération des infos sélectionnées par l'utilisateur
    int m_categorie;
    int m_mp3;
    int m_album;
    int m_artiste;


    void EnvoyerTexteAMain();
    void afficherMP3ouAlbum( const QString& MouA );

    int CompilsAnnees(int annee);
    void copier();
};

#endif // ONGLETMP3_H

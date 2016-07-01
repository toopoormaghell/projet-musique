#ifndef ONGLETMP3_H
#define ONGLETMP3_H

#include <QWidget>
#include "bddaffichermp3.h"
#include <QAbstractButton>
#include <QTableWidgetItem>


namespace Ui
{
class OngletMP3;
}

class OngletMP3 : public QWidget
{
    Q_OBJECT

public:
    explicit OngletMP3( QWidget* parent = 0 );
    ~OngletMP3();

    //Concerne seulement l'affichage
    void afficherListeType();
    void affichageartistes();
    void afficherListeAnnees();
    void afficheralbumsettitres();
    void afficherTitresAlbum( QString Album, int Cate, int row );
    void afficherInfosTitre();
    void Similaires( int id );
    void vider( QString Type );
    void afficherAlbumSelectionne();

    void ActualiserOnglet();

    QString m_fichierlu;
signals:
    void fichcopier();
private slots:
    void on_AlbumsTitres_doubleClicked( const QModelIndex& index );
    void on_buttonBox_clicked( QAbstractButton* button );
    void on_ArtistesAnnees_doubleClicked( const QModelIndex& index );
    void on_Categories_clicked( const QModelIndex& index );
    void on_ArtistesAnnees_clicked( const QModelIndex& index );
    void on_AlbumsTitres_clicked( const QModelIndex& index );

    void on_Similaires_clicked(const QModelIndex &index);

private:
    Ui::OngletMP3* ui;
    BDDAfficherMp3 m_bddInterface; //Permet de récupérer les infos de la BDD
    int m_lignestitres;

    int m_colonnetitre;
    int m_ajoutlignes;

    //Concerne la récupération des infos sélectionnées par l'utilisateur
    int m_categorie;
    int m_mp3;
    int m_album;
    int m_artiste;


    void afficherMP3ouAlbum( const QString& MouA );

    int CompilsAnnees(int annee);
};

#endif // ONGLETMP3_H

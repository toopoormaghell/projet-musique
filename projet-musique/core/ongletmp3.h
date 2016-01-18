#ifndef ONGLETMP3_H
#define ONGLETMP3_H

#include <QWidget>
#include "bddaffichermp3.h"
#include <QAbstractButton>
#include <QTableWidgetItem>


namespace Ui {
class OngletMP3;
}

class OngletMP3 : public QWidget
{
    Q_OBJECT

public:
    explicit OngletMP3(QWidget *parent = 0);
    ~OngletMP3();

    //Concerne seulement l'affichage
    void afficherListeType();
    void affichageartistes();
    void afficherListeAnnees();
    void afficheralbumsettitres();
    void afficherTitresAlbum(QString Album, QString Cate, int row);
    void afficherInfosTitre();
    void Similaires(int id);
    void vider(QString Type);
    void afficherAlbumSelectionne();

    void ActualiserOnglet();
private slots:
    void on_AlbumsTitres_doubleClicked(const QModelIndex &index);
    void on_Categories_currentRowChanged(int currentRow);
     void on_buttonBox_clicked(QAbstractButton *button);

    void on_ArtistesAnnees_currentRowChanged(int currentRow);

    void on_AlbumsTitres_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    void on_ArtistesAnnees_doubleClicked(const QModelIndex &index);

private:
    Ui::OngletMP3 *ui;
    BDDAfficherMp3 m_bddInterface; //Permet de récupérer les infos de la BDD
    int m_lignestitres;

    int m_colonnetitre;


    //Concerne la récupération des infos sélectionnées par l'utilisateur
    QString m_categorie;
    QString m_mp3;
    QString m_album;
    QString m_artiste;
    void choix(QString Index);

    void afficherMP3ouAlbum(const QString &MouA);
};

#endif // ONGLETMP3_H

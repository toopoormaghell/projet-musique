#ifndef ONGLETMP3_H
#define ONGLETMP3_H

#include <QWidget>
#include "bddaffichermp3.h"
#include <QStandardItemModel>
#include "lecteur.h"
#include <QAbstractButton>

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

    //Concerne la récupération des infos sélectionnées par l'utilisateur
    QString choixArtiste();
    QString choixMp3();
    QString choixCategories();
    int titreLecteur() const;
    QString artisteLecteur() const;
    QString choixAlbum();

private slots:
    void on_AlbumsTitres_doubleClicked(const QModelIndex &index);
    void on_Categories_currentRowChanged(int currentRow);
    void on_AlbumsTitres_clicked(const QModelIndex &index);
    void on_ArtistesAnnees_clicked(const QModelIndex &index);
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::OngletMP3 *ui;
    BDDAfficherMp3 m_bddInterface; //Permet de récupérer les infos de la BDD
    QStandardItemModel m_albumtitres;
    int m_lignestitres;
    QStandardItemModel m_artistes;
    int m_colonnetitre;
    Lecteur* m_player;

};

#endif // ONGLETMP3_H

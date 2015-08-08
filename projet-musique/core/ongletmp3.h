#ifndef ONGLETMP3_H
#define ONGLETMP3_H

#include <QWidget>
#include "bddaffichermp3.h"
#include <QStandardItemModel>
#include "lecteur.h"
namespace Ui {
class OngletMP3;
}

class OngletMP3 : public QWidget
{
    Q_OBJECT

public:
    explicit OngletMP3(QWidget *parent = 0);
    ~OngletMP3();

    QString choixArtiste();
    void vider(QString Type);
    void afficherTitresAlbum(QString Album, QString Cate, int row);
    void afficherInfosTitre();
    QString choixMp3();
    void afficherListeType();
    QString choixCategories();
    void Similaires(int id);
    void afficherListeAnnees();
    void afficheralbumsettitres();
    void affichageartistes();
    void Lecture();
    int titreLecteur() const;
    QString artisteLecteur() const;
signals:

public slots:
    void on_Categories_currentRowChanged(int currentRow);
    void on_AlbumsTitres_clicked(const QModelIndex &index);

private slots:
    void on_ArtistesAnnees_clicked(const QModelIndex &index);
private:
    Ui::OngletMP3 *ui;
    BDDAfficherMp3 m_bddInterface;
    QStandardItemModel m_albumtitres;
    int m_lignestitres;
    QStandardItemModel m_artistes;
    int m_colonnetitre;
    Lecteur* m_player;


};

#endif // ONGLETMP3_H

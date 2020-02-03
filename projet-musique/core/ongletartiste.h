#ifndef ONGLETARTISTE_H
#define ONGLETARTISTE_H

#include <QWidget>
#include "bddafficherartiste.h"

namespace Ui {
    class OngletArtiste;
}

class OngletArtiste : public QWidget
{
    Q_OBJECT

public:
    explicit OngletArtiste(QWidget *parent = nullptr);
    ~OngletArtiste();

    void ActualiserOnglet();
    void AfficherInfosArtiste();
    void AfficherListeTitresDistincts();
    void AfficherAlbums();
    void CacherRubriques();
    void appliquerstyle(QString stylecoul);
private slots:
    void on_ChangerNom_clicked();

    void on_Albums_clicked(const QModelIndex &index);

    void on_Singles_clicked(const QModelIndex &index);

    void on_Compil_clicked(const QModelIndex &index);



private:
    Ui::OngletArtiste *ui;
    BddAfficherArtiste* appelBDD;
    int m_artiste;
    int m_album;
    void InfosAlbum();
};

#endif // ONGLETARTISTE_H

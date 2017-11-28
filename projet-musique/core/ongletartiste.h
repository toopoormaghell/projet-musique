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
    explicit OngletArtiste(QWidget *parent = 0);
    ~OngletArtiste();

    void ActualiserOnglet();
    void AfficherInfosArtiste();
    void AfficherListeTitresDistincts();
    void AfficherAlbums();
private slots:
    void on_ChangerNom_clicked();

private:
    Ui::OngletArtiste *ui;
    BddAfficherArtiste* appelBDD;
    QString m_artiste;
};

#endif // ONGLETARTISTE_H

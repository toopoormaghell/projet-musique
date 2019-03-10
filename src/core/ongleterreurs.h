#ifndef ONGLETERREURS_H
#define ONGLETERREURS_H

#include <QWidget>
#include "bdderreurs.h"
#include "ongleterreurs.h"
#include <QListWidgetItem>

namespace Ui {
    class OngletErreurs;
}

class OngletErreurs : public QWidget
{
    Q_OBJECT

public:
    explicit OngletErreurs(QWidget *parent = nullptr);
    ~OngletErreurs();

    QString categorie();

private slots:

    void on_ErreursAlbums_clicked();

    void on_ErreursRelations_clicked();

    void on_ErreursArtistes_clicked();

    void on_ErreursTitres_clicked();

    void on_ErreursPoch_clicked();

    void on_ErreursPhys_clicked();

    void on_ErreursMP3_clicked();

    void on_ListeErreurs_itemClicked(QListWidgetItem *item);

    void on_Supprimer_clicked();

    void on_TrouverRel_clicked();

private:
    Ui::OngletErreurs *ui;
    BDDErreurs* m_bddinterface;

    void trouverErreurs(QList<int> liste);
    int m_categorie;
    int m_erreurlue;
    void lireErreur();
    void lireErreurRelation(QStringList temp);
    void lireErreurArtiste(QStringList temp);
    void lireErreurAlbum(QStringList temp);
    void lireErreurTitre(QStringList temp);
    void lireErreurPoch(QStringList temp);
    void lireErreurMP3(QStringList temp);
    void lireErreurPhys(QStringList temp);
    void lireErreurPochArt(QStringList temp);
    void ViderDonnees();
};

#endif // ONGLETERREURS_H



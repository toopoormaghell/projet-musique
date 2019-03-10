#ifndef ONGLETLISTE_H
#define ONGLETLISTE_H

#include <QWidget>

#include <bddafficherliste.h>
#include <QListWidgetItem>

namespace Ui {
    class OngletListe;
}

class OngletListe : public QWidget
{
    Q_OBJECT

public:
    explicit OngletListe(QWidget *parent = nullptr);
    ~OngletListe();

    void AfficherAlbums(int id);
    void ViderSelection();
    void ActualiserOnglet();
    void AfficherBoites();
private slots:
    void on_ListeAlbums_itemSelectionChanged();

    void on_ViderSelection_clicked();


    void on_ListeBoite_itemSelectionChanged();

    void on_OkAjout_clicked();



    void on_ListeBoite_itemClicked(QListWidgetItem *item);

private:
    BddAfficherListe* m_bddInterface;
    QList<int> id_selectionnes;
    Ui::OngletListe *ui;
};

#endif // ONGLETLISTE_H

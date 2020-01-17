#ifndef ONGLETPLAYLIST_H
#define ONGLETPLAYLIST_H

#include <QWidget>
#include "bddlisteplaylist.h"
#include <QListWidgetItem>

namespace Ui {
    class OngletPlaylist;
}

class OngletPlaylist : public QWidget
{
    Q_OBJECT

public:
    explicit OngletPlaylist(QWidget *parent = nullptr);
    ~OngletPlaylist();
    void ActualiserOnglet();

    void appliquerstyle(QString stylecoul);
private slots:
    void on_SupprimerPlaylist_clicked();
    void on_AjouterPlaylist_clicked();
    void on_ListePlaylist_currentRowChanged(int currentRow);
    void on_Copier_clicked();

    void on_ActuListe_clicked();

    void on_ActuPlaylist_clicked();

    void on_titreaz_clicked();

    void on_artaz_clicked();

    void on_artza_clicked();

    void on_titreza_clicked();

private:
    BDDListePlaylist* m_bddInterface;
    int m_playlist_selectionne;
    Ui::OngletPlaylist *ui;

    void ListeMp3(int Ordre);
    void AfficherPlaylist();
    void CopierListe();
};

#endif // ONGLETPLAYLIST_H

#ifndef ONGLETPLAYLIST_H
#define ONGLETPLAYLIST_H

#include <QWidget>
#include <bddinterface.h>
#include "affichagecommun.h"
namespace Ui {
class OngletPlaylist;
}

class OngletPlaylist : public QWidget
{
    Q_OBJECT
    
public:
    explicit OngletPlaylist(QWidget *parent = 0);
    ~OngletPlaylist();
    
    void afficherInfosPlaylist();
    void afficherTitrePlaylist(MP3Gestion mp3);
    void afficherListePlaylists();
    QString choixPlaylist();
    void nettoyer();
private slots:
    void on_ListePlaylists_currentRowChanged(int currentRow);

    void on_Ajouter_clicked();

private:
    Ui::OngletPlaylist *ui;
    BDDInterface m_bddInterface;
    AffichageCommun affi;
};

#endif // ONGLETPLAYLIST_H

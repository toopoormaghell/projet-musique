#ifndef DIALOGAJOUTERPLAYLISTMP3_H
#define DIALOGAJOUTERPLAYLISTMP3_H

#include <QDialog>
#include <bddinterface.h>
#include "affichagecommun.h"
namespace Ui {
class DialogAjouterPlaylistMp3;
}

class DialogAjouterPlaylistMp3 : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAjouterPlaylistMp3(QString Id_Mp3,QWidget *parent = 0);
    ~DialogAjouterPlaylistMp3();
    
    //Affichage
    void afficherListePlaylists();

    //Actions
    QString choixPlaylist();
    void ajouterMp3dansPlaylist();
private slots:
    void on_NouvellePlaylist_clicked();
    void on_buttonBox_accepted();
private:
    Ui::DialogAjouterPlaylistMp3 *ui;
    BDDInterface m_bddInterface;
    AffichageCommun affi;
    QString Mp3;
};

#endif // DIALOGAJOUTERPLAYLISTMP3_H

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
    explicit DialogAjouterPlaylistMp3(QWidget *parent = 0);
    ~DialogAjouterPlaylistMp3();
    
    void afficherListePlaylists();
private slots:
    void on_NouvellePlaylist_clicked();

private:
    Ui::DialogAjouterPlaylistMp3 *ui;
      BDDInterface m_bddInterface;
       AffichageCommun affi;
};

#endif // DIALOGAJOUTERPLAYLISTMP3_H

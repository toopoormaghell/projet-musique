#ifndef DIALOGALBUMSSMP3_H
#define DIALOGALBUMSSMP3_H

#include <QDialog>
#include "bddafficherphys.h"

namespace Ui {
    class DialogAlbumSSMP3;
}

class DialogAlbumSSMP3 : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAlbumSSMP3(QWidget *parent = nullptr);
    ~DialogAlbumSSMP3();

    void AjouterAlbums();
private:
    Ui::DialogAlbumSSMP3 *ui;
    BDDAfficherPhys m_bddInterface;
};

#endif // DIALOGALBUMSSMP3_H

#ifndef DIALOGAJOUTERPHYS_H
#define DIALOGAJOUTERPHYS_H

#include <QDialog>
#include "util.h"
namespace Ui {
class DialogAjouterPhys;
}

class DialogAjouterPhys : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAjouterPhys(QWidget *parent = 0);
    ~DialogAjouterPhys();

    void recupererEAN();
    void AfficherAlbum();

   QString m_EAN;
private slots:
    void on_buttonBox_accepted();

    void on_ChercherEAN_clicked();

    void on_Enregistrer_clicked();

private:
    Ui::DialogAjouterPhys *ui;
    AlbumPhys m_album;
    void AfficherPoch();

};

#endif // DIALOGAJOUTERPHYS_H

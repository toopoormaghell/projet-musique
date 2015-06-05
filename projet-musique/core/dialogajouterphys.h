#ifndef DIALOGAJOUTERPHYS_H
#define DIALOGAJOUTERPHYS_H

#include <QDialog>
#include "util.h"
#include "rechercheurl.h"

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
    int m_Type;

public slots:
    void AfficheInteraction();
private slots:


    void on_ChercherEAN_clicked();

    void on_Enregistrer_clicked();


    void AffichageListeAristes(int id);
private:
    Ui::DialogAjouterPhys *ui;
    AlbumPhys m_album;
    RechercheURL m_rech;
    void AfficherPoch();
    QString m_affichage;

};

#endif // DIALOGAJOUTERPHYS_H

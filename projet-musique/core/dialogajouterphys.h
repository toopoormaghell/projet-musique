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

    QString m_EAN;
    int m_Type;
    explicit DialogAjouterPhys(QString id_album, QWidget *parent = 0 );
signals:
    void ajout();
public slots:
    void AfficheInteraction();
private slots:
    void on_ChercherEAN_clicked();
    void on_Enregistrer_clicked();
    void AffichageListeArtistes(int id);
    void on_ViderAlbum_clicked();
    void on_Supprimer_Titre_clicked();
    void on_pushButton_clicked();
    void on_Ajouter_Titre_clicked();
    void AjouterTitreManuel(const QString &titre, const QString &duree, const QString &artiste);
private:
    void recupererEAN();
    void AfficherAlbum();
    void AfficherPoch();
    void ViderBoiteDialogue();

    Ui::DialogAjouterPhys *ui;
    AlbumPhys m_album;
    RechercheURL m_rech;
    QString m_affichage;


    void RecupererAlbum();
    void listeNumeros();
    void AjoutConnex();
};

#endif // DIALOGAJOUTERPHYS_H

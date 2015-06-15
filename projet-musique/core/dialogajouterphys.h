#ifndef DIALOGAJOUTERPHYS_H
#define DIALOGAJOUTERPHYS_H

#include <QDialog>
#include "util.h"
#include "rechercheurl.h"
#include "sousdialogajouttitre.h"
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

    void AjouterTitreManuel();
private:
    void recupererEAN();
    void AfficherAlbum();
    void AfficherPoch();
    void ViderBoiteDialogue();

    Ui::DialogAjouterPhys *ui;
    AlbumPhys m_album;
    RechercheURL m_rech;
    QString m_affichage;
    SousDialogAjoutTitre m_ajouttitre;

    void RecupererAlbum();
    void listeNumeros();
};

#endif // DIALOGAJOUTERPHYS_H

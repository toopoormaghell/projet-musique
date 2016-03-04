#ifndef MODIFIERALBUMDIALOG_H
#define MODIFIERALBUMDIALOG_H

#include <QDialog>
#include "bddgestionphys.h"
#include "util.h"


namespace Ui
{
    class ModifierAlbumDialog;
}

class ModifierAlbumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifierAlbumDialog( int selection, QWidget* parent = 0 );
    ~ModifierAlbumDialog();

private slots:
    void Supprimer_Titre();
 void on_buttonBox_accepted();

    void on_Parcourir_clicked();



private:
    //Affichage des données dans la fenêtre
    void AfficherAlbum();
    void ListeNumeros();
    //Enregistrement des différences
    void EnregistrerAlbum();

    //Données utilisées dans la classe
    Ui::ModifierAlbumDialog* ui;
    BDDGestionPhys* m_bddinterface;
    int m_selection;
    AlbumPhys m_album;
};

#endif // MODIFIERALBUMDIALOG_H

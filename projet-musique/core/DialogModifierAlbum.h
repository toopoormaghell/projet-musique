#ifndef MODIFIERALBUMDIALOG_H
#define MODIFIERALBUMDIALOG_H

#include <QDialog>
#include "bddgestionphys.h"

class Meta_Album;


namespace Ui
{
class DialogModifierAlbum;
}

class DialogModifierAlbum : public QDialog
{
    Q_OBJECT

public:
    explicit DialogModifierAlbum( int selection, QWidget* parent = nullptr );
    ~DialogModifierAlbum();

public slots:
     void AjouterTitreManuel(QString Num_Piste, QString Titre, QString Artiste);
private slots:
    void Supprimer_Titre();
    void on_buttonBox_accepted();
    void on_Parcourir_clicked();
    void on_Supprimer_clicked();
    void on_AjouterTitre_clicked();

private:
    //Affichage des données dans la fenêtre
    void AfficherAlbum();
    void ListeNumeros();
    //Enregistrement des différences
    void EnregistrerAlbum();

    //Données utilisées dans la classe
    Ui::DialogModifierAlbum* ui;
    BDDGestionPhys* m_bddinterface;
    int m_selection;
    Meta_Album* m_album;
    void RecupererListeType();
    void RecupererListeSupport();
};

#endif // MODIFIERALBUMDIALOG_H

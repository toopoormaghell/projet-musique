#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include "bddinterface.h"

namespace Ui {
class FenetrePrincipale;
}
class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
public:
    explicit FenetrePrincipale(QWidget *parent = 0);
    ~FenetrePrincipale();

    void ActualiserOngletMp3();
    void ActualiserOngletPhys();
private slots:
    //Vider
    void on_actionViderBDD_triggered();
    void on_actionViderMP3_triggered();
    //Supports Physiques
    void on_actionAjouter_Liste_Albums_triggered();
    void on_actionAjouter_Album_triggered();
    void on_actionExporter_Liste_Physique_triggered();
    //Exporter
    void on_actionEn_HTML_Supports_Physiques_triggered();
    void on_actionAlbums_triggered();
    void on_actionCompils_Singles_triggered();
    //Supports MP3
    void on_actionActualiser_Mp3_triggered();
    //Supports Outils
    void on_actionArtistes_Inverses_triggered();
    void on_actionChanger_Pochettes_triggered();
    //Supports Playlist
    //Support Config
    void on_actionDossier_par_d_faut_triggered();
    void on_actionCopier_BDD_triggered();
    void on_actionCharger_BDD_triggered();
private:
    Ui::FenetrePrincipale *ui;
    BDDInterface m_bddInterface;
};

#endif // FENETREPRINCIPALE_H

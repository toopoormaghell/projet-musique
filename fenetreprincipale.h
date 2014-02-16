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


private slots:
     void on_actionActualiser_Mp3_triggered();
     void on_actionViderBDD_triggered();
     void on_actionAjouter_Liste_Albums_triggered();
     void on_actionAjouter_Album_triggered();
     void on_actionEn_HTML_Supports_Physiques_triggered();

     void on_actionAlbums_triggered();

     void on_actionCompils_Singles_triggered();

     void on_actionArtistes_Inverses_triggered();

     void on_actionExporter_Liste_Physique_triggered();

private:
    Ui::FenetrePrincipale *ui;
 BDDInterface m_bddInterface;
};

#endif // FENETREPRINCIPALE_H

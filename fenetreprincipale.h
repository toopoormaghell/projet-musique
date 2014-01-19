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

private:
    Ui::FenetrePrincipale *ui;
 BDDInterface m_bddInterface;
};

#endif // FENETREPRINCIPALE_H

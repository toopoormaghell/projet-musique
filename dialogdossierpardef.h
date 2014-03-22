#ifndef DIALOGDOSSIERPARDEF_H
#define DIALOGDOSSIERPARDEF_H

#include <QDialog>
#include "bddinterface.h"

namespace Ui {
class DialogDossierParDef;
}

class DialogDossierParDef : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogDossierParDef(QWidget *parent = 0);
    ~DialogDossierParDef();
    
    void AfficherDossierParDef();
    void EnregistrerDossierParDef();
    void AfficherActu();
    void EnregistrerActualiser();
private slots:
   void on_pushButton_clicked();

   void on_buttonBox_accepted();

private:
    Ui::DialogDossierParDef *ui;
    BDDInterface m_bddInterface;
};

#endif // DIALOGDOSSIERPARDEF_H

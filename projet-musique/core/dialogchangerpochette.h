#ifndef DIALOGCHANGERPOCHETTE_H
#define DIALOGCHANGERPOCHETTE_H

#include <QDialog>
#include "bddinterface.h"
#include "affichagecommun.h"

namespace Ui {
class DialogChangerPochette;
}

class DialogChangerPochette : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogChangerPochette(QWidget *parent = 0);
    ~DialogChangerPochette();
    
    void AfficherPochette();
    QString getId();
private slots:
    void on_AjouterPochette_clicked();

    void on_buttonBox_accepted();

private:
    Ui::DialogChangerPochette *ui;
    BDDInterface m_bddInterface;
    AffichageCommun affi;
    QString Id_Pochette;
};

#endif // DIALOGCHANGERPOCHETTE_H

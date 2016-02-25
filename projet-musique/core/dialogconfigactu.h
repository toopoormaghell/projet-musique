#ifndef DIALOGCONFIGACTU_H
#define DIALOGCONFIGACTU_H

#include <QDialog>
#include <QAbstractButton>
#include "bddconfig.h"

namespace Ui
{
    class DialogConfigActu;
}

class DialogConfigActu : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConfigActu(QWidget *parent = 0);
    ~DialogConfigActu();

private slots:
    void on_buttonBox_accepted();
    void on_Changer_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);



private:
    void AfficherDossParDef();
    void EnregisDossParDef();

    void RemiseaZero();
    Ui::DialogConfigActu *ui;
    BDDConfig m_database;
    void AfficherCategories();
    void EnregistrerCategories();
};

#endif // DIALOGCONFIGACTU_H

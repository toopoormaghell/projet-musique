#ifndef DIALOGMODIFNOMSARTISTES_H
#define DIALOGMODIFNOMSARTISTES_H

#include <QDialog>
#include "bddgestionmodifnomartiste.h"

namespace Ui {
    class DialogModifNomsArtistes;
}

class DialogModifNomsArtistes : public QDialog
{
    Q_OBJECT

public:
    explicit DialogModifNomsArtistes(QWidget *parent = nullptr);
    ~DialogModifNomsArtistes();

    void AfficherListeArtistes();
    void Enregistrer(int id);
    void EnregistrerTout();
private slots:


    void on_Enregistrer_clicked();

    void on_buttonBox_accepted();

private:
    Ui::DialogModifNomsArtistes *ui;
    bddgestionmodifnomartiste* appelBDD;
};

#endif // DIALOGMODIFNOMSARTISTES_H

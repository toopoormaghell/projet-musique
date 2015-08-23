#ifndef MODIFIERALBUMDIALOG_H
#define MODIFIERALBUMDIALOG_H

#include <QDialog>
#include "bddgestionphys.h"


namespace Ui {
class ModifierAlbumDialog;
}

class ModifierAlbumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifierAlbumDialog(int selection,QWidget *parent = 0);
    ~ModifierAlbumDialog();

    void AfficherAlbum();
private:
    Ui::ModifierAlbumDialog *ui;
    BDDGestionPhys* m_bddinterface;
    int m_selection;
};

#endif // MODIFIERALBUMDIALOG_H

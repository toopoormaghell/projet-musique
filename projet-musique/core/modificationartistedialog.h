#ifndef MODIFICATIONARTISTEDIALOG_H
#define MODIFICATIONARTISTEDIALOG_H

#include <QDialog>
#include "bddartiste.h"

namespace Ui {
class ModificationArtisteDialog;
}

class ModificationArtisteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModificationArtisteDialog(BDDArtiste *Artiste, QWidget *parent = 0);
    ~ModificationArtisteDialog();

private slots:
    void on_Inversion_clicked();

    void on_ChangerPochette_clicked();

    void on_buttonBox_accepted();

private:
    Ui::ModificationArtisteDialog *ui;
    BDDArtiste* m_artiste;
    void AfficherArtiste();
    void Enregistrer();
};

#endif // MODIFICATIONARTISTEDIALOG_H

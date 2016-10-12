#ifndef MODIFICATIONARTISTEDIALOG_H
#define MODIFICATIONARTISTEDIALOG_H

#include <QDialog>
#include "bddartiste.h"

namespace Ui
{
    class DialogModifierArtiste;
}

class DialogModifierArtiste : public QDialog
{
    Q_OBJECT

public:
    explicit DialogModifierArtiste( BDDArtiste* Artiste, QWidget* parent = 0 );
    ~DialogModifierArtiste();

private slots:
    void on_Inversion_clicked();

    void on_ChangerPochette_clicked();

    void on_buttonBox_accepted();

private:
    Ui::DialogModifierArtiste* ui;
    BDDArtiste* m_artiste;
    void AfficherArtiste();
    void Enregistrer();
};

#endif // MODIFICATIONARTISTEDIALOG_H

#ifndef MODIFICATIONARTISTEDIALOG_H
#define MODIFICATIONARTISTEDIALOG_H

#include <QDialog>
#include "meta_artiste.h"

namespace Ui
{
    class DialogModifierArtiste;
}

class DialogModifierArtiste : public QDialog
{
    Q_OBJECT

public:
    explicit DialogModifierArtiste( Meta_Artiste* Artiste, QWidget* parent = nullptr );
    ~DialogModifierArtiste();

private slots:
    void on_Inversion_clicked();

    void on_ChangerPochette_clicked();

    void on_buttonBox_accepted();

private:
    Ui::DialogModifierArtiste* ui;
    Meta_Artiste* m_artiste;
    void AfficherArtiste();
    void Enregistrer();
};

#endif // MODIFICATIONARTISTEDIALOG_H

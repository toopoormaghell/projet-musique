#ifndef DIALOGCHOIXTITREFUSION_H
#define DIALOGCHOIXTITREFUSION_H

#include <QDialog>
#include "util.h"
class BDDFusion;
namespace Ui {
class DialogChoixTitreFusion;
}

class DialogChoixTitreFusion : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChoixTitreFusion(QList< TitresPhys > titres,int Ancien,QWidget *parent = 0);
    ~DialogChoixTitreFusion();
    int m_selection;
private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogChoixTitreFusion *ui;
    int RecupererTitreSelectionne();
    const BDDFusion* m_parent;
    QList < TitresPhys > m_titres;
    void AfficherTitres();
    int m_Ancien;
};

#endif // DIALOGCHOIXTITREFUSION_H

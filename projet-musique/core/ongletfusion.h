#ifndef ONGLETFUSION_H
#define ONGLETFUSION_H

#include <QWidget>
#include "bddrech.h"

namespace Ui {
class OngletFusion;
}

class OngletFusion : public QWidget
{
    Q_OBJECT

public:
    explicit OngletFusion(QWidget *parent = 0);
    ~OngletFusion();

private slots:
    void on_Ok_clicked();

    void on_ChoixFusions_clicked(const QModelIndex &index);

private:
    Ui::OngletFusion *ui;
    QString m_donnee;
    QString m_choix1;
    QString m_choix2;
   int nb_passage;
    BDDRech* appelBDD;
    void affichageChoixPossibles();
    void AffichageFusions(QString id);
    void Choix(QString id);
    void AfficherChoix();
};

#endif // ONGLETFUSION_H

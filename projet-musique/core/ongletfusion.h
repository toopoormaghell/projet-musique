#ifndef ONGLETFUSION_H
#define ONGLETFUSION_H

#include <QWidget>
#include "bddrech.h"
#include <QImage>
#include "util.h"

namespace Ui {
class OngletFusion;
}

class OngletFusion : public QWidget
{
    Q_OBJECT

public:
    explicit OngletFusion(QWidget *parent = 0);
    ~OngletFusion();

    void InitialiserWidget();
private slots:
    void on_Ok_clicked();
    void on_ChoixFusions_clicked(const QModelIndex &index);

    void Pochette1();
    void Pochette2();
    void Album2();
    void Album1();
    void Annee1();
    void Annee2();


    void on_Supprimer_clicked();

    void on_Choix1_Titres_clicked(const QModelIndex &index);

    void on_Choix2_Titres_clicked(const QModelIndex &index);

    void on_buttonBox_accepted();

private:
    void affichageChoixPossibles();
    void AffichageFusions(QString id);
    void Choix(QString id);
    void AfficherChoix1();
    void AfficherChoix2();

    int nb_passage;
    Ui::OngletFusion *ui;
    QString m_donnee;
    QString m_choix1;
    QString m_choix2;
    BDDRech* appelBDD;

    QString Choix1_Annee;
    QPair<QString,QString> Choix1_Album;
    QPair<QImage,QString> Choix1_Pochette;
    QList<TitresPhys> Choix1_Titres;

    QString Choix2_Annee;
    QPair<QString,QString> Choix2_Album;
    QPair<QImage,QString> Choix2_Pochette;
    QList<TitresPhys > Choix2_Titres;

    int ChoixFusion_Annee;
    int ChoixFusion_Album;
    int ChoixFusion_Pochette;
    QStringList ChoixFusion_Titres;


    void ListeNumeros();
};

#endif // ONGLETFUSION_H

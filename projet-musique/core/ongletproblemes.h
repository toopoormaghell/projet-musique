#ifndef ONGLETPROBLEMES_H
#define ONGLETPROBLEMES_H

#include <QWidget>
#include "bdderreurs.h"
#include "meta_titre.h"

namespace Ui {
    class OngletProblemes;
}

class OngletProblemes : public QWidget
{
    Q_OBJECT

public:
    explicit OngletProblemes(QWidget *parent = nullptr);
    ~OngletProblemes();

    QString categorie();
    void RemplirTableau();
    void appliquerstyle( QString stylecoul );
private slots:
    void on_Relations_clicked();

    void on_Physiques_clicked();

private:
    Ui::OngletProblemes *ui;
    BDDErreurs* m_bddinterface;

    int m_categorie;
    int m_erreurlue;
    void lireErreurRelation( Meta_Titre* temp , int ligne);
};

#endif // ONGLETPROBLEMES_H

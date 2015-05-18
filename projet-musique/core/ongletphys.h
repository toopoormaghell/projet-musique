#ifndef ONGLETPHYS_H
#define ONGLETPHYS_H

#include <QWidget>
#include "bddinterface.h"
#include "affichagecommun.h"
#include "QTableWidgetItem"
namespace Ui {
class OngletPhys;
}

class OngletPhys : public QWidget
{
    Q_OBJECT

public:
    explicit OngletPhys(QWidget *parent = 0);
    ~OngletPhys();

    void afficherListeArtiste();
    void afficherListeAlbum();
    void afficherListeCategories();
    void afficherListeAnnees();

    QString choixCategorie();
    QString choixArtiste();
QString choixAlbum();

    void afficherListeCompil();


    void vider(QString Type);

    void afficherNomArtiste();
    void afficherInfosAlbum(QListWidgetItem *item);

public slots:
    void on_Artistes_currentTextChanged(const QString &arg1);
private slots:
    void on_Categories_currentTextChanged(const QString &currentText);

    void on_Albums_itemClicked(QListWidgetItem *item);

    void on_Singles_itemClicked(QListWidgetItem *item);

    void on_Modifier_clicked();

    void on_Artistes_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::OngletPhys *ui;
    BDDInterface m_bddInterface;
    AffichageCommun temp;
};

#endif // ONGLETPHYS_H

#ifndef ONGLETPHYS_H
#define ONGLETPHYS_H

#include <QWidget>
#include "bddinterface.h"
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
    int AfficherAlbum(AlbumGestion album, int Colonne, int Ligne);

    void afficherListeCompil();
    int AfficherAlbum(CompilGestion album, int Colonne, int Ligne);
public slots:
    void on_Artistes_currentTextChanged(const QString &arg1);
private slots:
    void on_Categories_currentTextChanged(const QString &currentText);

    void on_Albums_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::OngletPhys *ui;
    BDDInterface m_bddInterface;
};

#endif // ONGLETPHYS_H

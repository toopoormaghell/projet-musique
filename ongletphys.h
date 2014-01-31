#ifndef ONGLETPHYS_H
#define ONGLETPHYS_H

#include <QWidget>
#include "bddinterface.h"
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


    QString choixCategorie();
    QString choixArtiste();
    int AfficherAlbum(AlbumGestion album, int Colonne, int Ligne);
public slots:
    void on_Artistes_currentTextChanged(const QString &arg1);
private slots:
    void on_Categories_currentTextChanged(const QString &currentText);

private:
    Ui::OngletPhys *ui;
    BDDInterface m_bddInterface;
};

#endif // ONGLETPHYS_H

#ifndef ONGLETPHYS_H
#define ONGLETPHYS_H

#include <QWidget>
#include "bddafficherphys.h"

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
    QString choixArtiste();
private:
    Ui::OngletPhys *ui;
    BDDAfficherPhys m_bddInterface;
};

#endif // ONGLETPHYS_H

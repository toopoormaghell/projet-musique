#ifndef ONGLETMP3_H
#define ONGLETMP3_H

#include <QWidget>
#include "bddinterface.h"
namespace Ui {
class OngletMp3;
}

class OngletMp3 : public QWidget
{
    Q_OBJECT
    
public:
    explicit OngletMp3(QWidget *parent = 0);
    ~OngletMp3();

    void afficherListeArtiste();
    
private:
    Ui::OngletMp3 *ui;
    BDDInterface m_bddInterface;
};

#endif // ONGLETMP3_H

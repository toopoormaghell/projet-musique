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
    QString choixAlbum();
    void AfficherInfosAlbum();
    void vider(QString type);
public slots:
    void on_Artistes_currentTextChanged(const QString &arg1);

private slots:
    void on_Albums_currentTextChanged(const QString &currentText);

private:
    Ui::OngletPhys *ui;
    BDDAfficherPhys m_bddInterface;
};

#endif // ONGLETPHYS_H

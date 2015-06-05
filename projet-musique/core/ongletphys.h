#ifndef ONGLETPHYS_H
#define ONGLETPHYS_H

#include <QWidget>
#include <QListWidgetItem>
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
    void AfficherInfosAlbum(int Type);
    void vider(QString type);
    void afficherListeCompils();
    QString choixCompil();

    void afficherListeType();
public slots:
    void on_Artistes_currentTextChanged(const QString &arg1);

private slots:


    void on_Albums_itemPressed(QListWidgetItem *item);

    void on_Compil_itemPressed(QListWidgetItem *item);

private:
    Ui::OngletPhys *ui;
    BDDAfficherPhys m_bddInterface;
};

#endif // ONGLETPHYS_H

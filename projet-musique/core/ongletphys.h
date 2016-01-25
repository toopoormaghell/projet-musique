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


    void AfficherArtisteSelectionne();
    void afficherListeSingles();
    QString choixSingle();
    int m_selection;
public slots:
    void on_Artistes_currentTextChanged(const QString &arg1);
private slots:
   void on_Albums_itemPressed(QListWidgetItem *item);
    void on_Compil_itemPressed(QListWidgetItem *item);
    void on_Singles_itemPressed(QListWidgetItem *item);
    void on_Modifier_clicked();
    void on_SupprimerAlbum_clicked();

    void on_Artistes_doubleClicked(const QModelIndex &index);

private:
    Ui::OngletPhys *ui;
    BDDAfficherPhys m_bddInterface;
    QString m_artiste;
    int m_Albums;
    int m_Compils;
    int m_Singles;

};

#endif // ONGLETPHYS_H

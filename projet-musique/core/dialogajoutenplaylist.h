#ifndef DIALOGAJOUTENPLAYLIST_H
#define DIALOGAJOUTENPLAYLIST_H

#include <QDialog>
#include "bddlisteplaylist.h"

namespace Ui {
    class DialogAjoutEnPlaylist;
}

class DialogAjoutEnPlaylist : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAjoutEnPlaylist(QString titre, int relation, QString Cate, QWidget *parent = nullptr);
    explicit DialogAjoutEnPlaylist(QList<int> liste, QWidget *parent=nullptr);
    ~DialogAjoutEnPlaylist();

    void ActualiserOnglet();
    void EnregistrerEnPlaylist();
private slots:
    void on_buttonBox_accepted();

private:
    BDDListePlaylist* m_bddInterface;
    QString m_titre;
    int m_relation;
    QString m_Cate;
    QList<int> m_liste;
    Ui::DialogAjoutEnPlaylist *ui;
    void AfficherTitre();
    void AfficherPlaylists();
};

#endif // DIALOGAJOUTENPLAYLIST_H

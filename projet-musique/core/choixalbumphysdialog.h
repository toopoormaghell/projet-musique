#ifndef CHOIXALBUMPHYSDIALOG_H
#define CHOIXALBUMPHYSDIALOG_H

#include <QDialog>
#include "bddaffichermp3.h"
#include <QStandardItemModel>
class RechercheURL;

namespace Ui
{
    class ChoixAlbumPhysDialog;
}

class ChoixAlbumPhysDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChoixAlbumPhysDialog(QString artiste, QWidget *parent = 0);
    ~ChoixAlbumPhysDialog();
    int m_selection;
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    void AfficherAlbums();
    Ui::ChoixAlbumPhysDialog *ui;
    BDDAfficherMp3 m_bddInterface;
    QStandardItemModel m_albums;
    int RecupererAlbumSelectionne();
    const RechercheURL* m_parent;
    QString m_artiste;
};

#endif // CHOIXALBUMPHYSDIALOG_H


#ifndef DIALOGMODIFIERALBUM_H
#define DIALOGMODIFIERALBUM_H

#include <QDialog>
#include "util.h"
#include "bddinterface.h"
#include "affichagecommun.h"
namespace Ui {
class DialogModifierAlbum;
}

class DialogModifierAlbum : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogModifierAlbum(AlbumGestion album_modif, QWidget *parent = 0);
    ~DialogModifierAlbum();
    
    int ChoisirType(QString Type);
    void EnregistrerAlbum();
    QString getType() const;
private slots:
    void on_buttonBox_accepted();

    void on_pushButton_clicked();

private:
    Ui::DialogModifierAlbum *ui;
    AlbumGestion album;
    BDDInterface m_bddInterface;
    AffichageCommun tmp;
};

#endif // DIALOGMODIFIERALBUM_H

#ifndef ONGLETRECH_H
#define ONGLETRECH_H

#include <QWidget>
#include "bddrech.h"

namespace Ui {
class OngletRech;
}

class OngletRech : public QWidget
{
    Q_OBJECT

public:
    explicit OngletRech(QWidget *parent = 0);
    ~OngletRech();

private slots:
    void on_pushButton_clicked();

private:
    Ui::OngletRech *ui;
    void affichageResultats();
    QString m_rech;
    BDDRech* appelBDD;
    void affichageTitres();
    void affichageAlbums();
    void affichageArtistes();
};

#endif // ONGLETRECH_H

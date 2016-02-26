#ifndef ONGLETRECH_H
#define ONGLETRECH_H

#include <QWidget>
#include "bddrech.h"

namespace Ui
{
    class OngletRech;
}

class OngletRech : public QWidget
{
    Q_OBJECT

public:
    explicit OngletRech( QWidget *parent = 0 );
    ~OngletRech();

private slots:
    void on_pushButton_clicked();

    void on_TitResult_clicked( const QModelIndex &index );

    void on_ArtResult_clicked( const QModelIndex &index );

private:
    Ui::OngletRech *ui;
    void affichageResultats();
    QString m_rech;
    BDDRech* appelBDD;
    void affichageTitres();
    void affichageAlbums();
    void affichageArtistes();
    void AffichageResGroup( int Type );

    QString m_affiche;


};

#endif // ONGLETRECH_H

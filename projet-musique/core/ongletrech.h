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
    explicit OngletRech( QWidget* parent = 0 );
    ~OngletRech();

private slots:
    void on_pushButton_clicked();
    void on_TitResult_clicked( const QModelIndex& index );
    void on_ArtResult_clicked( const QModelIndex& index );
    void on_AlbResult_clicked( const QModelIndex& index );
    void on_AlbumspourArt_clicked( const QModelIndex& index );
    void on_TitresResultats_clicked( const QModelIndex& index );
    void on_voirAlbum_clicked();
    void on_VoirArtiste_clicked();
    void on_Similaires_clicked();

    void on_CopierDansDossier_clicked();



private:
    Ui::OngletRech* ui;
    void affichageResultats();
    QString m_rech;
    BDDRech* appelBDD;
    void affichageTitres();
    void affichageAlbums();
    void affichageArtistes();
    void AffichageResGroup( int Type );
    void affichageResultatspourArtiste();
    QString m_artiste;
    QString m_album;
    QString m_titre;

    void affichageTitresParAlbum();
    void AffichInfosTitres();

    void affichageTitresParArtiste();
};

#endif // ONGLETRECH_H

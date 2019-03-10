#ifndef ONGLETPHYS_H
#define ONGLETPHYS_H

#include <QWidget>
#include <QListWidgetItem>
#include "bddafficherphys.h"

namespace Ui
{
    class OngletPhys;
}

class OngletPhys : public QWidget
{
    Q_OBJECT

public:
    explicit OngletPhys( QWidget* parent = nullptr );
    ~OngletPhys();

    void afficherListeArtiste();
    void afficherListeAlbum();
    void AfficherInfosAlbum( int Type );
    void vider( QString type );
    void afficherListeCompils();
    void afficherListeAlbSansMP3();

    void AfficherArtisteSelectionne();
    void afficherListeSingles();
void AfficherCategories();
    void actualiserOnglet();

    void remplirStats();

private slots:
    void on_Modifier_clicked();
    void on_SupprimerAlbum_clicked();
    void on_Albums_itemPressed( QListWidgetItem* item );
    void on_Compil_itemPressed( QListWidgetItem* item );
    void on_Singles_itemPressed( QListWidgetItem* item );
    void on_Artistes_doubleClicked( const QModelIndex& index );
    void on_Artistes_clicked( const QModelIndex& index );

    void on_AlbSansMP3_pressed(const QModelIndex &index);

    void on_Categories_clicked(const QModelIndex &index);


    void on_ModifArtiste_clicked();

private:
    Ui::OngletPhys* ui;
    BDDAfficherPhys m_bddInterface;
    QString m_artiste;
    int m_Albums;
    int m_Compils;
    int m_Singles;
    int m_selection;
    int m_categorie;
    void afficherListeCds();


};

#endif // ONGLETPHYS_H

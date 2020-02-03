#include "dialogmodifnomsartistes.h"
#include "ui_dialogmodifnomsartistes.h"

#include "meta_artiste.h"
#include "bddgestionmodifnomartiste.h"
#include "bddartiste.h"

DialogModifNomsArtistes::DialogModifNomsArtistes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogModifNomsArtistes)
{
    ui->setupUi(this);
    AfficherListeArtistes();
}

DialogModifNomsArtistes::~DialogModifNomsArtistes()
{
    delete ui;
}
void DialogModifNomsArtistes::AfficherListeArtistes()
{

    ui->ListeArtistes->clear();

    QList<int> listeArt = appelBDD->ListeArtiste();

    ui->ListeArtistes->setRowCount( listeArt.count() );

    //Pour chaque artiste
    for ( int i = 0 ; i < listeArt.count() ; i ++ )
    {
        //On récupère l'artiste
        //On affiche le nom de l'artiste
        Meta_Artiste* art = Meta_Artiste::RecupererBDD( listeArt[i] );

        //Premier Element : l'id de l'artiste
        QTableWidgetItem* item = new  QTableWidgetItem;
        item->setText( QString::number( art->get_id_artiste() ) );
        ui->ListeArtistes->setItem( i, 0, item);

        //Deuxième : le nom de l'artiste
        item = new QTableWidgetItem;
        QString temp = art->getNom_Artiste();
        item->setText( temp );
        ui->ListeArtistes->setItem( i , 1, item );

        //Troisième : l'inversion du nom de l'artiste
        item = new QTableWidgetItem;
        BDDArtiste::EchangerArtiste( temp );
        item->setData( Qt::UserRole, art->get_id_artiste()  );
        item->setText( temp );
        ui->ListeArtistes->setItem( i , 2, item );

        delete art;
    }

    ui->ListeArtistes->resizeRowsToContents();
    ui->ListeArtistes->resizeColumnsToContents();
}
void DialogModifNomsArtistes::Enregistrer( int id )
{
    Meta_Artiste* art = Meta_Artiste::RecupererBDD( id );
    art->inversion();
    art->update();

}


void DialogModifNomsArtistes::on_Enregistrer_clicked()
{
    EnregistrerTout();
    AfficherListeArtistes();

}
void DialogModifNomsArtistes::EnregistrerTout()
{
    QModelIndexList modelIndList = ui->ListeArtistes->selectionModel()->selectedIndexes();

    for ( int i = 0; i < modelIndList.count() ; i++ )
    {
        Enregistrer( modelIndList.at( i ).data( Qt::UserRole).toInt() );
    }

}

void DialogModifNomsArtistes::on_buttonBox_accepted()
{
    EnregistrerTout();
}

#include "ongletproblemes.h"
#include "ui_ongletproblemes.h"
#include "meta_titre.h"

OngletProblemes::OngletProblemes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletProblemes),
    m_bddinterface ( new BDDErreurs ),
    m_categorie ( 0 ),
    m_erreurlue ( 0 )
{
    ui->setupUi(this);

}

OngletProblemes::~OngletProblemes()
{
    delete ui;
}

QString OngletProblemes::categorie()
{
    return "Relation";
}

void OngletProblemes::RemplirTableau()
{
    QList<int> liste = m_bddinterface->retrouverRelations();


    for (int i =0 ; i< liste.count(); i++ )
    {
        Meta_Titre* temp = Meta_Titre::RecupererBDD( liste[i ] );
        ui->TabProbl->setRowCount( liste.count() );
        ui->TabProbl->setColumnCount( 10 );
        lireErreurRelation( temp, i );
    }
}

void OngletProblemes::appliquerstyle(QString stylecoul)
{
    setStyleSheet( stylecoul );
    update();
}

void OngletProblemes::lireErreurRelation(Meta_Titre* temp, int ligne)
{
    QTableWidgetItem* item = new QTableWidgetItem;
    item->setText( temp->getnom_titre() );
    ui->TabProbl->setItem(ligne, 0, item );

    item= new QTableWidgetItem;
    item->setText( temp->getnom_album() );
    ui->TabProbl->setItem(ligne, 1, item );

    item= new QTableWidgetItem;
    item->setText( temp->getnom_artiste() );
    ui->TabProbl->setItem(ligne, 2, item );

    item= new QTableWidgetItem;
    item->setText( temp->getcheminmp3() );
    ui->TabProbl->setItem(ligne, 3, item );

    item= new QTableWidgetItem;
    item->setText( QString::number( temp->getnum_piste() ) );
    ui->TabProbl->setItem(ligne, 4, item );

    item= new QTableWidgetItem;
    item->setText( temp->gettype() );
    ui->TabProbl->setItem(ligne, 5, item );

    item= new QTableWidgetItem;
    item->setText( QString::number( temp->getannee() ) );
    ui->TabProbl->setItem(ligne, 6, item );

    item= new QTableWidgetItem;
    item->setText( temp->getsupportmp3() );
    ui->TabProbl->setItem(ligne, 7, item );

    item= new QTableWidgetItem;
    item->setText( temp->getsupportphys() );
    ui->TabProbl->setItem(ligne, 8, item );

    item= new QTableWidgetItem;
    item->setText( temp->getean() );
    ui->TabProbl->setItem(ligne, 9, item );

    item= new QTableWidgetItem;
    item->setText( temp->getcommentaires() );
    ui->TabProbl->setItem(ligne, 10, item );

    item= new QTableWidgetItem;
    item->setText( QString::number( temp->getid_titre() ) );
    item->setData(Qt::UserRole, QString::number( temp->getid_titre() ) );
    ui->TabProbl->setItem(ligne, 10, item );

}

void OngletProblemes::on_Relations_clicked()
{
    RemplirTableau();
}

void OngletProblemes::on_Physiques_clicked()
{

}

void OngletProblemes::on_Ok_Titre_clicked()
{
    int id_alb = ui->Id_Album->text().toInt();
    int id_tit = ui->Id_Titre->text().toInt();

    m_bddinterface->supprimerRelParTitre(id_alb,id_tit);
}

void OngletProblemes::on_Ok_Album_clicked()
{
    int id = ui->Id_Album->text().toInt();
    QList<int> liste  = m_bddinterface->AfficherListeTitresAlbum( id );

    for (int i =0 ; i< liste.count(); i++ )
    {
        Meta_Titre* temp = Meta_Titre::RecupererBDD( liste[i ] );
        ui->TabProbl->setRowCount( liste.count() );
        ui->TabProbl->setColumnCount( 11 );
        lireErreurRelation( temp, i );
    }
}

void OngletProblemes::on_TabProbl_cellClicked(int row, int column)
{
    if (column==10)
    {
        ui->Id_Titre->setText( ui->TabProbl->item(row,column)->data(Qt::UserRole).toString() );
    }
}

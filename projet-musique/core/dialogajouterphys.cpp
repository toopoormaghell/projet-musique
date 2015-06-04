#include "dialogajouterphys.h"
#include "ui_dialogajouterphys.h"
#include "qdebug.h"
#include "bddgestionphys.h"
#include "util.h"
#include "rechercheurl.h"

DialogAjouterPhys::DialogAjouterPhys(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAjouterPhys)
{
    ui->setupUi(this);
    connect(&m_rech,SIGNAL(test()),this,SLOT(test2()));

}

DialogAjouterPhys::~DialogAjouterPhys()
{
    delete ui;
}
void DialogAjouterPhys::recupererEAN()
{

    m_EAN = ui->EAN->text();
}

void DialogAjouterPhys::on_buttonBox_accepted()
{
}
void DialogAjouterPhys::recupererType()
{
    m_Type = 2;
}

void DialogAjouterPhys::on_ChercherEAN_clicked()
{
    recupererEAN();
    recupererType();
    m_album = m_rech.RequeteAlbums(m_EAN,m_Type);
    AfficherAlbum();
}
void DialogAjouterPhys::AfficherAlbum()
{
    ui->Annee->setText(QString::number(m_album.Annee));
    ui->Nom_Album->setText(m_album.Album);
    ui->Nom_Artiste->setText(m_album.Artiste);

    for (int cpt=0;cpt<m_album.titres.count();cpt++)
    {
        TitresPhys titre = m_album.titres[cpt];
        ui->Piste->addItem(QString::number(titre.Num_Piste));
        ui->Titres->addItem(titre.Titre+"("+titre.Duree+")");
        ui->Artiste_Titres->addItem(titre.Artiste);
    }
    AfficherPoch();
}
void DialogAjouterPhys::AfficherPoch()
{
    QPixmap* pixmap = new QPixmap();
    pixmap->convertFromImage(m_album.Poch);

    QPixmap imageScaled = pixmap->scaled(150,150,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    ui->Pochette->setPixmap(imageScaled);
}

void DialogAjouterPhys::on_Enregistrer_clicked()
{
    BDDGestionPhys m_bddinterface;
    m_bddinterface.ajouterAlbum(m_album.Poch,m_album.Album,m_album.Artiste,m_EAN,m_album.Annee,m_album.titres,1);
}

void DialogAjouterPhys::test2()
{
    ui->Interaction->append(m_rech.m_interaction);
}



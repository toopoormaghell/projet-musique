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
    ui->ArtisteLabel->setHidden(true);
    ui->Artiste_Titres->setHidden(true);
    connect(&m_rech,SIGNAL(test()),this,SLOT(AfficheInteraction()));
    connect(ui->buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(AffichageListeAristes(int))) ;
}

DialogAjouterPhys::~DialogAjouterPhys()
{
    delete ui;
}
void DialogAjouterPhys::recupererEAN()
{

    m_EAN = ui->EAN->text();
}


void DialogAjouterPhys::on_ChercherEAN_clicked()
{
    recupererEAN();

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

void DialogAjouterPhys::AfficheInteraction()
{
    ui->Interaction->append(m_rech.m_interaction);
}
void DialogAjouterPhys::AffichageListeAristes(int id) {

    switch (id)
    {
    case (-2):m_Type=1;ui->Artiste_Titres->setHidden(true); ui->ArtisteLabel->setHidden(true);break;
    case (-3): m_Type=2;ui->Artiste_Titres->setHidden(false); ui->ArtisteLabel->setHidden(false);break;
    case (-4): m_Type=3;ui->Artiste_Titres->setHidden(true); ui->ArtisteLabel->setHidden(true);break;
    }
}


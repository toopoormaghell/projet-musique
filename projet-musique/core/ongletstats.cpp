#include "ongletstats.h"
#include "ui_ongletstats.h"
#include "bddtype.h"
OngletStats::OngletStats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletStats)
{
    ui->setupUi(this);
    AfficherInfos();

}

OngletStats::~OngletStats()
{
    delete ui;
}

void OngletStats::AfficherInfos()
{
    ui->NbMp3Total->setText("Nombre de Mp3 : "+QString::number(m_bddInterface.NbMp3Total()));
    ui->NbPhysTotal->setText("Nombre de cds : "+QString::number(m_bddInterface.NbPhysTotal()));

    AfficherInfosCategoriesPhys();
    AfficherInfosCategoriesMP3();

}
void OngletStats::AfficherInfosCategoriesMP3()
{
    int nb=0;
    //Classique
    int temp=m_bddInterface.NbMp3Categorie(8);
    nb=temp+nb;
    ui->NbMp3Classique->setText("<dd><dd>Classique: "+QString::number(temp));
    //BOF
    temp=m_bddInterface.NbMp3Categorie(4);
    nb=temp+nb;
    ui->NbMp3BOF->setText("<dd><dd>BOF: "+QString::number(temp));
    //Spectacles
    temp=m_bddInterface.NbMp3Categorie(5);
    nb=temp+nb;
    ui->NbMp3Spect->setText("<dd><dd>Spectacle Musical: "+QString::number(temp));
    //Tele
    temp=m_bddInterface.NbMp3Categorie(6);
    nb=temp+nb;
    ui->NbMp3Tele->setText("<dd><dd>Télé Réalités: "+QString::number(temp));
    //New Age
    temp=m_bddInterface.NbMp3Categorie(7);
    nb=temp+nb;
    ui->NbMp3NA->setText("<dd>New Age: "+QString::number(temp));
    //Generiques
    temp=m_bddInterface.NbMp3Categorie(9);
    nb=temp+nb;
    ui->NbMp3Gene->setText("<dd>Génériques: "+QString::number(temp));
    //Reprises
    temp=m_bddInterface.NbMp3Categorie(10);
    nb=temp+nb;
    ui->NbMp3Reprises->setText("<dd><dd>Reprises: "+QString::number(temp));
    //Albums
    temp=m_bddInterface.NbMp3Categorie(1);
    nb=temp+nb;
    ui->NbMp3Album->setText("<dd><dd>Albums: "+QString::number(temp));

    ui->NbMp3ScAlbum->setText("Categorie Albums: "+QString::number(nb));
    ui->NbMp3Compil->setText("Categorie Compils: "+QString::number(m_bddInterface.NbMp3Categorie(2)));

}
void OngletStats::AfficherInfosCategoriesPhys()
{
    ui->NbPhysAlbum->setText("<dd>Albums : "+QString::number(m_bddInterface.NbPhysCategorie(1)));
    ui->NbPhysCompil->setText("<dd>Singles : "+QString::number(m_bddInterface.NbPhysCategorie(3)));
    ui->NbPhysSingle->setText("<dd>Compils : "+QString::number(m_bddInterface.NbPhysCategorie(2)));
}

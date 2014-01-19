#include "ongletmp3.h"
#include "ui_ongletmp3.h"
#include <QStringListModel>

OngletMp3::OngletMp3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletMp3)
{
    ui->setupUi(this);
    afficherListeArtiste();
}

OngletMp3::~OngletMp3()
{
    delete ui;
}
void OngletMp3::afficherListeArtiste()
{
QStringList artistes;
artistes << "Alex" << "Nico" << "titou" << "dlkdlk"<<"lddkfd"<<"nnnn"<<"dkjd";

for (int cpt=0;cpt<artistes.count();cpt++) {

    QListWidgetItem *mediaCell = new  QListWidgetItem ();
    QPixmap* pixmap = new QPixmap();

 /*   if (ui->ListeTypes->currentRow()==0)
    {
        QString Chemin=m_bddInterface.afficherPochette(artistes[cpt+1],"Artiste");
        //On s'occupe de la pochette

        QImage* image=new QImage(Chemin);


        pixmap->convertFromImage(*image);
        mediaCell->setIcon(QIcon(*pixmap));
        mediaCell->setData(Qt::UserRole,artistes[cpt+1]);
    } else
    {
*/
    QImage * image=new QImage("./Pochettes/def.jpg");
        pixmap->convertFromImage(*image);
        mediaCell->setIcon(QIcon(*pixmap));
        mediaCell->setData(Qt::UserRole,artistes[cpt]);

//    }
    mediaCell->setText(artistes[cpt]);

    ui->Artistes->addItem(mediaCell);
    ui->Artistes->item(0)->setSelected(true);
/*    if (ui->ListeTypes->currentRow()==0)
    {
        cpt++;
    }
*/
}
}



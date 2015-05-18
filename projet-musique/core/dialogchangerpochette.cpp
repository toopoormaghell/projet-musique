#include "dialogchangerpochette.h"
#include "ui_dialogchangerpochette.h"
#include "util.h"
#include <QDebug>
#include <QFileDialog>

DialogChangerPochette::DialogChangerPochette(int Artiste, QWidget *parent) :
    QDialog(parent),
    Id_Artiste(Artiste),
    ui(new Ui::DialogChangerPochette)
{
    ui->setupUi(this);
    AfficherPochette();
}
DialogChangerPochette::~DialogChangerPochette()
{
    delete ui;
}
void DialogChangerPochette::AfficherPochette()
{


    QList<Pochette> liste=m_bddInterface.ListePochettes(Id_Artiste);
    for (int cpt=0;cpt<liste.count();cpt++)
    {
        Pochette poch=liste[cpt];
        QListWidgetItem *mediaCell= affi.afficherPochetteList(poch.Pochette);
        mediaCell->setText(poch.Nom);
        mediaCell->setData(Qt::UserRole,poch.Id_Poch);

        ui->ListePoch->addItem(mediaCell);
    }
}
void DialogChangerPochette::on_AjouterPochette_clicked()
{
    QString fileName = QFileDialog::getOpenFileName( this,
                                                     "Ouvrir l'image contenant la pochette",
                                                     "C:/Users/Nico/Desktop",
                                                     "Images (*.png *.xpm *.jpg *.bmp)" );
   QImage* image=new QImage(fileName);
    QListWidgetItem *mediaCell = affi.afficherPochetteList(*image);
    mediaCell->setText("Ajout");
    ui->ListePoch->insertItem(0,mediaCell);
}
QString DialogChangerPochette::getId()
{
    return Id_Pochette;
}

void DialogChangerPochette::on_buttonBox_accepted()
{
    QListWidgetItem *item= ui->ListePoch->currentItem();

    if (item->text()!="Ajout")
    {
        Id_Pochette=item->data(Qt::UserRole).toString();
    } else {

    }
}

void DialogChangerPochette::on_ListePoch_itemDoubleClicked(QListWidgetItem *item)
{
  on_buttonBox_accepted();

}

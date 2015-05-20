#include "dialogajouterphys.h"
#include "ui_dialogajouterphys.h"
#include "qdebug.h"
#include "bddgestionphys.h"
#include "util.h"

DialogAjouterPhys::DialogAjouterPhys(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAjouterPhys)
{
    ui->setupUi(this);
}

DialogAjouterPhys::~DialogAjouterPhys()
{
    delete ui;
}
QString DialogAjouterPhys::recupererEAN() const
{

    return ui->EAN->text();
}

void DialogAjouterPhys::on_buttonBox_accepted()
{
BDDGestionPhys m_bddinterface;

  QImage* image=new QImage("./Pochettes/def.jpg");
  QList<TitresPhys> titres;
  TitresPhys temp;
  temp.Duree="03:45";
  temp.Num_Piste=01;
  temp.Titre="blablabla";
  titres << temp;
m_bddinterface.ajouterAlbum(*image,"bla","art",144444444,2015,titres,01);
}

void DialogAjouterPhys::on_ChercherEAN_clicked()
{
    QString temp=recupererEAN();
    ui->Interaction->setText(temp);
}

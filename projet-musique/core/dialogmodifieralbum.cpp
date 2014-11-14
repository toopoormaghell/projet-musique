#include "dialogmodifieralbum.h"
#include "ui_dialogmodifieralbum.h"
#include "QDebug"

DialogModifierAlbum::DialogModifierAlbum(AlbumGestion album_modif, QWidget *parent) :
    QDialog(parent),
    album(album_modif),
    ui(new Ui::DialogModifierAlbum)
{
    ui->setupUi(this);
    ui->Album->setText(album.Album);
    ui->Artiste->setText(album.Artiste);
    ui->Annee->setText(album.Annee);
    QPixmap* pixmap = new QPixmap();
    pixmap->convertFromImage(album.Pochette);

    QPixmap imageScaled = pixmap->scaled(150,150,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    ui->Poch->setPixmap(imageScaled);
    ui->Titres->clear();
    for(int cpt=0;cpt<album.titres.count();cpt++)
    {
        TitreGestion titre=album.titres[cpt];
        titre.Num_Piste=cpt+1;
        QListWidgetItem *item=new QListWidgetItem();
        item->setText(titre.Titre+"("+titre.Duree+")");
        ui->Titres->addItem(item);
    }

    ui->m_type->setCurrentIndex(ChoisirType(album.Type));

}

DialogModifierAlbum::~DialogModifierAlbum()
{
    delete ui;
}
int DialogModifierAlbum::ChoisirType(QString Type)
{
    int num_Type=0;
    if (Type=="Compil")
    {
        num_Type=1;
    }
    if (Type=="Single")
    {
        num_Type=2;
    }

    return num_Type;

}
void DialogModifierAlbum::EnregistrerAlbum()
{
    album.Type=getType();
    album.Album=ui->Album->text();
    album.Annee=ui->Annee->text();
    album.Artiste=ui->Artiste->text();

    album.titres.clear();

    for (int i=0;i<ui->Titres->count();i++)
    {
        TitreGestion titre;
        QListWidgetItem *item= ui->Titres->item(i);
        QStringList parsing = item->text().split("(");
        titre.Titre=parsing[0];

        QStringList parsing2 = parsing[1].split(")");
        titre.Duree=parsing2[0];
        titre.Num_Piste=i+1;

        album.titres << titre;
    }


}
QString DialogModifierAlbum::getType() const
{
    return ui->m_type->currentText();
}

void DialogModifierAlbum::on_buttonBox_accepted()
{
    EnregistrerAlbum();
    m_bddInterface.ModifierAlbumPhys(album);
}

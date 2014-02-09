#include "dialogueajouterphysique.h"
#include "ui_dialogueajouterphysique.h"
#include "discogs.h"
#include <QDebug>
#include <QFileDialog>

DialogueAjouterPhysique::DialogueAjouterPhysique(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogueAjouterPhysique)
{
    ui->setupUi(this);
}

DialogueAjouterPhysique::~DialogueAjouterPhysique()
{
    delete ui;
}

QString DialogueAjouterPhysique::getCodeBarre() const
{
    return ui->m_codeBarre->text();
}

QString DialogueAjouterPhysique::getType() const
{
    return ui->m_type->currentText();
}

void DialogueAjouterPhysique::on_pushButton_clicked()
{
    Discogs temp;
    QStringList resultat;
    resultat = temp.RequeteAlbums( getCodeBarre() );

    if (!resultat.isEmpty()) {
        ui->Interaction->setText("CD trouvé. Vérifiez les informations.");
        AlbumGestion *album = temp.RequeteInfosAlbum(resultat[0],resultat[1]);
        album->Type = getType();

        ui->Album->setText(album->Album);
        ui->Annee->setText(album->Annee);
        ui->Artiste->setText(album->Artiste);

        QPixmap* pixmap = new QPixmap();
        pixmap->convertFromImage(album->Pochette);

        QPixmap imageScaled = pixmap->scaled(150,150,Qt::IgnoreAspectRatio,Qt::FastTransformation);
        ui->Pochette->setPixmap(imageScaled);
        ui->Titres->clear();
        for(int cpt=0;cpt<album->titres.count();cpt++)
        {
            TitreGestion titre=album->titres[cpt];
            titre.Num_Piste=cpt+1;
            QListWidgetItem *item=new QListWidgetItem();
            item->setText(titre.Titre+"("+titre.Duree+")");
            ui->Titres->addItem(item);
        }

        listeNumeros();
    } else {

        ui->Interaction->setText("Le code de barres n'a pas été trouvé. Le CD doit être rentré manuellement.");
    }

}
void DialogueAjouterPhysique::on_AjouterTitre_clicked()
{
    QListWidgetItem *item=new QListWidgetItem();
    item= ui->Titres->item(0);

    if(item->text()=="Liste des Titres")
    {
        ui->Titres->clear();
    }

    QString inputMask("00:00");
    ui->DureeAjout->setInputMask(inputMask);

    QString Titre=ui->TitreAjout->text();
    QString Duree=ui->DureeAjout->text();
    item=new QListWidgetItem();

    item->setText(Titre+"("+Duree+")");
    ui->Titres->addItem(item);

    listeNumeros();
}
void DialogueAjouterPhysique::listeNumeros()
{
    ui->NumeroPiste->clear();
    for (int i=1;i<ui->Titres->count()+1;i++)
    {
        ui->NumeroPiste->addItem(new QListWidgetItem(QString::number(i).rightJustified(2,'0')+" - "));
    }
}

void DialogueAjouterPhysique::on_Supprimer_clicked()
{
    QList<QListWidgetItem *> fileSelected = ui->Titres->selectedItems();
    if(fileSelected.size())
    {
        for (int i = 0; i < ui->Titres->count(); ++i)
        {
            if(ui->Titres->item(i)->isSelected())
            {
                QListWidgetItem * item = ui->Titres->takeItem(i);
                delete item;
            }
        }
    }
    listeNumeros();
}

void DialogueAjouterPhysique::on_ChangerPochette_clicked()
{
    QString fileName = QFileDialog::getOpenFileName( this,
                                                     "Ouvrir l'image contenant la pochette",
                                                     "C:/Users/Nico/Desktop",
                                                     "Images (*.png *.xpm *.jpg *.bmp)" );
    QPixmap* pixmap = new QPixmap();
    QImage* image=new QImage(fileName);
    pixmap->convertFromImage(*image);
    QPixmap pixmapscaled= pixmap->scaled(150,150,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    ui->Pochette->setPixmap(pixmapscaled);
}

void DialogueAjouterPhysique::on_buttonBox_accepted()
{
    ajouterAlbum();
}
void DialogueAjouterPhysique::ajouterAlbum()
{
    AlbumGestion album;
    album.Type=getType();
    album.Album=ui->Album->text();
    album.Annee=ui->Annee->text();
    album.Artiste=ui->Artiste->text();
    album.CodeBarres=getCodeBarre();

    const QPixmap* pixmap =ui->Pochette->pixmap();
    QImage image = pixmap->toImage();
    album.Pochette=image;

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
    m_bddInterface.ajouterAlbumPhysique(album);
    ui->Interaction->setText("CD entré dans la BDD");
}

void DialogueAjouterPhysique::on_AjouterTitre_2_clicked()
{
    ajouterAlbum();
    ui->Titres->clear();
    ui->Album->clear();
    ui->Annee->clear();
    ui->Artiste->clear();
    ui->m_codeBarre->clear();
    ui->Pochette->clear();
}

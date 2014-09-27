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
    AffichageArtistesCompil();
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
void DialogueAjouterPhysique::AffichageArtistesCompil()
{
    if (getType()!="Compil")
    {
        ui->ArtistesTitres->setHidden(true);
    }
    else
    {
        ui->ArtistesTitres->setHidden(false);
    }
}
void DialogueAjouterPhysique::ChargerCompil()
{
    ui->Titres->clear();
    ui->ArtistesTitres->clear();
    ui->Artiste->setText("Divers");
    ui->Album->setText(compil.Album);
    ui->Annee->setText(compil.Annee);

    QPixmap* pixmap = new QPixmap();
    pixmap->convertFromImage(compil.Pochette);

    QPixmap imageScaled = pixmap->scaled(150,150,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    ui->Pochette->setPixmap(imageScaled);

    for(int cpt=0;cpt<compil.titres.count();cpt++)
    {
        MP3Gestion titre=compil.titres[cpt];
        titre.Num_Piste=cpt+1;
        QListWidgetItem *item=new QListWidgetItem();
        item->setText(titre.Titre+"("+titre.Duree+")");
        ui->Titres->addItem(item);
        QListWidgetItem *item2=new QListWidgetItem();
        item2->setText(titre.Artiste);
        ui->ArtistesTitres->addItem(item2);
    }

    listeNumeros();
}

void DialogueAjouterPhysique::on_Codebarres_clicked()
{
    ui->Interaction->setText("Interrogation de l'API...");
    Discogs temp;
    QString codeBarres= getCodeBarre();
    if ( codeBarres.size()==13) {

        if (getType()=="Compil")
        {
            compil=temp.RequeteCompil( codeBarres );

        } else {
            album = temp.RequeteAlbums( codeBarres );

        }


        if (album.Album!="Non trouvé" || compil.Album!="Non trouvé")
        {
            ui->Interaction->setText("CD trouvé. Vérifiez les informations.");

            if (getType()=="Compil")
            {
                ChargerCompil();
            } else
            {

                ui->Artiste->setText(album.Artiste);
                album.Type = getType();

                ui->Album->setText(album.Album);
                ui->Annee->setText(album.Annee);

                QPixmap* pixmap = new QPixmap();
                pixmap->convertFromImage(album.Pochette);

                QPixmap imageScaled = pixmap->scaled(150,150,Qt::IgnoreAspectRatio,Qt::FastTransformation);
                ui->Pochette->setPixmap(imageScaled);
                ui->Titres->clear();
                for(int cpt=0;cpt<album.titres.count();cpt++)
                {
                    TitreGestion titre=album.titres[cpt];
                    titre.Num_Piste=cpt+1;
                    QListWidgetItem *item=new QListWidgetItem();
                    item->setText(titre.Titre+"("+titre.Duree+")");
                    ui->Titres->addItem(item);
                }

                listeNumeros();
            }
        } else {

            ui->Interaction->setText("Le code-barres n'a pas été trouvé. Le CD doit être rentré manuellement.");
        } }
    else
    {
        ui->Interaction->setText("Le code barres n'est pas valable. Veuillez tapez 13 chiffres.");
    }
}
void DialogueAjouterPhysique::on_AjouterTitre_clicked()
{
    QListWidgetItem *item= ui->Titres->item(0);

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

    ui->TitreAjout->clear();

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
    if (ui->Artiste->text()!="")
    {
        if(getType()=="Compil")
        {
            ajouterCompil();
        } else
        {
            ajouterAlbum();
        }
        emit AlbumAjoute();

        ui->Titres->clear();
        ui->Album->clear();
        ui->Annee->clear();
        ui->Artiste->clear();
        ui->m_codeBarre->clear();
        ui->Pochette->clear();
        ui->DureeAjout->clear();
        ui->TitreAjout->clear();
        ui->NumeroPiste->clear();
        album.Album="Non trouvé";
        compil.Album="Non trouvé";


    } else {
        ui->Interaction->setText("Il manque des informations pour enregistrer l'album.");
    }
}
void DialogueAjouterPhysique::ajouterAlbum()
{

    album.Type=getType();
    album.Album=ui->Album->text();
    album.Annee=ui->Annee->text();
    album.Artiste=ui->Artiste->text();
    album.CodeBarres=getCodeBarre();

    const QPixmap* pixmap =ui->Pochette->pixmap();
    QImage image = pixmap->toImage();
    album.Pochette=image;

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
    m_bddInterface.ajouterAlbumPhysique(album);
    ui->Interaction->setText("CD entré dans la BDD");
}
void DialogueAjouterPhysique::ajouterCompil()
{
    compil.Type=getType();
    compil.Album=ui->Album->text();
    compil.Annee=ui->Annee->text();
    compil.Artiste=ui->Artiste->text();
    compil.CodeBarres=getCodeBarre();

    const QPixmap* pixmap =ui->Pochette->pixmap();
    QImage image = pixmap->toImage();
    compil.Pochette=image;

    compil.titres.clear();
    for (int i=0;i<ui->Titres->count();i++)
    {
        MP3Gestion titre;
        QListWidgetItem *item= ui->Titres->item(i);
        QStringList parsing = item->text().split("(");
        titre.Titre=parsing[0];

        QStringList parsing2 = parsing[1].split(")");
        titre.Duree=parsing2[0];
        titre.Num_Piste=i+1;

        QListWidgetItem *art=ui->ArtistesTitres->item(i);
        titre.Artiste=art->text();

        compil.titres << titre;
    }
    m_bddInterface.ajouterCompilPhysique(compil);
    ui->Interaction->setText("CD entré dans la BDD");
}

void DialogueAjouterPhysique::on_AjouterTitre_2_clicked()
{
    if (!ui->Artiste->text().isNull() || !ui->Album->text().isNull())
    {
        ajouterAlbum();
        ui->Titres->clear();
        ui->Album->clear();
        ui->Annee->clear();
        ui->Artiste->clear();
        ui->m_codeBarre->clear();
        ui->Pochette->clear();
        ui->DureeAjout->clear();
        ui->TitreAjout->clear();
        ui->NumeroPiste->clear();
    } else
    {
        ui->Interaction->setText("Il manque des informations pour enregistrer l'album.");
    }
}

void DialogueAjouterPhysique::on_m_type_currentIndexChanged(const QString &arg1)
{
    AffichageArtistesCompil();
}


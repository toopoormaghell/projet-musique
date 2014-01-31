#include "ongletmp3.h"
#include "ui_ongletmp3.h"
#include <QStringListModel>
#include <phonon>

OngletMp3::OngletMp3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletMp3)
{
    ui->setupUi(this);
    afficherListeCategories();
    if (ui->Categories->count()>0)
    {
        ui->Artistes->clear();
        afficherListeArtiste();
        afficherListeAlbum();
    }
}

OngletMp3::~OngletMp3()
{
    delete ui;
}
void OngletMp3::afficherListeArtiste()
{
    //Choix de la Categorie des Mp3 à afficher
    QListWidgetItem *item=ui->Categories->currentItem();
    if (item==NULL)
    {
        item=ui->Categories->item(0);
    }
    QString Categorie=item->text();

    //Affichage des artistes
    QStringList artistes=m_bddInterface.listeArtistesMp3(Categorie);

    for (int cpt=0;cpt<artistes.count();cpt=cpt+2) {

        QListWidgetItem *mediaCell = new  QListWidgetItem ();
        QPixmap* pixmap = new QPixmap();

        //On s'occupe de la pochette
        QImage image=m_bddInterface.afficherPochette(artistes[cpt+1],"Artiste");
        pixmap->convertFromImage(image);
        QPixmap pixmapscaled= pixmap->scaled(150,150,Qt::IgnoreAspectRatio,Qt::FastTransformation);
        mediaCell->setIcon(QIcon(pixmapscaled));
        //On s'occupe du nom de l'artiste
        mediaCell->setData(Qt::UserRole,artistes[cpt+1]);
        mediaCell->setText(artistes[cpt]);

        ui->Artistes->addItem(mediaCell);
        ui->Artistes->item(0)->setSelected(true);

    }
}
void OngletMp3::afficherListeCategories()
{
    QStringList categories=m_bddInterface.listeCategoriesMp3();
    for (int cpt=0;cpt<categories.count();cpt++) {
        QListWidgetItem *mediaCell = new  QListWidgetItem ();
        QPixmap* pixmap = new QPixmap();
        QImage* image=new QImage("./Pochettes/def.jpg");
        pixmap->convertFromImage(*image);
        mediaCell->setIcon(QIcon(*pixmap));
        //On s'occupe du nom de l'artiste
        mediaCell->setText(categories[cpt]);

        ui->Categories->addItem(mediaCell);
        ui->Categories->item(0)->setSelected(true);
    }
}
void OngletMp3::afficherListeAlbum()
{
    //Choix de l'Artiste des Albums à afficher
    QListWidgetItem *item=ui->Artistes->currentItem();
    if (item==NULL)
    {
        item=ui->Artistes->item(0);
    }
    QString Artiste=item->data(Qt::UserRole).toString();

    //Affichage des albums
    QStringList albums=m_bddInterface.listeAlbumsMp3(Artiste);

    for (int cpt=0;cpt<albums.count();cpt=cpt+2) {

        QListWidgetItem *mediaCell = new  QListWidgetItem ();
        QPixmap* pixmap = new QPixmap();

        //On s'occupe de la pochette

        QImage image=m_bddInterface.afficherPochette(albums[cpt+1],"Album");
        pixmap->convertFromImage(image);
        QPixmap pixmapscaled= pixmap->scaled(150,150,Qt::IgnoreAspectRatio,Qt::FastTransformation);
        mediaCell->setIcon(QIcon(pixmapscaled));
        //On s'occupe du nom de l'album
        mediaCell->setFlags(Qt::ItemIsEnabled );
        mediaCell->setText(albums[cpt]);

        ui->Albums->addItem(mediaCell);
        afficherTitresAlbum(albums[cpt+1]);
        ui->Albums->item(1)->setSelected(true);

    }
}
void OngletMp3::afficherTitresAlbum(QString Album)
{
    QStringList titres=m_bddInterface.listeTitresAlbumMp3(Album);

    for (int cpt=0;cpt<titres.count();cpt=cpt+2)
    {
        QListWidgetItem *item=new QListWidgetItem();
        item->setData(Qt::UserRole,titres[cpt+1]);
        item->setText(titres[cpt]);
        ui->Albums->addItem(item);
    }

}
void OngletMp3::afficherInfosTitre()
{




}
void OngletMp3::lectureMp3(bool lect)
{
    QString fileName("F:/Albums/Jenifer/06 - Je Danse.mp3");
    Phonon::MediaObject* media = new Phonon::MediaObject(this);
    createPath(media, new Phonon::AudioOutput(Phonon::MusicCategory, this));
    media->setCurrentSource(fileName);
    if(lect)
    {
        media->play();
    } else
    {
        media->stop();
    }
}
void OngletMp3::on_Artistes_currentTextChanged(const QString &arg1)
{
    ui->Albums->clear();
    afficherListeAlbum();
    afficherInfosTitre();
}
void OngletMp3::on_Categories_currentTextChanged(const QString &currentText)
{
    if (ui->Categories->count()>0)
    {
        ui->Artistes->clear();
        afficherListeArtiste();
        afficherListeAlbum();
    }
}
void OngletMp3::on_Lecture_clicked()
{
    lectureMp3(true);
}

void OngletMp3::on_Stop_clicked()
{
    lectureMp3(false);
}

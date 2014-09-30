#include "ongletmp3.h"
#include "ui_ongletmp3.h"
#include <QStringListModel>
#include <phonon>
#include "affichagecommun.h"
#include "dialogajouterplaylistmp3.h"

OngletMp3::OngletMp3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletMp3)
{
    ui->setupUi(this);
    afficherListeCategories();

    ui->m_player->setParentTab( *this );
}
OngletMp3::~OngletMp3()
{
    delete ui;
}
void OngletMp3::afficherListeCategories()
{
    QStringList categories=m_bddInterface.listeCategoriesMp3();
    for (int cpt=0;cpt<categories.count();cpt++) {
        QImage* image=new QImage("./Pochettes/def.jpg");
        QListWidgetItem *mediaCell=temp.afficherPochetteList(image);
        //On s'occupe du nom de l'artiste
        mediaCell->setText(categories[cpt]);

        ui->Categories->addItem(mediaCell);
        ui->Categories->setCurrentRow(0);
    }
}
void OngletMp3::afficherListeArtiste()
{
    //Choix de la Categorie des Mp3 à afficher
    QString Categorie=choixCategorie();

    //Affichage des artistes
    QStringList artistes=m_bddInterface.listeArtistesMp3(Categorie);

    for (int cpt=0;cpt<artistes.count();cpt=cpt+2) {
        //On s'occupe de la pochette
        QImage image=m_bddInterface.afficherPochette(artistes[cpt+1],"Artiste");
        QListWidgetItem *mediaCell=temp.afficherPochetteList(&image);

        //On s'occupe du nom de l'artiste
        mediaCell->setData(Qt::UserRole,artistes[cpt+1]);
        mediaCell->setText(artistes[cpt]);

        ui->Artistes->addItem(mediaCell);
        ui->Artistes->setCurrentRow(0);
    }
}
void OngletMp3::afficherListeAlbum()
{
    //Choix de l'Artiste des Albums à afficher
    QString Artiste=choixArtiste();

    //Affichage des albums
    QStringList albums=m_bddInterface.listeAlbumsMp3(Artiste);

    for (int cpt=0;cpt<albums.count();cpt=cpt+2) {
        //On s'occupe de la pochette
        QImage image=m_bddInterface.afficherPochette(albums[cpt+1],"Album");
        QListWidgetItem *mediaCell=temp.afficherPochetteList(&image);
        //On s'occupe du nom de l'album
        mediaCell->setFlags(Qt::ItemIsEnabled );
        mediaCell->setText(albums[cpt]);

        ui->Albums->addItem(mediaCell);
        afficherTitresAlbum(albums[cpt+1]);
    }
    ui->Albums->setCurrentRow(1);
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
    QString cmp3=choixMp3();

    MP3Gestion mp3=m_bddInterface.RecupererInfosMp3(cmp3.toInt());

    //On affiche la pochette
    ui->Pochette->setPixmap(temp.afficherPochetteLabel(&mp3.Pochette));

    //On affiche le titre
    QString titre=QString::number(mp3.Num_Piste).rightJustified(2,'0')+" - "+mp3.Titre.toUpper()+"("+mp3.Duree+")";
    ui->Titre->setText(titre);

    //On affiche l'artiste
    ui->NomArtiste->setText("de "+mp3.Artiste.toUpper());

    //on affiche l'album
    ui->NomAlbum->setText("sur "+mp3.Album.toUpper()+"("+mp3.Annee+")");

    //on affiche si le mp3 existe en phys
    if(mp3.TitreenMp3etPhys)
    {
        ui->Mp3Phys->setText("Existe sur Support Physique");
    }
    else
    {
        ui->Mp3Phys->clear();
    }
}
void OngletMp3::afficherSimilaires()
{
    ui->Similaires->clear();
    QString mp3choisi = choixMp3();

    QMap<int, MP3Gestion> simi=m_bddInterface.similaires(mp3choisi);
    QMap<int,MP3Gestion>::const_iterator iterateur;

    for (iterateur = simi.constBegin();iterateur != simi.constEnd();++iterateur)
    {
        MP3Gestion mp3 = iterateur.value();
        QListWidgetItem *mediaCell= temp.afficherPochetteList(&mp3.Pochette);
        //On s'occupe du nom du mp3
        mediaCell->setText(mp3.Titre+" de "+mp3.Artiste+("(")+mp3.Album+")");
        mediaCell->setData(Qt::UserRole,mp3.Id_Titre);
        ui->Similaires->addItem(mediaCell);
    }
}
void OngletMp3::changerMp3()
{
    QString cmp3= choixSimilaires();

    MP3Gestion mp3=m_bddInterface.RecupererInfosMp3(cmp3.toInt());

    ui->Artistes->setCurrentRow(changerArtiste(mp3.Id_Artiste));
    ui->Albums->setCurrentRow(changerAlbum(mp3.Id_Titre));
}
int OngletMp3::changerAlbum(int Id_Titre)
{
    int resultat=0;

    for (int cpt=0;cpt<ui->Albums->count();cpt++)
    {
        QListWidgetItem *item=ui->Albums->item(cpt);
        int tmp=item->data(Qt::UserRole).toInt();

        if(Id_Titre==tmp)
        {
            resultat=cpt;
        }
    }
    return resultat;
}
int OngletMp3::changerArtiste(int Id_Artiste)
{
    int resultat=0;

    for (int cpt=0;cpt<ui->Artistes->count();cpt++)
    {
        QListWidgetItem *item=ui->Artistes->item(cpt);
        int tmp=item->data(Qt::UserRole).toInt();

        if(Id_Artiste==tmp)
        {
            resultat=cpt;
        }
    }
    return resultat;
}
QString OngletMp3::choixCategorie()
{
    QListWidgetItem *item=ui->Categories->currentItem();
    if (item==NULL)
    {
        item=ui->Categories->item(0);
    }
    return item != NULL ? item->text() : QString();
}
QString OngletMp3::choixArtiste()
{
    QListWidgetItem *item=ui->Artistes->currentItem();
    if (item==NULL)
    {
        item=ui->Artistes->item(0);
    }
    return item != NULL ? item->data(Qt::UserRole).toString() : QString();
}
QString OngletMp3::choixMp3()
{
    QListWidgetItem *item=ui->Albums->currentItem();
    if(item==NULL)
    {
        item=ui->Albums->item(1);
    }
    return item != NULL ? item->data(Qt::UserRole).toString() : QString();
}
QString OngletMp3::choixSimilaires()
{
    QListWidgetItem *item=ui->Similaires->currentItem();
    if(item==NULL)
    {
        item=ui->Similaires->item(0);
    }
    return item != NULL ? item->data(Qt::UserRole).toString() : QString();
}
void OngletMp3::afficherListeAnnees()
{
    QStringList ListeAnnees;
    ListeAnnees << "Avant 1980" <<"1980-1990"<< "1990-2000" << "2000-2005" << "2005-2010" << "2010-2014" ;
    for (int cpt=0;cpt<ListeAnnees.count();cpt++) {

        QListWidgetItem *mediaCell;
        QImage* image=new QImage("./Pochettes/def.jpg");
        mediaCell=temp.afficherPochetteList(image);
        //On s'occupe du nom de l'artiste
        mediaCell->setText(ListeAnnees[cpt]);

        ui->Artistes->addItem(mediaCell);
    }
    ui->Artistes->setCurrentRow(0);
}
void OngletMp3::afficherListeMp3Compil()
{
    QString requete= AnneesSwitch(ui->Artistes->currentRow());
    if (requete!="pas bon")
    {
        QString annee="0";
        QList<int> listeMp3=m_bddInterface.ListeMp3Compil(requete);
        for (int cpt=0;cpt<listeMp3.count();cpt++)
        {
            MP3Gestion mp3=m_bddInterface.RecupererInfosMp3(listeMp3[cpt]);
            if(annee!=mp3.Annee)
            {
                annee=mp3.Annee;
                QListWidgetItem *Cellu=new QListWidgetItem;
                Cellu->setText(annee);

                ui->Albums->addItem(Cellu);

            }
            QListWidgetItem *mediaCell;
            if (mp3.Pochette.isNull())
            {
                QImage* image=new QImage("./Pochettes/def.jpg");
                mediaCell=temp.afficherPochetteList(image);
            } else {
                mediaCell = temp.afficherPochetteList(&mp3.Pochette);
            }

            mediaCell->setText(mp3.Titre+"("+mp3.Artiste+")");
            mediaCell->setData(Qt::UserRole,listeMp3[cpt]);
            ui->Albums->addItem(mediaCell);
        }
        ui->Albums->setCurrentRow(1);
    }
}
QString OngletMp3::AnneesSwitch(int annee)
{
    switch (annee)
    {
    case 0: return " Annee <1980";
    case 1: return " Annee >=1980 AND Annee <1990";
    case 2: return " Annee >=1990 AND Annee<2000";
    case 3: return " Annee>=2000 AND Annee<2005";
    case 4: return " Annee>=2005 AND Annee<2010";
    case 5: return " Annee>=2010";
    default: return "pas bon";
    }
}
void OngletMp3::on_Artistes_currentTextChanged(const QString &arg1)
{
    vider("Albums");
    if (choixCategorie()!="Compil")
    {
        afficherListeAlbum();
    } else {
        afficherListeMp3Compil();
    }
}
void OngletMp3::on_Categories_currentTextChanged(const QString &currentText)
{
    if (ui->Categories->count()>0)
    {
        vider("Artiste");
        if (choixCategorie()!="Compil")
        {
            afficherListeArtiste();
        } else
        {
            afficherListeAnnees();
        }
    }
}
void OngletMp3::vider(QString Type)
{
    if (Type=="Artiste")
    {
        ui->Artistes->clear();
    }
    if (Type=="Categories")
    {
        ui->Categories->clear();
    }
    if (Type=="Albums")
    {
        ui->Albums->clear();
    }
}

void OngletMp3::on_Albums_currentRowChanged(int currentRow)
{
    afficherInfosTitre();
    Playlist();
    afficherSimilaires();
}
QString OngletMp3::getSelectedTitleId() const
{
    QString valueToReturn;
    const QListWidgetItem* const selectedSong = ui->Albums->currentItem();
    if ( selectedSong != NULL )
        valueToReturn = selectedSong->data( Qt::UserRole ).toString();
    return valueToReturn;
}
void OngletMp3::on_Similaires_doubleClicked(const QModelIndex &index)
{
    changerMp3();
}
void OngletMp3::on_Bouton_Playlist_clicked()
{
    DialogAjouterPlaylistMp3 temp(choixMp3(),this);
    temp.exec();
    Playlist();
}
void OngletMp3::Playlist()
{

    QString mp3choisi = choixMp3();

    ui->Playlists->clear();
    QStringList resultat(m_bddInterface.listePlaylistMp3(mp3choisi));
    if ( resultat.size()==0) {
        ui->Playlists->addItem(new QListWidgetItem("Pas de playlist"));
    } else
    {
        int cpt=0;
        while (cpt<resultat.size()/2)
        {
            //On s'occupe de la pochette

            QPixmap* pixmap = new QPixmap();
            QImage* image=new QImage(resultat[cpt+1]);
            pixmap->convertFromImage(*image);

            QListWidgetItem *mediaCell = new QListWidgetItem();
            mediaCell->setIcon(QIcon(*pixmap));
            mediaCell->setText(resultat[cpt]);
            mediaCell->setTextAlignment(Qt::AlignCenter );


            ui->Playlists->addItem(mediaCell);
            cpt++;
            cpt++;
        }
    }
}

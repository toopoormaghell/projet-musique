#include "ongletplaylist.h"
#include "ui_ongletplaylist.h"
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>
#include "meta_titre.h"
#include <QDir>
#include <QFile>


OngletPlaylist::OngletPlaylist(QWidget *parent) :
    QWidget(parent),
    m_playlist_selectionne(-1 ),
    ui(new Ui::OngletPlaylist)
{
    ui->setupUi(this);
    ActualiserOnglet();
}

OngletPlaylist::~OngletPlaylist()
{
    delete ui;
}
void OngletPlaylist::appliquerstyle( QString stylecoul )
{
    setStyleSheet( stylecoul );
    update();
}
void OngletPlaylist::on_SupprimerPlaylist_clicked()
{
    int reponse  = QMessageBox::question(this, "Verification", "Etes-vous sûr de vouloir supprimer "+ ui->ListePlaylist->currentItem()->text() + "?", QMessageBox::Yes | QMessageBox::No);

    if ( reponse == QMessageBox::Yes )
    {
        m_bddInterface->SupprimerPlaylist( ui->ListePlaylist->currentItem()->data( Qt::UserRole ).toInt() );
        ActualiserOnglet();
    }
    else if (reponse == QMessageBox::No)
    {
        qDebug() << "non";
    }
}
void OngletPlaylist::AfficherPlaylist()
{
    ui->ListePlaylist->clear();

    QStringList liste;
    liste += m_bddInterface->listePlaylist();

    for (int i = 0; i < liste.count(); i=i+2 )
    {
        QListWidgetItem* item = new QListWidgetItem;
        //on affiche la pochette et le nom de l'album
        item->setData( Qt::UserRole, liste[i] );
        QString nb = m_bddInterface->NbMp3( liste[i].toInt() );
        item->setText( liste[i+1]  +  " (" + nb + ")" ) ;
        ui->ListePlaylist->addItem( item );

    }
    ui->ListePlaylist->setCurrentRow( 0 );
}

void OngletPlaylist::on_AjouterPlaylist_clicked()
{
    bool ok = false;
    QString nom_playlist = QInputDialog::getText(this, "Nouvelle Playlist", "Quel sera le nom de la nouvelle playlist ?", QLineEdit::Normal, QString(), &ok);

    if (ok && !nom_playlist.isEmpty())
    {
        m_bddInterface->EnregistrerPlaylist( nom_playlist );
        ActualiserOnglet();
    }
    else
    {

        qDebug() << "test ";
    }
}
void OngletPlaylist::ActualiserOnglet()
{
    AfficherPlaylist();
}


void OngletPlaylist::ListeMp3( int Ordre)
{

    ui->ListeMp3->clear();

    QList<int> liste = m_bddInterface->listeMp3( m_playlist_selectionne, Ordre );

    for (int i = 0; i < liste.count(); i++ )

    {
        //On récupère les infos du titre
        Meta_Titre* mp3 = Meta_Titre::RecupererBDD( liste[i] );

        //On affiche les infos du titre dans un item
        QListWidgetItem* item = new QListWidgetItem;
        item->setData( Qt::UserRole, mp3->getid_relation() );
        item->setText( QString::number( mp3->getnum_piste() ).rightJustified(2,'0') + " - " + mp3->getnom_titre() );
        item->setToolTip( mp3->getnom_titre() );
        item->setFlags( Qt::ItemIsEnabled );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( mp3->getpoch() ) );
        item->setIcon( QIcon( scaled ) );

        ui->ListeMp3->addItem( item );

        delete mp3;

    }
}

void OngletPlaylist::on_ListePlaylist_currentRowChanged(int currentRow)
{
    Q_UNUSED( currentRow)
    if ( currentRow != -1 )
    m_playlist_selectionne = ui->ListePlaylist->currentItem()->data( Qt::UserRole ).toInt();
    ListeMp3( 1 );
}

void OngletPlaylist::on_Copier_clicked()
{
    CopierListe();
}

void OngletPlaylist::CopierListe()
{
    QList<int> liste = m_bddInterface->listeMp3( m_playlist_selectionne, 1 );

    for (int i = 0; i < liste.count(); i++ )

    {
        Meta_Titre* mp3 = Meta_Titre::RecupererBDD( liste[i] );
    //    qDebug() << mp3->getnom_album() << mp3->getcheminmp3() << QString::number( mp3->getid_mp3() ) << QString::number( mp3->getid_relation() );
        QFileInfo fich( mp3->getcheminmp3() );
        QString doss = ("C:/Users/Alex/Desktop/Musique/");

        doss +=  ui->ListePlaylist->currentItem()->text();

        QDir dir( doss );
        dir.mkpath(doss);
        QString nouvelemplacementchemin =  doss + "/" + fich.fileName();
        QFile::copy( mp3->getcheminmp3(), nouvelemplacementchemin );


        delete mp3;

    }
}

void OngletPlaylist::on_ActuListe_clicked()
{
    ActualiserOnglet();
}

void OngletPlaylist::on_ActuPlaylist_clicked()
{
    m_playlist_selectionne = ui->ListePlaylist->currentItem()->data( Qt::UserRole ).toInt();
    ListeMp3( 1 );
}

void OngletPlaylist::on_titreaz_clicked()
{
    m_playlist_selectionne = ui->ListePlaylist->currentItem()->data( Qt::UserRole ).toInt();
    ListeMp3( 3 );
}

void OngletPlaylist::on_artaz_clicked()
{
    m_playlist_selectionne = ui->ListePlaylist->currentItem()->data( Qt::UserRole ).toInt();
    ListeMp3( 1 );
}

void OngletPlaylist::on_artza_clicked()
{
    m_playlist_selectionne = ui->ListePlaylist->currentItem()->data( Qt::UserRole ).toInt();
    ListeMp3( 2 );
}

void OngletPlaylist::on_titreza_clicked()
{
    m_playlist_selectionne = ui->ListePlaylist->currentItem()->data( Qt::UserRole ).toInt();
    ListeMp3( 4 );
}

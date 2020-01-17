#include "dialogajoutenplaylist.h"
#include "ui_dialogajoutenplaylist.h"
#include "bddrel_playlist.h"

DialogAjoutEnPlaylist::DialogAjoutEnPlaylist(QString titre, int relation, QString Cate, QWidget *parent) :
    QDialog(parent),
    m_titre( titre ),
    m_relation ( relation ),
    m_Cate( Cate),
    ui(new Ui::DialogAjoutEnPlaylist)
{
    ui->setupUi(this);
    ActualiserOnglet();
}

DialogAjoutEnPlaylist::DialogAjoutEnPlaylist(QList<int> liste, QWidget* parent)  :
    QDialog(parent),
    m_titre( "Liste de MP3"),
    m_liste( liste),
    ui(new Ui::DialogAjoutEnPlaylist)
{
    ui->setupUi( this );

    ActualiserOnglet();
}

DialogAjoutEnPlaylist::~DialogAjoutEnPlaylist()
{
    delete ui;
}

void DialogAjoutEnPlaylist::ActualiserOnglet()
{
    AfficherTitre();
    AfficherPlaylists();
}

void DialogAjoutEnPlaylist::on_buttonBox_accepted()
{
    EnregistrerEnPlaylist();
}
void DialogAjoutEnPlaylist::AfficherPlaylists()
{
    ui->ListePlaylist->clear();

    QStringList liste;
    liste += m_bddInterface->listePlaylist();

    for (int i = 0; i < liste.count(); i=i+2 )
    {
        QListWidgetItem* item = new QListWidgetItem;
        //on affiche la pochette et le nom de l'album
        item->setData( Qt::UserRole, liste[i] );
        item->setText( liste[i+1]  );

        ui->ListePlaylist->addItem( item );

    }
    ui->ListePlaylist->setCurrentRow( liste.count()/2 -1 );
}
void DialogAjoutEnPlaylist::AfficherTitre()
{
    ui->Titre->setText( m_titre );
}
void DialogAjoutEnPlaylist::EnregistrerEnPlaylist()
{
    BDDRel_Playlist*  temp = new BDDRel_Playlist;
    if ( m_liste.count() > 0 )
    {
        for (int i = 0; i < m_liste.count(); i ++ )
        {
            temp->AjoutRel_Playlist( ui->ListePlaylist->currentItem()->data(Qt::UserRole).toInt(),  m_liste[i]  );
        }
    } else
    {
        if ( m_Cate == "MP3" )
        {
            temp->AjoutRel_Playlist( ui->ListePlaylist->currentItem()->data(Qt::UserRole).toInt(),  m_relation  );
        } else
        {
            temp->AjouterAlbumEnPlaylist( ui->ListePlaylist->currentItem()->data(Qt::UserRole).toInt(),  m_relation);
        }
    }
}

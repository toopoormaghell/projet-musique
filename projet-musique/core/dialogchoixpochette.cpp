#include "dialogchoixpochette.h"
#include "ui_dialogchoixpochette.h"
#include "bddaffichermp3.h"
#include "bddpoch.h"
#include "bddartiste.h"
DialogChoixPochette::DialogChoixPochette(QString artiste, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChoixPochette),
    m_artiste ( artiste )
{
    ui->setupUi(this);
    AfficherPochettes();

    ui->ListePochettes->setModel( &m_pochettes);
}

DialogChoixPochette::~DialogChoixPochette()
{
    delete ui;
}

void DialogChoixPochette::on_buttonBox_accepted()
{
    m_selection = RecupererPochetteSelectionnee();
}

void DialogChoixPochette::on_buttonBox_rejected()
{
    m_selection = -1;
}
void DialogChoixPochette::AfficherPochettes()
{
    //Création du modèle pour le QListView
    m_pochettes.clear();

    //On récupère en premier l'id de l'artiste
    BDDArtiste* art = BDDArtiste::RecupererArtparNom(m_artiste);


    QList<int> listepoch = BDDPoch::pochettesparart( QString::number( art->m_id ) );

    for (int cpt = 0; cpt < listepoch.count(); cpt ++)
    {
        //Pour chaque pochette...
        BDDPoch* poch = BDDPoch::recupererBDD( listepoch[cpt] );

        QStandardItem* item = new QStandardItem;
        //on affiche la pochette
        QPixmap scaled( QPixmap::fromImage( poch->m_image ) );
        item->setIcon( QIcon( scaled ) );
        item->setData(  Qt::UserRole, poch->m_id );
        item->setText(  poch->m_chemin );

        //On ajoute l'item dans le modèle
        m_pochettes.setItem( cpt, item );
    }
}
int DialogChoixPochette::RecupererPochetteSelectionnee()
{
    QModelIndex index = ui->ListePochettes->currentIndex();

    return index.data( Qt::UserRole ).toInt();
}

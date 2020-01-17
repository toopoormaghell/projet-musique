#include "dialogchoixpochette.h"
#include "ui_dialogchoixpochette.h"
#include "bddaffichermp3.h"
#include "bddpoch.h"
#include <QListWidgetItem>
#include <QDebug>
#include "dialogajoutpoch.h"
#include "bddartiste.h"


DialogChoixPochette::DialogChoixPochette( QString artiste, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChoixPochette),
    m_artiste ( artiste ),
    m_nom_artiste( )
{
    ui->setupUi(this);
    Handle<BDDArtiste> art = BDDArtiste::recupererBDD( m_artiste.toInt() );
    m_nom_artiste = art->m_nom;
    delete art;
    AfficherPochettes();
}

DialogChoixPochette::~DialogChoixPochette()
{
    delete ui;
}

void DialogChoixPochette::on_buttonBox_accepted()
{
}

void DialogChoixPochette::on_buttonBox_rejected()
{
    m_selection = -1;
}
void DialogChoixPochette::AfficherPochettes()
{
    ui->ListePoch->clear();

    QList<int> listepoch = BDDPoch::pochettesparart( m_nom_artiste, m_artiste );

    for (int cpt = 0; cpt < listepoch.count(); cpt ++)
    {
        //Pour chaque pochette...
        Handle<BDDPoch> poch = BDDPoch::recupererBDD( listepoch[cpt] );
        QListWidgetItem* item = new QListWidgetItem;

        //on affiche la pochette
        QPixmap scaled( QPixmap::fromImage( poch->m_image ) );
        item->setIcon( QIcon( scaled ) );
        item->setData( Qt::UserRole, poch->id() );
        item->setText(  poch->m_chemin );

        //On ajoute l'item dans le modèle

        ui->ListePoch->addItem( item );
    }
}

void DialogChoixPochette::on_ListePoch_itemClicked(QListWidgetItem *item)
{
    m_selection = item->data( Qt::UserRole).toInt();
}

void DialogChoixPochette::on_NewPoch_clicked()
{
    DialogAjoutPoch temp (  m_nom_artiste , this );

    connect( &temp,SIGNAL(fini()), this, SLOT(RelancePochettes() ) );

    temp.exec();
}

void DialogChoixPochette::RelancePochettes()
{
    AfficherPochettes();
}

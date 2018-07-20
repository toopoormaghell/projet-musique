#include "dialogchoixpochette.h"
#include "ui_dialogchoixpochette.h"
#include "bddaffichermp3.h"
#include "bddpoch.h"
#include <QListWidgetItem>
#include <QDebug>

DialogChoixPochette::DialogChoixPochette( QString artiste, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChoixPochette),
    m_artiste ( artiste )
{
    ui->setupUi(this);
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

    QList<int> listepoch = BDDPoch::pochettesparart( m_artiste );

    for (int cpt = 0; cpt < listepoch.count(); cpt ++)
    {
        //Pour chaque pochette...
        BDDPoch* poch = BDDPoch::recupererBDD( listepoch[cpt] );
        QListWidgetItem* item = new QListWidgetItem;

        //on affiche la pochette
        QPixmap scaled( QPixmap::fromImage( poch->m_image ) );
        item->setIcon( QIcon( scaled ) );
        item->setData( Qt::UserRole, poch->id() );
        item->setText(  poch->m_chemin );

        //On ajoute l'item dans le modèle

        ui->ListePoch->addItem( item );

        delete poch;
    }
}

void DialogChoixPochette::on_ListePoch_itemClicked(QListWidgetItem *item)
{
    m_selection = item->data( Qt::UserRole).toInt();
}

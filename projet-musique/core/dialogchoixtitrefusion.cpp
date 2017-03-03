#include "dialogchoixtitrefusion.h"
#include "ui_dialogchoixtitrefusion.h"
#include "bddtitre.h"
#include <QListWidgetItem>

DialogChoixTitreFusion::DialogChoixTitreFusion(QList<TitresPhys> titres, int Ancien, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChoixTitreFusion),
    m_titres ( titres ),
    m_Ancien ( Ancien )
{
    ui->setupUi(this);
    AfficherTitres();
}

DialogChoixTitreFusion::~DialogChoixTitreFusion()
{
    delete ui;
}

void DialogChoixTitreFusion::on_buttonBox_accepted()
{
    m_selection = RecupererTitreSelectionne();
}
void DialogChoixTitreFusion::AfficherTitres()
{
    ui->TitresProposes->clear();

    BDDTitre* titre = BDDTitre::RecupererTitre( m_Ancien );
    ui->PhrasedeSupport->setText( titre->m_nom );

    for (int cpt =0; cpt < m_titres.count(); cpt++ )
    {

        if ( m_titres[cpt].Garde )
        {
            QListWidgetItem* item = new QListWidgetItem;
            item->setData( Qt::UserRole, m_titres[cpt].id );
            item->setText( m_titres[cpt].Titre );

            ui->TitresProposes->addItem( item );

        }
    }
    ui->TitresProposes->setCurrentRow( 0 );
    delete titre;
}
int DialogChoixTitreFusion::RecupererTitreSelectionne()
{
    QListWidgetItem* index = ui->TitresProposes->currentItem();
    return index->data( Qt::UserRole ).toInt();
}

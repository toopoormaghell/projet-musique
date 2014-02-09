#include "dialogueartistesinverses.h"
#include "ui_dialogueartistesinverses.h"
#include "QDebug"
DialogueArtistesInverses::DialogueArtistesInverses(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogueArtistesInverses)
{
    ui->setupUi(this);
    QStringList Liste= InitialiserListeArtistes();
    AfficherListeArtistes(Liste);
    QStringList Invers=InitialiserListeArtistesInverses();
    AfficherListeInversee(Invers);


}
DialogueArtistesInverses::~DialogueArtistesInverses()
{
    delete ui;
}
void DialogueArtistesInverses::AfficherListeArtistes(QStringList ListeArtistes)
{
    ui->ListeArtistes->clear();

    for(int cpt=0;cpt<ListeArtistes.count();cpt=cpt+2)
    {
        QListWidgetItem *item=new QListWidgetItem;
        item->setText(ListeArtistes[cpt]);
        item->setData(Qt::UserRole,ListeArtistes[cpt+1]);
        ui->ListeArtistes->addItem(item);
    }
    ui->ListeArtistes->setCurrentRow(0);
}
QStringList DialogueArtistesInverses::InitialiserListeArtistes()
{
    QStringList ListeArtistes=m_bddInterface.ListeArtistes();
    return ListeArtistes;
}
void DialogueArtistesInverses::EchangerListeArtistes()
{
    QListWidgetItem* listItem = ui->ListeArtistes->currentItem();
    QListWidgetItem* listInvers = ui->ListeInversee->currentItem();
    if ( ( listItem != NULL ) && ( listInvers != NULL ) )
    {
        const QString temp = listItem->text();
        listItem->setText( listInvers->text() );
        listInvers->setText( temp );
    }
}

void DialogueArtistesInverses::AfficherListeInversee(QStringList ListeArtistes)
{
    ui->ListeInversee->clear();
    for(int cpt=0;cpt<ListeArtistes.count();cpt=cpt+2)
    {
        QListWidgetItem *item=new QListWidgetItem;
        item->setText(ListeArtistes[cpt]);
        item->setData(Qt::UserRole,ListeArtistes[cpt+1]);
        ui->ListeInversee->addItem(item);
    }
    ui->ListeInversee->setCurrentRow(0);
}
QStringList DialogueArtistesInverses::InitialiserListeArtistesInverses()
{
    QStringList ListeArtistes=m_bddInterface.ListeArtistesInvers();
    return ListeArtistes;
}

void DialogueArtistesInverses::on_ListeArtistes_currentRowChanged(int currentRow)
{
//    ui->ListeInversee->item(currentRow)->setSelected(true);
    ui->ListeInversee->setCurrentRow( currentRow );
}

void DialogueArtistesInverses::on_ListeInversee_currentRowChanged(int currentRow)
{
//    ui->ListeArtistes->item(currentRow)->setSelected(true);
    ui->ListeArtistes->setCurrentRow( currentRow );
}

void DialogueArtistesInverses::on_Inversion_clicked()
{
    EchangerListeArtistes();
}
QStringList DialogueArtistesInverses::RecupererListeArtiste()
{
    QStringList Liste;
    QListWidgetItem *item = NULL;
    for(int i = 0 ; i < ui->ListeArtistes->count() ; i++)
    {
        item = ui->ListeArtistes->item(i);

        Liste << item->text() << item->data(Qt::UserRole).toString();

    }
    return Liste;
}
QStringList DialogueArtistesInverses::RecupererListeArtisteInvers()
{
    QStringList Liste;
    QListWidgetItem *item = NULL;
    for(int i = 0 ; i < ui->ListeInversee->count() ; i++)
    {
        item = ui->ListeInversee->item(i);

        Liste << item->text() << item->data(Qt::UserRole).toString();

    }
    return Liste;
}

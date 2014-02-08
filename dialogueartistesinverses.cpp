#include "dialogueartistesinverses.h"
#include "ui_dialogueartistesinverses.h"
#include "QDebug"
DialogueArtistesInverses::DialogueArtistesInverses(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogueArtistesInverses)
{
    ui->setupUi(this);
    QStringList Liste;
    GererListeArtistes(Liste);
    GererListeArtistesInvers(Liste);
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
}
QStringList DialogueArtistesInverses::InitialiserListeArtistes()
{
    QStringList ListeArtistes=m_bddInterface.ListeArtistes();
    return ListeArtistes;
}
void DialogueArtistesInverses::EchangerListeArtistes(QStringList& Liste,int Position,QString Changement)
{
    Liste.replace(Position,Changement);
}
void DialogueArtistesInverses::GererListeArtistes(QStringList Liste)
{
    if(Liste.count()==0)
    {
        Liste=InitialiserListeArtistes();
    } else{
        int cpt = ui->ListeArtistes->currentRow()*2;
        QListWidgetItem *item = ui->ListeInversee->item(cpt);
        QString chang=item->text();
        EchangerListeArtistes(Liste,cpt,chang);
   }
    AfficherListeArtistes(Liste);
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
}
QStringList DialogueArtistesInverses::InitialiserListeArtistesInverses()
{
    QStringList ListeArtistes=m_bddInterface.ListeArtistesInvers();
    return ListeArtistes;
}

void DialogueArtistesInverses::GererListeArtistesInvers(QStringList Liste)
{
    if(Liste.count()==0)
    {
        Liste=InitialiserListeArtistesInverses();
    } else{
        int cpt=0;
        QString chang="Essai";
        EchangerListeArtistes(Liste,cpt,chang);
    }
    AfficherListeInversee(Liste);
}

void DialogueArtistesInverses::on_ListeArtistes_currentRowChanged(int currentRow)
{
    ui->ListeInversee->item(currentRow)->setSelected(true);
}

void DialogueArtistesInverses::on_ListeInversee_currentRowChanged(int currentRow)
{
    ui->ListeArtistes->item(currentRow)->setSelected(true);
}

void DialogueArtistesInverses::on_Inversion_clicked()
{
    QStringList Liste=RecupererListeArtiste();
    GererListeArtistes(Liste);
    Liste.clear();
    Liste = RecupererListeArtisteInvers();
    GererListeArtistesInvers(Liste);
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

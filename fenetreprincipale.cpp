#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include "importationlistephysiques.h"
#include "discogs.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}
void FenetrePrincipale::on_actionActualiser_Mp3_triggered()
{
    m_bddInterface.enregistrerObservateur( ui->widget );
    m_bddInterface.actualiserMP3();
    m_bddInterface.desenregistrerObservateur( ui->widget );
}
void FenetrePrincipale::on_actionViderBDD_triggered()
{
    m_bddInterface.ViderBDD();

}
void FenetrePrincipale::on_actionAjouter_Liste_Albums_triggered()
{
    QString fileName = QFileDialog::getOpenFileName( this,
                                                     "Ouvrir le fichier contenant une liste de CD",
                                                     "F:/",
                                                     "Fichier texte (*.txt)" );
    ImportationListePhysiques tmp( this );
    tmp.initFromFile( fileName );
    tmp.exec();
}
void FenetrePrincipale::on_actionAjouter_Album_triggered()
{
Discogs temp;

QString resultat=temp.RequeteAlbums("731454733823");
AlbumGestion *album= temp.RequeteInfosAlbum(resultat);
}

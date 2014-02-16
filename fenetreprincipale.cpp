#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include "importationlistephysiques.h"
#include "discogs.h"
#include "dialogueajouterphysique.h"
#include "dialogueartistesinverses.h"

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
    DialogueAjouterPhysique tmpDialog( this );
    tmpDialog.exec();
}

void FenetrePrincipale::on_actionEn_HTML_Supports_Physiques_triggered()
{
      m_bddInterface.ExporterHTML("Tout");
}

void FenetrePrincipale::on_actionAlbums_triggered()
{
     m_bddInterface.ExporterHTML("Album");
}

void FenetrePrincipale::on_actionCompils_Singles_triggered()
{
    m_bddInterface.ExporterHTML("Single");
}

void FenetrePrincipale::on_actionArtistes_Inverses_triggered()
{
    DialogueArtistesInverses tmp(this);
    tmp.exec();
}

void FenetrePrincipale::on_actionExporter_Liste_Physique_triggered()
{
    m_bddInterface.SauvegarderAlbums();
}

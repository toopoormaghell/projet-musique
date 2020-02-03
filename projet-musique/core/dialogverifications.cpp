#include "dialogverifications.h"
#include "ui_dialogverifications.h"
#include "gestionverifications.h"
#include <QObject>
#include "dialogmodifnomsartistes.h"

DialogVerifications::DialogVerifications(QWidget *parent) :
    QDialog(parent),
    ui( new Ui::DialogVerifications ),
    m_gestion ( new GestionVerifications )

{
    ui->setupUi(this);


     connect (m_gestion ,SIGNAL(EnvoyerTexte(QString)), this ,SLOT(EcrireMessage(QString)));

}


DialogVerifications::~DialogVerifications()
{
    delete ui;
}

void DialogVerifications::on_pochvides_clicked()
{

    m_gestion->SuppressionPochettes();

}

void DialogVerifications::on_auto_2_clicked()
{

    m_gestion->VerifierBDD();

}

void DialogVerifications::on_mp3phys_clicked()
{

    m_gestion->titresphysetmp3();

}

void DialogVerifications::EcrireMessage(QString texte)
{
    ui->interaction->append(texte);
}

void DialogVerifications::on_Reformatage_clicked()
{

    m_gestion->ReformatageEntites();

}

void DialogVerifications::on_majuscules_clicked()
{

    m_gestion->MajusculesEntites();

}

void DialogVerifications::on_ArtisteCompilAlbum_clicked()
{
    m_gestion->ArtistesCompils();
}

void DialogVerifications::on_Virgule_clicked()
{
    m_gestion->VirguleArtistes();
}

void DialogVerifications::on_doublontitre_clicked()
{
    m_gestion->SupprimerDoublonsTitre();
}

void DialogVerifications::on_doublonealbum_clicked()
{
    m_gestion->SupprimerDoublonsAlbum();
}

void DialogVerifications::on_doublonartiste_clicked()
{
    m_gestion->SupprimerDoublonsArtiste();
}

void DialogVerifications::on_integritetout_clicked()
{
    m_gestion->VerifierIntegrite();
}

void DialogVerifications::on_integritepoch_clicked()
{
    m_gestion->VerifierPoch();
}

void DialogVerifications::on_integriterelations_clicked()
{
    m_gestion->VerifierRelation();
}

void DialogVerifications::on_integritemp3_clicked()
{
    m_gestion->VerifierMP3();
}

void DialogVerifications::on_integritephys_clicked()
{
    m_gestion->VerifierPhys();
}

void DialogVerifications::on_integritealbums_clicked()
{
    m_gestion->VerifierAlbum();
}

void DialogVerifications::on_integriteartistes_clicked()
{
    m_gestion->VerifierArtiste();
}

void DialogVerifications::on_integritetitres_clicked()
{
    m_gestion->VerifierTitre();
}

void DialogVerifications::on_pushButton_clicked()
{
    DialogModifNomsArtistes* temp= new DialogModifNomsArtistes( this );
    temp->exec();
}

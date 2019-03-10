#include "gestionverifications.h"
#include "bddsingleton.h"
#include <QObject>


GestionVerifications::GestionVerifications(QObject* parent ) :
    QObject( parent ),
    m_outils ( new OutilsBDD )
{
    Q_UNUSED ( parent);

connect ( m_outils,SIGNAL(EcrireMessage(QString)),this,SLOT(EcrireTexte(QString)));

}
void GestionVerifications::ChangerArtisteDansCompilAlbum()
{
    m_outils->ChangerArtisteDansCompilAlbum();
}
void GestionVerifications::VirguleArtistes()
{
    m_outils->VirguleArtistes();
}
void GestionVerifications::SupprimerDoublonsArtiste()
{
    m_outils->SupprimerDoublonsArtiste();
}
void GestionVerifications::SupprimerDoublonsAlbum()
{
    m_outils->SupprimerDoublonsAlbum();
}
void GestionVerifications::SupprimerDoublonsTitre()
{

     m_outils->SupprimerDoublonsTitre();
}

void GestionVerifications::VerifierIntegrite()
{
    VerifierPoch();
    VerifierRelation();
    VerifierAlbum();
    VerifierArtiste();
    VerifierTitre();
    VerifierMP3();
    VerifierPhys();
}

void GestionVerifications::VerifierBDD()
{
    VerifierIntegrite();
}

void GestionVerifications::titresphysetmp3()
{
    m_outils->titresphysetmp3();
}
void GestionVerifications::SuppressionPochettes()
{
    m_outils->SuppressionPochettes();
}
void GestionVerifications::ReformatageEntites()
{
    m_outils->ReformatageCompletEntites();
}
void GestionVerifications::MajusculesEntites()
{
    m_outils->MajusculesCompletEntites();
}
void GestionVerifications::ArtistesCompils()
{
    m_outils->ArtistesCompils();
}
void GestionVerifications::VerifierPoch()
{
    m_outils->VerifierPoch();
}

void GestionVerifications::VerifierRelation()
{
    m_outils->VerifierRelation();
}

void GestionVerifications::VerifierAlbum()
{
    m_outils->VerifierAlbum();
}

void GestionVerifications::VerifierArtiste()
{
    m_outils->VerifierArtiste();
}

void GestionVerifications::VerifierTitre()
{
    m_outils->VerifierTitre();
}
void GestionVerifications::VerifierMP3()
{
    m_outils->VerifierMP3();
}

void GestionVerifications::VerifierPhys()
{
    m_outils->VerifierPhys();
}

void GestionVerifications::EcrireTexte(QString text)
{
    emit EnvoyerTexte(text);
}

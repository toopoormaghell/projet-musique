#ifndef GESTIONVERIFICATIONS_H
#define GESTIONVERIFICATIONS_H

#include <QObject>
#include "bdd_global.h"
#include "outilsbdd.h"


class BDDSHARED_EXPORT GestionVerifications: public QObject
{
    Q_OBJECT

public:
   explicit GestionVerifications( QObject* parent = 0);

    void titresphysetmp3();
    void ReformatageEntites();
    void ArtistesCompils();
    void MajusculesEntites();
    void SuppressionPochettes();
    void ChangerArtisteDansCompilAlbum();
    void VirguleArtistes();
    void SupprimerDoublonsArtiste();
    void SupprimerDoublonsAlbum();
    void SupprimerDoublonsTitre();

    void VerifierIntegrite();
    void VerifierBDD();

    void VerifierPoch();
    void VerifierRelation();
    void VerifierAlbum();
    void VerifierArtiste();
    void VerifierTitre();
    void VerifierMP3();
    void VerifierPhys();

signals:
    void EnvoyerTexte(QString );

public slots:
    void EcrireTexte(QString text);

private:
    OutilsBDD* m_outils;
};

#endif // GESTIONVERIFICATIONS_H

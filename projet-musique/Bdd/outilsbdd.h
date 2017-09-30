#ifndef OUTILSBDD_H
#define OUTILSBDD_H

#include <QString>
#include <QStringList>
#include <QObject>
#include "bdd_global.h"


class BDDSHARED_EXPORT OutilsBDD: public QObject
{
    Q_OBJECT
public:
    explicit OutilsBDD(QWidget* parent = 0);
    void VirguleArtistes();
    void titresphysetmp3();
    void SupprimerDoublonsArtiste();
    void SupprimerDoublonsAlbum();
    void ReformatageCompletEntites();
    void ChangerArtisteDansCompilAlbum();
    void SupprimerDoublonsTitre();
    void MajusculesCompletEntites();
    void ArtistesCompils();
    void SuppressionPochettes();

    bool removeDir( const QString& dirPath, const bool remove = true, const QString fichier = "def.jpg" );


    void VerifierPoch();
    void VerifierRelation();
    void VerifierAlbum();
    void VerifierArtiste();
    void VerifierTitre();
    void VerifierMP3();
    void VerifierPhys();
signals:
    void EcrireMessage(QString texte);
private:
    void Reformatage(QString Entite, QString Id_Entite, int Categorie);
    void Majuscules(QString Entite, QString Id_Entite, int Categorie);
    void ExecutionRequeteFormate(QString queryStr, int Categorie);
    void ExecutionRequeteMajuscules(QString queryStr, int Categorie);
    QStringList creerfilepochettes();

    void SupprimerDossiersVides();
};



#endif // OUTILSBDD_H

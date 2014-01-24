#ifndef BDDCOMMUN_H
#define BDDCOMMUN_H

#include <QObject>
#include <QString>
#include <QSet>
#include "util.h"
class BarreAvancement;

class BDDCommun : public QObject
{
public:
    explicit BDDCommun( QObject* parent = 0 );

    void viderBDD();

    bool removeDir(const QString& dirPath, const bool remove = true, const QString fichier = "def.jpg");

    QString lireIDArtiste( const QStringList& Artiste);
    QString lireIDAlbum( const QStringList& Album);
    QString lireIDTitre( const QStringList& Titre);
    QString lireIDPoch( const QString& ArtAlb);

    void supprimerArtiste( const QStringList& Param);
    void supprimerAlbum( const QStringList& Param);
    void supprimerTitre( const QStringList& infos);
    void supprimerPoch( const QString& IdPoch);

    void enregistrerObservateur( BarreAvancement* obs );
    void desenregistrerObservateur( BarreAvancement* obs );

    QString afficherPochette(const QString &Id, const QString &Type);
    bool verifierTitreMp3Phys(QString Id_Titre);
    QString AjouterPochette(AlbumGestion album);
protected:
    void notifierObservateurs( const QString& chemin, const float pourcentage );

private:
    QSet<BarreAvancement*> m_observateurs;
};

#endif // BDDCOMMUN_H

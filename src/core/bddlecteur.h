#ifndef BDDLECTEUR_H
#define BDDLECTEUR_H

#include <QObject>
#include "bddsingleton.h"

class BDDLecteur : public QObject
{
    Q_OBJECT
public:
    explicit BDDLecteur(QObject *parent = nullptr);
    QStringList listeTitresAlbum ( QString Album);
    QStringList listeTitresArtiste (QString Artiste );
    QStringList listeTitresAnnee ( QString Annee);

};

#endif // BDDLECTEUR_H

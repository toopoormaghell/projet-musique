#ifndef BDDAFFICHERLISTE_H
#define BDDAFFICHERLISTE_H

#include <QObject>
#include "bddsingleton.h"
class BddAfficherListe : public QObject
{
    Q_OBJECT
public:
    explicit BddAfficherListe( QObject* parent = nullptr  );

    int EnregistrerBoite( QString nom_boite );
    void EnregistrerSelection( QList<int> liste, int boite );

    QStringList AfficherBoites();
    QList<int> listeAlbums();
    QList<int> listeAlbums(int Id_Boite);
};

#endif // BDDAFFICHERLISTE_H

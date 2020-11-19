#ifndef BDDERREURS_H
#define BDDERREURS_H

#include <QObject>
#include "outilsbdd.h"
#include "bdd_global.h"


class BDDSHARED_EXPORT BDDErreurs : public QObject
{
    Q_OBJECT
public:

    explicit BDDErreurs(QObject *parent = nullptr);
    ~BDDErreurs();
    QList<int> retrouverErreurs( int categorie );
    QStringList lectureErreur(int categorie, int id);
    void supprimer(int categorie, int id);

    QImage AfficherImagePoch(int id);
    QList<int> retrouverRelations();

private:

    OutilsBDD* m_outils;
    QStringList lectureErreurRelation(int id);
    QStringList lectureErreurAlbum(int id);
    QStringList lectureErreurArtiste(int id);
    QStringList lectureErreurTitre(int id);
    QStringList lectureErreurPochette(int id);
    QStringList lectureErreurMP3(int id);
    QStringList lectureErreurPhys(int id);
    QList<int> retrouvererreursArtistes();
    QList<int> retrouvererreursAlbums();
    QList<int> retrouvererreursRelations();
    QList<int> retrouvererreursTitres();
    QList<int> retrouvererreursPoch();
    QList<int> retrouvererreursPhys();
    QList<int> retrouvererreursMP3();
    void supprimerPoch(int id);
    void supprimerRelation(int id);
    void supprimerAlbum(int id);
    void supprimerArtiste(int id);
    void supprimerTitre(int id);
    void supprimerMP3(int id);
    void supprimerPhys(int id);
};

#endif // BDDERREURS_H

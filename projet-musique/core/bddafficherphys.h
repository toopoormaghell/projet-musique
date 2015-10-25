#ifndef BDDAFFICHERPHYS_H
#define BDDAFFICHERPHYS_H

#include <QObject>

class BDDAfficherPhys : public QObject
{
    Q_OBJECT

public:
    explicit BDDAfficherPhys(QObject *parent = 0);

    QList<int> ListeArtiste();
    QList<int> listeAlbums(QString Id_Artiste);
    QList<int> listeCompils(QString Id_Artiste);
    QList<int> listeSingles(QString Id_Artiste);
    static void exporterHTML();
    static QStringList ListeAlbumSauvegarde();
    QStringList ListeTitresPossibles();
    QStringList ListeArtistesPossibles();
signals:

public slots:

};

#endif // BDDAFFICHERPHYS_H

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
signals:

public slots:

};

#endif // BDDAFFICHERPHYS_H

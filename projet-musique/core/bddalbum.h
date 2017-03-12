#ifndef BDDALBUM_H
#define BDDALBUM_H

#include "util.h"
#include <QObject>
class BDDArtiste;
class BDDPoch;
class BDDType;

class BDDAlbum : public QObject
{
    Q_OBJECT
public:
    explicit BDDAlbum(const QString& album, const BDDPoch& pochette, int annee, const BDDType& type, const BDDArtiste& artiste, QObject* parent = 0);
    virtual ~BDDAlbum();

    void updateBDD();
    void supprimerenBDD() const;
    static BDDAlbum* RecupererAlbum( const int Id );

    int m_id;
    QString m_nom;
    BDDPoch const* m_pochette;
    QString m_nomFormate;
    int m_annee;
    BDDType const* m_type;
    BDDArtiste const* m_artiste;

    static AlbumPhys RecupAlbumEntite( const int id );
private:
    // Indique que le type et la pochette ont été créés par RecupererAlbum, et doivent donc être détruits explicitement
    bool m_areTypeAndPochetteSelfCreated;

    void ajouterBDD();
    void recupererId();

    //Constructeur avec une id
    explicit BDDAlbum(const int id, QObject* parent = NULL);

};

#endif // BDDALBUM_H

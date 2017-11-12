#ifndef BDDALBUM_H
#define BDDALBUM_H

#include "util.h"
#include "idowner.h"
#include <QObject>
class BDDArtiste;
class BDDPoch;
class BDDType;

class BDDAlbum : public IdOwner
{
    Q_OBJECT
public:
    explicit BDDAlbum(const QString& album, BDDPoch& pochette, int annee, const BDDType& type, const BDDArtiste& artiste, QObject* parent = 0);
    virtual ~BDDAlbum();

    void updateBDD();
    void supprimerenBDD() const;
    static BDDAlbum* RecupererAlbum( const int Id );

    QString m_nom;
    BDDPoch* m_pochette;
    QString m_nomFormate;
    int m_annee;
    BDDType const* m_type;
    BDDArtiste const* m_artiste;

    static AlbumPhys RecupAlbumEntite( const int id );
    static bool ExisteEnPhys( const int id );
private:
    // Indique que le type et la pochette ont été créés par RecupererAlbum, et doivent donc être détruits explicitement
    bool m_areTypeAndPochetteSelfCreated;

    void ajouterBDD();
    void recupererId();

    //Constructeur avec une id
    explicit BDDAlbum(const int id, QObject* parent = NULL);

};

#endif // BDDALBUM_H

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
    void updateBDD();
    void supprimerenBDD() const;

    virtual ~BDDAlbum();
    static BDDAlbum* recupererBDD( const int Id );
    static BDDAlbum* recupererBDD(const QString& album, BDDPoch& pochette, int annee, const BDDType& type, const BDDArtiste& artiste);


    QString m_nom;
    QString m_nomFormate;
    BDDPoch* m_pochette;
    int m_annee;
    BDDType const* m_type;
    BDDArtiste const* m_artiste;

    static AlbumPhys RecupAlbumEntite( const int id );

    static bool ExisteEnPhys( const int id );


private:
    static int recupererId(const QString& nomFormate, const QString& id_Artiste);
    static int TrouverId(const QString& nom, const int& id_Artiste);

    explicit BDDAlbum(const int id, const QString& nom, const QString &nomFormate, BDDPoch* pochette, int annee, const BDDType* type, const BDDArtiste* artiste, QObject* parent = NULL);


};

#endif // BDDALBUM_H

#ifndef BDDRELATION_H
#define BDDRELATION_H

#include <QObject>
#include "idowner.h"
#include "bdd_global.h"

class BDDAlbum;
class BDDTitre;
class BDDArtiste;


class BDDSHARED_EXPORT BDDRelation : public IdOwner
{
    Q_OBJECT
public:
    void updateBDD();

    void supprimerenBDDMP3() const;
    void supprimerenBDDPhys() const;
    void supprimerModifier() const;

    virtual ~BDDRelation();

    static BDDRelation* recupererBDD( const int id );
    static BDDRelation* recupererBDD( BDDAlbum& alb, BDDArtiste& art, BDDTitre& titre, const int num_piste, const QString& duree, const int mp3, const int phys);

    BDDTitre const* m_titre;
    BDDAlbum const* m_album;
    BDDArtiste const* m_artiste;
    int m_num_piste;
    QString m_duree;
    int m_mp3;
    int m_phys;

private:

    static  int recupererId(const QString& id_album, const QString& id_artiste, const QString& id_titre);

    explicit BDDRelation(const int id, BDDAlbum* album, BDDArtiste* artiste, BDDTitre* titre, const int num_piste, const QString& duree, const int mp3, const int phys,  QObject* parent = nullptr);
};

#endif // BDDRELATION_H

#ifndef BDDRELATION_H
#define BDDRELATION_H

#include <QObject>
#include "idowner.h"

class BDDAlbum;
class BDDTitre;
class BDDArtiste;


class BDDRelation : public IdOwner
{
    Q_OBJECT
public:
    explicit BDDRelation(const BDDAlbum& album, const BDDArtiste& artiste, const BDDTitre& titre, const int num_piste, const QString& duree, const int mp3, const int phys, const int MP3Phys, QObject* parent = 0);
    virtual ~BDDRelation();

    static BDDRelation* RecupererRelation( const int id );
    void supprimerenBDDMP3() const;
    void supprimerenBDDPhys() const;
    void supprimerModifier() const;
    static BDDRelation* RecupererRelationParTitre (const int id);
    void updateBDD(const int MP3Phys);

    BDDTitre const* m_titre;
    BDDAlbum const* m_album;
    BDDArtiste const* m_artiste;
    int m_num_piste;
    QString m_duree;
    int m_mp3;
    int m_phys;
private:
    // Indique que le type et la pochette ont été créés par RecupererRelation, et doivent donc être détruits explicitement
    bool m_areSelfCreated;
    explicit BDDRelation(const int id, QObject* parent = NULL);
    void ajouterBDD();
    void recupererId();
    explicit BDDRelation(const int id, QString Type, QObject* parent = NULL);

};

#endif // BDDRELATION_H

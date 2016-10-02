#ifndef BDDRELATION_H
#define BDDRELATION_H

#include <QObject>

class BDDAlbum;
class BDDTitre;
class BDDArtiste;


class BDDRelation : public QObject
{
    Q_OBJECT
public:
    explicit BDDRelation( const BDDAlbum& album, const BDDArtiste& artiste, const BDDTitre& titre, QObject* parent = 0 );

    static BDDRelation* RecupererRelation( const int id );
    void supprimerenBDDMP3() const;
    void supprimerenBDDPhys() const;
    void supprimerModifier() const;
    static BDDRelation* RecupererRelationParTitre (const int id);
    void updateBDD();
    int m_id;
    int m_id_artiste;
    int m_id_album;
    int m_id_titre;
private:
    BDDRelation( const int id, QObject* parent = NULL );
    void ajouterBDD();
    void recupererId();
    BDDRelation(const int id, QString Type, QObject* parent = NULL);

};

#endif // BDDRELATION_H

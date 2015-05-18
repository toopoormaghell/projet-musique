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
    explicit BDDRelation(const BDDAlbum& album, const BDDArtiste& artiste, const BDDTitre& titre,QObject *parent = 0);

static BDDRelation* RecupererRelation(const int id);
void deleteBDD(const int &Id);

int m_id;
int m_id_artiste;
int m_id_album;
int m_id_titre;


private:
BDDRelation(const int id,QObject* parent=NULL);
void ajouterBDD();
void recupererId();

};

#endif // BDDRELATION_H

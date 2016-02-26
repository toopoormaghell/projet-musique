#ifndef BDDPHYS_H
#define BDDPHYS_H

#include <QObject>
class BDDArtiste;
class BDDAlbum;
class BDDTitre;
class BDDRelation;
class BDDType;

class BDDPhys : public QObject
{
    Q_OBJECT
public:
    explicit BDDPhys(const BDDAlbum& album, const QString&ean, const int &type, QObject *parent = 0);
    virtual ~BDDPhys();

    void deleteBDD();
    static BDDPhys* RecupererPhys(const int id);

    int m_id;
    BDDAlbum const* m_album;
    BDDArtiste const* m_artiste;
    QList<BDDTitre*>   m_titres;
    BDDType const* m_type;
    QString m_ean;

private:
    bool m_membersAreSelfCreatad;
    void ajouterBDD();
    void recupererId();
    void RecupererTitres();
    //Constructeur avec une id
    BDDPhys(const int id, QObject* parent = NULL);


    void updateBDD();
};

#endif // BDDPHYS_H

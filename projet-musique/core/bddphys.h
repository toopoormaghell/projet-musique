#ifndef BDDPHYS_H
#define BDDPHYS_H

#include <QObject>
class BDDArtiste;
class BDDAlbum;
class BDDRelation;
class BDDType;

class BDDPhys : public QObject
{
    Q_OBJECT
public:
    explicit BDDPhys( const BDDAlbum& album, const QString& ean, const int& type, const QString& Commentaires, QObject* parent = 0 );
    virtual ~BDDPhys();

    void deleteBDD();
    static BDDPhys* RecupererPhys( const int id );

    int m_id;
    BDDAlbum const* m_album;
    BDDArtiste const* m_artiste;
    QList<BDDRelation*>   m_relations;
    BDDType const* m_type;
    QString m_ean;
    QString m_commentaires;
private:
    bool m_membersAreSelfCreatad;
    void ajouterBDD();
    void recupererId();
    void RecupererTitres();
    //Constructeur avec une id
    BDDPhys( const int id, QObject* parent = NULL );


    void updateBDD();
};

#endif // BDDPHYS_H

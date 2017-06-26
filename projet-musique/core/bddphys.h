#ifndef BDDPHYS_H
#define BDDPHYS_H

#include <QObject>
#include "idowner.h"
class BDDAlbum;
class BDDSupport;

class BDDPhys : public IdOwner
{
    Q_OBJECT
public:
    explicit BDDPhys(const BDDAlbum& album, const QString& ean, const BDDSupport& support, const QString& Commentaires, QObject* parent = 0);
    virtual ~BDDPhys();

    void deleteBDD();
    static BDDPhys* RecupererPhys( const int id );

    BDDAlbum const* m_album;
    BDDSupport const* m_support;
    QString m_ean;
    QString m_commentaires;

private:
    bool m_membersAreSelfCreatad;
    void ajouterBDD();
    void recupererId();
    //Constructeur avec une id
    explicit BDDPhys(const int id, QObject* parent = NULL);


    void updateBDD();
};

#endif // BDDPHYS_H

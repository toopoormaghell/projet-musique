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
    void updateBDD();

    virtual ~BDDPhys();

    void supprimerBDD();

    static BDDPhys* RecupererBDD( const int id );
    static BDDPhys* RecupererBDD(const BDDAlbum& album, const QString& ean, const BDDSupport& support, const QString& Commentaires );

    BDDAlbum const* m_album;
    BDDSupport const* m_support;
    QString m_ean;
    QString m_commentaires;


private:
    static int recupererId(const int id_alb );

    explicit  BDDPhys(const int id, const BDDAlbum* album, const QString& ean, const BDDSupport*support, const QString& Commentaires, QObject* parent = NULL );

};

#endif // BDDPHYS_H

#ifndef BDDPHYS_H
#define BDDPHYS_H

#include <QObject>
#include "idowner.h"
#include "bdd_global.h"
#include "handle.h"
class BDDAlbum;
class BDDSupport;

class BDDSHARED_EXPORT BDDPhys : public IdOwner
{
    Q_OBJECT
public:
    void updateBDD();

    virtual ~BDDPhys();

    void supprimerBDD();

    static Handle<BDDPhys> RecupererBDD( const int id );
    static Handle<BDDPhys> RecupererBDD(const Handle<BDDAlbum>& album, const QString& ean, const Handle<BDDSupport>& support, const QString& Commentaires );

    Handle<BDDAlbum> m_album;
    Handle<BDDSupport> m_support;
    QString m_ean;
    QString m_commentaires;


private:
    static int recupererId(const int id_alb );

    explicit  BDDPhys(const int id, const Handle<BDDAlbum>& album, const QString& ean, const Handle<BDDSupport> support, const QString& Commentaires, QObject* parent = nullptr );

};

#endif // BDDPHYS_H

#ifndef BDDARTISTE_H
#define BDDARTISTE_H

#include <QObject>
#include "idowner.h"
#include "bdd_global.h"
#include "handle.h"
class BDDPoch;


class BDDSHARED_EXPORT BDDArtiste : public IdOwner
{
    Q_OBJECT
public:
    void updateBDD();
    void supprimerenBDD() const;

    virtual ~BDDArtiste();
    static Handle<BDDArtiste> recupererBDD( const int id );
    static Handle<BDDArtiste> recupererBDD( const QString& nom );
    static Handle<BDDArtiste> recupererBDD( const QString& artiste , const Handle<BDDPoch>& pochette );

    QString m_nom;
    QString m_nomFormate;
    Handle<BDDPoch> m_pochette;

    static void EchangerArtiste( QString& nom );
    void changerPoch( int id_nouv_poch );
    void EchangerBDD( QString art );

private:
    static int recupererId(const QString &nomFormate);
    static QString ChoisirArtisteEchange(const QString& nom);
    static int TrouverId(const QString& nom );

    explicit BDDArtiste(const int id, const QString &nom, const QString &nomFormate, const Handle<BDDPoch>& pochette, QObject* parent = nullptr);
};


#endif // BDDARTISTE_H

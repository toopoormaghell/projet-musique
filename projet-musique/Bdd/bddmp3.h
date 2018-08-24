#ifndef BDDMP3_H
#define BDDMP3_H

#include <QObject>
#include "idowner.h"
#include "bdd_global.h"
#include "handle.h"
class BDDArtiste;
class BDDAlbum;
class BDDTitre;
class BDDRelation;
class BDDSupport;
class BDDPoch;
class BDDSHARED_EXPORT BDDMp3 : public IdOwner
{
    Q_OBJECT
public:
    void updateBDD();

    void supprimerenBDD() const;

    virtual ~BDDMp3();

    static Handle<BDDMp3> RecupererBDD( const int id );
    static Handle<BDDMp3> RecupererBDD(const QString& Chemin, const Handle<BDDRelation>& relation, const BDDSupport& support );
    static Handle<BDDMp3> RecupererBDDParRelation( const int id );
static Handle<BDDMp3> RecupererBDDParChemin( const QString& Chemin);



    Handle<BDDRelation> m_relation;
    QString m_chemin;
    BDDSupport const* m_support;

    static QMap < int, QStringList> RecupererMP3s( int Type );
    void ChangerTag (const QString& NouveauAlbum, const QString& NouveauTitre, const QString& NouveauArtiste, const int &NouvelleAnnee, const int &NouvellePiste, const QString &NouvellePoch);
private:

    static int recupererId( const QString& Chemin);

    explicit BDDMp3(const int id, const QString& Chemin, const Handle<BDDRelation>& relation, const BDDSupport* support, QObject* parent = nullptr);
};

#endif // BDDMP3_H

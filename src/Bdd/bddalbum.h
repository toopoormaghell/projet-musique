#ifndef BDDALBUM_H
#define BDDALBUM_H

#include "util.h"
#include "idowner.h"
#include <QObject>
#include "bdd_global.h"
#include "handle.h"

class BDDArtiste;
class BDDPoch;
class BDDType;


class BDDSHARED_EXPORT BDDAlbum : public IdOwner
{
    Q_OBJECT
public:
    void updateBDD();
    void supprimerenBDD() const;

    virtual ~BDDAlbum();
    static Handle<BDDAlbum> recupererBDD( const int Id );
    static Handle<BDDAlbum> recupererBDD(const QString& album, const Handle<BDDPoch>& pochette, int annee, const Handle<BDDType>& type, const Handle<BDDArtiste>& artiste);


    QString m_nom;
    QString m_nomFormate;
    Handle<BDDPoch> m_pochette;
    int m_annee;
    Handle<BDDType> m_type;
    Handle<BDDArtiste> m_artiste;

    static bool ExisteEnPhys( const int id );

private:
    static int recupererId(const QString& nomFormate, const QString& id_Artiste);
    static int TrouverId(const QString& nom, const int& id_Artiste);

    explicit BDDAlbum(const int id, const QString& nom, const QString &nomFormate, const Handle<BDDPoch>& pochette, int annee, const Handle<BDDType>& type, const Handle<BDDArtiste>& artiste, QObject* parent = nullptr);


};

#endif // BDDALBUM_H

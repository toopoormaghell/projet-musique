#ifndef BDDARTISTE_H
#define BDDARTISTE_H

#include <QObject>
#include "idowner.h"
#include "bdd_global.h"
class BDDPoch;


class BDDSHARED_EXPORT BDDArtiste : public IdOwner
{
    Q_OBJECT
public:
    void updateBDD();
    void supprimerenBDD() const;

    virtual ~BDDArtiste();
    static BDDArtiste* recupererBDD(const int id);
    static BDDArtiste* recupererBDD(const QString& nom);
    static BDDArtiste* recupererBDD(const QString& artiste, BDDPoch &pochette);

    QString m_nom;
    QString m_nomFormate;
    BDDPoch* m_pochette;

    static void EchangerArtiste( QString& nom );

private:
    static int recupererId(const QString &nomFormate);
    static QString ChoisirArtisteEchange(const QString& nom);
    static int TrouverId(const QString& nom );

    explicit BDDArtiste(const int id, const QString &nom, const QString &nomFormate, BDDPoch *pochette, QObject* parent = NULL);
};


#endif // BDDARTISTE_H

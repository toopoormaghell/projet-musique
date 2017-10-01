#ifndef BDDARTISTE_H
#define BDDARTISTE_H

#include <QObject>
#include "idowner.h"
class BDDPoch;


class BDDArtiste : public IdOwner
{
    Q_OBJECT
public:
    void updateBDD();
    void supprimerenBDD() const;
    explicit BDDArtiste(const QString& artiste, BDDPoch &pochette, QObject* parent = NULL);
    virtual ~BDDArtiste();
    static BDDArtiste* RecupererArtiste( const int id );
    static BDDArtiste* RecupererArtparNom( QString& nom );

    QString m_nom;
    QString m_nomFormate;
    BDDPoch* m_pochette;

    static void EchangerArtiste( QString& nom );

private:
    // Indique que le créateur de la pochette est RecupererArstiste, la pochette doit donc être détruite
    bool m_isPochetteSelfCreated;
    void ajouterBDD();
    void recupererId();
    void ChoisirArtisteEchange( QString& nom );
    void TrouverId( QString& nom );

    explicit BDDArtiste(const int id, QObject* parent = NULL);
    explicit BDDArtiste(const QString& artiste, QObject* parent = NULL);
};


#endif // BDDARTISTE_H

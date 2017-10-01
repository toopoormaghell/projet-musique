#ifndef BDDARTISTE_H
#define BDDARTISTE_H

#include <QObject>
#include "idowner.h"
class BDDPoch;


class BDDArtiste : public IdOwner
{
    Q_OBJECT
public:

    explicit BDDArtiste(const QString& artiste, BDDPoch &pochette, QObject* parent = NULL);
    virtual ~BDDArtiste();

    void updateBDD();
    void supprimerenBDD() const;
    static BDDArtiste* RecupererArtiste( const int id );
    static void EchangerArtiste( QString& nom );
    void ChoisirArtisteEchange( QString& nom );

    QString m_nom;
    BDDPoch* m_pochette;
    QString m_nomFormate;



    static BDDArtiste* RecupererArtparNom( QString& nom );
private:
    // Indique que le créateur de la pochette est RecupererArstiste, la pochette doit donc être détruite
    bool m_isPochetteSelfCreated;
    void ajouterBDD();
    void recupererId();
    void TrouverId( QString& nom );
    // Constructeur avec une id
    explicit BDDArtiste(const int id, QObject* parent = NULL);
    //Construceur avec un nom d'artiste
    explicit BDDArtiste(const QString& artiste, QObject* parent = NULL);
};


#endif // BDDARTISTE_H

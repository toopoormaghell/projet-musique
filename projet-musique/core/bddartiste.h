#ifndef BDDARTISTE_H
#define BDDARTISTE_H

#include <QObject>
class BDDPoch;


class BDDArtiste : public QObject
{
    Q_OBJECT
public:

    explicit BDDArtiste(const QString& artiste, const BDDPoch& pochette, QObject* parent = NULL );
    virtual ~BDDArtiste();

    void updateBDD();
    void supprimerenBDD() const;
    static BDDArtiste* RecupererArtiste( const int id );
    static void EchangerArtiste( QString& nom );
    void ChoisirArtisteEchange( QString& nom );

    int m_id;
    QString m_nom;
    BDDPoch const* m_pochette;
    QString m_nomFormate;



    static BDDArtiste* RecupererArtparNom( QString& nom );
private:
    // Indique que le créateur de la pochette est RecupererArstiste, la pochette doit donc être détruite
    bool m_isPochetteSelfCreated;
    void ajouterBDD();
    void recupererId();
    void TrouverId( QString& nom );
    // Constructeur avec une id
    BDDArtiste( const int id, QObject* parent = NULL );
    //Construceur avec un nom d'artiste
    BDDArtiste( const QString& artiste, QObject* parent = NULL );
};


#endif // BDDARTISTE_H

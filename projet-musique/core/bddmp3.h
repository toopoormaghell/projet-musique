#ifndef BDDMP3_H
#define BDDMP3_H

#include <QObject>
#include "idowner.h"
class BDDArtiste;
class BDDAlbum;
class BDDTitre;
class BDDRelation;
class BDDType;
class BDDPoch;
class BDDMp3 : public IdOwner
{
    Q_OBJECT
public:

    explicit BDDMp3(const QString& Chemin, const BDDRelation& relation, const BDDType& type, QObject* parent = 0);
    virtual ~BDDMp3();

    void updateBDD();
    void supprimerenBDD() const;
    static BDDMp3* RecupererMp3( const int id );

    BDDRelation const* m_relation;
    QString m_chemin;
    BDDType const* m_type;

    static BDDMp3* RecupererMp3ParChemin( const QString& chemin );
    static BDDMp3* RecupererMP3ParTitre ( const int& id );
    void ChangerTag (const QString& NouveauAlbum, const QString& NouveauTitre, const QString& NouveauArtiste, const int &NouvelleAnnee, const int &NouvellePiste, const QString &NouvellePoch);
private:
    // Indique que les membres ont été créés par RecupererMp3 et doivent donc être détruits explicitement
    bool m_membersAreSelfCreated;

    void ajouterBDD();
    void recupererId();

    //Constructeur avec une ide
    explicit BDDMp3(const int id, QObject* parent = NULL);
    //Constructeur avec un chemin
    explicit BDDMp3(const QString& chemin, QObject* parent = NULL);
};

#endif // BDDMP3_H

#ifndef BDDMP3_H
#define BDDMP3_H

#include <QObject>
class BDDArtiste;
class BDDAlbum;
class BDDTitre;
class BDDRelation;
class BDDType;

class BDDMp3 : public QObject
{
    Q_OBJECT
public:

    explicit BDDMp3(const QString& Chemin, const BDDRelation& relation, const int&type, QObject *parent = 0);
    virtual ~BDDMp3();

    void updateBDD();
    void supprimerenBDD() const;
    static BDDMp3* RecupererMp3(const int id);

    BDDAlbum const* m_album;
    BDDArtiste const* m_artiste;
    BDDTitre const* m_titre;
    QString m_chemin;
    int m_id;
    BDDRelation const* m_relation;
    BDDType const* m_type;
private:
    // Indique que les membres ont été créés par RecupererMp3 et doivent donc être détruits explicitement
    bool m_membersAreSelfCreated;

    void ajouterBDD();
    void recupererId();

    //Constructeur avec une ide
    BDDMp3(const int id, QObject* parent=NULL);

};

#endif // BDDMP3_H

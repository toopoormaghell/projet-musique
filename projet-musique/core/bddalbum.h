#ifndef BDDALBUM_H
#define BDDALBUM_H

#include "util.h"
#include <QObject>
class BDDPoch;
class BDDType;

class BDDAlbum : public QObject
{
    Q_OBJECT
public:
    explicit BDDAlbum(const QString &album, const BDDPoch &pochette, int annee, int type, QObject *parent = 0);
    virtual ~BDDAlbum();

    void updateBDD();
    void supprimerenBDD() const;
    static BDDAlbum* RecupererAlbum(const int Id);


    int m_id;
    QString m_nom;
    QString m_nomFormate;
    int m_annee;
    BDDType* m_type;
    BDDPoch const* m_pochette;

   static AlbumPhys RecupAlbumEntite(const int id);
private:
    // Indique que le type et la pochette ont été créés par RecupererAlbum, et doivent donc être détruits explicitement
    bool m_areTypeAndPochetteSelfCreated;

    void ajouterBDD();
    void recupererId();

    //Constructeur avec une id
    BDDAlbum(const int id,QObject* parent=NULL);

};

#endif // BDDALBUM_H

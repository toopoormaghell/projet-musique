#ifndef META_ALBUM_H
#define META_ALBUM_H

#include <QObject>
#include <QImage>
#include "meta_titre.h"

class Meta_Album : public QObject
{
    Q_OBJECT
public:

    static Meta_Album* RecupererBDD(const int id);
    virtual ~Meta_Album();

    //Donner entités
    QString getnom_album();
    QString getnom_artiste();
    int getannee();
    QString gettype();
    QList<Meta_Titre*> gettitres();
    QImage getPoch();
    QString getsupport_p();
    int getid_alb();
    int getid_support_p();
    QString getcommentaires();
    int getid_type();
    int getid_support_m();

    //Changer entités
    void setnom_album(QString nom);
    void setnom_artiste( QString nom );
    void setannee(int annee);
    void setPoch(QImage poch);
    void settype(QString type);
    void settitres(QList<Meta_Titre*> titres);
    void setsupport_p(QString support_p);
    void setcommentaires(QString commentaires);

    Meta_Album* CreerMeta_Album(const QString& nom_album, const QString& nom_artiste, int annee, const QImage& Poch, int type, const QList<Meta_Titre*>& titres, int support_p, const QString& commentaires, const QString& ean);


    void SupprimerBDDPhys();

    void UpdateBDD();
private:
    QString m_nom_album;
    QString m_nom_artiste;
    int m_annee;
    QImage m_poch;
    QString m_Type;
    QList<Meta_Titre *> m_titres;
    QString m_support_p;
    QString m_support_m;
    QString m_commentaires;
    QString m_ean;
    //Tous les id
    int m_id_album;
    int m_id_artiste;
    int m_id_poch;
    int m_id_type;
    int m_id_support_p;
    int m_id_support_m;

    explicit Meta_Album(const QString& nom_album, const QString& nom_artiste, int annee, const QImage& Poch, const QString& Type, const QList<Meta_Titre*>& titres, const QString& support_p, const QString& support_m, const QString& commentaires, const QString& ean, int id_album, int id_artiste, int id_poch, int id_type, int id_support_p, int id_support_m, QObject* parent = NULL);
};

#endif // META_ALBUM_H

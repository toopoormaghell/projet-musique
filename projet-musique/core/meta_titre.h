#ifndef META_TITRE_H
#define META_TITRE_H

#include <QObject>
#include <QImage>

class Meta_Titre : public QObject
{
    Q_OBJECT

public:

    static Meta_Titre* RecupererBDD(const int id);
    //Donner entités
    QString getnom_album();
    QString getnom_artiste();
    QString getnom_titre();
    int getannee();
    QString getduree();
    int getnum_piste();
    QString gettype();
    QString getsupport();

    //Changer entités
    void setnom_album(QString nom);
    void setnom_artiste( QString nom );
    void setnom_titre(QString nom);
    void setannee(int annee);
    void setduree(QString duree);
    void setnum_piste(int num);
    void settype(QString type);
    void setsupport( QString support);

private:
    QString m_nom_album;
    QString m_nom_artiste;
    QString m_nom_titre;
    int m_annee;
    QString m_duree;
    int m_num_piste;
    QImage m_poch;
    QString m_Type;
    QString m_Support_phys;
    bool m_MP3;

    //Tous les id
    int m_id_album;
    int m_id_artiste;
    int m_id_titre;
    int m_id_relation;
    int m_id_type;
    int m_id_support_phys;

    explicit Meta_Titre(const QString& nom_album, const QString& nom_artiste, const QString& nom_titre, int annee, const QString& duree, int num_piste, const QImage& poch, const QString& type, const QString& support, int id_alb, int id_art, int id_titre, int id_relation, int id_type, int id_support, bool MP3, QObject* parent = NULL);
};

#endif // META_TITRE_H

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
    QString getsupportphys();
    QString getsupportmp3();
    int getid_support_p();
    int getid_support_m();
    QString getcheminmp3();
    int getid_relation();
    int getid_titre();
    QImage getpoch();
    int getid_art();
    int getid_alb();
    int getid_type();

    //Changer entités
    void setnom_album(QString nom);
    void setnom_artiste( QString nom );
    void setnom_titre(QString nom);
    void setannee(int annee);
    void setduree(QString duree);
    void setnum_piste(int num);
    void settype(QString type);
    void setsupportphys(QString support);
    void setsupportmp3(QString support);
    void setcheminmp3(QString chemin);

   virtual ~Meta_Titre();

    void ChangerDonnees(const QString& nom_album, const QString& nom_artiste, const QString& nom_titre, int annee, const QString& duree, int num_piste, const QImage& poch, const QString& type, const QString& support_p, const QString& support_m, const QString& chemin_m, int id_alb, int id_art, int id_titre, int id_relation, int id_type, int id_support_p, int id_support_m);
private:
    QString m_nom_album;
    QString m_nom_artiste;
    QString m_nom_titre;
    int m_annee;
    QString m_duree;
    int m_num_piste;
    QImage m_poch;
    QString m_Type;
    QString m_Support_p;
    QString m_Support_m;
    QString m_chemin_m;

    //Tous les id
    int m_id_album;
    int m_id_artiste;
    int m_id_titre;
    int m_id_relation;
    int m_id_type;
    int m_id_support_p;
    int m_id_support_m;


    explicit  Meta_Titre(const QString& nom_album, const QString& nom_artiste, const QString& nom_titre, int annee, const QString& duree, int num_piste, const QImage& poch, const QString& type, const QString& support_p, const QString& support_m, const QString& chemin_m, int id_alb, int id_art, int id_titre, int id_relation, int id_type, int id_support_p, int id_support_m, QObject* parent = NULL);
};

#endif // META_TITRE_H

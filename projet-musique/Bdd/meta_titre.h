#ifndef META_TITRE_H
#define META_TITRE_H

#include <QObject>
#include <QImage>
#include "bdd_global.h"

class BDDSHARED_EXPORT Meta_Titre : public QObject
{
    Q_OBJECT

public:

    static Meta_Titre* RecupererBDD(const int id);
    static Meta_Titre* RecupererBDDMP3( const int id);

    //Donner entités
    const QString& getnom_album();
    const QString& getnom_artiste();
    const QString& getnom_titre();
    int getannee();
    const QString& getduree();
    int getnum_piste();
    const QString& gettype();
    const QString& getsupportphys();
    const QString& getsupportmp3();
    int getid_support_p();
    int getid_support_m();
    const QString& getcheminmp3();
    int getid_relation();
    int getid_titre();
    const QImage& getpoch();
    int getid_art();
    int getid_alb();
    int getid_type();
    int getid_mp3();
    const QString& getcommentaires();
    const QString& getean();

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

    static Meta_Titre* CreerMeta_Titre(const QString& nom_album, const QString& nom_artiste, const QString& nom_titre, int annee, const QString& duree, int num_piste, const QImage& poch, int type, int support_p, int support_m, const QString& chemin_m, const QString& commentaires, const QString& ean);

    void ChangerDonnees(const QString& nom_album, const QString& nom_artiste, const QString& nom_titre, int annee, const QString& duree, int num_piste, const QImage& poch, const QString& type, const QString& support_p, const QString& support_m, const QString& chemin_m, int id_alb, int id_art, int id_titre, int id_relation, int id_type, int id_support_p, int id_support_m);

    void UpdateBDD();

    void SupprimerBDDMP3();
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
    QString m_commentaires;
    QString m_ean;

    //Tous les id
    int m_id_album;
    int m_id_artiste;
    int m_id_titre;
    int m_id_relation;
    int m_id_type;
    int m_id_support_p;
    int m_id_support_m;
    int m_id_mp3;

    explicit  Meta_Titre(const QString& nom_album, const QString& nom_artiste, const QString& nom_titre, int annee, const QString& duree, int num_piste, const QImage& poch, const QString& type, const QString& support_p, const QString& support_m, const QString& chemin_m, const QString& commentaires, const QString& ean, int id_alb, int id_art, int id_titre, int id_relation, int id_type, int id_support_p, int id_support_m, int id_mp3, QObject* parent = NULL);
};

#endif // META_TITRE_H

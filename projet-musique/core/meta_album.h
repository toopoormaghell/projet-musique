#ifndef META_ALBUM_H
#define META_ALBUM_H

#include <QObject>
#include <QImage>
#include "meta_titre.h"

class Meta_Album : public QObject
{
    Q_OBJECT
public:
    explicit Meta_Album(QObject *parent = nullptr);

 /*   //Donner entités
    QString getnom_album();
    QString getnom_artiste();
    int getannee();
    QString gettype();
    QList<Meta_Titre> gettitres();

    //Changer entités
    void setnom_album(QString nom);
    void setnom_artiste( QString nom );
    void setannee(int annee);
    void settype(QString type);
    void settitres( QList < Meta_Titre > titres);


private:
    QString m_nom_album;
    QString m_nom_artiste;
    int m_annee;
    QImage m_poch;
    QString m_Type;
    QList<Meta_Titre> m_titres;

    //Tous les id
    int m_id_album;
    int m_id_artiste;
    int m_id_type;

    */
};

#endif // META_ALBUM_H

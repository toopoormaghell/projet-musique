#ifndef META_ARTISTE_H
#define META_ARTISTE_H

#include <QObject>
#include <QImage>
#include "meta_album.h"
#include "bdd_global.h"

class BDDSHARED_EXPORT Meta_Artiste : public QObject
{
    Q_OBJECT
public:
    static Meta_Artiste* RecupererBDD( const int id );
    virtual ~Meta_Artiste();

    QString getNom_Artiste();
    QImage getPoch();


    int get_id_artiste();
    int get_id_poch();

private:
    QString m_nom_artiste;
    QImage m_poch;

    int m_id_artiste;
    int m_id_poch;

    explicit Meta_Artiste(const QString& nom_artiste, QImage& Poch, int id_artiste, int id_poch, QObject *parent = nullptr);
};

#endif // META_ARTISTE_H

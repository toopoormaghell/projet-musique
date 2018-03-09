#ifndef BDDPOCH_H
#define BDDPOCH_H

#include <QObject>
#include <QString>
#include <QImage>
#include <QList>
#include "idowner.h"

class BDDPoch : public IdOwner
{
    Q_OBJECT

public:
    void updateBDD();
    void supprimerenBDD() const;
    static BDDPoch* recupererBDD(const int id);
    static BDDPoch* recupererBDD(const QImage& image, const QString& album, const QString& artiste);

    QImage m_image;
    QString m_chemin;

    static QList<int> pochettesparart(const QString& artiste);

private:
    void sauverImage() const;
    static QString creerchemin(const QString& album, const QString& artiste);

    explicit BDDPoch(const int id, const QImage& image, const QString& chemin,QObject* parent = NULL);
};


#endif // BDDPOCH_H

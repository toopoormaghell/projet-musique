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
    explicit BDDPoch(const QImage& image, const QString& album, const QString& artiste, QObject* parent = NULL);

    void updateBDD();
    void supprimerenBDD() const;
    static BDDPoch* recupererBDD(const int id);

    QImage m_image;
    QString m_chemin;

    static QString creerchemin(const QString& album, const QString& artiste);
    static QList<int> pochettesparart(const QString& artiste);

private:
    void sauverImage(const QString& album, const QString& artiste);
    void recupererId();
    void ajouterBDD();

    explicit BDDPoch(const int id, const QImage& image, const QString& chemin,QObject* parent = NULL);
};


#endif // BDDPOCH_H

#ifndef BDDPOCH_H
#define BDDPOCH_H

#include <QObject>
#include <QString>
#include <QImage>
#include <QList>
#include "idowner.h"
#include "bdd_global.h"
#include "handle.h"

class BDDSHARED_EXPORT BDDPoch : public IdOwner
{
    Q_OBJECT

public:
    virtual ~BDDPoch();
    void updateBDD();
    void supprimerenBDD() const;
    static Handle<BDDPoch> recupererBDD(const int id);
    static Handle<BDDPoch> recupererBDD(const QImage& image, const QString& album, const QString& artiste);
    void sauverImage() const;
    QImage m_image;
    QString m_chemin;

    static QList<int> pochettesparart(const QString& artiste, const QString id_art);
    static QString creerchemin(const QString& album, const QString& artiste);
private:

    explicit BDDPoch(const int id, const QImage& image, const QString& chemin,QObject* parent = nullptr);

};


#endif // BDDPOCH_H

#ifndef BDDPOCH_H
#define BDDPOCH_H

#include <QObject>
#include <QString>
#include <QImage>
#include <QList>

class BDDPoch : public QObject
{
    Q_OBJECT

public:
    explicit BDDPoch(const QImage& image, const QString& album, const QString& artiste, QObject* parent = NULL);

    void updateBDD();
    void supprimerenBDD() const;
    static BDDPoch* recupererBDD( const int id );
    static BDDPoch* recupererPoch( const QString& album, const QString& artiste );

    int m_id;
    QString m_chemin;
    QImage m_image;


    static QString creerchemin( const QString& album, const QString& artiste );
    static QList<int> pochettesparart( const QString& artiste );

private:
    void sauverImage( const QString& album, const QString& artiste );
    void recupererId();
    void ajouterBDD();

    explicit BDDPoch(const int id, QObject* parent = NULL);
};


#endif // BDDPOCH_H

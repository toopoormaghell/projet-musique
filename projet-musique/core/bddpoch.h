#ifndef BDDPOCH_H
#define BDDPOCH_H

#include <QObject>
#include <QString>
#include <QImage>

class BDDPoch : public QObject
{
    Q_OBJECT

public:
    explicit BDDPoch( const QImage& image, const QString& album, const QString& artiste, QObject* parent = NULL );
    virtual ~BDDPoch();

    void updateBDD();
    void supprimerenBDD() const;
    static BDDPoch* recupererBDD( const int id );
    static BDDPoch* recupererPoch( const QString& album, const QString& artiste );
    int m_id;
    QImage m_image;
    QString m_chemin;


    static QString creerchemin( const QString& album, const QString& artiste );


private:
    void sauverImage( const QString& album, const QString& artiste );
    void recupererId();
    void ajouterBDD();

    BDDPoch( const int id, QObject* parent = NULL );
    BDDPoch( const QString& album, const QString& artiste, QObject* parent );

};


#endif // BDDPOCH_H

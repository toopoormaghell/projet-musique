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
    void deleteBDD();
    static BDDPoch* recupererBDD( const int id );

    int m_id;
    QImage m_image;
    QString m_chemin;


private:
    void sauverImage(const QString& album, const QString& artiste);
    void recupererId();
    void ajouterBDD();

    BDDPoch( const int id, QObject* parent = NULL );
};


#endif // BDDPOCH_H

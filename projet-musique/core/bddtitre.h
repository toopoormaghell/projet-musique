#ifndef BDDTITRE_H
#define BDDTITRE_H

#include <QObject>
class BDDArtiste;
class BDDAlbum;
class BDDTitre : public QObject
{
    Q_OBJECT
public:
    explicit BDDTitre( const QString& nom, const int& num_piste, const QString& duree, QObject *parent = 0 );

    void updateBDD();
    void supprimerenBDD()const;

    static BDDTitre* RecupererTitre( const int id );

    int m_id;
    QString m_nom;
    QString m_nomFormate;
    int m_num_piste;
    QString m_duree;
    bool m_mp3;
    bool m_phys;
    QList<int> Similaires( const int id );
    BDDArtiste const* m_artiste;
    BDDAlbum const* m_album;
private:
    void ajouterBDD();
    void recupererId();
    void mp3etphys();
    //Constructeur avec une id
    BDDTitre( const int id, QObject* parent = NULL );

};

#endif // BDDTITRE_H

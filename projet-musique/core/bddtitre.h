#ifndef BDDTITRE_H
#define BDDTITRE_H

#include <QObject>
class BDDArtiste;
class BDDAlbum;
class BDDTitre : public QObject
{
    Q_OBJECT
public:
    explicit BDDTitre(const QString& nom, QObject* parent = 0  );
    ~BDDTitre();

    void updateBDD();
    void supprimerenBDD()const;

    static BDDTitre* RecupererTitre( const int id );

    int m_id;
    QString m_nom;
    QString m_nomFormate;
    QList<int> Similaires( const int id );
  //  BDDArtiste const* m_artiste;
  //  BDDAlbum const* m_album;

    void mp3physfusion();
private:
    void ajouterBDD();
    //Indique que l'artiste et l'album ont été créés par RécupérerTitre et doivent donc être détruits explicitement
    bool m_areAlbumAndArtisteSelfCreated;
    void recupererId();

    //Constructeur avec une id
    BDDTitre( const int id, QObject* parent = NULL );

};

#endif // BDDTITRE_H

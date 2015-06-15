#ifndef BDDGESTIONMP3_H
#define BDDGESTIONMP3_H

#include <QObject>
#include <fileref.h>
#include <id3v2/frames/attachedpictureframe.h>
#include <id3v2/id3v2tag.h>
#include <QStringList>
#include <QMap>

class BDDGestionMp3 : public QObject
{
    Q_OBJECT
public:
    explicit BDDGestionMp3(QObject *parent = 0);
     void demarreractualiser(int type);

    QString m_fichierlu;
    int m_pourcentage;
signals:
    void pourcentage();
private slots:
    void step();
private:
    //Actualiser MP3 + fonctions associées
    void actualiserMp3(QString chemin);
    QMap<int, QStringList> recupererMp3(int Type);
    QString getdossierpardef();
    void ArtisteParChemin(TagLib::String &artist, QString chemin);
    QImage ImageAlbum(const TagLib::FileRef& f);
    void creerfilefichiers();
    void supprimerAnciensMP3();

    QStringList m_filelist;
    QMap < int, QStringList > m_Chemins;
    int m_type;
    int m_iteration;

  void SupprimerMP3(int Id);

};

#endif // BDDGESTIONMP3_H

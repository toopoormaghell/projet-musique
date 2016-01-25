#ifndef LECTEURMODELE_H
#define LECTEURMODELE_H



#include <QObject>
#include <QScopedPointer>
class LecteurVue;
class QMediaPlayer;



class LecteurModele : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( LecteurModele )

public:
    explicit LecteurModele( QObject* parent = 0 );
    virtual ~LecteurModele();



    // Returns GUI of the model
    QWidget* getGui() const;



private slots:
    // Lance la lecture du lecteur MP3
    void on_lectureDemandee();
    // Lance la pause du lecteur MP3
    void on_pauseDemandee();



private:
    // Connecte les signaux provenant de la GUI
    void connecteSignauxDeGui();
    // Deconnecte les signaux provenant de la GUI
    void deconnecteSignauxDeGui();

    // GUI du lecteur
    LecteurVue* m_vue;
    // Objet Qt representant un lecteur de media (MP3 entre autres)
    QMediaPlayer* m_player;
};



#endif // LECTEURMODELE_H

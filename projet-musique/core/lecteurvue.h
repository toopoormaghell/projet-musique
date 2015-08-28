#ifndef LECTEUR_H
#define LECTEUR_H



#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>



class OngletMP3;



namespace Ui {
class LecteurVue;
}



class LecteurVue : public QWidget
{
    Q_OBJECT

public:
    explicit LecteurVue( QWidget* parent = 0 );
    virtual ~LecteurVue();



signals:
    // Signal emit lorsque l'utilisateur demande la lecture
    void lectureDemandee();
    // Signal emit lorsque l'utilisateur demande une pause
    void pauseDemandee();



private slots:
    // Slot permettant de reemettre un signal pour lecture / pause demandee
    void on_lecturePause_clicked();



private:
    // GUI du lecteur
    Ui::LecteurVue *ui;
    // Indique l'etat courant du lecteur
    enum StatutLecturePause
    {
        LECTURE_EN_COURS = 0,
        PAUSE_EN_COURS,
        AUCUN
    };
    StatutLecturePause m_statutLecturePause;



public:
    void Lecture();
    void Stop();

    void setParentTab(const OngletMP3 &parentTab );
    const OngletMP3& getParentTab() const;
public slots:
    void AfficherTag();
signals:
    void tick();
private slots:
    void on_Stop_clicked();

    void positionChanged( qint64 time );
    void on_LectureEnCours_sliderMoved(int position);

    void on_AleaArtiste_clicked();

private:
    QMediaPlayer* m_player;
    const OngletMP3* m_parentTab;
    QMediaPlaylist* m_playlist;
};

#endif // LECTEUR_H

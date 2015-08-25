#ifndef LECTEURMP3_H
#define LECTEURMP3_H



#include <QObject>
#include <QScopedPointer>
class QMediaPlayer;
class QMediaPlaylist;
class LecteurMP3Gui;




class LecteurMP3 : public QObject
{
    Q_OBJECT
public:
    explicit LecteurMP3( LecteurMP3Gui* const gui, QObject* parent = 0 );
    virtual ~LecteurMP3();


private slots:
    void on_playPause_clicked();

private:
    // Manager du player
    QScopedPointer<QMediaPlayer> m_player;
    // Manager de la playlist
    QScopedPointer<QMediaPlaylist> m_playlist;
    // Pointeur vers la GUI du lecteur
    LecteurMP3Gui* const m_lecteurGui;
};



#endif // LECTEURMP3_H

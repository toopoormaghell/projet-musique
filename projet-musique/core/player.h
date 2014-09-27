#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <phonon>
class OngletMp3;

namespace Ui {
class Player;
}

class Player : public QWidget
{
    Q_OBJECT
    
public:
    explicit Player(QWidget *parent = 0);
    ~Player();

    void setParentTab( const OngletMp3& parentTab );
    const OngletMp3& getParentTab() const;
    
private slots:
    void on_m_playPause_clicked();

    void on_m_stopButton_clicked();

    void updateTime( qint64 time );
    void updateSlider( qint64 time );

    void on_m_songSlider_sliderMoved(int position);

    void on_m_songSlider_valueChanged(int value);

private:
    Ui::Player *ui;
    const OngletMp3* m_parentTab;
    Phonon::MediaObject m_mediaObject;
    Phonon::AudioOutput m_mediaAudioOutput;
};

#endif // PLAYER_H

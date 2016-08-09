#ifndef DIALOGCONTROLES_H
#define DIALOGCONTROLES_H

#include <QWidget>
#include <QMediaPlayer>
#include <fileref.h>
#include <id3v2/frames/attachedpictureframe.h>
#include <id3v2/id3v2tag.h>

namespace Ui {
class DialogControles;
}

class DialogControles : public QWidget
{
    Q_OBJECT

public:
    explicit DialogControles( QWidget *parent = 0);
    ~DialogControles();
    QMediaPlayer* player;
signals:
    void FinMP3();
public slots:
    void ChangerMP3(QString temp);
    void Changer(QString temp);
private slots:
    void on_Lecture_clicked();

    void on_Arret_clicked();

    void on_Volume_sliderMoved(int position);

    void avancerSlider(qint64 pos);
    void changerduree(qint64 dur);


    void on_Position_sliderReleased();

    void ArriverFin(QMediaPlayer::MediaStatus status);
private:
    Ui::DialogControles *ui;
    void AfficherIcones();

    QString mp3;
    void ChargerMp3();

    void AfficherInfos();
    QPixmap ImageAlbum(const TagLib::FileRef &f);
};

#endif // DIALOGCONTROLES_H

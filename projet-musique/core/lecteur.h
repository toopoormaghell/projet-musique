#ifndef LECTEUR_H
#define LECTEUR_H

#include <QWidget>
#include <QMediaPlayer>
class OngletMP3;

namespace Ui {
class Lecteur;
}

class Lecteur : public QWidget
{
    Q_OBJECT

public:
    explicit Lecteur(QWidget *parent = 0);
    ~Lecteur();
    void Lecture();
    void Stop();

    void setParentTab(const OngletMP3 &parentTab );
    const OngletMP3& getParentTab() const;
signals:
    void tick();
private slots:
    void on_Lecture_clicked();
    void on_Stop_clicked();

    void positionChanged( qint64 time );
    void on_LectureEnCours_sliderMoved(int position);

private:
    Ui::Lecteur *ui;
    QMediaPlayer* m_player;
    const OngletMP3* m_parentTab;
};

#endif // LECTEUR_H

#ifndef LECTEURMP3GUI_H
#define LECTEURMP3GUI_H



#include <QWidget>



namespace Ui {
class LecteurMP3Gui;
}



class LecteurMP3Gui : public QWidget
{
    Q_OBJECT

public:
    explicit LecteurMP3Gui(QWidget *parent = 0);
    ~LecteurMP3Gui();
//    void Lecture();
//    void Stop();

//    void setParentTab(const OngletMP3 &parentTab );
//    const OngletMP3& getParentTab() const;
public slots:
//    void AfficherTag();
signals:
    void playPauseClicked();

//    void tick();
private slots:
//    void on_Lecture_clicked();
//    void on_Stop_clicked();

//    void positionChanged( qint64 time );
//    void on_LectureEnCours_sliderMoved(int position);

//    void on_AleaArtiste_clicked();

private:
    // GUI du lecteur
    Ui::LecteurMP3Gui *ui;
};



#endif // LECTEURMP3GUI_H

#ifndef PRESENTATIONLECTURE_H
#define PRESENTATIONLECTURE_H

#include <QWidget>

namespace Ui {
class PresentationLecture;
}

class PresentationLecture : public QWidget
{
    Q_OBJECT

public:
    explicit PresentationLecture(QWidget *parent = 0);
    ~PresentationLecture();

private:
    Ui::PresentationLecture *ui;
};

#endif // PRESENTATIONLECTURE_H

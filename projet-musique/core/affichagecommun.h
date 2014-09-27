#ifndef AFFICHAGECOMMUN_H
#define AFFICHAGECOMMUN_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
class AffichageCommun  : public QObject
{

public:
    explicit AffichageCommun(QObject *parent = 0);

    QListWidgetItem *afficherPochetteList(QImage* image);
    QTableWidgetItem *afficherPochetteTable(QImage *image);
    QPixmap afficherPochetteLabel(QImage *image);
};

#endif // AFFICHAGECOMMUN_H

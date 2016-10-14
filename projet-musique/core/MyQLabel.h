#ifndef LIBELLE_H
#define LIBELLE_H
#include <QLabel>
#include <QMouseEvent>
#include <QObject>
#include <QtGui>

class MyQLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyQLabel (QObject* parent=0);
    void mousePressEvent(QMouseEvent *e);
signals :
    void clic();


};

#endif // LIBELLE_H

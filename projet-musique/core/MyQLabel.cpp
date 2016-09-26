#include "MyQLabel.h"
#include <QMouseEvent>

MyQLabel::MyQLabel(QObject* parent)
{

}

void MyQLabel::mousePressEvent(QMouseEvent *e)
{
    //On regarde quelle bouton a été appuyé si c'est le bouton gauche on émet le signal
    // on met aussi deux signes = sinon c'est une affectation
    if(e->button() == Qt::LeftButton)
    {
        emit clic();
    }
}

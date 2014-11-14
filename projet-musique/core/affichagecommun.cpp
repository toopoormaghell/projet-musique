#include "affichagecommun.h"

AffichageCommun::AffichageCommun(QObject *parent) :
    QObject(parent)
{
}
QListWidgetItem* AffichageCommun::afficherPochetteList(QImage* image)
{
    QListWidgetItem *item=new QListWidgetItem;
    QPixmap* pixmap=new QPixmap;
    pixmap->convertFromImage(*image);
    QPixmap pixmapscaled= pixmap->scaled(150,150,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    item->setIcon(QIcon(pixmapscaled));

    return item;
}
QTableWidgetItem* AffichageCommun::afficherPochetteTable(QImage* image)
{
    QTableWidgetItem *item=new QTableWidgetItem();
    QPixmap* pixmap=new QPixmap();
    pixmap->convertFromImage(*image);
    QPixmap pixmapscaled=pixmap->scaled(150,150,Qt::IgnoreAspectRatio,Qt::FastTransformation);

    item->setIcon(QIcon(pixmapscaled));
    return item;
}
QPixmap AffichageCommun::afficherPochetteLabel(QImage* image)
{

    QPixmap* pixmap = new QPixmap();
   pixmap->convertFromImage(*image);
   QPixmap imageScaled = pixmap->scaled(150,150,Qt::IgnoreAspectRatio,Qt::FastTransformation);


   return imageScaled;
}

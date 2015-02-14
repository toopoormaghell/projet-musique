#include "affichagecommun.h"
#include <QListWidgetItem>
#include <QImage>
#include <QIcon>



AffichageCommun::AffichageCommun()
{
}



AffichageCommun::~AffichageCommun()
{
}



QListWidgetItem* AffichageCommun::afficherPochetteList( const QImage& image ) const
{
    QPixmap pixmapScaled( afficherPochetteLabel( image ) );
    QListWidgetItem* item = new QListWidgetItem;
    item->setIcon( QIcon( pixmapScaled ) );
    return item;
}



QPixmap AffichageCommun::afficherPochetteLabel( const QImage& image ) const
{
    QPixmap scaled( QPixmap::fromImage( image ) );
    scaled = scaled.scaled( 150, 150 );
    return scaled;
}

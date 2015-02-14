#include "barreavancement.h"



BarreAvancement::BarreAvancement( QWidget* parent ):
    QProgressBar( parent )
{
    reset();
}



BarreAvancement::~BarreAvancement()
{
}



void BarreAvancement::reset()
{
    update( 0.0f );
}



void BarreAvancement::update( const float percent, const QString& message )
{
    setValue( percent * 100 );
    setFormat( message );
}

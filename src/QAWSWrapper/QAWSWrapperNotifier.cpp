#include "QAWSWrapperNotifier.h"



QAWSWrapperNotifier::QAWSWrapperNotifier( QObject* parent ):
    QObject( parent )
{
}



void QAWSWrapperNotifier::emitStepAchieved( QString message )
{
    Q_EMIT stepAchieved( message );
}

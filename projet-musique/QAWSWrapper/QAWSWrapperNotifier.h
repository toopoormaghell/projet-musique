#ifndef QAWSWRAPPERNOTIFIER_H
#define QAWSWRAPPERNOTIFIER_H



#include "QAWSWrapper_global.h"
#include <QObject>



class QAWSWRAPPERSHARED_EXPORT QAWSWrapperNotifier : public QObject
{

    Q_OBJECT

public:
    /**
     * @brief Default constructor for QObject derived class
     * @param parent Parent QObject of this class
     */
    explicit QAWSWrapperNotifier( QObject* parent = nullptr );



    /**
     * @brief Emits a signal indicating that a step was achieved in QAWSWrapper
     * @param message Message related to the achieved step
     */
    void emitStepAchieved( QString message );



Q_SIGNALS:
    /**
     * @brief Signal emitted when a step of QAWSWrapper is achieved
     * @param message String containing an English message
     */
    void stepAchieved( QString message );
};



#endif // QAWSWRAPPERNOTIFIER_H

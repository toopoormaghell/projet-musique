#ifndef QAWSWRAPPER_H
#define QAWSWRAPPER_H



#include "QAWSWrapper_global.h"
#include <QScopedPointer>
#include <QStringList>
class Meta_Album;
class QAWSWrapperNotifier;



class QAWSWRAPPERSHARED_EXPORT QAWSWrapper
{
public:
    /**
     * @brief Constructor with one parameter
     * @param ean EAN from which to take information
     */
    QAWSWrapper();

    /**
     * @brief Destructor
     */
    ~QAWSWrapper();

    /**
     * @brief Return the notifier for the object
     * @return A const reference to the notifier used to emit signals
     */
    QAWSWrapperNotifier& getNotifier();

    // Return the album related to the given EAN
    Meta_Album* getAlbumFromEAN( const QString& ean );

    //Retour l'album relatif à la release donnée
    Meta_Album* getAlbumFromRelease( const QString& ean );

private:
    // Notifier to emit signals
    QScopedPointer<QAWSWrapperNotifier> m_notifier;

    // Default copy constructor, not implemented on purpose
    QAWSWrapper( const QAWSWrapper& other );
    // Default assignement operator, not implemented on purpose
    QAWSWrapper& operator=( const QAWSWrapper& rhs );
};



#endif // QAWSWRAPPER_H

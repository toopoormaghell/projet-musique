#ifndef QAWSWRAPPER_H
#define QAWSWRAPPER_H



#include "QAWSWrapper_global.h"
#include "util.h"



/**
 * @brief Class wrapping calls to Amazon Web Service API
 *
 * This class contains one method that returns an AlbumPhys object.
 * It makes the necessary stuff to get all the information associated
 * to an EAN.
 */
class QAWSWRAPPERSHARED_EXPORT QAWSWrapper
{
public:
    // Default constructor, not implemented on purpose
    QAWSWrapper();
    // Default copy constructor, not implemented on purpose
    QAWSWrapper( const QAWSWrapper& other );
    // Destructor
    ~QAWSWrapper();
    // Default assignement operator, not implemented on purpose
    QAWSWrapper& operator=( const QAWSWrapper& rhs );

    // Return the album related to the given EAN
    AlbumPhys getAlbumFromEAN( const QString& ean );

    // Return the list of possible artists
    const QStringList& getArtistsList() const;



private:
    // List of the artists received from the AWS
    QStringList m_artistsList;
};



#endif // QAWSWRAPPER_H

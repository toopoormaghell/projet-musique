#ifndef QAWSWRAPPER_H
#define QAWSWRAPPER_H



#include "QAWSWrapper_global.h"
#include "util.h"



class QAWSWRAPPERSHARED_EXPORT QAWSWrapper
{
public:
    // Default constructor, not implemented on purpose
    QAWSWrapper();
    // Destructor
    ~QAWSWrapper();

    // Return the album related to the given EAN
    AlbumPhys getAlbumFromEAN( const QString& ean );

    // Return the list of possible artists
    const QStringList& getArtistsList() const;



private:
    // List of the artists received from the AWS
    QStringList m_artistsList;

    // Default copy constructor, not implemented on purpose
    QAWSWrapper( const QAWSWrapper& other );
    // Default assignement operator, not implemented on purpose
    QAWSWrapper& operator=( const QAWSWrapper& rhs );
};



#endif // QAWSWRAPPER_H

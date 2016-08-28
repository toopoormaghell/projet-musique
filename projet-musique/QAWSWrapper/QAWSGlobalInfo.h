#ifndef QAWSGLOBALINFO_H
#define QAWSGLOBALINFO_H



/**
 * This namespace gives access to the necessary information to
 * create signed requests to Amazon Web Services.
 */
namespace QAWSGlobalInfo
{
    /**
     * @brief Return the French market place URL
     */
    const char* getMarketPlaceURL()
    {
        return "webservices.amazon.fr";
    }

    /**
     * @brief Return the market place URI to get XML
     */
    const char* getMarketPlaceURI()
    {
        return "/onca/xml";
    }

    /**
     * @brief Return the associate tag
     *
     * The associate tag is an alphanumeric token that uniquely identifies
     * someone as an associate
     */
    const char* getAssociateTag()
    {
        return "990460715344";
    }

    /**
     * @brief Return the access key ID
     *
     * The Amazon Web Services access key ID which uniquely identifies someone.
     */
    const char* getAccessKeyID()
    {
        return "AKIAJOCTDCSVNM5IJ5PQ";
    }

    /**
     * @brief Return the secret access key
     *
     * A key that is used in conjunction with the Access Key ID to
     * cryptographically sign an API request.
     */
    const char* getSecretAccessKey()
    {
        return "fVKexEofcDNu7s1DAUlbygltFqnb+GoYseafq5+6";
    }
}



#endif // QAWSGLOBALINFO_H

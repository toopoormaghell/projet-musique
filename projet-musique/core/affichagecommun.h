#ifndef AFFICHAGECOMMUN_H
#define AFFICHAGECOMMUN_H



#include <QPixmap>
class QListWidgetItem;
class QImage;



/**
 * @brief Utilities class
 *
 * This class might be removed later since it contains few and short
 * utility methods. They also could be made static, since no data is stored
 * in this class.
 */
class AffichageCommun
{
public:
    explicit AffichageCommun();
    ~AffichageCommun();

    /**
     * @brief Return a QListWidgetItem with a QImage as icon in it
     * @param image QImage scaled to 150x150 then inserted as icon in the returned objet
     * @return A QListWidgetItem with a QImage as icon in it
     */
    QListWidgetItem* afficherPochetteList( const QImage& image) const;

    /**
     * @brief Convert a QImage to a QPixmap, scaling it to 150x150.
     * @param image Image to convert
     * @return A QPixmap containing the scaled image
     */
    QPixmap afficherPochetteLabel(const QImage& image ) const;

private:
    // Default copy constructor, not implemented on purpose
    AffichageCommun( const AffichageCommun& rhs );
    // Default assignment operator, not implemented on purpose
    AffichageCommun& operator=( const AffichageCommun& other );
};



#endif // AFFICHAGECOMMUN_H

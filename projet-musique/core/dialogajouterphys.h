#ifndef DIALOGAJOUTERPHYS_H
#define DIALOGAJOUTERPHYS_H



#include <QDialog>
#include "util.h"
#include "QAWSWrapper.h"



namespace Ui
{
    class DialogAjouterPhys;
}



class DialogAjouterPhys : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Default constructor inherited by QWidget way of working
     * @param parent Parent widget of this dialog
     */
    explicit DialogAjouterPhys( QWidget* parent = 0 );

    /**
     * @brief Constructor for this dialog with an album id
     * @param id_album Album id used to initialize the dialog
     * @param parent Parent widget of this dialog
     */
    explicit DialogAjouterPhys( int id_album, QWidget* parent = 0 );

    /**
     * @brief Destructor
     */
    virtual ~DialogAjouterPhys();



private Q_SLOTS:
    /**
     * @brief Affiche les messages informatifs pour l'utilisateur
     * @param message Message à afficher
     */
    void AfficherInteraction( QString message );



signals:
    void ajout();
private slots:
    void on_ChercherEAN_clicked();
    void on_Enregistrer_clicked();
    void AffichageListeArtistes( int id );
    void on_ViderAlbum_clicked();
    void on_Supprimer_Titre_clicked();
    void on_pushButton_clicked();
    void on_Ajouter_Titre_clicked();
    void AjouterTitreManuel( const QString& titre, const QString& duree, const QString& artiste );

private:
    void recupererEAN();
    void AfficherAlbum();
    void AfficherPoch();
    void ViderBoiteDialogue();

    Ui::DialogAjouterPhys* ui;
    AlbumPhys m_album;
    QAWSWrapper m_research;
    QString m_affichage;
    QString m_EAN;
    int m_Type;

    void RecupererAlbum();
    void listeNumeros();
    void AjoutConnex();

    // Make this class not copiable
    Q_DISABLE_COPY( DialogAjouterPhys )
};



#endif // DIALOGAJOUTERPHYS_H

#include "importationlistephysiques.h"
#include "ui_importationlistephysiques.h"
#include "bddinterface.h"
#include "discogs.h"

ImportationListePhysiques::ImportationListePhysiques(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportationListePhysiques)
{
    ui->setupUi(this);
}

ImportationListePhysiques::~ImportationListePhysiques()
{
    delete ui;
}

void ImportationListePhysiques::initFromFile( const QString& fileName )
{
    afficherContenuFichierSauvegarde( fileName );
}

void ImportationListePhysiques::afficherContenuFichierSauvegarde( const QString& fileName )
{
/*    BDDInterface tmp;
    QMap<int,QStringList> resultat = tmp.lecturefichiersauv(fileName);

    ui->m_vueTable->setRowCount(resultat.size());
    QMap<int,QStringList>::const_iterator iterateur = resultat.constBegin();
    for( ; iterateur != resultat.constEnd(); ++iterateur )
    {
        const int& cle = iterateur.key ();
        const QStringList& ligne = iterateur.value ();

        QString Artiste( ligne[0] );
        Artiste.replace( "$", "'" );
        QString Album( ligne[1] );
        Album.replace( "$", "'" );
        const QString Origine( ligne[2] );
        const QString bdd( ligne[3] );

        QColor couleur( 255, 255, 255 );
        if ( bdd == "non entre" )
            couleur.setRgb( 180, 150, 255 );

        QTableWidgetItem* temp = new QTableWidgetItem( Artiste );
        temp->setBackgroundColor( couleur );
        ui->m_vueTable->setItem( cle, 0, temp );
        temp = new QTableWidgetItem( Album );
        temp->setBackgroundColor( couleur );
        ui->m_vueTable->setItem( cle, 1, temp );
        temp = new QTableWidgetItem( Origine );
        temp->setBackgroundColor( couleur );
        ui->m_vueTable->setItem( cle, 2, temp );
    }
    ui->m_vueTable->resizeColumnsToContents();
    */
}

void ImportationListePhysiques::on_m_vueTable_cellClicked(int row, int column)
{
  /*  //déclaration des classes
    Discogs tmp;

    //récupération des données du tableau
    QString albumSelectionne = ui->m_vueTable->item( row, 0 )->text();
    QString artisteSelectionne = ui->m_vueTable->item( row, 1 )->text();
    QString Type = ui->m_vueTable->item(row,2)->text();

    //déclaration des paramètres pour les fonctions
    QStringList temp;
    temp << albumSelectionne << artisteSelectionne;

    //on vérifie si l'album est déjà entré dans la BDD
    BDDInterface interfaceBDD;
    //   QString bdd= interfaceBDD.verifAlbum(temp);
    QString bdd="non";
    //on récupère la fonction permettant de faire la liste des albums sur la requête
    QStringList resultat=tmp.RequeteAlbums(temp);


    if (resultat.size()!=0)
    {
        // on affiche "entre" si l'album existe en base, "non entre" sinon
        ui->m_estEntre->setText( bdd );

        //on choisit le premier album dans la liste et on en extrait les infos
        AlbumGestion* album = new AlbumGestion;
        album= tmp.RequeteInfosAlbum(resultat[3]);

        album->Artiste=artisteSelectionne.replace("'","$");
        album->Album=albumSelectionne.replace("'","$");
        album->Type=Type;

        // on affiche la pochette
        QPixmap* pixmap= new QPixmap();
        if( !album->pochette.isNull() )
        {
            pixmap->convertFromImage( album->pochette );
        }
        //si Discogs n'a pas trouvé de pochettes, on en met une par défaut.
        else
        {

            QString che="./Pochettes/def.jpg";

            QImage* image=new QImage( che );

            pixmap->convertFromImage( *image );
        }
        ui->m_pochette->setPixmap( pixmap->scaled( 200,200,Qt::KeepAspectRatio ) );

        //On affiche les titres
        int compteur=0;
        QString titresCumules;
        while (compteur<album->titres.size())
        {
            QString nom=QString::number((compteur/2)+1).rightJustified(2,'0')+" - "+album->titres[compteur]+"("+album->titres[compteur+1]+")";
            titresCumules = titresCumules + nom + "\n";
            compteur++;compteur++;
        }
        ui->m_titres->setText( titresCumules );

        interfaceBDD.AjouterAlbumPhys(*album);
    }
    else
    {
        ui->m_estEntre->setText( "pas de résultat trouvé" );
        ui->m_pochette->clear();
        ui->m_titres->clear();
    }
    */
}

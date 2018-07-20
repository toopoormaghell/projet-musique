#include "ongleterreurs.h"
#include "ui_ongleterreurs.h"
#include <QWidget>
#include <QObject>
#include <QListWidgetItem>
#include <QDebug>

OngletErreurs::OngletErreurs( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::OngletErreurs ),
    m_bddinterface ( new BDDErreurs ),
    m_categorie ( 0 ),
    m_erreurlue ( 0 )

{
    Q_UNUSED ( parent);

    ui->setupUi(this);
}

OngletErreurs::~OngletErreurs()
{
    delete ui;
}

void OngletErreurs::on_ErreursAlbums_clicked()
{
    m_categorie = 2 ;

    QList<int> liste = m_bddinterface->retrouverErreurs( m_categorie );

    trouverErreurs( liste );

}

void OngletErreurs::on_ErreursRelations_clicked()
{
    m_categorie =1;

    QList<int> liste = m_bddinterface->retrouverErreurs( m_categorie );

    trouverErreurs( liste );

}

void OngletErreurs::on_ErreursArtistes_clicked()
{
    m_categorie =3;

    QList<int> liste = m_bddinterface->retrouverErreurs( m_categorie );

    trouverErreurs( liste );

}

void OngletErreurs::on_ErreursTitres_clicked()
{
    m_categorie =4;

    QList<int> liste = m_bddinterface->retrouverErreurs( m_categorie );

    trouverErreurs( liste );

}

void OngletErreurs::on_ErreursPoch_clicked()
{
    m_categorie = 5 ;

    QList<int> liste = m_bddinterface->retrouverErreurs( m_categorie );

    trouverErreurs( liste );
}

void OngletErreurs::on_ErreursPhys_clicked()
{
    m_categorie = 6 ;

    QList<int> liste = m_bddinterface->retrouverErreurs( m_categorie );

    trouverErreurs( liste );
}

void OngletErreurs::on_ErreursMP3_clicked()
{
    m_categorie = 7;

    QList<int> liste = m_bddinterface->retrouverErreurs( m_categorie );

    trouverErreurs( liste );
}

void OngletErreurs::on_ListeErreurs_itemClicked( QListWidgetItem* item)
{
    ViderDonnees();
    m_erreurlue = item->data( Qt::UserRole ).toInt();
    lireErreur();
}
void OngletErreurs::trouverErreurs( QList<int> liste )
{
    ui->ListeErreurs->clear();

    QString cate = categorie();
    for ( int i = 0 ; i < liste.count() ; i++ )
    {
        QListWidgetItem* item = new QListWidgetItem;
        item->setData( Qt::UserRole, liste[i] );
        item->setText( cate +QString::number( liste[i] ) );

        ui->ListeErreurs->addItem( item );
    }

    if ( liste.count() > 0 )
    {
        ui->ListeErreurs->setCurrentRow( 0 );
        m_erreurlue = ui->ListeErreurs->currentItem()->data( Qt::UserRole ).toInt();
        lireErreur();
    }
    ui->label->setText( QString::number( liste.count() ) +" erreurs trouvées." );
}
QString OngletErreurs::categorie()
{
    switch ( m_categorie )
    {
    case 1 : return "Relation ";break;
    case 2 : return "Album ";break;
    case 3 : return "Artiste "; break;
    case 4 : return "Titre "; break;
    case 5 : return "Poch ";break;
    case 6 : return "Phys ";break;
    case 7 : return "MP3 ";break;
    default : return "Relation";
    }
}
void OngletErreurs::lireErreur( )
{
    if ( m_erreurlue != 0 )
    {
        QStringList temp = m_bddinterface->lectureErreur( m_categorie, m_erreurlue );

        switch ( m_categorie )
        {
        case 1 : lireErreurRelation( temp );break;
        case 2 : lireErreurAlbum ( temp );break;
        case 3 : lireErreurArtiste( temp );break;
        case 4 : lireErreurTitre( temp );break;
        case 5 : lireErreurPoch( temp );break;
        case 6 : lireErreurPhys( temp ); break;
        case 7: lireErreurMP3( temp);break;
        default : QString texte;
            for ( int i=0; i < temp.count(); i=i+2 )
            {
                texte += temp[i] + " : " + temp[ i+1 ]+ " \n";
            }
            ui->Interaction->setText( texte );
        }

    }
}
void OngletErreurs::lireErreurRelation(QStringList temp )
{
    ui->Rel_Id->setText( temp[0] );
    if ( ui->Alb_Id->text().isNull() )
        ui->Alb_Id->setText(  temp[1] );
    if ( ui->Art_Id->text().isNull() )
        ui->Art_Id->setText(  temp[2] );
    if ( ui->Titre_Id->text().isNull() )
        ui->Titre_Id->setText(  temp[3] );
    ui->Rel_Num->setText(  temp[4] );
    ui->Rel_Duree->setText( temp[5] );
    ui->Rel_MP3->setText(  temp[6] );
    ui->Rel_Phys->setText(  temp[7] );
    ui->Rel_Isole->setText(  temp[8] );
    if ( ui->Phys_Id->text().isNull()  )
        ui->Phys_Id->setText( temp[9] );
    if ( ui->MP3_Id->text().isNull() )
        ui->MP3_Id->setText( temp[10] );
}
void OngletErreurs::lireErreurArtiste(QStringList temp )
{
    ui->Art_Id->setText( temp [0] );
    ui->Art_Nom->setText( temp[1] );
    ui->Art_Formate->setText( temp[2] );
    if ( ui->Poch_Art_Id->text().isNull() )
        ui->Poch_Art_Id->setText( temp[3] );
    ui->Art_Isole->setText( temp[4] );

    lireErreurPochArt( m_bddinterface->lectureErreur( 5,  temp[3].toInt() ) );

}
void OngletErreurs::lireErreurAlbum(QStringList temp )
{
    ui->Alb_Id->setText( temp[0] );
    ui->Alb_Nom->setText( temp[1] );
    ui->Alb_Form->setText( temp[2] );
    if ( ui->Poch_Id->text().isNull() )
        ui->Poch_Id->setText( temp[3] );
    ui->Alb_Annee->setText( temp[4] );
    ui->Alb_Type->setText( temp[5] );
    if (ui->Art_Id->text().isNull() )
        ui->Art_Id->setText( temp[6] );
    ui->Alb_Isole->setText( temp[7] );
    if ( ui->Phys_Id->text().isNull() )
        ui->Phys_Id->setText( temp[8] );
}
void OngletErreurs::lireErreurTitre(QStringList temp )
{
    ui->Titre_Id->setText( temp [0] );
    ui->Titre_Nom->setText( temp[1] );
    ui->Titre_Formate->setText( temp[2] );
    ui->Titre_Isole->setText( temp[3] );
}
void OngletErreurs::lireErreurPoch(QStringList temp )
{
    ui->Poch_Id->setText( temp [0] );
    ui->Poch_Chemin->setText( temp[1] );
    ui->Poch_Isole->setText( temp[2] );

    QPixmap scaled( QPixmap::fromImage( m_bddinterface->AfficherImagePoch( temp[0].toInt() ) ) );
    scaled = scaled.scaled( 75, 75 );
    ui->Poch_Aff->setPixmap( scaled );

}
void OngletErreurs::lireErreurMP3(QStringList temp )
{
    ui->MP3_Id->setText( temp [0] );
    if(ui->Rel_Id->text().isNull() )
        ui->Rel_Id->setText( temp[1] );
    ui->MP3_Chemin->setText( temp[2] );
    ui->MP3_Support->setText( temp[3] );
    ui->MP3_Isole->setText( temp[4] );
}
void OngletErreurs::lireErreurPhys(QStringList temp )
{
    ui->Phys_Id->setText( temp [0] );
    if ( ui->Alb_Id->text().isNull() )
        ui->Alb_Id->setText( temp[1] );
    ui->Phys_Support->setText( temp[2] );
    ui->Phys_CB->setText( temp[3] );
    ui->Phys_Comment->setText( temp[4] );
    ui->Phys_Isole->setText( temp[5] );
}
void OngletErreurs::lireErreurPochArt( QStringList temp )
{
    ui->Poch_Art_Id->setText( temp[0] );
    ui->Poch_Art_Chemin->setText( temp[1] );
    ui->Poch_Art_Isole->setText( temp[2] );

    QPixmap scaled( QPixmap::fromImage( m_bddinterface->AfficherImagePoch( temp[0].toInt() ) ) );
    scaled = scaled.scaled( 75, 75 );
    ui->Poch_Art_Aff->setPixmap( scaled );

}
void OngletErreurs::on_Supprimer_clicked()
{
    m_bddinterface->supprimer( m_categorie, m_erreurlue );
    ui->Interaction->append( "suppression effectuée. ");
    trouverErreurs(  m_bddinterface->retrouverErreurs( m_categorie ) );
}

void OngletErreurs::on_TrouverRel_clicked()
{
    if ( m_categorie != 1 && !ui->Rel_Id->text().isNull())
    {
        lireErreurRelation( m_bddinterface->lectureErreur( 1, ui->Rel_Id->text().toInt()));
    }
    if ( m_categorie != 2 && !ui->Alb_Id->text().isNull() )
    {
        lireErreurAlbum( m_bddinterface->lectureErreur( 2, ui->Alb_Id->text().toInt()));
    }
    if ( m_categorie != 3 && !ui->Art_Id->text().isNull() )
    {
        lireErreurArtiste( m_bddinterface->lectureErreur( 3,  ui->Art_Id->text().toInt() ) );
    }
    if ( m_categorie != 4 && !ui->Titre_Id->text().isNull()  )
    {
        lireErreurTitre( m_bddinterface->lectureErreur( 4 , ui->Titre_Id->text().toInt() ) );
    }
    if ( m_categorie != 5  && !ui->Poch_Id->text().isNull() )
    {
        lireErreurPoch( m_bddinterface->lectureErreur( 5, ui->Poch_Id->text().toInt()));
    }
    if ( m_categorie != 6 && !ui->Phys_Id->text().isNull() )
    {
        lireErreurPhys( m_bddinterface->lectureErreur( 6 , ui->Phys_Id->text().toInt() ) );
    }
    if ( m_categorie != 7 && !ui->MP3_Id->text().isNull() )
    {
        lireErreurMP3( m_bddinterface->lectureErreur( 7, ui->MP3_Id->text().toInt()));
    }

}
void OngletErreurs::ViderDonnees(  )
{
    ui->Poch_Aff->clear();
    ui->Poch_Chemin->clear();
    ui->Poch_Id->clear();
    ui->Poch_Isole->clear();

    ui->Poch_Art_Aff->clear();
    ui->Poch_Art_Chemin->clear();
    ui->Poch_Art_Id->clear();
    ui->Poch_Art_Isole->clear();

    ui->Titre_Formate->clear();
    ui->Titre_Id->clear();
    ui->Titre_Isole->clear();
    ui->Titre_Nom->clear();

    ui->Alb_Annee->clear();
    ui->Alb_Form->clear();
    ui->Alb_Id->clear();
    ui->Alb_Nom->clear();
    ui->Alb_Isole->clear();
    ui->Alb_Type->clear();

    ui->Art_Formate->clear();
    ui->Art_Id->clear();
    ui->Art_Isole->clear();
    ui->Art_Nom->clear();

    ui->Rel_Duree->clear();
    ui->Rel_Id->clear();
    ui->Rel_Isole->clear();
    ui->Rel_MP3->clear();
    ui->Rel_Num->clear();
    ui->Rel_Phys->clear();

    ui->MP3_Chemin->clear();
    ui->MP3_Id->clear();
    ui->MP3_Isole->clear();
    ui->MP3_Support->clear();

    ui->Phys_CB->clear();
    ui->Phys_Comment->clear();
    ui->Phys_Id->clear();
    ui->Phys_Isole->clear();
    ui->Phys_Support->clear();
}



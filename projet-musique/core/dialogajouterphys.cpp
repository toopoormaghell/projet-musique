#include "DialogAjouterPhys.h"
#include "ui_dialogajouterphys.h"
#include "qdebug.h"
#include "bddgestionphys.h"
#include "util.h"
#include <QFileDialog>
#include "sousdialogajouttitre.h"
#include "bddalbum.h"
#include "QAWSWrapperNotifier.h"
#include <QAbstractTableModel>
#include <QComboBox>
#include <QStyledItemDelegate>
class QTableModel;

class QComboBoxDelegate : public QStyledItemDelegate
{
public:
    QComboBoxDelegate( QObject* parent = 0 ):
        QStyledItemDelegate( parent )
    {
    }

    QWidget* createEditor( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index ) const
    {
        QComboBox* editor = NULL;
        if ( index.column() == 2 )
        {
            editor = new QComboBox( parent );
        }
        return editor;
    }

    void setEditorData( QWidget* editor, const QModelIndex& index ) const;

    void setModelData( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
    {

    }

    void updateEditorGeometry( QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
    {
        editor->setGeometry( option.rect );
    }
};

class LineModel
{
public:
    LineModel():
        m_track()
      , m_song()
      , m_artist()
    {
    }

    LineModel( const QString& track, const QString& song, const QString& artist ):
        m_track( track )
      , m_song( song )
      , m_artist( artist )
    {
    }

    LineModel( const LineModel& other ):
        m_track( other.m_track )
      , m_song( other.m_song )
      , m_artist( other.m_artist )
    {
    }

    LineModel& operator=( const LineModel& rhs )
    {
        if ( this != &rhs )
        {
            m_track = rhs.m_track;
            m_song = rhs.m_song;
            m_artist = rhs.m_artist;
        }
        return *this;
    }

    ~LineModel()
    {
    }

    void setTrack( const QString& track )
    {
        m_track = track;
    }

    const QString& track() const
    {
        return m_track;
    }

    void setSong( const QString& song )
    {
        m_song = song;
    }

    const QString& song() const
    {
        return m_song;
    }

    void setArtist( const QString& artist )
    {
        m_artist = artist;
    }

    const QString& artist() const
    {
        return m_artist;
    }

    static int width()
    {
        return 3;
    }

private:
    QString m_track, m_song, m_artist;
};

class QTableModel : public QAbstractTableModel
{
public:
    explicit QTableModel( QObject* parent = 0 ):
        QAbstractTableModel( parent )
    {
    }

    virtual Qt::ItemFlags flags( const QModelIndex& index ) const
    {
        Q_UNUSED( index )
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }

    virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const
    {
        QVariant valueToReturn;
        if ( role == Qt::DisplayRole )
        {
            if ( ( index.column() == 0 ) && ( index.row() < m_lineList.size() ) )
                valueToReturn = QVariant( m_lineList[index.row()].track() );
            else
                if ( ( index.column() == 1 ) && ( index.row() < m_lineList.size() ) )
                    valueToReturn = QVariant( m_lineList[index.row()].song() );
                else
                    if ( ( index.column() == 2 ) && ( index.row() < m_lineList.size() ) )
                        valueToReturn = QVariant( m_lineList[index.row()].artist() );
        }
        return valueToReturn;
    }

    virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const
    {
        QVariant valueToReturn;
        if ( ( role == Qt::DisplayRole ) && ( orientation == Qt::Horizontal ) )
        {
            if ( section == 0 )
                valueToReturn = QVariant( tr( "N°" ) );
            else
                if ( section == 1 )
                    valueToReturn = QVariant( tr( "Titre" ) );
                else
                    if ( section == 2 )
                        valueToReturn = QVariant( tr( "Artiste" ) );
        }
        return valueToReturn;
    }

    virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const
    {
        Q_UNUSED( parent )
        return m_lineList.size();
    }

    virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const
    {
        Q_UNUSED( parent )
        return LineModel::width();
    }

    virtual bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole )
    {
        bool hasDataChanged = true;
        if ( role == Qt::EditRole )
        {
            if ( ( index.column() == 0 ) && ( index.row() < m_lineList.size() ) )
                m_lineList[index.row()].setTrack( value.toString() );
            else
                if ( ( index.column() == 1 ) && ( index.row() < m_lineList.size() ) )
                    m_lineList[index.row()].setSong( value.toString() );
                else
                    if ( ( index.column() == 2 ) && ( index.row() < m_lineList.size() ) )
                        m_lineList[index.row()].setArtist( value.toString() );
                    else
                        hasDataChanged = false;
        }
        else
            hasDataChanged = false;

        if ( hasDataChanged )
            Q_EMIT dataChanged( index, index );

        return hasDataChanged;
    }

    bool insertRows( int row, int count, const QModelIndex& parent = QModelIndex() )
    {
        beginInsertRows( parent, row, row + count - 1 );

        for ( int i = row; i <= row + count - 1; ++i )
            m_lineList.insert( i, LineModel() );

        endInsertRows();

        return true;
    }

    bool removeRows( int row, int count, const QModelIndex& parent = QModelIndex() )
    {
        beginRemoveRows( parent, row, row + count - 1 );

        for ( int i = 0; i < count; ++i )
            m_lineList.removeAt( row );

        endRemoveRows();

        return true;
    }

    void clearLines()
    {
        if ( rowCount() > 0 )
            removeRows( 0, rowCount() );
    }

    void appendLine( const LineModel& line )
    {
        insertRows( rowCount() + 1, 1 );

        setData( index( rowCount() - 1, 0 ), line.track() );
        setData( index( rowCount() - 1, 1 ), line.song() );
        setData( index( rowCount() - 1, 2 ), line.artist() );
    }

    void setArtistList( const QStringList& list )
    {
        m_artistList = list;
    }

    const QStringList& getArtistList() const
    {
        return m_artistList;
    }

private:
    QList<LineModel> m_lineList;
    QStringList m_artistList;
};

void QComboBoxDelegate::setEditorData( QWidget* editor, const QModelIndex& index ) const
{
    QComboBox* comboBox = static_cast<QComboBox*>( editor );
    QTableModel const* const tableModel = static_cast<QTableModel const* const>( index.model() );
    for ( int i = 0; i < tableModel->rowCount(); ++i )
        comboBox->addItem( tableModel->data( tableModel->index( i, 2 ) ).toString() );
}



DialogAjouterPhys::DialogAjouterPhys( QWidget* parent ) :
    QDialog( parent )
  , ui( new Ui::DialogAjouterPhys )
  , m_tableModel( new QTableModel )
{
    ui->setupUi( this );

    ui->tableView->setModel( m_tableModel );
    ui->tableView->setItemDelegate( new QComboBoxDelegate );

    m_Type = 1;
    AffichageListeArtistes( -2 );

    AjoutConnex();
}



DialogAjouterPhys::DialogAjouterPhys( int id_album, QWidget* parent ) :
    QDialog( parent )
  , ui( new Ui::DialogAjouterPhys )
  , m_tableModel( new QTableModel )
{
    m_Type = 1;

    ui->setupUi( this );
    ui->tableView->setModel( m_tableModel );
    ui->tableView->setItemDelegate( new QComboBoxDelegate );
    AffichageListeArtistes( -2 );

    m_album = BDDAlbum::RecupAlbumEntite( id_album );
    AfficherAlbum();
    AjoutConnex();
}



void DialogAjouterPhys::AjoutConnex()
{
    connect( ui->buttonGroup, SIGNAL( buttonClicked( int ) ), this, SLOT( AffichageListeArtistes( int ) ) ) ;
    QObject::connect( &m_research.getNotifier(), SIGNAL( stepAchieved( QString ) ), this, SLOT( AfficherInteraction( QString ) ) );
}



DialogAjouterPhys::~DialogAjouterPhys()
{
    delete ui;
}



void DialogAjouterPhys::recupererEAN()
{
    m_EAN = ui->EAN->text();
}



void DialogAjouterPhys::on_ChercherEAN_clicked()
{
    recupererEAN();

    //On vérifie qu'il y a bien 13 caractères
    while ( m_EAN.count() != 13 )
    {
        m_EAN = "0" + m_EAN;
    }
    m_album = m_research.getAlbumFromEAN( m_EAN );

    const QStringList& artistList = m_research.getArtistsList();
    m_tableModel->setArtistList( artistList );

    m_tableModel->clearLines();
    int i = 0;
    Q_FOREACH( TitresPhys titre, m_album.titres )
    {
        m_tableModel->appendLine( LineModel( QString::number( titre.Num_Piste ), titre.Titre, titre.Artiste ) );
        i++;
    }
    AfficherAlbum();
}



void DialogAjouterPhys::AfficherAlbum()
{
    ui->Annee->setText( QString::number( m_album.Annee ) );
    ui->Nom_Album->setText( m_album.Album );
    ui->Nom_Artiste->setText( m_album.Artiste );

    for ( int cpt = 0; cpt < m_album.titres.count(); cpt++ )
    {
        TitresPhys titre = m_album.titres[cpt];
        //ui->Piste->addItem( QString::number( titre.Num_Piste ) );
        //ui->Titres->addItem( titre.Titre + "(" + titre.Duree + ")" );
        //ui->Artiste_Titres->addItem( titre.Artiste );
    }
    AfficherPoch();
}



void DialogAjouterPhys::AfficherPoch()
{
    QPixmap* pixmap = new QPixmap();
    pixmap->convertFromImage( m_album.Poch );

    QPixmap imageScaled = pixmap->scaled( 150, 150, Qt::IgnoreAspectRatio, Qt::FastTransformation );
    ui->Pochette->setPixmap( imageScaled );
}



void DialogAjouterPhys::on_Enregistrer_clicked()
{
    RecupererAlbum();
    BDDGestionPhys m_bddinterface;
    m_bddinterface.ajouterAlbum( m_album.Poch, m_album.Album, m_album.Artiste, m_EAN, m_album.Annee, m_album.titres, m_Type );
    ui->Interaction->append( "Album enregistré." );
    emit ajout();
    ViderBoiteDialogue();
}



void DialogAjouterPhys::AffichageListeArtistes( int id )
{
    switch ( id )
    {
        case ( -2 ):
            m_Type = 1;
            //ui->Artiste_Titres->setHidden( true );
            //ui->ArtisteLabel->setHidden( true );
            break;
        case ( -3 ):
            m_Type = 2;
            //ui->Artiste_Titres->setHidden( false );
            //ui->ArtisteLabel->setHidden( false );
            break;
        case ( -4 ):
            m_Type = 3;
            //ui->Artiste_Titres->setHidden( true );
            //ui->ArtisteLabel->setHidden( true );
            break;
    }
}



void DialogAjouterPhys::ViderBoiteDialogue()
{
    //ui->Artiste_Titres->clear();
    ui->EAN->clear();
    ui->Nom_Album->clear();
    ui->Nom_Artiste->clear();
    //ui->Piste->clear();
    ui->Pochette->clear();
    //ui->Titres->clear();
    ui->Annee->clear();

    m_album.titres.clear();
}



void DialogAjouterPhys::on_ViderAlbum_clicked()
{
    ViderBoiteDialogue();
}



void DialogAjouterPhys::RecupererAlbum()
{
    m_album.titres.clear();
    m_album.Album = ui->Nom_Album->text().replace( "'", "$" );
    m_album.Artiste = ui->Nom_Artiste->text().replace( "'", "$" );
    m_album.Annee = ui->Annee->text().toInt();
    m_album.Type = m_Type;

    //On récupère la pochette
    const QPixmap* pixmap = ui->Pochette->pixmap();
    QImage image = pixmap->toImage();
    m_album.Poch = image;

    //On récupère les titres
    for ( int i = 0; i < 0/*ui->Titres->count()*/; i++ )
    {
        TitresPhys titre;
        //QListWidgetItem* item = ui->Titres->item( i );
        //QStringList parsing = item->text().split( "(" );
        //titre.Titre = parsing[0];

        //QStringList parsing2 = parsing[1].split( ")" );
        //titre.Duree = parsing2[0];
        //titre.Num_Piste = i + 1;

        if ( m_Type == 2 )
        {
            //item = ui->Artiste_Titres->item( i );
            //titre.Artiste = item->text();
        }

        //m_album.titres << titre;
    }

}



void DialogAjouterPhys::listeNumeros()
{
    //ui->Piste->clear();
    for ( int i = 1; i < 0/*ui->Titres->count() + 1*/; i++ )
    {
        //ui->Piste->addItem( new QListWidgetItem( QString::number( i ).rightJustified( 2, '0' ) + " - " ) );
    }
}



void DialogAjouterPhys::on_Supprimer_Titre_clicked()
{
//    QList<QListWidgetItem*> fileSelected = ui->Titres->selectedItems();
//    if ( fileSelected.size() )
//    {
//        for ( int i = ui->Titres->count() - 1 ; i >= 0 ; i-- )
//        {
//            if ( ui->Titres->item( i )->isSelected() )
//            {
//                QListWidgetItem* item = ui->Titres->takeItem( i );
//                ui->Titres->removeItemWidget( item );
//            }
//        }
//    }
//    listeNumeros();
}



void DialogAjouterPhys::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName( this,
                       "Ouvrir l'image contenant la pochette",
                       "C:/Users/Nico/Desktop",
                       "Images (*.png *.xpm *.jpg *.bmp)" );
    QPixmap* pixmap = new QPixmap();
    QImage* image = new QImage( fileName );
    pixmap->convertFromImage( *image );
    QPixmap pixmapscaled = pixmap->scaled( 150, 150, Qt::IgnoreAspectRatio, Qt::FastTransformation );

    ui->Pochette->setPixmap( pixmapscaled );
}



void DialogAjouterPhys::on_Ajouter_Titre_clicked()
{
    SousDialogAjoutTitre toto( m_Type, this );
    connect( &toto, SIGNAL( enregistr( QString, QString, QString ) ), this, SLOT( AjouterTitreManuel( QString, QString, QString ) ) );
    int retVal = toto.exec();
    if ( ( retVal == QDialog::Accepted ) && !toto.m_Titre.isEmpty() )
    {
        AjouterTitreManuel( toto.m_Titre, toto.m_Duree, toto.m_Artiste );
    }

}



void DialogAjouterPhys::AjouterTitreManuel( const QString& titre, const QString& duree, const QString& artiste )
{
    //ui->Titres->addItem( titre + "(" + duree + ")" );
    //ui->Artiste_Titres->addItem( artiste );
    listeNumeros();

}



void DialogAjouterPhys::AfficherInteraction(QString message)
{
    ui->Interaction->append( message );
}

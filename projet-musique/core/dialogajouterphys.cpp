#include "DialogAjouterPhys.h"
#include "ui_dialogajouterphys.h"
#include "qdebug.h"
#include "bddgestionphys.h"
#include "util.h"
#include <QFileDialog>
#include "DialogAjoutTitre.h"
#include "bddalbum.h"
#include "QAWSWrapperNotifier.h"
#include "BDDAfficherPhys.h"
#include <QAbstractTableModel>
#include <QLineEdit>
#include <QStyledItemDelegate>
#include <QCompleter>

class QTableModel;

class QCompletedLineEditDelegate : public QStyledItemDelegate
{
public:
    QCompletedLineEditDelegate( QObject* parent = 0 ):
        QStyledItemDelegate( parent )
    {
    }

    QWidget* createEditor( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index ) const
    {
        QLineEdit* editor = NULL;
        if ((index.column() == 1) || (index.column() == 2))
        {
            editor = new QLineEdit( parent );
        }
        return editor;
    }

    void setEditorData( QWidget* editor, const QModelIndex& index ) const;

    void setModelData( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
    {
        if ((index.column() == 1) || (index.column() == 2))
        {
            QLineEdit* lineEdit = static_cast<QLineEdit*>( editor );
            const QString artist = lineEdit->text();
            model->setData( index, artist );
        }
    }

    void updateEditorGeometry( QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
    {
        if ((index.column() == 1) || (index.column() == 2 ))
        {
            editor->setGeometry( option.rect );
        }
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
    enum ModelType
    {
        MONO_ARTIST,
        MULTI_ARTISTS
    };

    explicit QTableModel( QObject* parent = 0 ):
        QAbstractTableModel( parent )
      , m_findArtists(false)
      , m_swapColumns(false)
      , m_lineList()
      , m_modelType( MONO_ARTIST )
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
                {
                    if (findArtists())
                    {
                        QStringList toto = m_lineList[index.row()].song().split( " - ");
                        if ( swapColumns())
                            valueToReturn = QVariant( toto.last() );
                        else
                            valueToReturn = QVariant( toto.first() );
                    }
                    else
                    {
                        valueToReturn = QVariant( m_lineList[index.row()].song() );
                    }
                }
                else
                    if ( ( index.column() == 2 ) && ( index.row() < m_lineList.size() ) )
                    {
                        if (findArtists())
                        {
                            QStringList toto = m_lineList[index.row()].song().split( " - ");
                            if ( swapColumns())
                                valueToReturn = QVariant( toto.first() );
                            else
                                valueToReturn = QVariant( toto.last() );
                        }
                        else
                        {
                            valueToReturn = QVariant( m_lineList[index.row()].artist() );
                        }
                    }
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
                {
                    if (findArtists())
                    {
                        QStringList toto = m_lineList[index.row()].song().split( " - ");
                        if ( swapColumns())
                            m_lineList[index.row()].setSong( toto.last() + " - " + value.toString() );
                        else
                            m_lineList[index.row()].setSong( value.toString() + " - " + toto.last() );
                    }
                    else
                    {
                        m_lineList[index.row()].setSong( value.toString() );
                    }
                }
                else
                    if ( ( index.column() == 2 ) && ( index.row() < m_lineList.size() ) )
                    {
                        if (findArtists())
                        {
                            QStringList toto = m_lineList[index.row()].song().split( " - ");
                            if ( swapColumns())
                                m_lineList[index.row()].setSong( value.toString() + " - " + toto.first() );
                            else
                                m_lineList[index.row()].setSong( toto.first() + " - " + value.toString() );
                        }
                        else
                        {
                            m_lineList[index.row()].setArtist( value.toString() );
                        }
                    }
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

    void setFindArtists( const bool findArtist)
    {
        if ( m_findArtists != findArtist )
        {
            m_findArtists = findArtist;
            Q_EMIT dataChanged( index(0,1), index(rowCount()-1, columnCount()-1) );
        }
    }

    bool findArtists() const
    {
        return m_findArtists;
    }

    void setSwapColumns( const bool swapColumns)
    {
        if ( m_swapColumns != swapColumns)
        {
            m_swapColumns = swapColumns;
            Q_EMIT dataChanged( index(0,1), index(rowCount()-1, columnCount()-1) );
        }
    }

    bool swapColumns() const
    {
        return m_swapColumns;
    }

    ModelType modelType() const
    {
        return m_modelType;
    }

    void setModelType( const ModelType modelType )
    {
        m_modelType = modelType;
        Q_EMIT dataChanged( index(0, 0), index(0,2) );
    }

private:
    QList<LineModel> m_lineList;
    bool m_findArtists;
    bool m_swapColumns;
    ModelType m_modelType;
};

void QCompletedLineEditDelegate::setEditorData( QWidget* editor, const QModelIndex& index ) const
{
    if ( index.column() == 2)
    {
        QLineEdit* lineEdit = static_cast<QLineEdit*>( editor );
        QTableModel const* const tableModel = static_cast<QTableModel const* const>( index.model() );
        QStringList completion (BDDAfficherPhys().ListeArtistesPossibles() );
        QCompleter* completer = new QCompleter( completion );
        completer->setCaseSensitivity( Qt::CaseInsensitive );
        lineEdit->setCompleter( completer );
    }
}



DialogAjouterPhys::DialogAjouterPhys( QWidget* parent ) :
    QDialog( parent )
  , ui( new Ui::DialogAjouterPhys )
  , m_tableModel( new QTableModel )
{
    ui->setupUi( this );

    ui->tableView->setModel( m_tableModel );
    ui->tableView->setItemDelegate( new QCompletedLineEditDelegate );

    m_Type = 1;
    AffichageListeArtistes( -3 );

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
    ui->tableView->setItemDelegate( new QCompletedLineEditDelegate );
    AffichageListeArtistes( -2 );

    m_album = BDDAlbum::RecupAlbumEntite( id_album );
    AfficherAlbum();
    AjoutConnex();
}



void DialogAjouterPhys::AjoutConnex()
{
    connect( ui->buttonGroup, SIGNAL( buttonClicked( int ) ), this, SLOT( AffichageListeArtistes( int ) ) ) ;
    QObject::connect( &m_research.getNotifier(), SIGNAL( stepAchieved( QString ) ), this, SLOT( AfficherInteraction( QString ) ) );
    QObject::connect( ui->findArtists, SIGNAL( stateChanged(int) ), this, SLOT( on_findArtists_stateChanged(int) ) );
    QObject::connect( ui->swapColumns, SIGNAL( stateChanged(int) ), this, SLOT( on_swapColumns_stateChanged(int) ) );
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

    ui->findArtists->setChecked(false);

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
    m_bddinterface.ajouterAlbum( m_album.Poch, m_album.Album, m_album.Artiste, m_EAN, m_album.Annee, m_album.titres, m_Type, ui->Commentaires->text() );
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
        ui->tableView->setColumnHidden( 2, true );
        //            m_tableModel->setModelType( QTableModel::MONO_ARTIST );
        break;
    case ( -3 ):
        m_Type = 2;
        ui->tableView->setColumnHidden( 2, false );
        //            m_tableModel->setModelType( QTableModel::MULTI_ARTISTS );
        break;
    case ( -4 ):
        m_Type = 3;
        ui->tableView->setColumnHidden( 2, true );
        //            m_tableModel->setModelType( QTableModel::MONO_ARTIST );
        break;
    }
}



void DialogAjouterPhys::ViderBoiteDialogue()
{

    ui->EAN->clear();
    ui->Nom_Album->clear();
    ui->Nom_Artiste->clear();
    ui->Pochette->clear();
    ui->Annee->clear();

    m_album.titres.clear();
    m_tableModel->clearLines();
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
    for ( int i = 0; i < m_tableModel->rowCount(); i++ )
    {
        TitresPhys titre;
        titre.Titre = m_tableModel->data( m_tableModel->index(i, 1 ) ).toString();

        titre.Duree = "0:00";

        titre.Num_Piste = m_tableModel->data( m_tableModel->index(i, 0 ) ).toInt();

        if ( m_Type == 2 )
        {
            titre.Artiste = m_tableModel->data( m_tableModel->index(i, 2 ) ).toString();
        }

        m_album.titres << titre;
    }

}



void DialogAjouterPhys::on_Supprimer_Titre_clicked()
{
    // QModelIndexList selectedItemsList = ui->tableView->selectedIndexes()

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
    SousDialogAjoutTitre toto( m_Type, m_tableModel->rowCount(), this );
   // connect( &toto, SIGNAL( enregistr( QString, QString, QString ) ), this, SLOT( AjouterTitreManuel( QString, QString, QString ) ) );
    int retVal = toto.exec();
    if ( ( retVal == QDialog::Accepted ) && !toto.m_Titre.isEmpty() )
    {
        m_tableModel->appendLine( LineModel( toto.m_Piste , toto.m_Titre, toto.m_Artiste ) );
    }

}


void DialogAjouterPhys::AfficherInteraction(QString message)
{
    ui->Interaction->append( message );
}

void DialogAjouterPhys::on_findArtists_stateChanged(int newValue)
{
    m_tableModel->setFindArtists(newValue==Qt::Checked);
    ui->swapColumns->setEnabled(newValue==Qt::Checked );
}

void DialogAjouterPhys::on_swapColumns_stateChanged(int newValue)
{
    m_tableModel->setSwapColumns(newValue == Qt::Checked);
}

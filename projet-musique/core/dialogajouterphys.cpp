#include "DialogAjouterPhys.h"
#include "ui_dialogajouterphys.h"
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
#include "util.h"

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
        Q_UNUSED (option)
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
    bool m_findArtists;
    bool m_swapColumns;
    QList<LineModel> m_lineList;

    ModelType m_modelType;
};

void QCompletedLineEditDelegate::setEditorData( QWidget* editor, const QModelIndex& index ) const
{
    if (index.column() == 2)
    {
        QVariant value = index.model()->data(index);
        QLineEdit* lineEdit = static_cast<QLineEdit*>( editor );
        lineEdit->setText(value.toString());
        lineEdit->selectAll();
        QStringList completion (BDDAfficherPhys().ListeArtistesPossibles() );
        QCompleter* completer = new QCompleter( completion );
        completer->setCaseSensitivity( Qt::CaseInsensitive );
        lineEdit->setCompleter( completer );

    }
    if (index.column() == 1)
    {
        QVariant value = index.model()->data(index);
        QLineEdit* lineEdit = static_cast<QLineEdit*>( editor );
        lineEdit->setText(value.toString());
        lineEdit->selectAll();
        QStringList completion (BDDAfficherPhys().ListeTitresPossibles() );
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
    ui->tableView->setItemDelegate( new QCompletedLineEditDelegate(ui->tableView) );

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
    ui->tableView->setItemDelegate( new QCompletedLineEditDelegate );
    AffichageListeArtistes( -2 );

    m_album = Meta_Album::RecupererBDD( id_album );
    AfficherAlbum();
    AjoutConnex();
}



void DialogAjouterPhys::AjoutConnex()
{
    QObject::connect( ui->buttonGroup, SIGNAL( buttonClicked( int ) ), this, SLOT( AffichageListeArtistes( int ) ) ) ;
    QObject::connect( ui->buttonGroup_2, SIGNAL( buttonClicked( int ) ), this, SLOT ( RecupererType ( int ) ) );
    QObject::connect( &m_research.getNotifier(), SIGNAL( stepAchieved( QString ) ), this, SLOT( AfficherInteraction( QString ) ) );
    QObject::connect( ui->findArtists, SIGNAL( stateChanged(int) ), this, SLOT( on_findArtists_stateChanged(int) ) );
    QObject::connect( ui->swapColumns, SIGNAL( stateChanged(int) ), this, SLOT( on_swapColumns_stateChanged(int) ) );
    QObject::connect( ui->buttonUp, SIGNAL(clicked(bool)), this, SLOT(moveUp_clicked()));
    QObject::connect( ui->buttonDown, SIGNAL(clicked(bool)), this, SLOT(moveDown_clicked()));


}



DialogAjouterPhys::~DialogAjouterPhys()
{
    delete ui;
    delete m_tableModel;
}



void DialogAjouterPhys::recupererEAN()
{
    m_EAN = ui->EAN->text();
}



void DialogAjouterPhys::on_ChercherEAN_clicked()
{
    recupererEAN();
    if ( m_EAN.count() < 14 )
    {
        //On vérifie qu'il y a bien 13 caractères
        while ( m_EAN.count() != 13 )
        {
            m_EAN = "0" + m_EAN;
        }
        m_album = m_research.getAlbumFromEAN( m_EAN );

        ui->findArtists->setChecked(false);

        m_tableModel->clearLines();
        int i = 0;
        Q_FOREACH( auto titre, m_album->gettitres() )
        {
            QString tit = titre->getnom_titre();
            MajusuculeAChaqueMot ( tit );

            m_tableModel->appendLine( LineModel( QString::number( titre->getnum_piste() ), tit, titre->getnom_artiste() ) );
            i++;
        }
        AfficherAlbum();
    } else {
        AfficherInteraction( "L'EAN possède trop de chiffres." );
    }

}
void DialogAjouterPhys::AfficherAlbum()
{
    ui->Annee->setText( QString::number( m_album->getannee() ) );
    ui->Nom_Album->setText( m_album->getnom_album() );
    if ( m_Type ==2 )
    {
        ui->Nom_Artiste->setText("Artistes Divers");
    } else
    {
        ui->Nom_Artiste->setText( m_album->getnom_artiste() );
    }
    AfficherPoch();
}



void DialogAjouterPhys::AfficherPoch()
{
    QPixmap* pixmap = new QPixmap();
    pixmap->convertFromImage( m_album->getPoch() );

    QPixmap imageScaled = pixmap->scaled( 150, 150, Qt::IgnoreAspectRatio, Qt::FastTransformation );
    ui->Pochette->setPixmap( imageScaled );
}




void DialogAjouterPhys::on_Enregistrer_clicked()
{
    ui->Interaction->append("Album en cours d'enregistrement.");
    RecupererAlbum();

    m_album->UpdateBDD();

    AfficherInteraction( "Album enregistré." );
    emit ajout();
    ViderBoiteDialogue();
}


void DialogAjouterPhys::AffichageListeArtistes( int id )
{
    m_Support = (id*-1)-1;
    switch ( m_Support )
    {
    case ( 1 ):

        ui->tableView->setColumnHidden( 2, true );
        break;
    case ( 2 ):

        ui->tableView->setColumnHidden( 2, false );

        break;
    case ( 3 ):

        ui->tableView->setColumnHidden( 2, true );

        break;
    }

}
void DialogAjouterPhys::RecupererType( int id )
{
    m_Type = (id*-1)-1;
    if ( m_Type == 3 )
    {
        m_Type = 11;
    }

}


void DialogAjouterPhys::ViderBoiteDialogue()
{
    ui->EAN->clear();
    ui->Nom_Album->clear();
    ui->Nom_Artiste->clear();
    ui->Pochette->clear();
    ui->Annee->clear();
    ui->Commentaires->clear();


    m_tableModel->clearLines();
}




void DialogAjouterPhys::on_ViderAlbum_clicked()
{
    ViderBoiteDialogue();
}



void DialogAjouterPhys::RecupererAlbum()
{
    //   m_album.titres.clear();
    m_album->setnom_artiste(ui->Nom_Artiste->text().replace( "'", "$" ));
    m_album->setnom_album(ui->Nom_Album->text().replace( "'", "$" ));
    m_album->setannee(ui->Annee->text().toInt());
    m_album->setid_type(m_Type);
    m_album->setsupport_p(m_Support);

    //On récupère la pochette
    const QPixmap* pixmap = ui->Pochette->pixmap();
    QImage image = pixmap->toImage();
    m_album->setPoch(image);

    //On récupère les titres
    struct TitreTemp
    {
        QString nomTitre;
        unsigned int numPiste;
        QString duree;
        QString nomArtiste;
    };
    QList<TitreTemp> titresTemp;
    for ( int i = 0; i < m_tableModel->rowCount(); i++ )
    {
        TitreTemp titre;
        titre.nomTitre = m_tableModel->data( m_tableModel->index(i, 1 ) ).toString();

        titre.duree = "0:00";

        titre.numPiste = m_tableModel->data( m_tableModel->index(i, 0 ) ).toInt();

        if ( m_Type == 2 )
        {
            titre.nomArtiste = m_tableModel->data( m_tableModel->index(i, 2 ) ).toString();
        }
        titresTemp.append(titre);
    }
    QList<Meta_Titre*> titres;
    for ( auto it : titresTemp )
    {
        Meta_Titre* titre = Meta_Titre::CreerMeta_Titre( m_album->getnom_album() , it.nomArtiste, it.nomTitre, m_album->getannee(), it.duree, it.numPiste, m_album->getPoch(), m_album->getid_type(), m_album->getid_support_p(), -1, "Aucun", "Aucun", m_EAN);
        titres.append(titre);
    }
    m_album->settitres(titres);
}




void DialogAjouterPhys::on_Supprimer_Titre_clicked()
{

    QItemSelectionModel* selection = ui->tableView->selectionModel();

    if ( selection->hasSelection() )
    {
        QModelIndexList listeLignes = selection->selectedRows();
        qSort( listeLignes.begin(), listeLignes.end() , qGreater<QModelIndex>() );
        Q_FOREACH ( QModelIndex ligne,listeLignes )
        {
            m_tableModel->removeRow( ligne.row() );
        }

        for(int i=0; i<m_tableModel->rowCount(); ++i)
            m_tableModel->setData(m_tableModel->index(i,0), QString::number(i+1));
    }
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
    DialogAjoutTitre toto( m_Type, m_tableModel->rowCount(), this );

    connect( &toto, SIGNAL( enregistr( QString, QString, QString ) ), this, SLOT( AjouterTitreManuel( QString, QString, QString ) ) );

    toto.exec();

}



void DialogAjouterPhys::AjouterTitreManuel( QString Piste, QString Titre, QString Artiste )
{
    if ( !Titre.isEmpty() )
    {
        m_tableModel->appendLine( LineModel ( Piste,Titre, Artiste ) );
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

void DialogAjouterPhys::moveUp_clicked()
{
    QItemSelectionModel* selection = ui->tableView->selectionModel();

    if (selection->hasSelection())
    {
        QModelIndexList listeLignes = selection->selectedRows();
        qSort( listeLignes.begin(), listeLignes.end() , qGreater<QModelIndex>() );
        Q_FOREACH( QModelIndex ligne, listeLignes )
        {
            if (ligne.row() > 0)
            {
                m_tableModel->insertRow( ligne.row()-1 );
                m_tableModel->setData(m_tableModel->index(ligne.row()-1, 0),
                                      m_tableModel->data(m_tableModel->index(ligne.row()+1,0)));
                m_tableModel->setData(m_tableModel->index(ligne.row()-1, 1),
                                      m_tableModel->data(m_tableModel->index(ligne.row()+1,1)));
                m_tableModel->setData(m_tableModel->index(ligne.row()-1, 2),
                                      m_tableModel->data(m_tableModel->index(ligne.row()+1,2)));
                m_tableModel->removeRow(ligne.row()+1);

                ui->tableView->selectRow( ligne.row()-1 );
            }

        }
        for(int i=0; i<m_tableModel->rowCount(); ++i)
            m_tableModel->setData(m_tableModel->index(i,0), QString::number(i+1));


    }

    // ui->tableView->setSelectionModel( selection );
}

void DialogAjouterPhys::moveDown_clicked()
{
    QItemSelectionModel* selection = ui->tableView->selectionModel();

    if ( selection->hasSelection() )
    {
        QModelIndexList listeLignes = selection->selectedRows();
        qSort( listeLignes.begin(), listeLignes.end() , qGreater<QModelIndex>() );
        Q_FOREACH(QModelIndex ligne, listeLignes)
        {
            if (ligne.row() < m_tableModel->rowCount()-1)
            {
                m_tableModel->insertRow(ligne.row()+2);
                m_tableModel->setData(m_tableModel->index(ligne.row()+2, 0),
                                      m_tableModel->data(m_tableModel->index(ligne.row(),0)));
                m_tableModel->setData(m_tableModel->index(ligne.row()+2, 1),
                                      m_tableModel->data(m_tableModel->index(ligne.row(),1)));
                m_tableModel->setData(m_tableModel->index(ligne.row()+2, 2),
                                      m_tableModel->data(m_tableModel->index(ligne.row(),2)));
                m_tableModel->removeRow(ligne.row());
            }
        }
        for(int i=0; i<m_tableModel->rowCount(); ++i)
            m_tableModel->setData(m_tableModel->index(i,0), QString::number(i+1));
    }
}

#include "dialogajoutpoch.h"
#include "ui_dialogajoutpoch.h"
#include <QFileDialog>
#include "bddpoch.h"

DialogAjoutPoch::DialogAjoutPoch(QString artiste, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAjoutPoch),
    m_artiste ( artiste ),
    m_chemin (  ),
    m_album("rien"),
    m_poch( nullptr)
{
    ui->setupUi(this);

}

DialogAjoutPoch::~DialogAjoutPoch()
{
    delete ui;
}
void DialogAjoutPoch::AfficherPoch()
{
    QPixmap* pixmap = new QPixmap();
    m_poch.load( m_chemin );
    pixmap->convertFromImage( m_poch );
    QPixmap pixmapscaled = pixmap->scaled( 150, 150, Qt::IgnoreAspectRatio, Qt::FastTransformation );

    ui->Poch->setPixmap( pixmapscaled );
}

void DialogAjoutPoch::on_Parcourir_clicked()
{
    m_chemin = QFileDialog::getOpenFileName( this,
                                             "Ouvrir l'image contenant la pochette",
                                             "C:/Users/Nico/Desktop",
                                             "Images (*.png *.xpm *.jpg *.bmp)" );
    AfficherPoch();
}



void DialogAjoutPoch::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->standardButton( button ) == QDialogButtonBox::Ok )
    {
        m_album = ui->NomAlbum->text();
        if ( m_album !="")
        {
            EnregistrerPochette();
            this->close();
        }
    }
}
void DialogAjoutPoch::EnregistrerPochette()
{
    Handle<BDDPoch> poch = BDDPoch::recupererBDD(m_poch, m_album, m_artiste );
    poch->updateBDD();
}

#include "bddinterface.h"
#include "BDDcommun.h"
#include "BDDmp3.h"
#include "BDDphys.h"
#include <QDebug>

BDDInterface::BDDInterface(QObject *parent) : QObject(parent),
    myCommun(),
    myMp3(),
    myPhys()
{
}
//Actualise la liste MP3
void BDDInterface::actualiserMP3()
{
    myMp3.actualiserMp3("Album");
}
void BDDInterface::ViderBDD()
{
    myCommun.viderBDD();
}


void BDDInterface::enregistrerObservateur(BarreAvancement *obs)
{
    myCommun.enregistrerObservateur( obs );
    myMp3.enregistrerObservateur( obs );
}

void BDDInterface::desenregistrerObservateur(BarreAvancement *obs)
{
    myCommun.desenregistrerObservateur( obs );
    myMp3.desenregistrerObservateur( obs );
}

#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QImage>
#include "helpers_global.h"

void HELPERSSHARED_EXPORT FormaterEntiteBDD( QString& Entite );
QString HELPERSSHARED_EXPORT EchangerArtiste( QString Artiste );
void HELPERSSHARED_EXPORT EnleverAccents( QString& Nom );
void HELPERSSHARED_EXPORT EnleverPonctuation( QString& Nom );
void HELPERSSHARED_EXPORT MajusuculeAChaqueMot( QString& Entite );
QString HELPERSSHARED_EXPORT AnneesSwitch( int type );
QString HELPERSSHARED_EXPORT CreerChemin( QString& alb, QString& art, QString& tit );



#endif // UTIL_H

#ifndef BDDTITRE_H
#define BDDTITRE_H

#include <QObject>
#include "idowner.h"
#include "bdd_global.h"
#include "handle.h"

class BDDSHARED_EXPORT BDDTitre : public IdOwner
{
    Q_OBJECT
public:
    void updateBDD();
    void supprimerenBDD()const;

    virtual ~BDDTitre();
    static Handle<BDDTitre> recupererBDD( const int id );
    static Handle<BDDTitre> recupererBDD(const QString& nom );
    QString m_nom;
    QString m_nomFormate;

   static QList<int> Similaires( const int id );

    void mp3physfusion();

private:
    static int recupererId(const QString &nomFormate);
    static int TrouverId(const QString &nom );

    explicit BDDTitre(const int id, QString& nom, QString& nomFormate, QObject* parent = nullptr);
};

#endif // BDDTITRE_H

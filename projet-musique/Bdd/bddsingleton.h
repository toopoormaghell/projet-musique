#ifndef BDDSINGLETON_H
#define BDDSINGLETON_H

#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include "bdd_global.h"
#include "outilsbdd.h"

class BDDSHARED_EXPORT BDDSingleton
{
public:
    // Destructeur : ferme la base de données
    ~BDDSingleton();
    // Retourne une référence sur l'unique objet de ce type
    static BDDSingleton& getInstance();

    // Executes a SQL statement on the database and returns a QSqlQuery object.
    // Use lastError() to retrieve error information. If query is empty, an empty,
    // invalid query is returned and lastError() is not affected
    QSqlQuery exec(const QString& query = QString()) const;

    void creationBase();
    void viderBDD();

      void changementversion();



private:
    // Constructeur privé : singleton
    BDDSingleton();
    // Volontairement non implémenté
    BDDSingleton( const BDDSingleton& other );
    // Volontairement non implémenté
    BDDSingleton& operator=( const BDDSingleton& rhs );
    // Base de données SQL
    QSqlDatabase m_database;
    static BDDSingleton s_singleton;

    OutilsBDD* m_outils;
};

#define madatabase BDDSingleton::getInstance()

#endif // BDDSINGLETON_H

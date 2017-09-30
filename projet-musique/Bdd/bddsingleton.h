#ifndef BDDSINGLETON_H
#define BDDSINGLETON_H

#include <QtSql/QSqlDatabase>
#include "bdd_global.h"
#include "outilsbdd.h"

class BDDSHARED_EXPORT BDDSingleton
{
public:
    // Destructeur : ferme la base de données
    ~BDDSingleton();
    // Retourne une référence sur l'unique objet de ce type
    static BDDSingleton& getInstance();
    // Retourne une référence sur la base de données SQL
    QSqlDatabase& getDataBase();


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

#define madatabase (BDDSingleton::getInstance().getDataBase())

#endif // BDDSINGLETON_H

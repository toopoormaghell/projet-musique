#ifndef BDDSINGLETON_H
#define BDDSINGLETON_H

#include <QObject>
#include <QSqlDatabase>

class BDDSingleton
{
public:
    // Destructeur : ferme la base de données
    ~BDDSingleton();
    // Retourne une référence sur l'unique objet de ce type
    static BDDSingleton& getInstance();
    // Retourne une référence sur la base de données SQL
    QSqlDatabase& getDataBase();


    void creationBase();
private:
    // Constructeur privé : singleton
    BDDSingleton();
    // Base de données SQL
    QSqlDatabase m_database;
    static BDDSingleton singleton;
};

#define madatabase (BDDSingleton::getInstance().getDataBase())

#endif // BDDSINGLETON_H

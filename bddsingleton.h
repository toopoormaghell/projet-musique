#ifndef BDDSINGLETON_H
#define BDDSINGLETON_H

#include <QObject>
#include <QSqlDatabase>

class BDDSingleton
{
public:
    // Destructeur : ferme la base de donn�es
    ~BDDSingleton();
    // Retourne une r�f�rence sur l'unique objet de ce type
    static BDDSingleton& getInstance();
    // Retourne une r�f�rence sur la base de donn�es SQL
    QSqlDatabase& getDataBase();


    void creationBase();
private:
    // Constructeur priv� : singleton
    BDDSingleton();
    // Base de donn�es SQL
    QSqlDatabase m_database;
    static BDDSingleton singleton;
};

#define madatabase (BDDSingleton::getInstance().getDataBase())

#endif // BDDSINGLETON_H

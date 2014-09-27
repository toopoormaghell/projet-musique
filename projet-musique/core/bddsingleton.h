#ifndef BDDSINGLETON_H
#define BDDSINGLETON_H



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
    // Volontairement non impl�ment�
    BDDSingleton( const BDDSingleton& other );
    // Volontairement non impl�ment�
    BDDSingleton& operator=( const BDDSingleton& rhs );
    // Base de donn�es SQL
    QSqlDatabase m_database;
    static BDDSingleton s_singleton;
};

#define madatabase (BDDSingleton::getInstance().getDataBase())

#endif // BDDSINGLETON_H

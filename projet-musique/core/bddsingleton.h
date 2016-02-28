#ifndef BDDSINGLETON_H
#define BDDSINGLETON_H

#include <QtSql/QSqlDatabase>

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
    void viderBDD();
    bool removeDir( const QString& dirPath, const bool remove = true, const QString fichier = "def.jpg" );
    void verifierBDD();
    void supprimerdossiersvides();
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
};

#define madatabase (BDDSingleton::getInstance().getDataBase())

#endif // BDDSINGLETON_H

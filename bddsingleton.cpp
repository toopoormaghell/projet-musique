#include "bddsingleton.h"
#include <QDebug>

BDDSingleton BDDSingleton::singleton;

BDDSingleton::BDDSingleton()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setHostName("localhost");
    m_database.setDatabaseName("Musique.db");
    m_database.setUserName("root");
    m_database.setPassword("");
    //Si la BDD n'est pas ouverte,elle affiche une erreur
    if(!m_database.open())
    {
        qDebug() << "Impossible d'ouvrir la base de données !";
    }
}
BDDSingleton::~BDDSingleton()
{
    m_database.close();
}
BDDSingleton& BDDSingleton::getInstance()
{
    return singleton;
}

QSqlDatabase &BDDSingleton::getDataBase()
{
    return m_database;
}

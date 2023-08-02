#include "db_manager.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

DBManager::DBManager(const QString &filePath)
    :m_db(QSqlDatabase::addDatabase("QSQLITE", "weatherGlobal"))
{
    m_db.setDatabaseName(filePath);
    m_db.setConnectOptions( "QSQLITE_BUSY_TIMEOUT=20000" );

    if(!m_db.open()){
        qDebug() << "can not open db"<< filePath;

        if(!m_db.lastError().databaseText().isEmpty()){
            qDebug() << m_db.lastError().databaseText();
        }
    }
}

DBManager::~DBManager()
{
    m_db.close();
}

QSqlDatabase &DBManager::db()
{
    return m_db;
}

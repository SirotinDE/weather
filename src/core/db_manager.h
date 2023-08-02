#pragma once

#include <QSqlDatabase>

class QSqlDatabase;

class DBManager
{
public:
    DBManager(const QString& filePath);
    ~DBManager();

    QSqlDatabase& db();
private:
    QSqlDatabase m_db;
};


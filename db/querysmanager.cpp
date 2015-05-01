#include "db/querysmanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

QuerysManager::QuerysManager()
{

}

QuerysManager::~QuerysManager()
{

}

bool QuerysManager::createTable_Data()
{
    const QString tableName("Data");
    QString sql = QString("CREATE TABLE IF NOT EXISTS %1( "
                  "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                  "PassGroup      VARCHAR(32), "
                  "Resource       VARCHAR(255), "
                  "Url            VARCHAR(255), "
                  "Login          VARCHAR(128), "
                  "Password       VARCHAR(255), "
                  "Mail           VARCHAR(128), "
                  "Phone          VARCHAR(128), "
                  "Answer         VARCHAR(128), "
                  "CreateTime     INTEGER, "
                  "PassLifeTime   INTEGER, "
                  "Description    TEXT "
                  ");").arg( tableName );

    QSqlQuery query;
    if( ! query.exec(sql) ){
        qCritical() << QString("Table %1 is not created!").arg( tableName )
                    << "\nSqlError: "
                    << query.lastError();
        return false;
    }
    return true;
}

bool QuerysManager::createTables()
{
    return createTable_Data();
}

bool QuerysManager::insert(Data &)
{
    return false;
}


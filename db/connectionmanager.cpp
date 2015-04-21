#include "db/connectionmanager.h"
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <definespath.h>

ConnectionManager::ConnectionManager()
{
    const QString dbUser("");
    const QString dbHost("");
    const QString dbPass("");
    const QString dbDriv("QSQLITE");

    // Проверяем доступность драйвера
    if( ! QSqlDatabase::isDriverAvailable(dbDriv) ){
        qCritical() << "Cannot avalible QSQLITE driver";
        QMessageBox::critical(0, QObject::tr("Critical"),
                    QObject::tr("Cannot avalible database driver"));
        return;
    }

    db = QSqlDatabase::addDatabase(dbDriv);

    // Попытка создания директории для БД
    if( ! QDir().mkpath( DefinesPath::dbPath() ) ){
        // Если создать не удалось - логируем и уведомляем пользователя
        qCritical() << "Cannot created work directory"
                    << "\nPath: " << DefinesPath::dbPath();
        QMessageBox::critical(0, QObject::tr("Critical"),
                              QObject::tr("It was not succeeded to create a directory for a database."));
    } else {
        // Непосредственно полезный код
        db.setDatabaseName( DefinesPath::dbPath(true) );
        db.setUserName( dbUser );
        db.setHostName( dbHost );
        db.setPassword( dbPass );
    }
}

/*!
 * \brief ConnectionManager::~ConnectionManager
 *
 * Деструктор, если БД открыта - закрыть
 */
ConnectionManager::~ConnectionManager()
{
    if( db.isOpen() )
        db.close();
}

bool ConnectionManager::open()
{
    return db.open();
}

void ConnectionManager::close()
{
    return db.close();
}

bool ConnectionManager::transaction()
{
    return db.transaction();
}

bool ConnectionManager::commit()
{
    return db.commit();
}

bool ConnectionManager::rollback()
{
    return db.rollback();
}

bool ConnectionManager::isOpen()
{
    return db.isOpen();
}


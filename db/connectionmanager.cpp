#include "db/connectionmanager.h"
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <definespath.h>

/*!
 * \brief Конструктор, инициализирует начальные значения полей
 * для подключения к БД, проверяет доступность драйвера
 */
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

    db.setUserName( dbUser );
    db.setHostName( dbHost );
    db.setPassword( dbPass );
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

/*!
 * \brief Метод для открытия подключения к базе данных
 * \param filePath - путь к файлу базы данных
 * \return true - в случае успеха подключения к БД
 */
bool ConnectionManager::open(QString &filePath)
{
    const QString dbFileName("PassMan.db");
    if( filePath.isEmpty() || filePath.isNull() ){
        filePath  = QStandardPaths::writableLocation( QStandardPaths::TempLocation );
        filePath += QDir::separator();
    }

    if( ! QDir().mkpath( filePath ) ){
        // Если создать не удалось - логируем и \todo уведомляем пользователя
        qCritical() << "Cannot created work directory"
                    << "\nPath: " << filePath;
        return false;
    } else {
        // Непосредственно полезный код
        db.setDatabaseName( filePath + dbFileName );
        return db.open();
    }
}

/*!
 * \brief Метод для закрытия соединения с БД
 */
void ConnectionManager::close()
{
    return db.close();
}

/*!
 * \brief Метод для начала транзации
 * \return успех операции
 */
bool ConnectionManager::transaction()
{
    return db.transaction();
}

/*!
 * \brief Метод для фиксирования изменений в транзации
 * \return успех операции
 */
bool ConnectionManager::commit()
{
    return db.commit();
}

/*!
 * \brief Метод для отката изменений в транзации
 * \return успех операции
 */
bool ConnectionManager::rollback()
{
    return db.rollback();
}

/*!
 * \brief Метод позволяет узнать открыто ли соединение с БД
 * \return true - если соединение с БД открыто.
 */
bool ConnectionManager::isOpen()
{
    return db.isOpen();
}


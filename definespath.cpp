#include "definespath.h"
#include "globalenum.h"

#include <QSettings>
#include <QDebug>

/// Any string(path) ended of QDir::separator()

/*! \~russian
 * \brief Метод для получения пути к домашней директории
 * \return QString - путь к домашней директории пользователя
 */
/*! \~english
 * \brief Method for receiving a path to a house directory
 * \return QString - path to writable location a user home directory
 */
QString DefinesPath::home()
{
    return QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
}

/*! \~russian
 * \brief Метод для получения пути к директории с лог-файлами
 * \return QString - путь к доступной для записи директории предназначенной
 * для хранения логов
 */
/*! \~english
 * \brief Method for receiving a way to a directory with log files
 * \return QString - path to writable location a log-files of program
 */
QString DefinesPath::log()
{
    return QStandardPaths::writableLocation( QStandardPaths::CacheLocation ) + QDir::separator() + "log" + QDir::separator();
}

/*! \~russian
 * \brief Метод для получения списка директорий с данными приложения
 * \return QStringList - список директорий с данными приложения
 */
/*! \~english
 * \brief Method for obtaining the list of dataful directories of application
 * \return QStringList - list of standard location of application data files
 */
QStringList DefinesPath::share()
{
    QStringList paths = QStandardPaths::standardLocations( QStandardPaths::DataLocation );
    QStringList newPaths;
    foreach (QString path, paths) {
        newPaths << path + QDir::separator();
    }
    return newPaths;
}

/*! \~russian
 * \brief Метод для получения пути к пользовательской директории с данными приложения
 * \param useDefault - использовать путь по умолчанию
 * \return QString - путь к доступной для записи директории приложения
 * если useDefault == true - возвращается стандартное значение
 * иначе возвращется значение указанное в настройках пользователя
 */
/*! \~english
 * \brief Method for receiving a path to an application dataful directory
 * \param useDefault - use default path
 * \return QString - path to writable location an application data
 * if useDefault is true - returned a default, system location
 * else returned a user settings location
 */
QString DefinesPath::appData(bool useDefault)
{
    if(useDefault)
        return QStandardPaths::writableLocation( QStandardPaths::DataLocation ) + QDir::separator();
    QSettings settings;
    return QDir(settings.value(Options::General::WorkDirectory,
                   QStandardPaths::writableLocation( QStandardPaths::DataLocation )
                   ).toString()).path() + QDir::separator();

    // Use in:
    // - dbPath()
}

/*! \~russian
 * \brief Метод для получения пути к файлу базы данных
 * \param appendFileName - добавить к возвращаемому значению имя файла базы данных
 * \return QString - путь к файлу быза данных
 * если appendFileName равен true - добавляется имя файла
 */
/*! \~english
 * \brief Method for receiving a path to the file of a database
 * \param appendFileName - append to return value a database file name
 * \return QString - path to database file
 * if appendFileName is true - appended a file name
 */
QString DefinesPath::dbPath(bool appendFileName)
{
    if(appendFileName)
        return appData() + "PassMan.db";
    else
        return appData();
}

/*! \~russian
 * \brief Метод для получения доступной для записи директории с файлами стилей
 * \return QString - доступная для записи директория
 */
/*! \~english
 * \brief Method for receiving a directory, available to record, with files of styles
 * \return QString - directory, available to write
 */
QString DefinesPath::styleLocation()
{
    return QStandardPaths::writableLocation( QStandardPaths::DataLocation ) + QDir::separator() + "Style" + QDir::separator();
}

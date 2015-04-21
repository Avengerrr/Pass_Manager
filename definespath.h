#ifndef DEFINESPATH_H
#define DEFINESPATH_H

#include <QString>
#include <QDir>
#include <QStandardPaths>

/*! \~russian
 * \brief Статический класс для доступа к файловой иерархии приложения
 * \warning Все возвращаемые классом пути(строки) обязаны заканчиваться на QDir::separator()
 */
/*! \~english
 * \brief The static class for access to file hierarchy of application
 * \warning Any string(path) ended of QDir::separator()
 */
class DefinesPath
{
public:
    static QString home();
    static QString log();
    static QStringList share();
    static QString styleLocation();

    static QString appData(bool useDefault = false);
        static QString dbPath(bool appendFileName = false);
};

#endif // DEFINESPATH_H

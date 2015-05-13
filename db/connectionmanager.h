#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QSqlDatabase>

class ConnectionManager
{
private:
    QSqlDatabase db;
public:
    ConnectionManager();
    ~ConnectionManager();
    bool open(QString &filePath);
    void close();
    bool remove();
    bool transaction();
    bool commit();
    bool rollback();
    bool isOpen();
};

#endif // CONNECTIONMANAGER_H

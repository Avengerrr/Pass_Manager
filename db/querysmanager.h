#ifndef QUERYSMANAGER_H
#define QUERYSMANAGER_H


class QuerysManager
{
private:
    QuerysManager();
    ~QuerysManager();
    static bool createTable_Data();
public:
    static bool createTables();
};

#endif // QUERYSMANAGER_H

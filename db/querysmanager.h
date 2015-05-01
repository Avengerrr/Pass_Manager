#ifndef QUERYSMANAGER_H
#define QUERYSMANAGER_H

#include <Data/data.h>

class QuerysManager
{
private:
    QuerysManager();
    ~QuerysManager();
    static bool createTable_Data();
public:
    static bool createTables();
    static bool insert( Data &data );
    static bool update( Data &data );
};

#endif // QUERYSMANAGER_H

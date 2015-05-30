#include "recentdocuments.h"
#include <QDebug>


int RecentDocuments::count()
{
    return _list.count();
}

bool RecentDocuments::addLastDocument(const QString &filePath)
{
    if( _list.count() < 5 ){
        _list.append( filePath );
        return true;
    } else {
        int i = 0;
        for (i = 0; i < ( _list.count() - 1 ); ++i) {
            _list[i] = _list[i+1];
        }
        _list[i] = filePath;
        return true;
    }
    return false;
}

QString RecentDocuments::getLastDocument()
{
    return _list.last();
}

QStringList RecentDocuments::getRecentDocuments()
{
    return _list;
}

bool RecentDocuments::setRecendDocuments(const QStringList &list)
{
    _list = list;
    return true;
}

#ifndef RECENTDOCUMENTS_H
#define RECENTDOCUMENTS_H

#include <QStringList>

class RecentDocuments
{
    QStringList _list;
    static const int MAX_COUNT = 5;
public:
    int         count();
    bool        addLastDocument(const QString& filePath);
    QString     getLastDocument();
    QStringList getRecentDocuments();
    bool        setRecendDocuments(const QStringList &list);
};

#endif // RECENTDOCUMENTS_H

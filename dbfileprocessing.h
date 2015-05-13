#ifndef DBFILEPROCESSING_H
#define DBFILEPROCESSING_H

#include <QString>

class DbFileProcessing
{
private:
    QString    _achtungDbPath;
    QString    _encryptDbPath;
    QByteArray _password;
    QByteArray _salt;
    size_t     _bufferSize = 51200;
public:
    explicit DbFileProcessing(const QString    &achtungDbPath,
                              const QString    &encryptDbPath,
                              const QByteArray &password,
                              const QByteArray &salt,
                              const size_t     bufferSize = 51200);
    bool openEncryptFile();
    bool saveEncryptFile();
};

#endif // DBFILEPROCESSING_H

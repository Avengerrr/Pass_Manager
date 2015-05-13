#include "cryptfiledevice.h"
#include "dbfileprocessing.h"

#include <QFile>
#include <QDebug>
#include <QApplication>


DbFileProcessing::DbFileProcessing(const QString    &achtungDbPath,
                                   const QString    &encryptDbPath,
                                   const QByteArray &password,
                                   const QByteArray &salt,
                                   const size_t     bufferSize)
{
    _achtungDbPath = achtungDbPath;
    _encryptDbPath = encryptDbPath;
    _password      = password;
    _salt          = salt;
    if(bufferSize > 1024)
        _bufferSize = bufferSize;
}

bool DbFileProcessing::openEncryptFile()
{
    QFile achtungDB( _achtungDbPath );
    CryptFileDevice encDB( _encryptDbPath, _password, _salt );

    if ( ! achtungDB.open(QIODevice::WriteOnly) ){
        qCritical() << "[DbFileProcessing::readEncryptFile()] "
                    << "cannot open decrypt file for write: " << _achtungDbPath;
        return false;
    }
    if ( ! encDB.open(QIODevice::ReadOnly) ){
        qCritical() << "[DbFileProcessing::readEncryptFile()] "
                    << "cannot open encrypt file for read: " << _encryptDbPath;
        return false;
    }

    while ( ! encDB.atEnd() ) {
        QByteArray buffer = encDB.read( _bufferSize );
        achtungDB.write( buffer );
        qApp->processEvents(); // Обработка событий
    }

    encDB.close();
    achtungDB.close();

    return true;
}

bool DbFileProcessing::saveEncryptFile()
{
    QFile achtungDbFile( _achtungDbPath );
    CryptFileDevice encryptDbfile( _encryptDbPath, _password, _salt );

    if ( ! achtungDbFile.open(QIODevice::ReadOnly) ){
        qCritical() << "[DbFileProcessing::saveEncryptFile()] "
                    << "cannot open decrypt file for read: " << _achtungDbPath;
        return false;
    }
    if ( ! encryptDbfile.open(QIODevice::WriteOnly) ){
        qCritical() << "[DbFileProcessing::saveEncryptFile()] "
                    << "cannot open encrypt file for write: " << _encryptDbPath;
        return false;
    }

    while ( ! achtungDbFile.atEnd() ) {
        QByteArray buffer = achtungDbFile.read( _bufferSize );
        encryptDbfile.write( buffer );
    }

    encryptDbfile.close();
    achtungDbFile.close();

    return true;
}

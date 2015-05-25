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
    CryptFileDevice encDB( _encryptDbPath, _password, _salt );
    QFile achtungDB( _achtungDbPath );

//    encDB.setKeyLength( CryptFileDevice::kAesKeyLength128 );
//    encDB.setKeyLength( CryptFileDevice::kAesKeyLength192 );
    encDB.setKeyLength( CryptFileDevice::kAesKeyLength256 );

    if ( ! encDB.open(QIODevice::ReadOnly) ){
        qCritical() << "[DbFileProcessing::readEncryptFile()] "
                    << "cannot open encrypt file for read: " << _encryptDbPath;
        qDebug() << "encDB.open: " << encDB.errorString();
        return false;
    }
    if ( ! achtungDB.open(QIODevice::WriteOnly) ){
        qCritical() << "[DbFileProcessing::readEncryptFile()] "
                    << "cannot open decrypt file for write: " << _achtungDbPath;
        return false;
    }

    qDebug() << "encDB.errorString: " << encDB.errorString();
    qDebug() << "encDB.size(): " << encDB.size();
    qDebug() << "encDB.fileName(): " << encDB.fileName();
    qDebug() << "encDB.isEncrypted(): " << encDB.isEncrypted();
    qDebug() << "encDB.isReadable(): " << encDB.isReadable();
    qDebug() << "encDB.isSequential(): " << encDB.isSequential();

    qDebug() << "0.encDB.bytesAvailable(): " << encDB.bytesAvailable();
    qDebug() << "0.encDB.pos(): " << encDB.pos();

    while ( ! encDB.atEnd() ) {
        QByteArray buffer = encDB.read( _bufferSize );
        achtungDB.write( buffer );
        qApp->processEvents(); // Обработка событий
    }

    qDebug() << "1.encDB.bytesAvailable(): " << encDB.bytesAvailable();
    qDebug() << "1.encDB.pos(): " << encDB.pos();

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

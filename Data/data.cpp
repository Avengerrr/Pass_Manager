#include "data.h"

#include <QDebug>
#include <QSqlError>
#include <QVariant>

QString Data::group() const
{
    return _group;
}

void Data::setGroup(const QString &group)
{
    _group = group;
}

QString Data::resource() const
{
    return _resource;
}

void Data::setResource(const QString &resource)
{
    _resource = resource;
}

QString Data::url() const
{
    return _url;
}

void Data::setUrl(const QString &url)
{
    _url = url;
}

QString Data::login() const
{
    return _login;
}

void Data::setLogin(const QString &login)
{
    _login = login;
}

QString Data::password() const
{
    return _password;
}

void Data::setPassword(const QString &password)
{
    _password = password;
}

QString Data::mail() const
{
    return _mail;
}

void Data::setMail(const QString &mail)
{
    _mail = mail;
}

QString Data::phone() const
{
    return _phone;
}

void Data::setPhone(const QString &phone)
{
    _phone = phone;
}

QString Data::answer() const
{
    return _answer;
}

void Data::setAnswer(const QString &answer)
{
    _answer = answer;
}

QString Data::createTime() const
{
    return _createTime;
}

void Data::setCreateTime(const QString &createTime)
{
    _createTime = createTime;
}

QString Data::passLifeTime() const
{
    return _passLifeTime;
}

void Data::setPassLifeTime(const QString &passLifeTime)
{
    _passLifeTime = passLifeTime;
}

QString Data::description() const
{
    return _description;
}

void Data::setDescription(const QString &description)
{
    _description = description;
}


bool Data::editMode() const
{
    return _editMode;
}

void Data::setEditMode(bool editMode)
{
    _editMode = editMode;
}
bool Data::insert()
{
    QSqlQuery query;

    query.prepare( QString("INSERT INTO %1("
                           "PassGroup, Resource, Url, Login,"
                           "Password, Mail, Phone,"
                           "Answer, CreateTime, PassLifeTime, Description"
                           ") VALUES ("
                           ":PassGroup, :Resource, :Url, :Login,"
                           ":Password, :Mail, :Phone,"
                           ":Answer, :CreateTime, :PassLifeTime, :Description);").arg(DataTable::tableName) );

    query.bindValue( ":PassGroup", group() );
    query.bindValue( ":Resource", resource() );
    query.bindValue( ":Url", url() );
    query.bindValue( ":Login", login() );
    query.bindValue( ":Password", password() );
    query.bindValue( ":Mail", mail() );
    query.bindValue( ":Phone", phone() );
    query.bindValue( ":Answer", answer() );
    query.bindValue( ":CreateTime", createTime() );
    query.bindValue( ":PassLifeTime", passLifeTime() );
    query.bindValue( ":Description", description() );

    if( ! query.exec() ){
        qDebug() << query.executedQuery() << "\n----\n"
                 << query.lastQuery();
        qCritical() << "Cannot insert Data to database\n"
                    << "SqlError: " << query.lastError();
        return false;
    }
    return true;
}

bool Data::update()
{
    QSqlQuery query;

    query.prepare( QString("UPDATE %1 SET "
                           "PassGroup = :PassGroup, Resource = :Resource, Url = :Url, Login = :Login,"
                           "Password = :Password, Mail = :Mail, Phone = :Phone,"
                           "Answer = :Answer, CreateTime = :CreateTime,"
                           "PassLifeTime = :PassLifeTime, Description = :Description"
                           "WHERE id = :id;"
                           ).arg(DataTable::tableName) );

    query.bindValue( ":id", id() );
    query.bindValue( ":PassGroup", group() );
    query.bindValue( ":Resource", resource() );
    query.bindValue( ":Url", url() );
    query.bindValue( ":Login", login() );
    query.bindValue( ":Password", password() );
    query.bindValue( ":Mail", mail() );
    query.bindValue( ":Phone", phone() );
    query.bindValue( ":Answer", answer() );
    query.bindValue( ":CreateTime", createTime() );
    query.bindValue( ":PassLifeTime", passLifeTime() );
    query.bindValue( ":Description", description() );

    if( ! query.exec() ){
        qCritical() << "Cannot update Data in database\n"
                    << "SqlError: " << query.lastError();
        return false;
    }
    return true;
}

bool Data::save()
{
    if( _editMode ){
        return update();
    }else{
        return insert();
    }
}

bool Data::load(const QString &id)
{
    QSqlQuery query;

    query.prepare( QString("SELECT * FROM %1 WHERE id = :id"
                           ).arg(DataTable::tableName) );

    query.bindValue( ":id", id );

    if( ! query.exec() ){
        qCritical() << "Cannot select Data from database\n"
                    << "SqlError: " << query.lastError();
        return false;
    }
    query.first();

    setId( query.value( DataTable::Fields::id ).toString() );
    setAnswer( query.value( DataTable::Fields::Answer ).toString() );
    setCreateTime( query.value( DataTable::Fields::CreateTime ).toString() );
    setDescription( query.value( DataTable::Fields::Description ).toString() );
    setGroup( query.value( DataTable::Fields::PassGroup ).toString() );
    setLogin( query.value( DataTable::Fields::Login ).toString() );
    setMail( query.value( DataTable::Fields::Mail ).toString() );
    setPassLifeTime( query.value( DataTable::Fields::PassLifeTime ).toString() );
    setPassword( query.value( DataTable::Fields::Password ).toString() );
    setPhone( query.value( DataTable::Fields::Phone ).toString() );
    setResource( query.value( DataTable::Fields::Resource ).toString() );
    setUrl( query.value( DataTable::Fields::Url ).toString() );


    return true;
}

QString Data::id() const
{
    return _id;
}

void Data::setId(const QString &id)
{
    _id = id;
}

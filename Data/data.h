#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QSqlQuery>

namespace DataTable {
    const QString tableName("Data");

    namespace Fields{
        const QString id("id");
        const QString PassGroup("PassGroup");
        const QString Resource("Resource");
        const QString Url("Url");
        const QString Login("Login");
        const QString Password("Password");
        const QString Mail("Mail");
        const QString Phone("Phone");
        const QString Answer("Answer");
        const QString CreateTime("CreateTime");
        const QString PassLifeTime("PassLifeTime");
        const QString Description("Description");
    }
}

class Data
{
    bool    _editMode;
    QString _id;
    QString _group;
    QString _resource;
    QString _url;
    QString _login;
    QString _password;
    QString _mail;
    QString _phone;
    QString _answer;
    QString _createTime;
    QString _passLifeTime;
    QString _description;

    bool insert();
    bool update();
public:
    bool save();

    QString id() const;
    void setId(const QString &id);
    QString group() const;
    void setGroup(const QString &group);
    QString resource() const;
    void setResource(const QString &resource);
    QString url() const;
    void setUrl(const QString &url);
    QString login() const;
    void setLogin(const QString &login);
    QString password() const;
    void setPassword(const QString &password);
    QString mail() const;
    void setMail(const QString &mail);
    QString phone() const;
    void setPhone(const QString &phone);
    QString answer() const;
    void setAnswer(const QString &answer);
    QString createTime() const;
    void setCreateTime(const QString &createTime);
    QString passLifeTime() const;
    void setPassLifeTime(const QString &passLifeTime);
    QString description() const;
    void setDescription(const QString &description);
    bool editMode() const;
    void setEditMode(bool editMode);
};

#endif // DATA_H

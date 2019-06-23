#include "JwUser.h"
#include <QDateTime>

JwUser::JwUser(QObject *parent) : QObject(parent)
{
    init();
}

QString JwUser::username() const
{
    return m_username;
}

void JwUser::setUsername(const QString &username)
{
    m_username = username;
}

quint32 JwUser::age() const
{
    return m_age;
}

void JwUser::setAge(const quint32 &age)
{
    m_age = age;
}

QString JwUser::email() const
{
    return m_email;
}

void JwUser::setEmail(const QString &email)
{
    m_email = email;
}

QString JwUser::className()
{
    return m_className;
}

QStringList JwUser::fieldNames()
{
    return QStringList() << "id INTEGER PRIMARY KEY AUTOINCREMENT"
                         << "username TEXT"
                         << "age TEXT"
                         << "email TEXT"
                         << "createdtime TEXT";
}

QStringList JwUser::fieldValues()
{
    return QStringList() << m_username
                         << QString("%1").arg(m_age)
                         << m_email
                         << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"); //m_createdTime;
}

void JwUser::init()
{
    m_className = "JwUser";

    m_username = "Bill Gates";
    m_age = 55;
    m_email = "Gates.Bill@hotmail.com";
    m_createdTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}

quint64 JwUser::id() const
{
    return m_id;
}

void JwUser::setId(const quint64 &id)
{
    m_id = id;
}

QString JwUser::createdTime() const
{
    return m_createdTime;
}

void JwUser::setCreatedTime(const QString &createdTime)
{
    m_createdTime = createdTime;
}

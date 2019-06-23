#include "JwUser.h"

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
    return QStringList() << "username"
                         << "age"
                         << "email";
}

QStringList JwUser::fieldValues()
{
    return QStringList() << m_username + QString("%1").arg(m_index ++)
                         << QString("%1").arg(m_age)
                         << m_email;
}

void JwUser::init()
{
    m_className = "JwUser";
    m_index = 0;

    m_username = "Bill Gates";
    m_age = 55;
    m_email = "Gates.Bill@hotmail.com";
}

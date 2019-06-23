#ifndef JWUSER_H
#define JWUSER_H

#include <QObject>

class JwUser : public QObject
{
    Q_OBJECT
public:
    explicit JwUser(QObject *parent = nullptr);


    QString username() const;
    void setUsername(const QString &username);

    quint32 age() const;
    void setAge(const quint32 &age);

    QString email() const;
    void setEmail(const QString &email);

    QString createdTime() const;
    void setCreatedTime(const QString &createdTime);

    quint64 id() const;
    void setId(const quint64 &id);

    QString className();
    QStringList fieldNames();
    QStringList fieldValues();

private:
    void init();

private:
    QString m_className;

    quint64 m_id;
    QString m_username;
    quint32 m_age;
    QString m_email;
    QString m_createdTime;
};

#endif // JWUSER_H

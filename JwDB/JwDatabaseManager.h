#ifndef JWDATABASEMANAGER_H
#define JWDATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariantMap>

#include "jwdb_global.h"

class JWDBSHARED_EXPORT JwDatabaseManager : public QObject
{

public:
    JwDatabaseManager(QObject *parent = nullptr);

public slots:
    bool openDatabase(QString name);
    void closeDatabase();

    bool createTable(QString tableName, QStringList fieldNames);
    bool dropTable(QString tableName);
    bool insertRecord(QString tableName, QStringList record, int fieldCount);
    bool deleteRecord(QString tableName, QString conditions = "");
    bool updateRecord(QString tableName, QMap<QString, QString> contents, QString conditions = "");
    qlonglong queryCount(QString tableName);
    QVariant querySelect(QString tableName, QString conditions = "");

    QVariant searchQuery(QString tableName, QString searchText);


private:
    QVariant exec(QString cmd, QVariantMap bindValues = QVariantMap());

    QString makeCreateTableSQL(QString tableName, QStringList fieldNames);
    QString makeDropTableSQL(QString tableName);

    QString makeInsertSQL(QString tableName, int fieldCount);
    QString makeDeleteSQL(QString tableName, QString conditions = "");

    QString makeCountSQL(QString tableName);
    QString makeSelectSQL(QString tableName, QString conditions = "");

    QString makeUpdateSQL(QString tableName, QMap<QString, QString> contents, QString conditions);

private:
    QSqlDatabase m_sqlDatabase;
    QSqlQuery m_sqlQuery;
};

#endif // JWDATABASEMANAGER_H

#include "JwDatabaseManager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QFile>
#include <Windows.h>

JwDatabaseManager::JwDatabaseManager(QObject *parent) : QObject(parent)
{
}

// public slots
qlonglong JwDatabaseManager::queryCount(QString tableName)
{
    QString sql = makeCountSQL(tableName);

    QVariant result = exec(sql);
    return result.toList().at(0).toMap().values().at(0).toInt();
}

QVariant JwDatabaseManager::querySelect(QString tableName, QString conditions)
{
    QString sql = makeSelectSQL(tableName, conditions);
    QVariant result = exec(sql);
    return result;
}

QVariant JwDatabaseManager::queryPage(QString tableName, int pageIndex, int rowCountPerPage)
{
    QString sql = makePageQuerySQL(tableName, pageIndex, rowCountPerPage);
    QVariant result = exec(sql);
    return result;
}

bool JwDatabaseManager::openDatabase(QString name)
{
    m_sqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    m_sqlQuery = QSqlQuery();

    m_sqlDatabase.setDatabaseName(name);
    if (!m_sqlDatabase.open())
    {
        qDebug() << metaObject()->className() << "::" << __FUNCTION__ << "()" << "-> Failed to Open DB : " << m_sqlDatabase.lastError();
        return false;
    }

    return true;
}

void JwDatabaseManager::closeDatabase()
{
    m_sqlDatabase.close();
}

bool JwDatabaseManager::createTable(QString tableName, QStringList fieldNames)
{
    QString createSql = makeCreateTableSQL(tableName, fieldNames);
    qDebug() << "createSql = " << createSql;

    m_sqlQuery.prepare(createSql);
    if(!m_sqlQuery.exec())
    {
        qDebug() << metaObject()->className() << "::" << __FUNCTION__ << "()" << "Failed to Create Table : " << m_sqlQuery.lastError();
        return false;
    }

    return true;
}

bool JwDatabaseManager::dropTable(QString tableName)
{
    QString sql = makeDropTableSQL(tableName);
    m_sqlQuery.prepare(sql);
    if(!m_sqlQuery.exec())
    {
        qDebug() << metaObject()->className() << "::" << __FUNCTION__ << "()" << "Failed to Create Table : " << m_sqlQuery.lastError();
        return false;
    }

    return true;
}

bool JwDatabaseManager::insertRecord(QString tableName, QStringList fieldNames, QStringList fieldValues)
{
    int fieldCount = fieldValues.size();


    QString insertSql = makeInsertSQL(tableName, fieldNames, fieldValues);
    qDebug() << "insertSql = " << insertSql;
    m_sqlQuery.prepare(insertSql);

    for (int i=0; i<fieldCount; i++)
    {
        QString text = fieldValues.at(i);
        m_sqlQuery.addBindValue(QStringList() << text);
        qDebug() << "record.at(i) = " << fieldValues.at(i);
    }

    if(!m_sqlQuery.execBatch())
    {
        qDebug()<< tr("Failed Insert : ") << m_sqlQuery.lastError() << m_sqlQuery.executedQuery();
        return false;
    }

    return true;
}

bool JwDatabaseManager::deleteRecord(QString tableName, QString conditions)
{
    QString sql = makeDeleteSQL(tableName, conditions);
    qDebug() << "sql = " << sql;
    m_sqlQuery.prepare(sql);
    if(!m_sqlQuery.exec())
    {
        qDebug() << metaObject()->className() << "::" << __FUNCTION__ << "() -> " << "Failed to Delete : " << m_sqlQuery.lastError();
        return false;
    }

    return true;
}

bool JwDatabaseManager::updateRecord(QString tableName, QMap<QString, QString> newContents, QString conditions)
{
    QString sql = makeUpdateSQL(tableName, newContents, conditions);
    qDebug() << "sql = " << sql;
    m_sqlQuery.prepare(sql);
    if(!m_sqlQuery.exec())
    {
        qDebug() << metaObject()->className() << "::" << __FUNCTION__ << "() -> " << "Failed to Update : " << m_sqlQuery.lastError();
        return false;
    }

    return true;
}

// private
QVariant JwDatabaseManager::exec(QString cmd, QVariantMap bindValues)
{
    QVariant result(false);

    do{
        if (!m_sqlDatabase.isOpen())
        {
            break;
        }

        QSqlQuery query(m_sqlDatabase);
        // prepare command
        if (!query.prepare(cmd))
        {
            qDebug() << query.lastError().text();
            break;
        }

        // bind values
        for (auto index = bindValues.begin(); index != bindValues.end(); ++index)
        {
            query.bindValue(index.key(), index.value());
        }

        // execute command
        if (!query.exec())
        {
            qDebug() << query.lastError().text();
            break;
        }

        // get result
        if (query.isSelect())
        {
            QVariantList buff;
            QVariantMap tmp;
            QSqlRecord record;

            while (query.next())
            {
                record = query.record();
                tmp.clear();
                for (auto index = 0; index != record.count(); ++index)
                {
                    tmp.insert(record.fieldName(index), record.value(index));
                }
                buff.push_back(tmp);
            }
            result = QVariant(buff);
        }
        else
        {
            result = QVariant(true);
        }
    }
    while (false);

    return result;
}

QString JwDatabaseManager::makeCreateTableSQL(QString tableName, QStringList fieldNames)
{
    QString sql = QString("CREATE TABLE IF NOT EXISTS %1 ").arg(tableName);
    sql += "(";
    for (int i=0; i<fieldNames.size(); i++)
    {
        sql += QString("%1%2").arg(fieldNames.at(i)).arg((i<(fieldNames.size() - 1)) ? ", " : "");
    }
    sql += ");";

    return sql;
}

QString JwDatabaseManager::makeDropTableSQL(QString tableName)
{
    QString sql = QString("DROP TABLE IF EXISTS %1;").arg(tableName);
    return sql;
}

QString JwDatabaseManager::makeInsertSQL(QString tableName, QStringList fieldNames, QStringList fieldValues)
{
    QString sql = QString("INSERT INTO %1 ").arg(tableName);

    sql += "(";
    for (int i=0; i<fieldNames.size(); i++)
    {
        QString fieldName = fieldNames.at(i);
        if (fieldName.contains("PRIMARY") || fieldName.contains("AUTOINCREMENT"))
        {
            continue;
        }

        sql += QString("%1%2").arg(fieldName.split(" ").at(0))
                              .arg((i<fieldNames.size() - 1) ? ", " : "");
    }
    sql += ")";

    sql += " VALUES(";
    for (int i=0; i<fieldValues.size(); i++)
    {
        sql += QString("?%1").arg((i < (fieldValues.size() - 1)) ? ", " : "");
    }
    sql += ");";

    return sql;
}

QString JwDatabaseManager::makeDeleteSQL(QString tableName, QString conditions)
{
    QString sql = QString("DELETE FROM %1").arg(tableName);
    if (conditions.isEmpty())
    {
        sql += ";";
        return sql;
    }

    sql += " WHERE " + conditions.trimmed() + ";";
    return sql;
}

QString JwDatabaseManager::makeCountSQL(QString tableName)
{
    QString sql = QString("SELECT COUNT(*) FROM %1").arg(tableName);
    return sql;
}

QString JwDatabaseManager::makeSelectSQL(QString tableName, QString conditions)
{
    QString sql;
    if (conditions.isEmpty())
    {
        sql = QString("SELECT * FROM %1;").arg(tableName);
    }
    else
    {
        sql = QString("SELECT * FROM %1 WHERE %2;").arg(tableName)
                                                   .arg(conditions);
    }

    return sql;
}

QString JwDatabaseManager::makeUpdateSQL(QString tableName, QMap<QString, QString> contents, QString conditions)
{
    QString sql = QString("UPDATE %1 SET ").arg(tableName);
    for (int i=0; i<contents.size(); i++)
    {
        sql += QString("%1 = '%2'%3").arg(contents.keys().at(i))
                                     .arg(contents.value(contents.keys().at(i)))
                                     .arg((i < contents.size() - 1) ? ", " : "");
    }

    if (conditions.isEmpty())
    {
        sql += ";";
    }
    else
    {
        sql += " WHERE " + conditions + ";";
    }

    return sql;
}

QString JwDatabaseManager::makePageQuerySQL(QString tableName, int pageIndex, int rowCountPerPage)
{
    return  QString("SELECT * FROM %1 LIMIT %2 OFFSET %3;").arg(tableName)
                                                           .arg(rowCountPerPage)
                                                           .arg(pageIndex * rowCountPerPage);
}

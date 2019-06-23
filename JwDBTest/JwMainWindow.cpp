#include "JwMainWindow.h"
#include "ui_JwMainWindow.h"

#include <QDebug>
#include "JwDatabaseManager.h"
#include "JwUser.h"

JwMainWindow::JwMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JwMainWindow)
{
    ui->setupUi(this);

    connect(ui->openDBButton, &QPushButton::clicked, [=](){ openDBButtonClicked(); });
    connect(ui->createButton, &QPushButton::clicked, [=](){ createTableButtonClicked(); });
    connect(ui->addButton, &QPushButton::clicked, [=](){ addRecordButtonClicked(); });
    connect(ui->deleteButton, &QPushButton::clicked, [=](){ deleteRecordsButtonClicked(); });
    connect(ui->countButton, &QPushButton::clicked, [=](){ countButttonClicked(); });
    connect(ui->modifyButton, &QPushButton::clicked, [=](){ modifyRecordButtonClicked(); });
    connect(ui->queryButton, &QPushButton::clicked, [=](){ queryRecordsButtonClicked(); });
    connect(ui->dropButton, &QPushButton::clicked, [=](){ dropTableButtonClicked(); });
    connect(ui->closeDBButton, &QPushButton::clicked, [=](){ closeDBButtonClicked(); });

    m_databaseManager = new JwDatabaseManager(this);
    m_user = new JwUser(this);
}

JwMainWindow::~JwMainWindow()
{
    delete ui;
}

void JwMainWindow::openDBButtonClicked()
{
    qDebug() << __FUNCTION__ << " called.";
    m_databaseManager->openDatabase("JwDBTest");
}

void JwMainWindow::createTableButtonClicked()
{
    qDebug() << __FUNCTION__ << " called.";
    m_databaseManager->createTable(m_user->className(), m_user->fieldNames());
}

void JwMainWindow::addRecordButtonClicked()
{
    qDebug() << __FUNCTION__ << " called.";
    m_databaseManager->insertRecord(m_user->className(), m_user->fieldValues(), m_user->fieldValues().size());
}

void JwMainWindow::deleteRecordsButtonClicked()
{
    qDebug() << __FUNCTION__ << " called.";
    m_databaseManager->deleteRecord(m_user->className());
}

void JwMainWindow::countButttonClicked()
{
    qDebug() << __FUNCTION__ << " called.";
    qlonglong count= m_databaseManager->queryCount(m_user->className());
    qDebug() << "count = " << count;
}

void JwMainWindow::queryRecordsButtonClicked()
{
    qDebug() << __FUNCTION__ << " called.";
    qDebug() << "select all =" << m_databaseManager->querySelect(m_user->className(), "username='Bill Gates3'");
}

void JwMainWindow::modifyRecordButtonClicked()
{
    qDebug() << __FUNCTION__ << " called.";
    QMap<QString, QString> newContents;
    newContents.insert("age", "30");
    newContents.insert("email", "xxx@yeah.net");

    m_databaseManager->updateRecord(m_user->className(), newContents, "username = 'Bill Gates1'");
}

void JwMainWindow::dropTableButtonClicked()
{
    qDebug() << __FUNCTION__ << " called.";
    m_databaseManager->dropTable(m_user->className());
}

void JwMainWindow::closeDBButtonClicked()
{
    qDebug() << __FUNCTION__ << " called.";
    m_databaseManager->closeDatabase();
}

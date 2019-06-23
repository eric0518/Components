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

    connect(ui->topPageButton, &QPushButton::clicked, [=]() { topPageButtonClicked(); });
    connect(ui->previousPageButton, &QPushButton::clicked, [=]() { previousPageButtonClicked(); });
    connect(ui->nextPageButton, &QPushButton::clicked, [=]() { nextPageButtonClicked(); });
    connect(ui->bottomPageButton, &QPushButton::clicked, [=]() { bottomPageButtonClicked(); });

    m_databaseManager = new JwDatabaseManager(this);
    m_user = new JwUser(this);

    m_rowCountPerPage = 3;
    m_pageIndex = 0;
    m_pageCount = 0;
}

JwMainWindow::~JwMainWindow()
{
    delete ui;
}

void JwMainWindow::openDBButtonClicked()
{
    qDebug() << __FUNCTION__ << " called.";
    m_databaseManager->openDatabase("JwDBTest");

    //updtePageNumber();
}

void JwMainWindow::createTableButtonClicked()
{
    qDebug() << __FUNCTION__ << " called.";
    m_databaseManager->createTable(m_user->className(), m_user->fieldNames());
}

void JwMainWindow::addRecordButtonClicked()
{
    qDebug() << __FUNCTION__ << " called.";
    m_databaseManager->insertRecord(m_user->className(), m_user->fieldNames(), m_user->fieldValues());
    updtePageNumber();
}

void JwMainWindow::deleteRecordsButtonClicked()
{
    qDebug() << __FUNCTION__ << " called.";
    m_databaseManager->deleteRecord(m_user->className());
    updtePageNumber();
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
    //updtePageNumber();
}

void JwMainWindow::closeDBButtonClicked()
{
    qDebug() << __FUNCTION__ << " called.";
    m_databaseManager->closeDatabase();
}

void JwMainWindow::topPageButtonClicked()
{
    m_pageIndex = 0;
    qDebug() << "Page " << m_pageIndex + 1 << ":" << m_databaseManager->queryPage(m_user->className(), m_pageIndex, m_rowCountPerPage);

    updtePageNumber();
}

void JwMainWindow::previousPageButtonClicked()
{
    m_pageIndex --;
    m_pageIndex = qBound(0, m_pageIndex, m_pageCount - 1);
    qDebug() << "Page " << m_pageIndex + 1 << ":" << m_databaseManager->queryPage(m_user->className(), m_pageIndex, m_rowCountPerPage);

    updtePageNumber();
}

void JwMainWindow::nextPageButtonClicked()
{
    m_pageIndex ++;
    m_pageIndex = qBound(0, m_pageIndex, m_pageCount - 1);
    qDebug() << "Page " << m_pageIndex + 1 << ":" << m_databaseManager->queryPage(m_user->className(), m_pageIndex, m_rowCountPerPage);

    updtePageNumber();
}

void JwMainWindow::bottomPageButtonClicked()
{
    m_pageIndex = m_pageCount - 1;
    qDebug() << "Page " << m_pageIndex + 1 << ":" << m_databaseManager->queryPage(m_user->className(), m_pageIndex, m_rowCountPerPage);

    updtePageNumber();
}

void JwMainWindow::updtePageNumber()
{
    int rowCount = m_databaseManager->queryCount(m_user->className());
    m_pageCount = rowCount / m_rowCountPerPage + ((rowCount % m_rowCountPerPage == 0) ? 0 : 1);

    QString pageNumberText = QString("第%1页/共%2页").arg(m_pageIndex + 1)
                                                    .arg(m_pageCount);

    ui->pageNumberLabel->setText(pageNumberText);
}

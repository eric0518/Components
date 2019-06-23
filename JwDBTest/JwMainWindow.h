#ifndef JWMAINWINDOW_H
#define JWMAINWINDOW_H

#include <QMainWindow>

class JwDatabaseManager;
class JwUser;

namespace Ui {
class JwMainWindow;
}

class JwMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit JwMainWindow(QWidget *parent = 0);
    ~JwMainWindow();

private slots:
    void openDBButtonClicked();
    void createTableButtonClicked();
    void addRecordButtonClicked();
    void deleteRecordsButtonClicked();
    void countButttonClicked();
    void queryRecordsButtonClicked();
    void modifyRecordButtonClicked();
    void dropTableButtonClicked();
    void closeDBButtonClicked();

    void topPageButtonClicked();
    void previousPageButtonClicked();
    void nextPageButtonClicked();
    void bottomPageButtonClicked();
    void updtePageNumber();


private:
    QList<JwUser *> parseUsers(QVariant data);
    void print(QList<JwUser *>);

private:
    Ui::JwMainWindow *ui;
    JwDatabaseManager *m_databaseManager;

    int m_rowCountPerPage;
    int m_pageIndex;
    int m_pageCount;

    JwUser *m_user;
};

#endif // JWMAINWINDOW_H

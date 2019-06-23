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

private:
    Ui::JwMainWindow *ui;
    JwDatabaseManager *m_databaseManager;

    JwUser *m_user;
};

#endif // JWMAINWINDOW_H

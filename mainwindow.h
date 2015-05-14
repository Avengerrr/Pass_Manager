#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "dbfileprocessing.h"
#include <db/connectionmanager.h>
#include "Data/data.h"
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSystemTrayIcon>

namespace PageIndex{
    enum PageIndex{
        FIRST     = 0,
        OPEN_FILE = 1,
        NEW_FILE  = 2,
        MAIN      = 3,
        EDIT      = 4
    };
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    bool              _existsChanges = false;
    ConnectionManager _db;
    Data              _data;
    QSqlQueryModel    _QueryModel;
    QSqlTableModel    _TableModel;
    QSystemTrayIcon   _trayIcon;

    DbFileProcessing *_dbFileProcessing;

    Ui::MainWindow ui;
    bool setPage(PageIndex::PageIndex index);
    QString getTmpDbPath();
    bool connectToDatabase(const QString &filePath);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void HideColumns();
    void setAdaptiveLastColumn();
    void setMainTable();
    void setDataFromUi();
    bool hasSaveChanges();
private slots:
    void on_PButton_First_NewFile_clicked();
    void on_PButton_Open_Cancel_clicked();
    void on_PButton_New_Cancel_clicked();
    void on_PButton_First_OpenFile_clicked();

    void on_PButton_Open_OpenFile_clicked();
    void on_actionExit_triggered();
    void on_actionNewRecord_triggered();
    void on_PushButton_Edit_GeneratePassword_clicked();
    void on_LineEdit_Edit_Password_textEdited(const QString &arg1);
    void on_ToolButton_Edit_Toogle_Password_toggled(bool checked);
    void on_PushButton_Edit_Save_clicked();
    void on_PushButton_Edit_Cancel_clicked();
    void on_actionCreateDatabase_triggered();
    void on_actionOpenDatabase_triggered();
    void on_actionDeleteRecord_triggered();
    void on_PButton_New_CreateDatabase_clicked();
    void on_actionSaveDatabase_triggered();
    void on_actionEditRecord_triggered();

    void on_TButton_New_ChooseFile_clicked();

    void on_TButton_Open_ChooseFile_clicked();

protected:
    void closeEvent(QCloseEvent *);
};

#endif // MAINWINDOW_H

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
        EDIT      = 4,
        LOCK      = 5
    };
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    bool              _existsChanges = false;
    ConnectionManager _db;
    Data              _data;
    QSqlQueryModel    _modelMainTable;
    QSqlQueryModel    _modelGroupsList;
    QSystemTrayIcon   _trayIcon;
    QByteArray        _passwordHash;

    DbFileProcessing *_dbFileProcessing = nullptr;

    Ui::MainWindow ui;
    bool setPage(PageIndex::PageIndex index);
    QString getTmpDbPath();
    bool connectToDatabase(const QString &filePath);

    bool goPage( const PageIndex::PageIndex index );
    bool goPage_FIRST();
    bool goPage_NEW_FILE();
    bool goPage_OPEN_FILE();
    bool goPage_MAIN();
    bool goPage_EDIT();
    bool goPage_LOCK();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void HideColumns();
    void setAdaptiveLastColumn();
    void updateMainTable();
    void setDataFromUi();
    bool hasSaveChanges();
    bool isFieldsComplete_New();
    bool isFieldsComplete_Open();
    void updateSectionsList();
    QByteArray getPasswordHash(const QString &password);
    QByteArray getSaltForPassword(const QString &password);
    void createEmptyFile(const QString &path);
    void clearEditPageFields();
    void loadCharGroupsUserSettings();
    void saveCharGroupsUserSettings();
    void clearFieldsOpenFilePage();
    bool isClearEditPageFields();
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
    void on_LineEdit_New_ConfirmPassword_textEdited(const QString &arg1);
    void on_LineEdit_New_Password_textEdited(const QString &arg1);
    void on_LineEdit_New_FilePath_textEdited(const QString &arg1);
    void on_LineEdit_Open_Password_textEdited(const QString &arg1);
    void on_LineEdit_Open_FilePath_textChanged(const QString &arg1);
    void on_TButton_Open_ShowPassword_toggled(bool checked);
    void on_TButton_New_ShowPassword_toggled(bool checked);
    void on_TButton_Lock_ShowPassword_toggled(bool checked);
    void on_actionLock_triggered();
    void on_PButton_Lock_Unclock_clicked();
    void on_TreeView_Main_Category_clicked(const QModelIndex &);
    void on_ComboBox_Edit_Group_currentTextChanged(const QString &text);

    void on_LineEdit_Edit_Title_editingFinished();

    void on_LineEdit_Edit_Login_editingFinished();

    void on_LineEdit_Edit_Password_editingFinished();

protected:
    void closeEvent(QCloseEvent *);
};

#endif // MAINWINDOW_H

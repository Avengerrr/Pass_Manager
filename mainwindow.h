#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

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
    Ui::MainWindow ui;
    bool setPage(PageIndex::PageIndex index);

public:
    explicit MainWindow(QWidget *parent = 0);

private slots:
    void on_PButton_First_NewFile_clicked();
    void on_PButton_Open_Cancel_clicked();
    void on_PButton_New_Cancel_clicked();
    void on_PButton_First_OpenFile_clicked();

    void on_PButton_Open_OpenFile_clicked();
    void on_actionExit_triggered();
    void on_actionNewRecord_triggered();
    void on_toolButton_toggled(bool checked);
    void on_PushButton_Edit_GeneratePassword_clicked();
    void on_LineEdit_Edit_Password_textEdited(const QString &arg1);
};

#endif // MAINWINDOW_H

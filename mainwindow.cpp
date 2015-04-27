#include "mainwindow.h"
#include <QDebug>
#include "cryptfiledevice.h"
#include "passwordgenerator.h"
#include <db/connectionmanager.h>
#include <db/querysmanager.h>

bool MainWindow::setPage(PageIndex::PageIndex index)
{
    ui.StackedWidget->setCurrentIndex( index );
    return true;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
    ui.MainMenuBar->setVisible( false );
    ui.MainToolBar->setVisible( false );
    setPage( PageIndex::FIRST );

    ConnectionManager db;
    db.open();
    QuerysManager::createTables();

//    QFile file("C:/Users/Максим/Desktop/manda.txt");
//    CryptFileDevice cryptFileDevice( &file, "132", "123" );

//    if ( ! cryptFileDevice.open(QIODevice::ReadWrite) )
//    {
//        qDebug() << "File is not open! Fuck YOU!";
//    }

//    QByteArray data = "Hello AES";
//    cryptFileDevice.write( data );
//    cryptFileDevice.reset();
//    qDebug() << cryptFileDevice.readAll();

//    cryptFileDevice.close();
}

void MainWindow::on_PButton_First_NewFile_clicked()
{
    setPage( PageIndex::NEW_FILE );
}

void MainWindow::on_PButton_Open_Cancel_clicked()
{
    setPage( PageIndex::FIRST );
}

void MainWindow::on_PButton_New_Cancel_clicked()
{
    setPage( PageIndex::FIRST );
}

void MainWindow::on_PButton_First_OpenFile_clicked()
{
    setPage( PageIndex::OPEN_FILE );
}

void MainWindow::on_PButton_Open_OpenFile_clicked()
{
    // Open File here

    setPage( PageIndex::MAIN );
    ui.MainMenuBar->setVisible( true );
    ui.MainToolBar->setVisible( true );
}

void MainWindow::on_actionExit_triggered()
{
    qApp->exit(0);
}

void MainWindow::on_actionNewRecord_triggered()
{
    setPage( PageIndex::EDIT );
}

void MainWindow::on_toolButton_toggled(bool checked)
{
    return;
}


void MainWindow::on_PushButton_Edit_GeneratePassword_clicked()
{
    int type = 0;
    int length = 0;

    length = ui.SpinBox_Edit_PasswordLenght->value();

    if( ui.CheckBox_Edit_Pas_ChType_Lower->isChecked() )
        type |= PasswordGenerator::Lower;
    if( ui.CheckBox_Edit_Pas_ChType_Upper->isChecked() )
        type |= PasswordGenerator::Upper;
    if( ui.CheckBox_Edit_Pas_ChType_Underline->isChecked() )
        type |= PasswordGenerator::Underline;
    if( ui.CheckBox_Edit_Pas_ChType_Minus->isChecked() )
        type |= PasswordGenerator::Minus;
    if( ui.CheckBox_Edit_Pas_ChType_Special->isChecked() )
        type |= PasswordGenerator::Special;
    if( ui.CheckBox_Edit_Pas_ChType_Numbers->isChecked() )
        type |= PasswordGenerator::Numbers;



    QString password = PasswordGenerator::getPassword(type, length);

    ui.ProgressBar_Edit_PasswordQuality->setValue( PasswordGenerator::entropy(password) );
    ui.LineEdit_Edit_Password->setText( password );
    ui.LineEdit_Edit_ConfirmPassword->setText( password );
}


void MainWindow::on_LineEdit_Edit_Password_textEdited(const QString &password)
{
     ui.ProgressBar_Edit_PasswordQuality->setValue( PasswordGenerator::entropy(password) );
}

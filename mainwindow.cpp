#include "mainwindow.h"

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

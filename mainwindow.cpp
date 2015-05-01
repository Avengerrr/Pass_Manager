#include "mainwindow.h"
#include <QDebug>
#include "cryptfiledevice.h"
#include "passwordgenerator.h"

#include <db/querysmanager.h>

/*! \~russian
 * \brief Метод для переключения страничной навигации
 * \param index - индекс необходимой страницы из перечисления PageIndex
 * \return Всегда истинный!
 */
bool MainWindow::setPage(PageIndex::PageIndex index)
{
    ui.StackedWidget->setCurrentIndex( index );
    return true;
}

/*!
 * \brief Конструктор Lego
 * \param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
    ui.MainMenuBar->setVisible( false );
    ui.MainToolBar->setVisible( false );
    setPage( PageIndex::FIRST );
}

/*!
 * \brief Деструктор Lego
 */
MainWindow::~MainWindow(){
    _db.close();

    /// \todo Crypt file and save
    /// \todo remove db file from temporary directory
    /// \todo YAY!

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

/*!
 * \brief Обработчик клика на кнопку Создания нового файла
 * переключает страницу в стак-виджете на страницу создания нового файла
 */
void MainWindow::on_PButton_First_NewFile_clicked()
{
    setPage( PageIndex::NEW_FILE );
}

/*!
 * \brief Обработчик клика на кнопку возврата со страницы открытия файла
 * Переключает страницу в стак-виджете на страницу приветствия
 */
void MainWindow::on_PButton_Open_Cancel_clicked()
{
    setPage( PageIndex::FIRST );
}

/*!
 * \brief Обработчки клика на кнопку возврата со страницы создания нового файла
 * Переключает страницу в стак-видежете на страницу приветствия
 */
void MainWindow::on_PButton_New_Cancel_clicked()
{
    setPage( PageIndex::FIRST );
}

/*!
 * \brief Обработчик клика на кнопку открытия файла
 * Переключает страницу в стак-виджете на страницу открытия файла
 */
void MainWindow::on_PButton_First_OpenFile_clicked()
{
    setPage( PageIndex::OPEN_FILE );
}

/*!
 * \brief Обработчик клика на кнопку истинного открытия файла
 * Собственно берёт и дерзко его открывает!!!
 */
void MainWindow::on_PButton_Open_OpenFile_clicked()
{
    _filePath = ui.LineEdit_New_FilePath->text();
    _db.open( QString::null ); /// \todo decrypt file and resave to database
    QuerysManager::createTables();

    setPage( PageIndex::MAIN );
    ui.MainMenuBar->setVisible( true );
    ui.MainToolBar->setVisible( true );
}

/*!
 * \brief Обработчик действия выход из приложения
 * Берёт и закрывает приложение, ни спросив них*я!
 */
void MainWindow::on_actionExit_triggered()
{
    qApp->exit(0);
}

/*!
 * \brief Обработчик действия добавления новой записи
 * Переключает страницу на страницу добавления/редактирования новой записи
 * устанавливает режим редактирования в false для _data
 */
void MainWindow::on_actionNewRecord_triggered()
{
    setPage( PageIndex::EDIT );
    _data.setEditMode(false);
}

/*!
 * \brief Обработчик клика на кнопку генерации пароля
 * Вычисляет тип пароля в соответствии с установленными флажками
 * Генерирует пароль пользуясь классом PasswordGenerator
 * Устанавливает пароль в 2 LineEdit
 */
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

/*!
 * \brief Метод обрабатывает ввод пароля в поле ввода
 * Вычисляет и устанавливает в виджет прогресс-бара значение
 * энтропии посредством класса PasswordGenerator
 * \param password - пароль, текст в LineEdit
 */
void MainWindow::on_LineEdit_Edit_Password_textEdited(const QString &password)
{
     ui.ProgressBar_Edit_PasswordQuality->setValue( PasswordGenerator::entropy(password) );
}

/*!
 * \brief Метод обрабатывает кнопку-переключатель отображения/скрытия пароля
 * Переключает метод отображения в полях ввода и подтверждения пароля
 * \param checked - состяние кнопки-переключателя
 */
void MainWindow::on_ToolButton_Edit_Toogle_Password_toggled(bool checked)
{
    if( checked ){
        ui.LineEdit_Edit_Password->setEchoMode( QLineEdit::Normal );
        ui.LineEdit_Edit_ConfirmPassword->setEchoMode( QLineEdit::Normal );
    }else{
        ui.LineEdit_Edit_Password->setEchoMode( QLineEdit::Password );
        ui.LineEdit_Edit_ConfirmPassword->setEchoMode( QLineEdit::Password );
    }
}

/*!
 * \brief Метод обрабатывает клик на кнопку сохранения записи
 * заполняет объект данными \todo вынести в отдельный метод
 * и вызывает метод Data::save() - для сохранения данных в БД
 * Переключает страницу на PageIndex::MAIN
 */
void MainWindow::on_PushButton_Edit_Save_clicked()
{
    _data.setGroup( ui.ComboBox_Edit_Group->currentText() );
    _data.setResource( ui.LineEdit_Edit_Title->text() );
    _data.setUrl( ui.LineEdit_Edit_Url->text() );
    _data.setLogin( ui.LineEdit_Edit_Login->text() );
    _data.setPassword( ui.LineEdit_Edit_Password->text() );
    _data.setAnswer( ui.LineEdit_Edit_Answer->text() );
    _data.setCreateTime( QString::number( QDateTime::currentMSecsSinceEpoch() ) );
    _data.setPassLifeTime( QString::number( ui.DateTimeEdit_Edit_Pas_PassOutdate->dateTime().toMSecsSinceEpoch() ) );
    _data.setPhone( ui.LineEdit_Edit_Phone->text() );
    _data.setDescription( ui.PlainTextEdit_Edit_Comment->toPlainText() );

    _data.save();
    setPage( PageIndex::MAIN );
}

/*!
 * \brief Метод обрабатывает нажатие на кнопку возврата со страницы редактирования/добавления записи
 * переключает страницу в стак-виджете на PageIndex::MAIN
 */
void MainWindow::on_PushButton_Edit_Cancel_clicked()
{
    setPage( PageIndex::MAIN );
}

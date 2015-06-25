#include "mainwindow.h"
#include <QDebug>
#include "cryptfiledevice.h"
#include "passwordgenerator.h"


#include <db/querysmanager.h>
#include <QHeaderView>

#include <QSqlRecord>
#include <QSqlResult>
#include <QString>
#include <QCryptographicHash>
#include <QDir>
#include <QStandardPaths>
#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>
#include <QSqlError>
#include <QClipboard>
#include <QDesktopServices>

#include "aboutdialog.h"
#include "helpdialog.h"

/*
    my.dbx -> read & decrypt -> write as SQLiteDB (achtung)
    NewRecor   -> write  to SQLiteDB;
    EditRecord <- read from SQLiteDB;
    SQliteDB -> read & encrypt -> write as my.dbx
// */

/// \todo Поиск
/// \todo Настройки
/// \todo Открытие недавних +/-
/// \todo ???

const QString warningStyle("border: 1px solid #CC0033");

namespace Options {
    const QString LAST_FILE_PATH("LastFilePath");
    const QString BUFFER_SIZE("ReadWriteBufferSize");
    const QString PASSWORD_HASH_CYCLES("PasswordHashCycles");
    const QString AES_ENCRYPT_ROUNDS("AesEncryptRounds");

    const QString LANGUAGE("Language");

    const QString RECENT_DOCUMENTS_LIST("RecentDocumentsList");

    namespace CharGroups {
        const QString GROUP_PREFIX("CharGroups/");
        const QString UPPER(    CharGroups::GROUP_PREFIX+"UpperLettersState");
        const QString LOWER(    CharGroups::GROUP_PREFIX+"LowerLettersState");
        const QString SPECIAL(  CharGroups::GROUP_PREFIX+"SpecialLettersState");
        const QString MINUS(    CharGroups::GROUP_PREFIX+"MinusLettersState");
        const QString NUMBERS(  CharGroups::GROUP_PREFIX+"NumbersLettersState");
        const QString UNDERLINE(CharGroups::GROUP_PREFIX+"UnderlineLettersState");
    }
}

namespace DefaultValues {
    const int BUFFER_SIZE(51200);
    const int PASSWORD_HASH_CYCLES(3);
    const int AES_ENCRYPT_ROUNDS(10000);

    const QStringList RECENT_DOCUMENTS_LIST;

    namespace CharGroups {
        const bool UPPER    (true);
        const bool LOWER    (true);
        const bool SPECIAL  (true);
        const bool MINUS    (true);
        const bool NUMBERS  (true);
        const bool UNDERLINE(true);
    }
}

/*! \~russian
 * \brief Метод для переключения страничной навигации
 * \param index - индекс необходимой страницы из перечисления PageIndex
 * \return Всегда истинный!
 */
bool MainWindow::setPage(PageIndex::PageIndex index)
{
    ui.StackedWidget->setCurrentIndex( index );
    if( index == PageIndex::MAIN ){
        ui.MainMenuBar->setVisible( true );
        ui.MainToolBar->setVisible( true );
        ui.StatusBar->setVisible(   true );

        _sessionTimer.start( _sessionTime*60*1000 );
//        QTimer::singleShot(time*60*1000, this, SLOT(sessionTimeout()) );
    }else if(    index == PageIndex::FIRST
               || index == PageIndex::OPEN_FILE
               || index == PageIndex::NEW_FILE
               || index == PageIndex::LOCK){

        ui.MainMenuBar->setVisible( false );
        ui.MainToolBar->setVisible( false );
        ui.StatusBar->setVisible(   false );
    } else if( index == PageIndex::EDIT ){
        ui.DateTimeEdit_Edit_Pas_PassOutdate->setDateTime( QDateTime::currentDateTime().addMonths(1) );
    }
    return true;
}

QString MainWindow::getTmpDbPath()
{
    return QStandardPaths::writableLocation( QStandardPaths::TempLocation )
            + QDir::separator()
            + QString::number( QDateTime::currentMSecsSinceEpoch() );
}

bool MainWindow::connectToDatabase(const QString &filePath)
{
    bool success = false;
    success = _db.open( filePath );
    success = success && QuerysManager::createTables();

    return success;
}

void MainWindow::setDataToInfoPanel(const Data &data)
{
    QDateTime create = QDateTime::fromMSecsSinceEpoch( data.createTime().toLongLong() );
    QDateTime life   = QDateTime::fromMSecsSinceEpoch( data.passLifeTime().toLongLong() );

    QString cssExpired;
    if( life <= QDateTime::currentDateTime() ){
        cssExpired = "color:red";
    }

    QString html,
            htmlHeader,
            htmlTable,
            htmlFooter;
    QString cssHeader;
    cssHeader = "background-color: #888; color: #EEE; padding-left: 4px;";

    htmlHeader = "<div style='"+ cssHeader +"'>"+ data.resource().toHtmlEscaped() +"</div>";

    QString htmlTableRow1 = "<tr>"
                              "<td width='50%'>"
                                "<strong>" + tr("Group:")+ "</strong> " + data.group().toHtmlEscaped() +
                              "</td>"
                              "<td width='50%'>"
                                "<strong>" + tr("Creation:")+ "</strong> " + create.toString("dd/MM/yyyy") +
                              "</td>"
                            "</tr>";
    QString htmlTableRow2 = "<tr>"
                              "<td>"
                                "<strong>" + tr("Login:")+ "</strong> " + data.login().toHtmlEscaped() +
                              "</td>"
                              "<td>"
                                "<strong>" + tr("Expiration:")+ "</strong> " + "<span style='"+ cssExpired +"'>" + life.toString("dd/MM/yyyy") + "</span>" +
                              "</td>"
                            "</tr>";
    QString htmlTableRow3 = "<tr>"
                              "<td>"
                                "<strong>" + tr("URL:")+ "</strong> " + data.url().toHtmlEscaped() +
                              "</td>"
                              "<td>"
                                "<strong>" + tr("Password:")+ "</strong> " + data.password().toHtmlEscaped() +
                              "</td>"
                            "</tr>";

    htmlTable  = "<table>"+ htmlTableRow1 + htmlTableRow2 + htmlTableRow3 +"</table>";
    htmlFooter = "<strong>"+tr("Comment:")+"</strong> "+ data.description();

    html = htmlHeader + htmlTable + htmlFooter;
    ui.Label_Main_RecordInfo->setText( html );
}

bool MainWindow::goPage(const PageIndex::PageIndex index)
{
    switch (index) {
    case PageIndex::FIRST:
        goPage_FIRST();
        break;
    case PageIndex::NEW_FILE:
        goPage_NEW_FILE();
        break;
    case PageIndex::OPEN_FILE:
        goPage_OPEN_FILE();
        break;
    case PageIndex::MAIN:
        goPage_MAIN();
        break;
    case PageIndex::EDIT:
        goPage_EDIT();
        break;
    case PageIndex::LOCK:
        goPage_LOCK();
        break;
    default:
        qWarning() << "PageIndex is not exists";
        break;
    }
    return true;
}

bool MainWindow::goPage_FIRST()
{
    ui.MainMenuBar->setVisible( false );
    ui.MainToolBar->setVisible( false );
    return setPage( PageIndex::FIRST );
}

bool MainWindow::goPage_NEW_FILE()
{
    ui.MainMenuBar->setVisible( false );
    ui.MainToolBar->setVisible( false );
    return setPage( PageIndex::NEW_FILE );
}

bool MainWindow::goPage_OPEN_FILE()
{
    ui.MainMenuBar->setVisible( false );
    ui.MainToolBar->setVisible( false );
    QSettings cfg;
    ui.LineEdit_Open_FilePath->setText( cfg.value( Options::LAST_FILE_PATH, "" ).toString() );
    if( cfg.contains( Options::LAST_FILE_PATH ) )
        ui.LineEdit_Open_Password->setFocus();
    return setPage( PageIndex::OPEN_FILE );
}

bool MainWindow::goPage_MAIN()
{
    ui.MainMenuBar->setVisible( true );
    ui.MainToolBar->setVisible( true );
    return setPage( PageIndex::MAIN );
}

bool MainWindow::goPage_EDIT()
{
    ui.MainMenuBar->setVisible( true );
    ui.MainToolBar->setVisible( true );
    return setPage( PageIndex::EDIT );
}

bool MainWindow::goPage_LOCK()
{
    ui.MainMenuBar->setVisible( false );
    ui.MainToolBar->setVisible( false );
    return setPage( PageIndex::LOCK );
}

/*!
 * \brief Конструктор Lego
 * \param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QSettings cfg;
    QLocale::Language language = static_cast<QLocale::Language>( cfg.value( Options::LANGUAGE, QLocale::Russian ).toInt());
    if( language == 0 ){
        language = QLocale::system().language();
    }



    ui.setupUi(this);

    if( language == QLocale::Russian ){
        emit ui.actionRussian->triggered( true );
        ui.TButton_First_LangSwitch->setText( "en" );
    }else{
        emit ui.actionEnglish->triggered( true );
        ui.TButton_First_LangSwitch->setText( "ru" );
    }



    ui.splitter_2->setStretchFactor(0, 1);
    ui.splitter_2->setStretchFactor(1, 3);


    if( cfg.contains( Options::LAST_FILE_PATH ) ){
        setPage( PageIndex::OPEN_FILE );
        emit ui.actionOpenDatabase->triggered();
    }else{
        setPage( PageIndex::FIRST );
    }
    ui.TreeView_Main_Category->setModel( &_modelGroupsList );
    ui.TableView_Main_Records->setModel( &_modelMainTable );

    // Load recent documents list
    _recentDocuments.setRecendDocuments( cfg.value(Options::RECENT_DOCUMENTS_LIST, DefaultValues::RECENT_DOCUMENTS_LIST).toStringList() );
    QMenu *recentDocuments = new QMenu("RecentDocumentsList", this);
    QStringList recentDocList = _recentDocuments.getRecentDocuments();
    foreach (QString doc, recentDocList) {
        recentDocuments->addAction( doc );
    }
    ui.actionOpenRecentDatabase->setMenu( recentDocuments );

    ui.StatusBar->addWidget( &_statusBar_countRecords );

    connect( &_sessionTimer, SIGNAL(timeout()), this, SLOT(sessionTimeout()) );
}

void MainWindow::closeEvent(QCloseEvent *){
    QSettings cfg;
    cfg.setValue(Options::RECENT_DOCUMENTS_LIST, _recentDocuments.getRecentDocuments() );
    _db.close();
    if( _existsChanges && hasSaveChanges() ){
        _dbFileProcessing->saveEncryptFile();
    }
    _existsChanges = false;
    _db.remove();
}

/*!
 * \brief Деструктор Lego
 */
MainWindow::~MainWindow(){
}

/*!
 * \brief Обработчик клика на кнопку Создания нового файла
 * переключает страницу в стак-виджете на страницу создания нового файла
 */
void MainWindow::on_PButton_First_NewFile_clicked()
{
    /// \todo delete that
    _trayIcon.setIcon( QIcon( ":/images/logotip.png" ) );
    _trayIcon.show();
    _trayIcon.showMessage("Hello", "Welcome To PassMan");
    setPage( PageIndex::NEW_FILE );
}

/*!
 * \brief Обработчик клика на кнопку возврата со страницы открытия файла
 * Переключает страницу в стак-виджете на страницу приветствия
 */
void MainWindow::on_PButton_Open_Cancel_clicked()
{
    goPage( PageIndex::FIRST );
    QSettings cfg;
    cfg.remove( Options::LAST_FILE_PATH );
}

/*!
 * \brief Обработчки клика на кнопку возврата со страницы создания нового файла
 * Переключает страницу в стак-видежете на страницу приветствия
 */
void MainWindow::on_PButton_New_Cancel_clicked()
{
    goPage( PageIndex::FIRST );
}

/*!
 * \brief Обработчик клика на кнопку открытия файла
 * Переключает страницу в стак-виджете на страницу открытия файла
 */
void MainWindow::on_PButton_First_OpenFile_clicked()
{
    goPage( PageIndex::OPEN_FILE );
}

/*!
 * \brief Метод для скрытия колонок в таблице
 */
void MainWindow::HideColumns()
{
    const int id = 0;
    ui.TableView_Main_Records->hideColumn( id );
//    ui.TableView_Main_Records->hideColumn( _modelMainTable.fieldIndex(DataTable::Fields::PassGroup) );
//    ui.TableView_Main_Records->hideColumn( _modelMainTable.fieldIndex(DataTable::Fields::Description) );
//    ui.TableView_Main_Records->hideColumn( _modelMainTable.fieldIndex(DataTable::Fields::CreateTime) );
//    ui.TableView_Main_Records->hideColumn( _modelMainTable.fieldIndex(DataTable::Fields::PassLifeTime) );
//    ui.TableView_Main_Records->hideColumn( _modelMainTable.fieldIndex(DataTable::Fields::Mail) );
//    ui.TableView_Main_Records->hideColumn( _modelMainTable.fieldIndex(DataTable::Fields::Phone) );
//    ui.TableView_Main_Records->hideColumn( _modelMainTable.fieldIndex(DataTable::Fields::Answer) );
}

/*!
 * \brief Метод делает последнюю колонку адаптивной
 */
void MainWindow::setAdaptiveLastColumn()
{
    ui.TableView_Main_Records->horizontalHeader()->setStretchLastSection(true);
}

/*!
 * \brief Метод производит настройка главной таблице
 * Устанавливает модель
 * Соеденяет сигналы и слоты
 * Скрывает ненужные колонки
 * Настраивает растяжение колонок
 */
void MainWindow::updateMainTable()
{
    QString group = ui.TreeView_Main_Category->currentIndex().data(Qt::DisplayRole).toString();

    QStringList fields;
    fields.append(DataTable::Fields::id);
    fields.append(DataTable::Fields::Resource);
    fields.append(DataTable::Fields::Url);
    fields.append(DataTable::Fields::Login);
    fields.append(DataTable::Fields::Password);

    QString sql("SELECT %1 FROM %3 WHERE %4='%5'");
    sql = sql.arg( fields.join(", "),
                   DataTable::tableName,
                   DataTable::Fields::PassGroup,
                   group );
    _modelMainTable.setQuery( sql );
    setAdaptiveLastColumn();

    _modelMainTable.setHeaderData(1, Qt::Horizontal, tr("Title"), Qt::DisplayRole);
    _modelMainTable.setHeaderData(2, Qt::Horizontal, tr("URL"), Qt::DisplayRole);
    _modelMainTable.setHeaderData(3, Qt::Horizontal, tr("Login"), Qt::DisplayRole);
    _modelMainTable.setHeaderData(4, Qt::Horizontal, tr("Password"), Qt::DisplayRole);
}

/*!
 * \brief Обработчик клика на кнопку истинного открытия файла
 * Собственно берёт и дерзко его открывает!!!
 */
void MainWindow::updateSectionsList()
{
    QString sql("SELECT `%1` FROM %2 GROUP BY %1");
    sql = sql.arg( DataTable::Fields::PassGroup, DataTable::tableName );
    _modelGroupsList.setQuery( sql );

    _modelGroupsList.setHeaderData(0, Qt::Horizontal, tr("Groups"), Qt::DisplayRole);
}

void MainWindow::clearFieldsOpenFilePage()
{
    ui.LineEdit_Open_FilePath->clear();
    ui.LineEdit_Open_Password->clear();
}

QString MainWindow::countRecords()
{
    QSqlQuery query;
    QString sqlCount("SELECT COUNT(*) AS rCount FROM %1");
    sqlCount = sqlCount.arg(DataTable::tableName);
    if( ! query.exec(sqlCount) ){
        qCritical() << "Cannot counted records.";
    }
    query.first();
    QString recCount = query.value("rCount").toString();

    return recCount;
}

void MainWindow::sessionTimeout()
{
    emit ui.actionLock->triggered();
}

void MainWindow::on_PButton_Open_OpenFile_clicked()
{
    QSettings cfg;

    int        bufferSize    = cfg.value( Options::BUFFER_SIZE, DefaultValues::BUFFER_SIZE).toInt();
    QString    achtungDbPath = getTmpDbPath();
    QString    encDbPath     = ui.LineEdit_Open_FilePath->text();
    QByteArray password      = getPasswordHash( ui.LineEdit_Open_Password->text() );
    QByteArray salt          = getSaltForPassword( ui.LineEdit_Open_Password->text() );
               _sessionTime  = ui.SpinBox_Open_sessionTimeOut->value();

    if( _dbFileProcessing ){
        qWarning() << "Чёта ты не в тот район забрёл...";
        delete _dbFileProcessing;
        _dbFileProcessing = nullptr;
    }
    _dbFileProcessing = new DbFileProcessing(achtungDbPath, encDbPath, password, salt, bufferSize);
    if( ! _dbFileProcessing->openEncryptFile() ){
        ui.Label_Open_Error->setText( tr("Cannot open encrypted file") );
        delete _dbFileProcessing;
        _dbFileProcessing = nullptr;
        return;
    }

    _passwordHash = password;
    connectToDatabase(achtungDbPath);
    setPage( PageIndex::MAIN );
    _modelGroupsList.clear();
    updateMainTable();
    updateSectionsList();
    HideColumns();


    cfg.setValue( Options::LAST_FILE_PATH , encDbPath );
    clearFieldsOpenFilePage();
    _recentDocuments.addLastDocument( encDbPath );


    QString recCount = countRecords();
    _statusBar_countRecords.setText( tr("Record count: ") + recCount );
}

/*!
 * \brief Обработчик действия выход из приложения
 * Берёт и закрывает приложение, \todo не спросив них*я!
 */
void MainWindow::on_actionExit_triggered()
{
    QSettings cfg;
    cfg.setValue( Options::RECENT_DOCUMENTS_LIST, _recentDocuments.getRecentDocuments() );
    qApp->exit(0);
}

/*!
 * \brief Обработчик действия добавления новой записи
 * Переключает страницу на страницу добавления/редактирования новой записи
 * устанавливает режим редактирования в false для _data
 */
void MainWindow::loadCharGroupsUserSettings()
{
    QSettings cfg;
    ui.CheckBox_Edit_Pas_ChType_Upper    ->setChecked( cfg.value(Options::CharGroups::UPPER,     DefaultValues::CharGroups::UPPER    ).toBool() );
    ui.CheckBox_Edit_Pas_ChType_Lower    ->setChecked( cfg.value(Options::CharGroups::LOWER,     DefaultValues::CharGroups::LOWER    ).toBool() );
    ui.CheckBox_Edit_Pas_ChType_Special  ->setChecked( cfg.value(Options::CharGroups::SPECIAL,   DefaultValues::CharGroups::SPECIAL  ).toBool() );
    ui.CheckBox_Edit_Pas_ChType_Minus    ->setChecked( cfg.value(Options::CharGroups::MINUS,     DefaultValues::CharGroups::MINUS    ).toBool() );
    ui.CheckBox_Edit_Pas_ChType_Numbers  ->setChecked( cfg.value(Options::CharGroups::NUMBERS,   DefaultValues::CharGroups::NUMBERS  ).toBool() );
    ui.CheckBox_Edit_Pas_ChType_Underline->setChecked( cfg.value(Options::CharGroups::UNDERLINE, DefaultValues::CharGroups::UNDERLINE).toBool() );
}

void MainWindow::on_actionNewRecord_triggered()
{
    loadCharGroupsUserSettings();

    ui.ComboBox_Edit_Group->setModel( &_modelGroupsList );

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

void MainWindow::getDataFromUi()
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
}

bool MainWindow::hasSaveChanges()
{
    QMessageBox::StandardButton btn = QMessageBox::question(this,
                                                            tr("Exit"),
                                                            tr("Save changes?"),
                                                            QMessageBox::Yes | QMessageBox::No);

    return (btn == QMessageBox::Yes);
}

bool MainWindow::isFieldsComplete_New()
{
    if( ui.LineEdit_New_FilePath->text().isEmpty() ){
        ui.Label_New_Error->setText( tr("Enter a new file path") );
        return false;
    }

    if( ui.LineEdit_New_Password->text() != ui.LineEdit_New_ConfirmPassword->text() ){
        ui.Label_New_Error->setText( tr("Paswords is not identical") );
        return false;
    }

    if(    ui.LineEdit_New_Password->text().isEmpty()
        || ui.LineEdit_New_ConfirmPassword->text().isEmpty() ){
        ui.Label_New_Error->setText( tr("Empty password is not allowed") );
        return false;
    }

    ui.Label_New_Error->clear();
    return true;
}

bool MainWindow::isFieldsComplete_Open()
{
    QString filePath = ui.LineEdit_Open_FilePath->text();
    if( filePath.isEmpty() ){
        ui.Label_Open_Error->setText( tr("Choose a file") );
        return false;
    }

    if( ! QFile::exists( filePath )
       || QFileInfo( filePath ).isDir() ){

        ui.Label_Open_Error->setText( tr("Choosen file is not exists") );
        return false;
    }

    if( ui.LineEdit_Open_Password->text().isEmpty() ){
        ui.Label_Open_Error->setText( tr("Empty password is not allowed") );
        return false;
    }

    ui.Label_Open_Error->clear();
    return true;
}

/*!
 * \brief Метод обрабатывает клик на кнопку сохранения записи
 * заполняет объект данными и вызывает метод
 * Data::save() - для сохранения данных в БД
 * Переключает страницу на PageIndex::MAIN
 */
void MainWindow::clearEditPageFields()
{
    ui.LineEdit_Edit_Title->clear();
    ui.LineEdit_Edit_Answer->clear();
    ui.LineEdit_Edit_ConfirmPassword->clear();
    ui.LineEdit_Edit_Login->clear();
    ui.LineEdit_Edit_Password->clear();
    ui.LineEdit_Edit_Phone->clear();
    ui.LineEdit_Edit_Url->clear();
    ui.PlainTextEdit_Edit_Comment->clear();
    ui.ProgressBar_Edit_PasswordQuality->setValue(0);
    ui.DateTimeEdit_Edit_Pas_PassOutdate->setDate( QDate::currentDate() );
}

void MainWindow::saveCharGroupsUserSettings()
{
    QSettings cfg;
    cfg.setValue(Options::CharGroups::UPPER     , ui.CheckBox_Edit_Pas_ChType_Upper->isChecked() );
    cfg.setValue(Options::CharGroups::LOWER     , ui.CheckBox_Edit_Pas_ChType_Lower->isChecked() );
    cfg.setValue(Options::CharGroups::SPECIAL   , ui.CheckBox_Edit_Pas_ChType_Special->isChecked() );
    cfg.setValue(Options::CharGroups::MINUS     , ui.CheckBox_Edit_Pas_ChType_Minus->isChecked() );
    cfg.setValue(Options::CharGroups::NUMBERS   , ui.CheckBox_Edit_Pas_ChType_Numbers->isChecked() );
    cfg.setValue(Options::CharGroups::UNDERLINE , ui.CheckBox_Edit_Pas_ChType_Underline->isChecked() );
}

bool MainWindow::isClearEditPageFields()
{
    bool result = false;
    if( ui.ComboBox_Edit_Group->currentText().isEmpty() ){
        ui.ComboBox_Edit_Group->setFocus();
        ui.ComboBox_Edit_Group->setStyleSheet(warningStyle);
        result = true;
    }else{
        ui.ComboBox_Edit_Group->setStyleSheet("");
    }
    if( ui.LineEdit_Edit_Title->text().isEmpty() ){
        ui.LineEdit_Edit_Title->setFocus();
        ui.LineEdit_Edit_Title->setStyleSheet(warningStyle);
        result = true;
    }else{
        ui.LineEdit_Edit_Title->setStyleSheet("");
    }
    if( ui.LineEdit_Edit_Login->text().isEmpty() ){
        ui.LineEdit_Edit_Login->setFocus();
        ui.LineEdit_Edit_Login->setStyleSheet(warningStyle);
        result = true;
    }else{
        ui.LineEdit_Edit_Login->setStyleSheet("");
    }
    if( ui.LineEdit_Edit_Password->text().isEmpty() ){
        ui.LineEdit_Edit_Password->setFocus();
        ui.LineEdit_Edit_Password->setStyleSheet(warningStyle);
        result = true;
    }else{
        ui.LineEdit_Edit_Password->setStyleSheet("");
    }
    return result;
}

void MainWindow::on_PushButton_Edit_Save_clicked()
{
    if( isClearEditPageFields() ){
        return;
    }

    if( ui.LineEdit_Edit_Password->text() != ui.LineEdit_Edit_ConfirmPassword->text() ){
        ui.LineEdit_Edit_Password->setStyleSheet(warningStyle);
        ui.LineEdit_Edit_ConfirmPassword->setStyleSheet(warningStyle);
        return;
    }else{
        ui.LineEdit_Edit_Password->setStyleSheet("");
        ui.LineEdit_Edit_ConfirmPassword->setStyleSheet("");
    }

    getDataFromUi();
    _data.save();

    saveCharGroupsUserSettings();
    clearEditPageFields();
    updateMainTable();
    updateSectionsList();
    setPage( PageIndex::MAIN );
    _existsChanges = true;

    QString recCount = countRecords();
    _statusBar_countRecords.setText( tr("Record count: ") + recCount );
}

/*!
 * \brief Метод обрабатывает нажатие на кнопку возврата со страницы редактирования/добавления записи
 * переключает страницу в стак-виджете на PageIndex::MAIN
 */
void MainWindow::on_PushButton_Edit_Cancel_clicked()
{
    _data.setEditMode( false );
    setPage( PageIndex::MAIN );
    clearEditPageFields();
}

void MainWindow::on_actionCreateDatabase_triggered()
{
    _db.close();
    if( _existsChanges && hasSaveChanges() ){
        _dbFileProcessing->saveEncryptFile();
    }
    _db.remove();
    _existsChanges = false;
    setPage( PageIndex::NEW_FILE );
}

void MainWindow::on_actionOpenDatabase_triggered()
{
    _db.close();
    if( _existsChanges && hasSaveChanges() ){
        _dbFileProcessing->saveEncryptFile();
    }
    _db.remove();
    _existsChanges = false;
    goPage( PageIndex::OPEN_FILE );
}

void MainWindow::on_actionDeleteRecord_triggered()
{
    QModelIndex index = ui.TableView_Main_Records->selectionModel()->currentIndex();
    if( ! index.isValid() )
        return;
    QString id = _modelMainTable.record(index.row()).value(DataTable::Fields::id).toString();
    qDebug() << id;

    QSqlQuery query;
    query.prepare( QString("DELETE FROM %1 WHERE id = :id").arg(DataTable::tableName) );
    query.bindValue( ":id", id );
    if( ! query.exec() ){
        qWarning() << query.lastError().text();
    }
    _existsChanges = true;
    updateMainTable();

    QString recCount = countRecords();
    _statusBar_countRecords.setText( tr("Record count: ") + recCount );
}

QByteArray MainWindow::getPasswordHash(const QString &password)
{
    QSettings cfg;
    QByteArray passwordHash = password.toUtf8();
    bool hashCyclessCastToIntSuccess = false;
    int hashCycles = cfg.value( Options::PASSWORD_HASH_CYCLES, DefaultValues::PASSWORD_HASH_CYCLES ).toInt(&hashCyclessCastToIntSuccess);
    if( (! hashCyclessCastToIntSuccess) || (hashCycles < 1) ){
        hashCycles = DefaultValues::PASSWORD_HASH_CYCLES;
    }
    for(int i = 0; i < hashCycles; ++i){
        passwordHash   = QCryptographicHash::hash( passwordHash, QCryptographicHash::Md5 );
    }

    return passwordHash;
}

QByteArray MainWindow::getSaltForPassword(const QString &password)
{
    QByteArray salt          = password.toUtf8().toHex();
    return salt;
}

void MainWindow::createEmptyFile(const QString &path)
{
    QFile f(path);
    f.open( QIODevice::WriteOnly );
    f.write(QByteArray());
    f.close();
}

void MainWindow::on_PButton_New_CreateDatabase_clicked()
{
    QSettings  cfg;
    QByteArray password      = getPasswordHash( ui.LineEdit_New_Password->text() );
    QByteArray salt          = getSaltForPassword( ui.LineEdit_New_Password->text() );
    QString    achtungDbPath = getTmpDbPath();
    QString    encDbPath     = ui.LineEdit_New_FilePath->text();
    int        bufferSize    = cfg.value( Options::BUFFER_SIZE, DefaultValues::BUFFER_SIZE).toInt();
               _sessionTime  = ui.SpinBox_New_SessionTime->value();

    if( _dbFileProcessing ){
        qWarning() << "Чёта ты не в тот район забрёл...";
        delete _dbFileProcessing;
        _dbFileProcessing = nullptr;
    }
    _dbFileProcessing = new DbFileProcessing(achtungDbPath, encDbPath, password, salt, bufferSize);

    createEmptyFile(encDbPath);
    connectToDatabase( achtungDbPath );
    _passwordHash = password;

    _modelGroupsList.clear();
    updateMainTable();
    HideColumns();
    setPage( PageIndex::MAIN );

    cfg.setValue( Options::LAST_FILE_PATH , encDbPath );
    _recentDocuments.addLastDocument( encDbPath );

    ui.LineEdit_New_FilePath->clear();
    ui.LineEdit_New_Password->clear();
    ui.LineEdit_New_ConfirmPassword->clear();
}

void MainWindow::on_actionSaveDatabase_triggered()
{
    _dbFileProcessing->saveEncryptFile();
    _existsChanges = false;
}

void MainWindow::setDataToUi()
{
    ui.ComboBox_Edit_Group->setCurrentText( _data.group() );
    ui.LineEdit_Edit_Title->setText( _data.resource() );
    ui.LineEdit_Edit_Url->setText( _data.url() );
    ui.LineEdit_Edit_Login->setText( _data.login() );
    ui.LineEdit_Edit_Password->setText( _data.password() );
    ui.LineEdit_Edit_ConfirmPassword->setText( _data.password() );
    ui.LineEdit_Edit_Answer->setText( _data.answer() );
    ui.LineEdit_Edit_Phone->setText( _data.phone() );
    ui.PlainTextEdit_Edit_Comment->setPlainText( _data.description() );
}

void MainWindow::on_actionEditRecord_triggered()
{
    QModelIndex index = ui.TableView_Main_Records->selectionModel()->currentIndex();
    if( ! index.isValid() )
        return;

    setDataToUi();
    _data.setEditMode( true );
    setPage( PageIndex::EDIT );
}

void MainWindow::on_TButton_New_ChooseFile_clicked()
{
    ui.LineEdit_New_FilePath->setText(
                QFileDialog::getSaveFileName(this,
                                             tr("Create new file"),
                                             QStandardPaths::writableLocation( QStandardPaths::HomeLocation )
                                             ) );
}

void MainWindow::on_TButton_Open_ChooseFile_clicked()
{
    ui.LineEdit_Open_FilePath->setText(
                QFileDialog::getOpenFileName(this,
                                             tr("Choose a file"),
                                             QStandardPaths::writableLocation( QStandardPaths::HomeLocation )
                                             ) );
}

void MainWindow::on_LineEdit_New_ConfirmPassword_textEdited(const QString &)
{
    ui.PButton_New_CreateDatabase->setEnabled( isFieldsComplete_New() );
}

void MainWindow::on_LineEdit_New_Password_textEdited(const QString &)
{
    ui.PButton_New_CreateDatabase->setEnabled( isFieldsComplete_New() );
}

void MainWindow::on_LineEdit_New_FilePath_textEdited(const QString &)
{
    ui.PButton_New_CreateDatabase->setEnabled( isFieldsComplete_New() );
}

void MainWindow::on_LineEdit_Open_Password_textEdited(const QString &)
{
    ui.PButton_Open_OpenFile->setEnabled( isFieldsComplete_Open() );
}

void MainWindow::on_LineEdit_Open_FilePath_textChanged(const QString &)
{
    ui.PButton_Open_OpenFile->setEnabled( isFieldsComplete_Open() );
}

void MainWindow::on_TButton_Open_ShowPassword_toggled(bool checked)
{
    QLineEdit::EchoMode mode;
    mode = (checked)? QLineEdit::Normal : QLineEdit::Password;

    ui.LineEdit_Open_Password->setEchoMode( mode );
}

void MainWindow::on_TButton_New_ShowPassword_toggled(bool checked)
{
    QLineEdit::EchoMode mode;
    mode = (checked)? QLineEdit::Normal : QLineEdit::Password;

    ui.LineEdit_New_Password->setEchoMode( mode );
    ui.LineEdit_New_ConfirmPassword->setEchoMode( mode );
}

void MainWindow::on_TButton_Lock_ShowPassword_toggled(bool checked)
{
    QLineEdit::EchoMode mode;
    mode = (checked)? QLineEdit::Normal : QLineEdit::Password;

    ui.LineEdit_Lock_Password->setEchoMode( mode );
}

void MainWindow::on_actionLock_triggered()
{
    setPage( PageIndex::LOCK );
}

void MainWindow::on_PButton_Lock_Unclock_clicked()
{
    QByteArray password = getPasswordHash( ui.LineEdit_Lock_Password->text() );
    if( password == _passwordHash ){
        setPage( PageIndex::MAIN );
        ui.Label_Lock_Error->setText("");
        ui.LineEdit_Lock_Password->clear();
    }else{
        ui.Label_Lock_Error->setText( tr("Password is uncorrect") );
    }
}

void MainWindow::on_TreeView_Main_Category_clicked(const QModelIndex &)
{
    updateMainTable();
}

void MainWindow::on_ComboBox_Edit_Group_currentTextChanged(const QString &text)
{
    if( text.isEmpty() ){
        ui.ComboBox_Edit_Group->setStyleSheet(warningStyle);
    }else{
        ui.ComboBox_Edit_Group->setStyleSheet("");
    }
}

void MainWindow::on_LineEdit_Edit_Title_editingFinished()
{
    if( ui.LineEdit_Edit_Title->text().isEmpty() ){
        ui.LineEdit_Edit_Title->setStyleSheet(warningStyle);
    }else{
        ui.LineEdit_Edit_Title->setStyleSheet("");
    }
}

void MainWindow::on_LineEdit_Edit_Login_editingFinished()
{
    if( ui.LineEdit_Edit_Login->text().isEmpty() ){
        ui.LineEdit_Edit_Login->setStyleSheet(warningStyle);
    }else{
        ui.LineEdit_Edit_Login->setStyleSheet("");
    }
}

void MainWindow::on_LineEdit_Edit_Password_editingFinished()
{
    if( ui.LineEdit_Edit_Password->text().isEmpty() ){
        ui.LineEdit_Edit_Password->setStyleSheet(warningStyle);
    }else{
        ui.LineEdit_Edit_Password->setStyleSheet("");
    }
}

void MainWindow::on_TableView_Main_Records_activated(const QModelIndex &index)
{
    QSqlRecord record = _modelMainTable.record( index.row() );
    _data.load( record.value( DataTable::Fields::id ).toString() );

    setDataToInfoPanel( _data );
}

void MainWindow::on_actionCopyNameInClipboard_triggered()
{
    QModelIndex index = ui.TableView_Main_Records->selectionModel()->currentIndex();
    if( ! index.isValid() )
        return;
    QString login = _modelMainTable.record(index.row()).value(DataTable::Fields::Login).toString();

    QClipboard *pcb = QApplication::clipboard();
    pcb->setText(login);
}

void MainWindow::on_actionCopyPasswordInClipboard_triggered()
{
    QModelIndex index = ui.TableView_Main_Records->selectionModel()->currentIndex();
    if( ! index.isValid() )
        return;
    QString password = _modelMainTable.record(index.row()).value(DataTable::Fields::Password).toString();

    QClipboard *pcb = QApplication::clipboard();
    pcb->setText(password);
}

//void test(){
//    const QPoint p(10,10);
//    QMouseEvent* pe = new QMouseEvent(QEvent::MouseButtonPress,p,Qt::LeftButton,Qt::NoButton, Qt::NoModifier);
//    QApplication::sendEvent(&txt, pe);
//}

void MainWindow::on_TableView_Main_Records_clicked(const QModelIndex &index)
{
    emit ui.TableView_Main_Records->activated(index);
}

void MainWindow::on_actionCopyUrl_triggered()
{
    QModelIndex index = ui.TableView_Main_Records->selectionModel()->currentIndex();
    if( ! index.isValid() )
        return;
    QString url = _modelMainTable.record(index.row()).value(DataTable::Fields::Url).toString();

//    QClipboard *pcb = QApplication::clipboard();
//    pcb->setText(url);

    QDesktopServices::openUrl( QUrl(url) );
}

void MainWindow::on_LineEdit_Main_Search_textEdited(const QString &searchText)
{
    QString group = ui.TreeView_Main_Category->currentIndex().data(Qt::DisplayRole).toString();

    QStringList fields;
    fields.append(DataTable::Fields::id);
    fields.append(DataTable::Fields::Resource);
    fields.append(DataTable::Fields::Url);
    fields.append(DataTable::Fields::Login);
    fields.append(DataTable::Fields::Password);

    QString sql("SELECT %1 FROM %2 WHERE %3='%4' AND %5 LIKE '\%" + searchText + "\%'");
    sql = sql.arg( fields.join(", "),
                   DataTable::tableName,
                   DataTable::Fields::PassGroup,
                   group,
                   DataTable::Fields::Resource);
    _modelMainTable.setQuery( sql );
}

void MainWindow::on_actionAbout_triggered()
{
    auto dialog = new AboutDialog(this);
    dialog->setModal(true);
    dialog->exec();
}

void MainWindow::on_actionHelp_triggered()
{
    QString file = QDir::currentPath() + QDir::separator();
    if( _currentLanguage == QLocale::Russian ){
        file += "help_ru.html";
    }else{
        file += "help_eng.html";
    }
    qDebug() << file;
    auto dialog = new HelpDialog(file, this);
    dialog->exec();
}

void MainWindow::on_actionRussian_triggered(bool checked)
{
    if( checked ){
        ui.actionEnglish->setChecked( !checked );


        if( ! qtTr.load( "://l10n/qtbase_ru.qm" ) )
            qDebug() << "Don't load qtBase russian localization";

        if( ! appTr.load( "://l10n/PassMan_ru.qm" ) )
            qDebug() << "Don't load qtApp russian localization";

        qApp->installTranslator(&qtTr);
        qApp->installTranslator(&appTr);
        ui.retranslateUi(this);
        updateSectionsList();
        updateMainTable();

        QSettings cfg;
        cfg.setValue( Options::LANGUAGE, QLocale::Russian );

        QString recCount = countRecords();
        _statusBar_countRecords.setText( tr("Record count: ") + recCount );

        _currentLanguage = QLocale::Russian;
    }
}

void MainWindow::on_actionEnglish_triggered(bool checked)
{
    if( checked ){
        ui.actionRussian->setChecked( !checked );

        qtTr.load( "" );
        appTr.load( "" );
        qApp->installTranslator(&qtTr);
        qApp->installTranslator(&appTr);
        ui.retranslateUi(this);
        updateSectionsList();
        updateMainTable();

        QSettings cfg;
        cfg.setValue( Options::LANGUAGE, QLocale::English );

        QString recCount = countRecords();
        _statusBar_countRecords.setText( tr("Record count: ") + recCount );

        _currentLanguage = QLocale::English;
    }
}

void MainWindow::on_TButton_First_LangSwitch_clicked()
{
    if( _currentLanguage == QLocale::English ){
        emit on_actionRussian_triggered(true);
        ui.TButton_First_LangSwitch->setText( "ru" );
    }else{
        emit on_actionEnglish_triggered(true);
        ui.TButton_First_LangSwitch->setText( "en" );
    }
}

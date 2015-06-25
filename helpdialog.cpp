#include "helpdialog.h"
#include "ui_helpdialog.h"

#include <QFile>

HelpDialog::HelpDialog(const QString &file, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);

    QFile help_html(file);
    help_html.open( QFile::ReadOnly );
    ui->label->setText( help_html.readAll() );
    help_html.close();
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

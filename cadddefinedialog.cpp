#include "cadddefinedialog.h"
#include "ui_cadddefinedialog.h"
#include <QDebug>

static QString s_exp;

CAddDefineDialog::CAddDefineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddDefineDialog)
{
    ui->setupUi(this);

    setWindowFlags( Qt::WindowCloseButtonHint );
}

CAddDefineDialog::~CAddDefineDialog()
{
    delete ui;
}

QString CAddDefineDialog::getDefineExp()
{
    s_exp.clear();
    CAddDefineDialog().exec();
    return s_exp.isEmpty() ? "null" : s_exp;
}

void CAddDefineDialog::on_pb_cancel_clicked()
{
    close();
}

void CAddDefineDialog::on_pb_ok_clicked()
{
    s_exp = "#define " + ui->lineEdit->text().trimmed() + "\n";
    close();
}

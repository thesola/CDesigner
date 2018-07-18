#include "caddincludedialog.h"
#include "ui_caddincludedialog.h"

static QString s_exp;

CAddIncludeDialog::CAddIncludeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddIncludeDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowCloseButtonHint);
}

CAddIncludeDialog::~CAddIncludeDialog()
{
    delete ui;
}

QString CAddIncludeDialog::getIncludeExp()
{
    s_exp.clear();
    CAddIncludeDialog().exec();
    return s_exp.isEmpty() ? "null" : s_exp;
}

void CAddIncludeDialog::on_pb_cancel_clicked()
{
    close();
}

void CAddIncludeDialog::on_pb_ok_clicked()
{
    s_exp = "#include<" + ui->comboBox->currentText().trimmed() + ">\n";
    close();
}

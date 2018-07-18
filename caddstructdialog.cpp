#include "caddstructdialog.h"
#include "ui_caddstructdialog.h"
#include "cargwidget.h"
#include "cdef.h"

static QString s_exp;

CAddStructDialog::CAddStructDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddStructDialog)
{
    ui->setupUi(this);

    setWindowFlags( Qt::WindowCloseButtonHint );
}

CAddStructDialog::~CAddStructDialog()
{
    delete ui;
}

QString CAddStructDialog::getStructExp()
{
    s_exp.clear();

    CAddStructDialog dia;
    dia.exec();

    return s_exp.isEmpty() ? "null" : s_exp;
}

void CAddStructDialog::on_pb_addMember_clicked()
{
    CArgWidget *member = new CArgWidget(this);
    ui->vl_members->addWidget( member );
    connect( member, SIGNAL(deleteArg(QWidget*)), this, SLOT(doDeleteMember(QWidget*)) );
}

void CAddStructDialog::doDeleteMember(QWidget *member)
{
    ui->vl_members->removeWidget( member );
    delete member;
}

void CAddStructDialog::on_pb_cancel_clicked()
{
    close();
}

void CAddStructDialog::on_pb_ok_clicked()
{
    s_exp = "";

    s_exp += ( ui->checkBox->isChecked() ? "typedef " : "" );
    s_exp += ( ui->rb_struct->isChecked() ? "struct " : "union " );
    s_exp += ui->lineEdit->text().trimmed() + "\n{\n";

    for( int i=0,n=ui->vl_members->count() ; i < n ; ++i )
    {
        CArgWidget *arg = (CArgWidget*)ui->vl_members->itemAt(i)->widget();
        s_exp += QString(g_s32Indent,' ') + arg->getArg().first + " " + arg->getArg().second + ";\n";
    }

    s_exp += "}";
    if( ui->checkBox->isChecked() )
    {
        //将类型名转为大写
        s_exp += ui->lineEdit->text().trimmed().toUpper();
    }
    s_exp += ";\n";


    close();
}

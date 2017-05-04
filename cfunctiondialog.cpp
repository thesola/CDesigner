#include "cfunctiondialog.h"
#include "ui_cfunctiondialog.h"
#include <QDebug>

CFunctionDialog::CFunctionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CFunctionDialog)
{
    ui->setupUi(this);
    // 将焦点给函数名输入框
//    ui->le_funcName->setFocus();
    // 焦点还是给参数列表的好
}

CFunctionDialog::~CFunctionDialog()
{
    delete ui;
}

// 更新 m_cFunction 的信息
void CFunctionDialog::on_pb_ok_clicked()
{
    ArgList list = CFunction::StringToArg( ui->le_args->text().trimmed() );

    if( ! list.isEmpty() )
        m_cFunction->setArgList( list );
    if( ! ui->le_funcName->text().trimmed().isEmpty() )
        m_cFunction->setFucName( ui->le_funcName->text().trimmed() );
    if( ! ui->cb_retType->currentText().trimmed().isEmpty() )
        m_cFunction->setRetType( ui->cb_retType->currentText().trimmed() );

    // 隐藏并重置面板
    on_pb_cancel_clicked();

    // 通知修改完毕
    emit okClicked();
}

// 隐藏并重置面板
void CFunctionDialog::on_pb_cancel_clicked()
{
    // 隐藏当前面板
    this->hide();
    // 重置面板信息
    setCFunction( m_cFunction );
}

// 绑定函数对象
void CFunctionDialog::setCFunction(CFunction *cFunction)
{
    m_cFunction = cFunction;

    if( m_cFunction == NULL ){
        return ;
    }

    ui->le_args->setText( CFunction::argToString( m_cFunction->argList() ) );
    ui->le_funcName->setText( m_cFunction->fucName() );
    ui->cb_retType->setCurrentText( m_cFunction->retType() );
}

QString CFunctionDialog::funcName() const
{
    return ui->le_funcName->text().trimmed();
}
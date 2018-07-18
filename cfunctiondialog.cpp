#include "cfunctiondialog.h"
#include "ui_cfunctiondialog.h"
#include <QDebug>
#include "cargwidget.h"


CFunctionDialog::CFunctionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CFunctionDialog)
{
    ui->setupUi(this);
    // 将焦点给函数名输入框
//    ui->le_funcName->setFocus();
    // 焦点还是给参数列表的好

    m_bOkClicked = false;

    // 取消问号
//    setWindowFlags( Qt::WindowCloseButtonHint );
}

CFunctionDialog::~CFunctionDialog()
{
    delete ui;
}

// 更新 m_cFunction 的信息
void CFunctionDialog::on_pb_ok_clicked()
{
    m_bOkClicked = true;

//    ArgList list = CFunction::StringToArg( ui->le_args->text().trimmed() );
    // 重置参数列表
    ArgList list;
    for( int i=0,n=ui->vl_args->count() ; i < n ; ++ i)
    {
        list.append( ((CArgWidget*)ui->vl_args->itemAt(i)->widget())->getArg() );
    }

    // 参数列表可以设置为空 函数名、返回值类型不能为空
    m_cFunction->setArgList( list );

    if( ! ui->le_funcName->text().trimmed().isEmpty() )
        m_cFunction->setFucName( ui->le_funcName->text().trimmed() );
    if( ! ui->cb_retType->currentText().trimmed().isEmpty() )
        m_cFunction->setRetType( ui->cb_retType->currentText().trimmed() );

    // 隐藏当前面板
    this->hide();
    // 重置面板信息
    setCFunction( m_cFunction );

    // 通知修改完毕
    emit okClicked();
}

// 隐藏并重置面板
void CFunctionDialog::on_pb_cancel_clicked()
{
    m_bOkClicked = false;

    // 隐藏当前面板
    this->hide();
    // 重置面板信息
    setCFunction( m_cFunction );
}

void CFunctionDialog::closeEvent(QCloseEvent *e)
{
    on_pb_cancel_clicked();
}

// 绑定函数对象
void CFunctionDialog::setCFunction(CFunction *cFunction)
{
    m_cFunction = cFunction;

    if( m_cFunction == NULL ){
        return ;
    }

    // 设置参数列表
    // 清空旧参数列表
    QLayoutItem *child;
    while( (child = ui->vl_args->takeAt(0)) != NULL )
    {
//        child->widget()->deleteLater();
        delete child->widget();
    }
    // 添加新列表
    ArgList list = m_cFunction->argList();
    foreach (Arg arg, list) {
        CArgWidget *argWidget = new CArgWidget(this, arg);
        ui->vl_args->addWidget( argWidget );	// 添加新函数参数以显示
        connect( argWidget, SIGNAL(deleteArg(QWidget*)), this, SLOT(doDeleteArg(QWidget*)) );
    }

//    ui->le_args->setText( CFunction::argToString( m_cFunction->argList() ) );
    ui->le_funcName->setText( m_cFunction->fucName() );
    ui->cb_retType->setCurrentText( m_cFunction->retType() );
}

QString CFunctionDialog::funcName() const
{
    return ui->le_funcName->text().trimmed();
}

bool CFunctionDialog::isOkClicked()
{
    return m_bOkClicked;
}

// 新增参数
void CFunctionDialog::on_pb_addArg_clicked()
{
    CArgWidget *argWidget = new CArgWidget(this);
    ui->vl_args->addWidget( argWidget );

    connect( argWidget, SIGNAL(deleteArg(QWidget*)), this, SLOT(doDeleteArg(QWidget*)) );
}

void CFunctionDialog::doDeleteArg(QWidget *widget)
{
    ui->vl_args->removeWidget( widget );
    delete widget;
}


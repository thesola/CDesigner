#include "insertfunctiondialog.h"
#include "ui_insertfunctiondialog.h"
#include "cfunction.h"
#include "global_vars.h"
#include <QTimer>

static QString s_exp;

InsertFunctionDialog::InsertFunctionDialog(QStringList vars, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertFunctionDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowCloseButtonHint);

    m_VarNames = vars;

    ui->cb_funcName->addItems( (QStringList()<<tr("函数名")) + g_tabWidget->funcNames() );
}

QString InsertFunctionDialog::getFuncExp(QStringList vars)
{
    s_exp.clear();

    InsertFunctionDialog dia(vars);
    dia.exec();

    return s_exp.isEmpty() ? "null" : s_exp ;
}

InsertFunctionDialog::~InsertFunctionDialog()
{
    delete ui;
}

void InsertFunctionDialog::on_rb_printf_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "printf", checked );
}

void InsertFunctionDialog::on_rb_puts_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "puts", checked );
}

void InsertFunctionDialog::on_rb_putchar_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "putchar", checked );
}

void InsertFunctionDialog::on_rb_sscanf_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "sscanf", checked );
}

void InsertFunctionDialog::on_rb_fprintf_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "fprintf", checked );
}

void InsertFunctionDialog::on_rb_scanf_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "scanf", checked );
}

void InsertFunctionDialog::on_rb_gets_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "gets", checked );
}

void InsertFunctionDialog::on_rb_getchar_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "getchar", checked );
}

void InsertFunctionDialog::on_rb_sprintf_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "sprintf", checked );
}

void InsertFunctionDialog::on_rb_fscanf_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "fscanf", checked );
}

void InsertFunctionDialog::on_rb_malloc_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "malloc", checked );
}

void InsertFunctionDialog::on_rb_calloc_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "calloc", checked );
}

void InsertFunctionDialog::on_rb_free_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "free", checked );
}

void InsertFunctionDialog::on_pb_ok_clicked()
{
    hide();

    QString funcName = ui->cb_funcName->currentText().trimmed();
    QStringList argNames;

    if( ! funcName.isEmpty() )
    {
        s_exp = funcName + "(";

        for( int i=0,n=ui->vl_args->count() ; i < n ; ++i )
        {
            CArgName *argName = (CArgName*)ui->vl_args->itemAt(i)->widget();
            s_exp += argName->isFirstArg() ? " " : "," ;
            s_exp += argName->argName() + " ";
            argNames.append( argName->argName() );
        }

        s_exp += ")";
    }

    // 对三种函数类型分别处理：库函数-添加头文件；已定义函数-null；未定义函数-添加函数定义
    if( CFunction::libFuncNames().contains(funcName) )
    {
        // 添加头文件
        g_tabWidget->addLibFuncHeader( funcName );
    }
    else if( ! g_tabWidget->funcNames().contains( funcName ) )
    {
        // 添加函数定义
        g_tabWidget->addFunction(funcName,argNames);
//        QTimer::singleShot( 40, g_tabWidget, SLOT(addFunction(funcName,argNames)) );
//        QTimer *timer = new QTimer(this);
//        timer->setInterval(40);
//        timer->setSingleShot(true);
//        connect( timer, SIGNAL(timeout()), g_tabWidget, SLOT(addFunction(funcName,argNames)) );
//        timer->start();
    }

    close();
}

void InsertFunctionDialog::on_pb_cancel_clicked()
{
    close();
}

void InsertFunctionDialog::on_pb_AddArg_clicked()
{
    CArgName *argName = new CArgName("",m_VarNames);
    argName->setAsFirstArg( ui->vl_args->isEmpty() );
    ui->vl_args->addWidget(argName);
    connect( argName, SIGNAL(deleteArgName(QWidget*)), this, SLOT(doDeleteArgName(QWidget*)) );
}

void InsertFunctionDialog::doDeleteArgName(QWidget *argName)
{
    ui->vl_args->removeWidget(argName);
    delete argName;

    // 重置第一个
    QLayoutItem *firstArgName = ui->vl_args->itemAt(0);
    if( firstArgName != NULL )
    {
        ((CArgName*)firstArgName->widget())->setAsFirstArg(true);
    }
}

void InsertFunctionDialog::resetFuncInfoAsLibFunc(QString libFuncName, bool checked)
{
    resetFuncInfo( libFuncName, CFunction::libFuncArgs(libFuncName), checked );
}

void InsertFunctionDialog::resetFuncInfo(QString funcNmae, QStringList funcArgs, bool checked)
{
    // 清空旧有函数信息
    QLayoutItem *item;
    while( item = ui->vl_args->takeAt(0) )
    {
        item->widget()->deleteLater();
    }
    ui->cb_funcName->setCurrentText("");

    // 设置新信息
    if( checked )
    {
        ui->cb_funcName->setCurrentText( funcNmae );
        foreach (QString argName, funcArgs) {
            CArgName *arg = new CArgName( argName, m_VarNames );
            arg->setAsFirstArg( ui->vl_args->count() == 0 );
            ui->vl_args->addWidget( arg );
            connect( arg, SIGNAL(deleteArgName(QWidget*)), this, SLOT(doDeleteArgName(QWidget*)) );
        }
    }
}

/****************【参数名称类】****************************/

CArgName::CArgName(QString argName, QStringList argNames, bool isFirst)
{
    m_Label = new QLabel(",\n",this);
    m_ComboBox = new QComboBox(this);
    m_PushButton = new QPushButton(tr("删除"),this);

    m_Label->setFont(QFont("宋体",12));
//    m_Label->setAlignment( Qt::AlignCenter | Qt::AlignVCenter );
//    m_Label->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);
//    m_Label->setFrameStyle(3);

    m_PushButton->setFont(QFont("宋体",10));
    m_PushButton->setMinimumWidth(50);
    m_PushButton->setMaximumWidth(50);
    m_PushButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    m_ComboBox->setFont(QFont("宋体",12));
    m_ComboBox->addItems(argNames);
    m_ComboBox->setCurrentText(argName);
    m_ComboBox->setMinimumHeight(30);
    m_ComboBox->setEditable(true);
    m_ComboBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    setAsFirstArg(isFirst);

    // 设置布局
    QHBoxLayout *hboxlayout = new QHBoxLayout;
    hboxlayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding));
    hboxlayout->addWidget(m_PushButton);
    hboxlayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding));

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(m_ComboBox);
    vLayout->addLayout( hboxlayout );
    vLayout->setMargin(0);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget( m_Label );
    hLayout->addLayout( vLayout );
    hLayout->setMargin(0);
    hLayout->setSpacing(0);

    setLayout( hLayout );

    m_ComboBox->setCurrentText( argName );

    connect( m_PushButton, SIGNAL(clicked()), this, SLOT(onDeleteClicked()) );
}

void CArgName::setAsFirstArg(bool isFirst)
{
    if( isFirst )
    {
        m_Label->hide();
    }
    else
    {
        m_Label->show();
    }
}

bool CArgName::isFirstArg() const
{
    return m_Label->isHidden();
}

QString CArgName::argName()
{
    return m_ComboBox->currentText().trimmed();
}

void CArgName::onDeleteClicked()
{
    emit deleteArgName(this);
}

void InsertFunctionDialog::on_rb_strlen_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "strlen", checked );
}

void InsertFunctionDialog::on_rb_strcmp_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "strcmp", checked );
}

void InsertFunctionDialog::on_rb_strcat_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "strcat", checked );
}

void InsertFunctionDialog::on_rb_strcpy_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "strcpy", checked );
}

void InsertFunctionDialog::on_rb_memcpy_toggled(bool checked)
{
    resetFuncInfoAsLibFunc( "memcpy", checked );
}

void InsertFunctionDialog::on_cb_funcName_currentIndexChanged(int index)
{
    // 偏移一个空白项位置
    resetFuncInfo( ui->cb_funcName->currentText(), g_tabWidget->funcArgs(index-1), true );
}

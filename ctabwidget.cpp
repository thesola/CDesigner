#include "ctabwidget.h"
#include "cfunction.h"

#include <QTabBar>
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QFile>
#include <windows.h>
#include <QMessageBox>


CTabWidget::CTabWidget(QWidget *parent):QTabWidget(parent)
{
    // 重置面板
    clearTabs();

    // 设置模态对话框
    m_cFunctionDialog = new CFunctionDialog(this);

    //  关联信号
    connect( this, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(doModifyFunction(int)) );
    connect( m_cFunctionDialog, SIGNAL(okClicked()), this, SLOT(doOkClicked()) );
    connect( this, SIGNAL(tabBarClicked(int)), this, SLOT(doTabBarClicked()) );
}

QString CTabWidget::toCCode() const
{
    QString str, dec, def;

    // 文件头
    str += m_textEdit->toPlainText().trimmed() + "\n\n";

    // 函数声明 & 定义
    for( int i=2, n=this->count()-1 ; i < n ; ++i ){
        CFunction *func = (CFunction*)this->widget(i);
        dec += func->toFuncDeclare();
    }

    if( ! dec.isEmpty() )
    {
        str += dec + "\n";
    }

    str += def;

    for( int i=1, n=this->count()-1 ; i < n ; ++i ){
        CFunction *func = (CFunction*)this->widget(i);
        str += func->toCCode();
        str += "\n";  // 函数之间空一行
    }

    return str;
}

void CTabWidget::doAddFunction()
{
    CFunction *newFunc = new CFunction("void","函数名");

    int index = insertTab( count()-1, newFunc, "函数名 " );

    QPushButton *pbtn = new QPushButton("",newFunc);

    pbtn->setFixedSize(18,18);
    pbtn->setIcon(QIcon(":/icons/close.ico"));
    pbtn->setToolTip("点击删除");

    connect( pbtn, SIGNAL(clicked()), this, SLOT(doTabClose()) );

    this->tabBar()->setTabButton( index, QTabBar::RightSide, pbtn );

    setCurrentIndex( index );

    doModifyFunction( index );

    qDebug()<<"[CTabWidget::doAddFunction] m_cFunctionDialog->isOkClicked() : "<<m_cFunctionDialog->isOkClicked();

    if( m_cFunctionDialog->isOkClicked() ){ // 确定添加
        setTabToolTip( index, "双击修改函数信息" );

        connect( newFunc, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()) );

        emit contentChanged();

    } else { // 取消添加

//        removeTab( index );
        delete newFunc;

        setCurrentIndex( index-1 );

    }

}

void CTabWidget::doOkClicked()
{
    // 修改当前tab的名称为新的函数名
    setTabText( currentIndex(), m_cFunctionDialog->funcName()+" " );
}

void CTabWidget::doTabBarClicked()
{
    int index = this->tabBar()->tabAt( this->tabBar()->mapFromGlobal(QCursor::pos()) );
    if( index == count()-1 ){
        doAddFunction();
    }
}


// 重置面板
void CTabWidget::clearTabs()
{
//    this->clear();
    while( count() ){
        delete this->widget(0);
        removeTab(0);
    }

    // 添加头部信息编辑
    m_textEdit = new QTextEdit(this);
    m_textEdit->setAcceptDrops(false);
    m_textEdit->append("#include<stdio.h>\n");
    m_textEdit->setFont(QFont("Consolas",15));
    addTab(m_textEdit,"    ");


    // 默认添加一个main函数
    CFunction *main = CFunction::getMainFunction();
    addTab(main,main->fucName());
    setTabToolTip(1,"main 函数");

    setCurrentIndex(1);

    // 添加增添函数选选项卡
    QWidget *widget = new QWidget(this);
    this->addTab( widget, "" );

    QPushButton *pbtn = new QPushButton("",widget);
    pbtn->setFixedSize(18,18);
    pbtn->setIcon(QIcon(":/icons/add.ico"));

    this->tabBar()->setTabButton( 2, QTabBar::RightSide, pbtn );
    this->setTabToolTip( 2, "点击添加" );
    this->setTabEnabled(2,false);

    connect( pbtn, SIGNAL(clicked()), this, SLOT(doTabBarClicked()) );
    connect( m_textEdit, SIGNAL(textChanged()), this, SIGNAL(contentChanged()) );
    connect( main, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()) );

    emit contentChanged();
}


// 编译 & 运行
void CTabWidget::runIt()
{
    qDebug()<<"[CTabWidget::runIt] beg";

    QFile file;

    // 读取 gcc 位置
    file.setFileName("cc.path");
    if( ! file.open(QIODevice::ReadOnly | QIODevice::Text) ){
        QMessageBox::warning(this,"警告","未找到编译器！\n请到当前目录下 cc.path 文件中正确配置编译器路径！");
        return;
    }
    QTextStream in(&file);
    QString gccPath;
    in >> gccPath;
    file.close();

    QString cmd( gccPath + " main.c 2> error.log && a.exe && pause && del main.c a.exe error.log ");

    // 将文本保存到文件
    file.setFileName("main.c");
    if( ! file.open(QIODevice::WriteOnly | QIODevice::Text) ){
        qDebug()<<"[CTabWidget::runIt] file open failed";
        return ;
    }
    QTextStream out(&file);
    out << this->toCCode();
    out.flush();
    file.close();

//    system("mingw491_32\\bin\\gcc.exe main.c 2> error.log && a.exe && pause && del main.c a.exe error.log " );
    system( cmd.toLatin1().data() );

    // 读取错误信息
    file.setFileName("error.log");
    if( file.open( QIODevice::ReadOnly | QIODevice::Text ) && file.size() )
    {
        QString errorInfo;

        QTextStream in(&file);
        while( ! in.atEnd() )
        {
            errorInfo += in.readLine() + "\n";
        }

        QMessageBox::warning(this, "编译信息", errorInfo);

        file.close();
    }

    qDebug()<<"[CTabWidget::runIt] end";
}

void CTabWidget::doModifyFunction(int index)
{

    if( index <=1 && index != count()-1 ){ // 不可修改
        return;
    }

    CFunction *func = (CFunction*)this->widget(index);

    m_cFunctionDialog->setCFunction( func );
    m_cFunctionDialog->setGeometry( this->x()+this->width()/2-200, this->y()+this->height()/2-135, 400, 270 );
    m_cFunctionDialog->exec();

}

void CTabWidget::doTabClose()
{
    // 获取当前点击的索引
    int index = this->tabBar()->tabAt( this->tabBar()->mapFromGlobal(QCursor::pos()) );

    if( index <= 1 ){ // main不可删
        QMessageBox::warning(this,"警告","不应删除该目标");
        return;
    }

    delete this->widget(index);
    setCurrentIndex( count()-2 );

    emit contentChanged();
}

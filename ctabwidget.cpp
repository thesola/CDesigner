#include "ctabwidget.h"
#include <QPainter>
#include "cfunction.h"
#include <QDebug>
#include <QFile>
#include <windows.h>
#include <QMessageBox>


CTabWidget::CTabWidget(QWidget *parent):QTabWidget(parent)
{
    // 默认添加一个main函数
    CFunction *main = CFunction::getMainFunction();
    addTab(main,main->fucName());

    // 设置模态对话框
    m_cFunctionDialog = new CFunctionDialog(this);

    // 设置菜单
    m_menu = new QMenu(this);
    m_menu->addAction("修改");
    m_menu->addAction("添加");
    m_menu->addAction("删除");

    // 设置标签可关闭
    setTabsClosable(true);

    //  关联信号
    connect( main, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()) );
    connect( this, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(doModifyFunction(int)) );
    connect( m_cFunctionDialog, SIGNAL(okClicked()), this, SLOT(doOkClicked()) );
    connect( this, SIGNAL(tabCloseRequested(int)), this, SLOT(doTabClose(int)) );
}

QString CTabWidget::toCCode() const
{
    QString str, dec, def;

    // 文件头
    str += readHeader();

    // 函数声明 & 定义
    for( int i=1, n=this->count() ; i < n ; ++i ){
        CFunction *func = (CFunction*)this->widget(i);
        dec += func->toFuncDeclare();
    }

    if( ! dec.isEmpty() )
    {
        str += dec + "\n\n";
    }

    str += def;

    for( int i=0, n=this->count() ; i < n ; ++i ){
        CFunction *func = (CFunction*)this->widget(i);
        str += func->toCCode();
        str += "\n";  // 函数之间空一行
    }

    return str;
}

// 读取预配置的文件头部信息
QString CTabWidget::readHeader() const
{
    QFile file("header.conf");

    if( ! file.open(QIODevice::ReadOnly | QIODevice::Text) || file.size() == 0 ){
        // 无文件 返回默认值
        return "#include <stdio.h>\n\n";
    }

    QString header;

    QTextStream in(&file);
    while( ! in.atEnd() )
    {
        header += in.readLine() + "\n" ;
    }
    header += "\n";

    file.close();

    return header;
}

void CTabWidget::doAddFunction()
{
    CFunction *newFunc = new CFunction("void","函数名");

    addTab( newFunc, "" );

    setCurrentIndex( count()-1 );

    doModifyFunction( count()-1 );

    connect( newFunc, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()) );

    emit contentChanged();
}

void CTabWidget::doOkClicked()
{
    // 修改当前tab的名称为新的函数名
    setTabText( currentIndex(), m_cFunctionDialog->funcName() );
}

void CTabWidget::clearTabs()
{
    this->clear();

    // 默认添加一个main函数
    CFunction *main = CFunction::getMainFunction();
    addTab(main,main->fucName());

    connect( main, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()) );

    emit contentChanged();
}


// 编译 & 运行
void CTabWidget::runIt()
{
    qDebug()<<"[CTabWidget::runIt] beg";

    // 将文本保存到文件
    QFile file("temp.c");
    if( ! file.open(QIODevice::WriteOnly | QIODevice::Text) ){
        qDebug()<<"[CTabWidget::runIt] file open failed";
        return ;
    }
    QTextStream out(&file);
    out << this->toCCode();
    out.flush();
    file.close();

    system( "mingw64\\bin\\gcc.exe temp.c 2> error.log && a.exe && pause && del temp.c a.exe error.log " );

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
    }

    qDebug()<<"[CTabWidget::runIt] end";
}

void CTabWidget::doModifyFunction(int index)
{

    if( index <=0 ){ // main 不可修改
        return;
    }

    CFunction *func = (CFunction*)this->widget(index);

    m_cFunctionDialog->setCFunction( func );

    m_cFunctionDialog->exec();

}

void CTabWidget::doTabClose(int index)
{
    if( index <= 0 ){ // main不可删
        return;
    }

    removeTab(index);

    emit contentChanged();
}

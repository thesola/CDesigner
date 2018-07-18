#include "ctabwidget.h"
#include "cfunction.h"

#include <QTabBar>
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QFile>
#include <windows.h>
#include <QMessageBox>

#include "global_vars.h"

CTabWidget::CTabWidget(QWidget *parent):QTabWidget(parent)
{
    // 将全局变量指向自身
    g_tabWidget = this;

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
    QString str, dec;

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

    for( int i=1, n=this->count()-1 ; i < n ; ++i ){
        CFunction *func = (CFunction*)this->widget(i);
        str += func->toCCode();
        str += "\n";  // 函数之间空一行
    }

    return str;
}

QString CTabWidget::toCCodeWithTime() const
{
    QString str, dec;

    // 文件头
    str += "#include<time.h>\n";
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

    // 添加 currentTime() 函数：
    str += "long currentTime(){struct timeval tv;gettimeofday(&tv,NULL);return tv.tv_sec*1000+tv.tv_usec/1000;}\n";

    str += ((CFunction*)this->widget(1))->toCCodeWithTime();

    for( int i=2, n=this->count()-1 ; i < n ; ++i ){
        CFunction *func = (CFunction*)this->widget(i);
        str += func->toCCode();
        str += "\n";  // 函数之间空一行
    }

    return str;
}

QStringList CTabWidget::funcNames() const
{
    QStringList list;

    for( int i=2, n=count()-1 ; i < n ; ++i )
    {
        CFunction *func = (CFunction*)this->widget(i);
        list<<func->fucName();
    }

    return list;
}

QStringList CTabWidget::funcArgs(int funcIndex) const
{
    QStringList list;

    funcIndex += 2;	// +2 为在tabWidget中的位置
    if( 2 <= funcIndex && funcIndex < count()-1 )
    {
        CFunction *func = (CFunction*)this->widget(funcIndex);
        foreach (Arg arg, func->argList()) {
            list<<arg.second;
        }
    }

    return list;
}

void CTabWidget::addLibFuncHeader(const QString &libFuncName)
{
    // 根据函数名查找头文件名
    QString fileName = CFunction::libFuncFileName( libFuncName );
qDebug()<<"fileName"<<fileName;
    // 检索头文件是否已经包含
    // 若未包含则包含该头文件
    if( ! m_textEdit->toPlainText().contains( fileName ) ) // 这种检测方法是有问题的 但是很方便 2017/6/20
    {
        // 定位到最后一个头文件包含的位置 添加新头文件
        QString text = m_textEdit->toPlainText();
        int index = text.lastIndexOf( "#include" );
        index = text.indexOf("\n",index);
        text.insert(index+1,"#include<"+fileName+">\n");
        m_textEdit->setText( text );
    }

}

void CTabWidget::doAddFunction()
{
    int oldIndex = currentIndex();

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

        setCurrentIndex( oldIndex );

    }

}

void CTabWidget::addFunction(QString funcName, QStringList funcArgs)
{
    int oldIndex = currentIndex();

    CFunction *newFunc = new CFunction("void",funcName);
    ArgList argList;
    foreach (QString argName, funcArgs) {
        argList.append( Arg("int",argName) );
    }
    newFunc->setArgList( argList );

    int index = insertTab( count()-1, newFunc, funcName+" " );

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

        setCurrentIndex( oldIndex );

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
//    addTab(m_textEdit,"    ");
    QWidget *funcInfo = new QWidget(this);
    QPushButton *pb_addInclude	= new QPushButton("添加头文件");
    QPushButton *pb_addDefine	= new QPushButton("添加宏定义");
    QPushButton *pb_addEnum		= new QPushButton("添加枚举");
    QPushButton *pb_addStruct	= new QPushButton("添加结构体/共用体");

    connect( pb_addInclude, SIGNAL(clicked()), this, SLOT(addInclude()) );
    connect( pb_addDefine, SIGNAL(clicked()), this, SLOT(addDefine()) );
    connect( pb_addStruct, SIGNAL(clicked()), this, SLOT(addStruct()) );
    connect( pb_addEnum, SIGNAL(clicked()), this, SLOT(addEnum()) );

    QFont font("宋体",12);
    pb_addInclude->setFont(font);
    pb_addDefine->setFont(font);
    pb_addStruct->setFont(font);
    pb_addEnum->setFont(font);

    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(pb_addInclude);
    hBoxLayout->addWidget(pb_addDefine);
    hBoxLayout->addWidget(pb_addEnum);
    hBoxLayout->addWidget(pb_addStruct);
    hBoxLayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Minimum));

    QVBoxLayout *vBoxLayout = new QVBoxLayout(funcInfo);
    vBoxLayout->addLayout( hBoxLayout );
    vBoxLayout->addWidget( m_textEdit );

    funcInfo->setLayout( vBoxLayout );
    addTab( funcInfo,"    " );

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

    // 将文本保存到文件
    file.setFileName("cda.c");
    if( ! file.open(QIODevice::WriteOnly | QIODevice::Text) ){
        qDebug()<<"[CTabWidget::runIt] file open failed";
        return ;
    }
    QTextStream out(&file);
    out << this->toCCodeWithTime();
    out.flush();
    file.close();

    QString cmd( gccPath + " cda.c 2> error.log && a.exe && pause && del cda.c a.exe error.log");
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

/****************【编辑非函数部分】*****************************/
#include "caddincludedialog.h"
#include "cadddefinedialog.h"
#include "caddstructdialog.h"
#include "caddenumdialog.h"

void CTabWidget::addInclude()
{
    QString strInclude = CAddIncludeDialog::getIncludeExp();

    if( strInclude == "null" )
    {
        return;
    }

    QString text = m_textEdit->toPlainText();
    int index = text.lastIndexOf("#include");
    index = text.indexOf("\n",index) + 1;

    if( ! text.contains(strInclude) )
    {
        text.insert( index, strInclude );
        m_textEdit->setText(text);
    }
}

void CTabWidget::addDefine()
{
    QString strDefine = CAddDefineDialog::getDefineExp();

    if( strDefine == "null" )
    {
        return;
    }

    QString text = m_textEdit->toPlainText();
    int index = text.lastIndexOf("#include");
    index = text.indexOf("\n",index) + 1;

    int indexDefine = text.lastIndexOf( "#define" );
    if( indexDefine == -1 ) // 是第一个define
    {
        text.insert( index, "\n" + strDefine );
    }
    else
    {
        index = text.indexOf( "\n", indexDefine ) + 1;
        text.insert( index, strDefine );
    }

    m_textEdit->setText(text);
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void CTabWidget::addStruct()
{
    QString strStruct = CAddStructDialog::getStructExp();

    if( strStruct == "null" )
    {
        return;
    }

    QString text = m_textEdit->toPlainText();
    int index = text.lastIndexOf("#include");
    index = text.indexOf("\n",index) + 1;

    int indexStruct1 = text.lastIndexOf( "typedef struct" );
    int indexStruct2 = text.lastIndexOf( "\nstruct" );
    int indexStruct3 = text.lastIndexOf("typedef union");
    int indexStruct4 = text.lastIndexOf( "\nunion" );
    int indexStruct = max( indexStruct1, max( indexStruct2, max( indexStruct3, indexStruct4 ) ) );

    if( indexStruct == -1 ) // 是第一个结构体
    {
        // 先找enum 再找define 再找include 确定index的位置
        int indexEnum = text.lastIndexOf("\nenum");
        if( indexEnum == -1 )
        {
            int indexDefine = text.lastIndexOf("#define");
            if( indexDefine != -1 )
            {
                index = text.indexOf("\n",indexDefine);
            }
        }
        else
        {
            index = text.indexOf( "}", indexEnum );
            index = text.indexOf( "\n", index );
        }

        text.insert( index+1, "\n" + strStruct );

    }
    else
    {
        index = text.indexOf("}",indexStruct);
        index = text.indexOf( "\n", index );
        text.insert( index+1, "\n" + strStruct );
    }

    m_textEdit->setText(text);
}

void CTabWidget::addEnum()
{
    QString strEnum = CAddEnumDialog::getEnumExp();

    if( strEnum == "null" )
    {
        return;
    }

    QString text = m_textEdit->toPlainText();
    int index = text.lastIndexOf("#include");
    index = text.indexOf("\n",index) + 1;


    int indexEnum = text.lastIndexOf("\nenum");
    if( indexEnum == -1 ) // 第一个enum
    {
        // 首先查找define
        // 再查找include
        int indexDefine = text.lastIndexOf("#define");
        if( indexDefine != -1 )
        {
            index = text.indexOf("\n",indexDefine);
            text.insert( index+1, "\n" + strEnum );
        }
        else
        {
            text.insert( index, "\n" + strEnum );
        }

    }
    else
    {
        index = text.indexOf( "}", indexEnum );
        index = text.indexOf("\n", index);
        text.insert( index+1, "\n" + strEnum );
    }


    m_textEdit->setText(text);
}

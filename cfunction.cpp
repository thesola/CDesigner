#include "cfunction.h"
#include <QHBoxLayout>
#include <QDebug>
#include "creturnsentence.h"
#include "csentence.h"

CFunction::CFunction()
{
    // 初始化域
    m_cScope = new CScope();
    m_cScope->setAsFunctionScope(true);
    m_cScope->setParent(this);

    // 设置布局 将域作为唯一控件占满面板
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(m_cScope);
    this->setLayout(layout);

    // 关联信号
    connect( m_cScope, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()));
    connect( m_cScope, SIGNAL(contentChanged()), this, SLOT(doContentChanged()) );

    qDebug()<<"[CFunction::CFunction()] finished. ";
}

CFunction::CFunction(const QString &retType, const QString &fucName)
{
    m_strFucName = fucName;
    m_strRetType = retType;

    // 初始化域
    m_cScope = new CScope();
    m_cScope->setAsFunctionScope(true);

    // 设置布局 将域作为唯一控件占满面板
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(m_cScope);
    this->setLayout(layout);

    // 设置信号联动
    connect( m_cScope, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()) );

    qDebug()<<"[CFunction::CFunction(,)] finished. ";
}

const QString &CFunction::fucName() const
{
    return m_strFucName;
}

const QString &CFunction::retType() const
{
    return m_strRetType;
}

const ArgList &CFunction::argList() const
{
    return m_ArgList;
}

void CFunction::setFucName(const QString &fucName)
{
    this->m_strFucName = fucName;
    // 发出信号
    emit this->contentChanged();
}

void CFunction::setRetType(const QString &retType)
{
    this->m_strRetType = retType;
    // 发出信号
    emit this->contentChanged();
}

void CFunction::setArgList(const ArgList &argList)
{
    this->m_ArgList = argList;
    // 发出信号
    emit this->contentChanged();
}

// 静态方法 返回一个main函数
CFunction *CFunction::getMainFunction()
{
    CFunction *main = new CFunction("int","main");

    CReturnSentence *sentence = new CReturnSentence();
    sentence->setText("0");
    main->m_cScope->insertStastement(-1,sentence);

    // 2017/8/9 添加欢迎3+2语句
    CSentence *welcomeSentence = new CSentence();
    welcomeSentence->setText(QString("puts(\"阿里你好啊~\")"));
    main->m_cScope->insertStastement(0, welcomeSentence);
    CSentence *w1 = new CSentence();
    w1->setText(QString("puts(\"试试把上边的按钮拖下来看看吧^_^\")"));
    main->m_cScope->insertStastement(1, w1);
    CSentence *w2 = new CSentence();
    w2->setText(QString("puts(\"别忘了试试main函数页右边的'+'号和左边的空白页哈~\")"));
    main->m_cScope->insertStastement(2, w2);
    CSentence *w3 = new CSentence();
    w3->setText(QString("puts(\"右击有菜单的哟^_^\")"));
    main->m_cScope->insertStastement(3, w3);
    CSentence *w4 = new CSentence();
    w4->setText(QString("puts(\"下拉按钮拉出的是已定义变量名嘎~(拖拽一个'声明/定义'到这句话上边一点点的位置看看)\")"));
    main->m_cScope->insertStastement(4, w4);

    return main;
}

QString CFunction::toCCode() const
{
    QString code;

    // 返回类型 + 函数名
    code +=  m_strRetType + " " + m_strFucName + "(" ;

    // 参数列表
    if( m_ArgList.isEmpty() ){
        code += "void";

    } else {

        // 参数列表
        code += " " + argToString(m_ArgList) + " ";

    }

    code += ")\n";

    // 域
    code += m_cScope->toCCode(0);

    return code;
}

QString CFunction::toCCodeWithTime() const
{
    QString code;

    // 返回类型 + 函数名
    code +=  m_strRetType + " " + m_strFucName + "(" ;

    // 参数列表
    if( m_ArgList.isEmpty() ){
        code += "void";

    } else {

        // 参数列表
        code += " " + argToString(m_ArgList) + " ";

    }

    code += ")\n";

    // 域
    code += m_cScope->toCCodeWithTime();

    return code;
}

QString CFunction::toFuncDeclare() const
{
    QString dec;

    dec += m_strRetType + " " + m_strFucName + "(";

    if( m_ArgList.isEmpty() ){

        dec += "void";

    } else {

        dec += " ";

        dec += m_ArgList.at(0).first;

        for( int i=1,n=m_ArgList.size() ; i<n ; ++i ){
            dec += ", " + m_ArgList.at(i).first;
        }

        dec += " ";
    }

    dec += ");\n";

    return dec;
}

QString CFunction::argToString(const ArgList argList)
{
    QString args;

    if( ! argList.isEmpty() ){

        args += argList.at(0).first + " " + argList.at(0).second;

        for( int i=1,n=argList.size() ; i<n ; ++i ){
            args += ", " + argList.at(i).first + " " + argList.at(i).second;
        }

    }

    return args;
}

ArgList CFunction::StringToArg(const QString str)
{
    // 解析参数列表
    QStringList  argList;
    ArgList list;

    if( ! str.isEmpty() )
        argList = str.split(","); // 获取以逗号分割的参数列表

    if( ! argList.isEmpty() ){

        foreach (QString arg, argList) {

            QStringList argPair = arg.trimmed().split(" ");
            if( argPair.size() == 2 ) { // 有两个参数
                list.append( Arg( argPair.at(0), argPair.at(1) ) );

            } else {
                list.append( Arg( argPair.at(0), "" ) );

            }

        }

    }

    return list;
}

/**【库函数列表 beg】*******************************************************/
static QMap<QString,QStringList>	s_funcMap;	// 函数名-参数列表
static QMap<QString,QString>		s_funcFile;	// 函数名-头文件名

void initFuncMap()
{
    // 初始化 函数名-参数列表
    if( ! s_funcMap.isEmpty() )
    {
        return;
    }

    s_funcMap.insert( "printf", QStringList()<<"format" );
    s_funcMap.insert( "putchar", QStringList()<<"ch" );
    s_funcMap.insert( "puts", QStringList()<<"str" );
    s_funcMap.insert( "sprintf", QStringList()<<"buffer"<<"format" );
    s_funcMap.insert( "fprintf", QStringList()<<"stream"<<"format" );

    s_funcMap.insert( "scanf", QStringList()<<"format"<<"" );
    s_funcMap.insert( "sscanf", QStringList()<<"source"<<"format"<<"" );
    s_funcMap.insert( "fscanf", QStringList()<<"stream"<<"format"<<"" );
    s_funcMap.insert( "getchar", QStringList() );
    s_funcMap.insert( "gets", QStringList()<<"buffer" );

    s_funcMap.insert( "strlen", QStringList()<<"str" );
    s_funcMap.insert( "strcat", QStringList()<<"dest"<<"source" );
    s_funcMap.insert( "strcpy", QStringList()<<"dest"<<"source" );
    s_funcMap.insert( "strcmp", QStringList()<<"str1"<<"str2" );
    s_funcMap.insert( "memcpy", QStringList()<<"dest"<<"source"<<"size" );

    s_funcMap.insert( "malloc", QStringList()<<"size" );
    s_funcMap.insert( "calloc", QStringList()<<"numOfElements"<<"sizeOfElements" );
    s_funcMap.insert( "free", QStringList()<<"memory" );

    // 初始化 函数名-头文件名
    if( ! s_funcFile.isEmpty() )
    {
        return ;
    }

    s_funcFile.insert( "printf", "stdio" );
    s_funcFile.insert( "putchar", "stdio" );
    s_funcFile.insert( "puts", "stdio" );
    s_funcFile.insert( "sprintf", "stdio" );
    s_funcFile.insert( "fprintf", "stdio" );

    s_funcFile.insert( "scanf", "stdio" );
    s_funcFile.insert( "sscanf", "stdio" );
    s_funcFile.insert( "fscanf", "stdio" );
    s_funcFile.insert( "getchar", "stdio" );
    s_funcFile.insert( "gets", "stdio" );

    s_funcFile.insert( "strlen", "string" );
    s_funcFile.insert( "strcat", "string" );
    s_funcFile.insert( "strcpy", "string" );
    s_funcFile.insert( "strcmp", "string" );
    s_funcFile.insert( "memcpy", "string" );

    s_funcFile.insert( "malloc", "stdlib" );
    s_funcFile.insert( "calloc", "stdlib" );
    s_funcFile.insert( "free", "stdlib" );
}

QStringList CFunction::libFuncNames()
{
    initFuncMap();
    return s_funcMap.keys();
}

QStringList CFunction::libFuncArgs(const QString &funcName)
{
    initFuncMap();
    return s_funcMap.value(funcName);
}

QString CFunction::libFuncFileName(const QString &funcName)
{
    initFuncMap();
    return s_funcFile.value( funcName )+".h";
}

/**【库函数列表 end】*******************************************************/

void CFunction::doContentChanged()
{
    qDebug()<<"[CFunction::doContentChanged]";
}


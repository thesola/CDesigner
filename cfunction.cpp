#include "cfunction.h"
#include <QHBoxLayout>
#include <QDebug>
#include "csentence.h"

CFunction::CFunction()
{
    // 初始化域
    m_cScope = new CScope();
    m_cScope->setAsFunctionScope(true);

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
    main->m_cScope->insertStastement(-1,new CSentence("return 0;"));

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

void CFunction::doContentChanged()
{
    qDebug()<<"[CFunction::doContentChanged]";
}


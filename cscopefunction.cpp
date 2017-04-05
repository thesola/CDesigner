#include "cscopefunction.h"
#include "cscopesentence.h"
#include <QHBoxLayout>

CScopeFunction::CScopeFunction(QWidget *parent):
    CScopeBase(parent),
    mFunctionBody(this)
{

}

CScopeFunction::~CScopeFunction()
{

}

CScopeFunction::CScopeFunction(QString returnType, QString functionName):
    mReturnType(returnType),
    mFunctionName(functionName),
    mFunctionBody(this)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(&mFunctionBody);
}

QString CScopeFunction::functionName() const
{
    return mFunctionName;
}

QList<ArgType> CScopeFunction::args() const
{
    return mArgs;
}

QString CScopeFunction::returnType() const
{
    return mReturnType;
}

void CScopeFunction::setFunctionName(QString functionName)
{
    this->mFunctionName = functionName;
}

void CScopeFunction::setArgs(QList<ArgType> args)
{
    this->mArgs = args;
}

void CScopeFunction::setReturnType(QString returnType)
{
    this->mReturnType = returnType;
}

QString CScopeFunction::resolveDeclare() const
{
    QString str;

    // 解析函数声明
    str += mReturnType + " " + mFunctionName + "(";

    if( mArgs.isEmpty() )
    {
        str += "void";
    }
    else
    {
        QListIterator<ArgType> it(mArgs);
        str += ((ArgType)it.next()).first;
        while( it.hasNext() )
        {
            str += "," + ((ArgType)it.next()).first;
        }
    }

    str += ");";

    return str;
}

QString CScopeFunction::resolveDefination() const
{
    QString str;

    // 函数头
    str += mReturnType + " " + mFunctionName + "(";
    if( mArgs.isEmpty() )
    {
        str += "void";
    }
    else
    {
        QListIterator<ArgType> it(mArgs);
        ArgType arg = it.next();
        str += arg.first + " " + arg.second;
        while(it.hasNext())
        {
            arg = it.next();
            str += ", " + arg.first + " " + arg.second; // 未考虑无参数名情况
        }
    }
    str += ")\n";

    // 解析子域
    str += "{\n";


    str += "}\n";

    return str;
}

CScopeFunction *CScopeFunction::getVoidMain()
{
    CScopeFunction *main = new CScopeFunction("int","main");
    // 无参
    // 添加返回语句
    new CScopeSentence("return 0;",main);
    return main;
}


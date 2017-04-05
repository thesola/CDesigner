#ifndef CSCOPEFUNCTION_H
#define CSCOPEFUNCTION_H

#include <QList>
#include <QPair>
#include "cscopebase.h"
#include "cscopescope.h"

typedef QPair<QString,QString> ArgType ;

class CScopeFunction : public CScopeBase
{
public:
    CScopeFunction(QWidget* parent=0);
    ~CScopeFunction();

    CScopeFunction(QString returnType,QString functionName);

    QString			functionName()const;
    QList<ArgType> 	args()const;
    QString 		returnType()const;

    void setFunctionName(QString functionName);
    void setArgs(QList<ArgType> args);
    void setReturnType(QString returnType);

    // 解析函数声明
    QString resolveDeclare()const;
    // 解析函数实体
    QString resolveDefination()const;

    // 获取空的 main 函数
    static CScopeFunction* getVoidMain();

private:
    QString			mFunctionName;	// 函数名
    QList<ArgType>	mArgs;			// 参数列表
    QString			mReturnType;	// 返回类型
    CScopeScope		mFunctionBody;	// 函数体
};

#endif // CSCOPEFUNCTION_H

/*
 * 函数类 本身不是语句 拥有成员：返回值、函数名、参数列表、域成员
*/
#ifndef CFUNCTION_H
#define CFUNCTION_H

#include <QWidget>
#include "cscope.h"

typedef QPair<QString,QString>	Arg;
typedef QList<Arg>				ArgList;

class CFunction : public QWidget
{
    Q_OBJECT
public:
    CFunction();
    CFunction(const QString &retType, const QString &fucName);

    // getter
    const QString& fucName()const;
    const QString& retType()const;
    const ArgList& argList()const;

    // setter
    void setFucName(const QString& fucName);
    void setRetType(const QString& retType);
    void setArgList(const ArgList& argList);

    // 初始化一个main函数
    static CFunction* getMainFunction();

    // 返回C代码
    QString toCCode()const;

    QString toFuncDeclare()const;

    // 解析参数列表
    static QString argToString(const ArgList argList);
    static ArgList StringToArg(const QString str);

signals:
    void contentChanged();

public slots:
    void doContentChanged();

private:
    QString		m_strFucName;
    QString		m_strRetType;
    ArgList		m_ArgList;
    CScope		*m_cScope;
};

#endif // CFUNCTION_H

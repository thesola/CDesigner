#include "ctabwidget.h"
#include <QDebug>

CTabWidget::CTabWidget(QWidget *parent):QTabWidget(parent)
{
    // 默认添加 main 函数
    addTab(CScopeFunction::getVoidMain());
}

CTabWidget::~CTabWidget()
{

}

void CTabWidget::addTab(CScopeFunction *cScpFunc)
{
    //QString title = cScpFunc->resolveDeclare();
    //title.replace(";",""); // 去除封号
    QString title = cScpFunc->functionName();
    QTabWidget::addTab(cScpFunc,title);
}

QString CTabWidget::toCCode() const
{
    QString str;

    str += "#include <stdio.h>\n" \
           "\n\n";

    // main 只解析实现 不解析声明
    QString funcDefination = ((CScopeFunction*)this->widget(0))->resolveDefination();

    QString funcDeclares;

    // 解析所有函数
    for(int i=1, n=this->count(); i< n; ++i )
    {
        CScopeFunction *func = (CScopeFunction*)this->widget(i);
        funcDeclares	+= func->resolveDeclare();
        funcDefination	+= func->resolveDefination() + "\n"; // 在函数体后追加一个换行符
    }

    str += funcDeclares;
    if( !funcDeclares.isEmpty() )
    {
        str += "\n\n";
    }
    str += funcDefination;

    return str;
}


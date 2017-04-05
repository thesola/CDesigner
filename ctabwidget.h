#ifndef CTABWIDGET_H
#define CTABWIDGET_H

#include <QTabWidget>
#include "cscopefunction.h"

class CTabWidget : public QTabWidget
{
public:
    CTabWidget(QWidget* parent=0);
    ~CTabWidget();

    // 新增
    void addTab(CScopeFunction *cScpFunc);

    // 返回C代码
    QString toCCode()const;
};

#endif // CTABWIDGET_H

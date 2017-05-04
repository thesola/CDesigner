#ifndef CTABWIDGET_H
#define CTABWIDGET_H

#include <QTabWidget>
#include <QMenu>

#include "cfunctiondialog.h"

class CTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    CTabWidget(QWidget* parent=0);

    QString toCCode()const;

    // 读取与配置的文件头
    QString readHeader()const;


public slots:
    void doAddFunction();
    void doOkClicked();

    // 重置面板为 main
    void clearTabs();

    // 编译运行
    void runIt();

private slots:
    void doModifyFunction(int index);
    void doTabClose(int index);

signals:
    void contentChanged();

private:
    CFunctionDialog *m_cFunctionDialog;
    QMenu			*m_menu;
};

#endif // CTABWIDGET_H

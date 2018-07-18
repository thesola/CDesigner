#ifndef CTABWIDGET_H
#define CTABWIDGET_H

#include <QTabWidget>
#include <QTextEdit>
#include <QProcess>

#include "cfunctiondialog.h"

class CTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    CTabWidget(QWidget* parent=0);

    QString toCCode()const;
    QString toCCodeWithTime()const;

    // 获取自定义函数名列表
    QStringList funcNames()const;
    // 获取自定义函数参数名称列表
    QStringList funcArgs(int funcIndex)const;

    // 根据库函数名添加头文件
    void addLibFuncHeader(const QString &libFuncName);

public slots:
    void doAddFunction();
    void addFunction(QString funcName, QStringList funcArgs);
    void doOkClicked();
    void doTabBarClicked();

    // 重置面板为 main
    void clearTabs();

    // 编译运行
    void runIt();

private slots:
    void doModifyFunction(int index);
    void doTabClose();

    // 添加头文件
    void addInclude();
    // 添加宏定义
    void addDefine();
    // 添加结构体/共用体
    void addStruct();
    // 添加枚举
    void addEnum();

signals:
    void contentChanged();

private:
    CFunctionDialog *m_cFunctionDialog;
    QTextEdit		*m_textEdit;
};

#endif // CTABWIDGET_H

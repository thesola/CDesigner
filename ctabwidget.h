#ifndef CTABWIDGET_H
#define CTABWIDGET_H

#include <QTabWidget>
#include <QTextEdit>

#include "cfunctiondialog.h"

class CTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    CTabWidget(QWidget* parent=0);

    QString toCCode()const;


public slots:
    void doAddFunction();
    void doOkClicked();
    void doTabBarClicked();

    // 重置面板为 main
    void clearTabs();

    // 编译运行
    void runIt();


private slots:
    void doModifyFunction(int index);
    void doTabClose();

signals:
    void contentChanged();

private:
    CFunctionDialog *m_cFunctionDialog;
    QTextEdit		*m_textEdit;
};

#endif // CTABWIDGET_H

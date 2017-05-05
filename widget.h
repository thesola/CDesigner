#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include <QMenuBar>

#include "ctabwidget.h"
#include "cbutton.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    // 处理变化信号
public slots:
    void doContentChanged();

private:
    // 三个主面板
    QWidget			*mToolBar;
    CTabWidget		*mTabWidget;
    QTextBrowser	*mTextBrowser;

    // 工具按钮
    CButton *mBtnIf;
    CButton	*mBtnIfElse;
    CButton	*mBtnWhile;
    CButton	*mBtnDWhile;
    CButton	*mBtnSwitch;
    CButton	*mBtnFor;
//    CButton	*mBtnFunc;
//    CButton	*mBtnScope;

    CButton	*mBtnSentence;
    CButton *mBtnBreakSentence;
    CButton *mBtnContinueSentence;
    CButton *mBtnReturnSentence;

    // 菜单栏
    QMenuBar *m_menubar;

};

#endif // WIDGET_H

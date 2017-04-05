#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include "cbuttonif.h"
#include "cbuttonswitch.h"
#include "cbuttonwhile.h"
#include "cbuttondwhile.h"
#include "cbuttonsentence.h"
#include "cbuttonscope.h"
#include "cbuttonfor.h"
#include "cbuttonfunction.h"
#include "ctabwidget.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    // 三个主面板
    QWidget				*mToolBar;
    CTabWidget			*mTabWidget;
    QTextBrowser		*mTextBrowser;

    // 工具按钮
    CButtonScope		*mBtnScope;
    CButtonSentence		*mBtnSentence;
    CButtonIf			*mBtnIf;
    CButtonWhile		*mBtnWhile;
    CButtonDWhile		*mBtnDWhile;
    CButtonSwitch		*mBtnSwitch;
    CButtonFor			*mBtnFor;
    CButtonFunction		*mBtnFunc;

};

#endif // WIDGET_H

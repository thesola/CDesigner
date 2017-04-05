#include "widget.h"
#include <QPushButton>
#include <QLayout>
#include <QSplitter>
#include <QDebug>

#include "cscopefunction.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    resize( 1024, 768 );	// 设置窗口大小

    mToolBar		= new QWidget();
    mTabWidget		= new CTabWidget();
    mTextBrowser	= new QTextBrowser();

    // 初始化工具栏内容
    mBtnScope 		= new CButtonScope(mToolBar);
    mBtnSentence	= new CButtonSentence(mToolBar);
    mBtnIf			= new CButtonIf(mToolBar);
    mBtnSwitch		= new CButtonSwitch(mToolBar);
    mBtnWhile		= new CButtonWhile(mToolBar);
    mBtnDWhile		= new CButtonDWhile(mToolBar);
    mBtnFor			= new CButtonFor(mToolBar);
    mBtnFunc		= new CButtonFunction(mToolBar);

    QVBoxLayout *vlayout= new QVBoxLayout(mToolBar);
    vlayout->setMargin(0);
    vlayout->addWidget(mBtnScope);
    vlayout->addWidget(mBtnSentence);
    vlayout->addWidget(mBtnIf);
    vlayout->addWidget(mBtnSwitch);
    vlayout->addWidget(mBtnWhile);
    vlayout->addWidget(mBtnDWhile);
    vlayout->addWidget(mBtnFor);
    vlayout->addWidget(mBtnFunc);
    vlayout->addStretch();	// 填充伸缩条

    // 初始化选项卡面板内容
    mTabWidget->setFont(QFont("宋体",12));

    // 初始化显示文本面板内容
    mTextBrowser->setFont(QFont("Consolas",15));
    mTextBrowser->setText(mTabWidget->toCCode());

    // 初始化页面整体布局
    // 水平布局工具栏和工作区 水平分割工作区

    QSplitter *splitter = new QSplitter();
    splitter->addWidget(mTabWidget);
    splitter->addWidget(mTextBrowser);
    splitter->setStyleSheet("QSplitter::handle{width:1px;border:none;border-left:2px dashed #5ca7ba}");
    splitter->setHandleWidth(2);
    // 以下两个数字为多次尝试结果
    splitter->setStretchFactor(0,4);
    splitter->setStretchFactor(1,1);

    QHBoxLayout *hlayout = new QHBoxLayout(this);
    hlayout->addWidget(mToolBar);
    hlayout->addWidget(splitter);

    // 最大化
    this->showMaximized();
}

Widget::~Widget()
{
}

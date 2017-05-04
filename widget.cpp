#include "widget.h"
#include <QLayout>
#include <QSplitter>
#include <QDebug>
#include <cdef.h>


Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    resize( 1024, 768 );	// 设置窗口大小

    mToolBar		= new QWidget();
    mTabWidget		= new CTabWidget();
    mTextBrowser	= new QTextBrowser();

    // 初始化工具栏内容
//    mBtnScope 		= new CButton( g_strBtnScope );
    mBtnStatement	= new CButton( g_strBtnStatement );
    mBtnIf			= new CButton( g_strBtnIf );
    mBtnIfElse		= new CButton( g_strBtnIfElse );
//    mBtnSwitch		= new CButton( g_strBtnSwitch );
    mBtnWhile		= new CButton( g_strBtnWhile );
    mBtnDWhile		= new CButton( g_strBtnDoWhile );
    mBtnFor			= new CButton( g_strBtnFor );
    mBtnFunc		= new CButton( g_strBtnFunction );

    QVBoxLayout *vlayout= new QVBoxLayout(mToolBar);
    vlayout->setMargin(0);
//    vlayout->addWidget(mBtnScope);
    vlayout->addWidget(mBtnStatement);
    vlayout->addWidget(mBtnIf);
    vlayout->addWidget(mBtnIfElse);
//    vlayout->addWidget(mBtnSwitch);
    vlayout->addWidget(mBtnWhile);
    vlayout->addWidget(mBtnDWhile);
    vlayout->addWidget(mBtnFor);
    vlayout->addWidget(mBtnFunc);
    vlayout->addStretch();	// 填充伸缩条

    // 添加全局标签 用于显示附加信息
    g_label = new QLabel("     双击\n 函数名以\n 修改函数\n 声明\n     main\n 函数不可\n 修改声明\n\nC.D.V. 1.0");
    vlayout->addWidget(g_label);

    // 初始化选项卡面板内容
    mTabWidget->setFont(QFont("宋体",12));

    // 初始化显示文本面板内容
    mTextBrowser->setFont(QFont("Consolas",15));
    mTextBrowser->setText(mTabWidget->toCCode());

    // 水平布局工具栏和工作区 水平分割工作区
    QSplitter *splitter = new QSplitter();
    splitter->addWidget(mTabWidget);
    splitter->addWidget(mTextBrowser);
    splitter->setStyleSheet("QSplitter::handle{width:1px;border:none;border-left:2px dashed #5ca7ba}");
    splitter->setHandleWidth(2);

    // 将主面板组合起来
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(mToolBar);
    hlayout->addWidget(splitter);

    // 设置菜单
    m_menubar = new QMenuBar(this);
    m_menubar->addAction("重置", mTabWidget, SLOT(clearTabs()));
    m_menubar->addAction("编译&&运行", mTabWidget, SLOT(runIt()));
//    m_menubar->addAction("运行");
//    m_menubar->setStyleSheet("QMenuBar{background:rgba(0,0,0,10)}");

    // 将菜单和主面板组合起来
    QVBoxLayout *vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->addWidget( m_menubar );
    vBoxLayout->addLayout( hlayout );
    vBoxLayout->setContentsMargins(8,0,8,8);



    // 最大化
    this->showMaximized();

    // 关联界面的重绘信号
    connect( mTabWidget, SIGNAL(contentChanged()), this, SLOT(doContentChanged()) );

    // 关联添加函数信号
    connect( mBtnFunc, SIGNAL(clicked()), mTabWidget, SLOT(doAddFunction()) );
}

Widget::~Widget()
{
}

void Widget::doContentChanged()
{
    qDebug()<<"[Widget::doContentChanged]";
    mTextBrowser->setText( mTabWidget->toCCode() );
}

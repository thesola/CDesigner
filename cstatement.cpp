#include "cstatement.h"
#include "cdef.h"
#include "cif.h"
#include "cifelse.h"
#include "cwhile.h"
#include "cdowhile.h"
#include "cfor.h"
#include "cscope.h"
#include "csentence.h"
#include "cswitch.h"
#include "cbreaksentence.h"
#include "ccontinuesentence.h"
#include "creturnsentence.h"
#include <QMimeData>
#include <QDebug>

CStatement::CStatement(QWidget *parent) : QWidget(parent)
{
    setMinimumHeight(40);

    // 默认父域为空
    m_parentScope = NULL;

    // 设置可填充背景
    setAutoFillBackground(true);
    // 水平/垂直方向均扩张
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    // 接收drop
    setAcceptDrops(true);

    // 设置菜单
    m_menu = new QMenu(this);
    m_menu->addAction("删除",this,SLOT(deleteSelf()));
}

CStatement::~CStatement()
{
    delete m_menu;
}

void CStatement::resizeEvent(QResizeEvent *e)
{
    QPixmap pixmap(this->size());
    pixmap.fill(Qt::transparent); // 透明化
    QPainter painter(&pixmap);
    painter.setPen(QPen(QColor(255,66,93),3));
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制矩形边框
    painter.drawRect( 0,0, this->width(), this->height() );

    drawBackGround(painter);

    // 绘制灰色背景

    QPalette palette = this->palette();
    palette.setBrush(this->backgroundRole(),QBrush(pixmap));
    setPalette(palette);

    QWidget::resizeEvent(e);

//    qDebug()<<"[CStatement::resizeEvent] e : "<<e;
}

void CStatement::dragEnterEvent(QDragEnterEvent *e)
{
    e->accept();
}

void CStatement::dropEvent(QDropEvent *e)
{
    if( m_parentScope == NULL ){ // 无父级域
        return;
    }

    QString name = e->mimeData()->text();
    CStatement *newStatement = getStatementByName( name );

    if( newStatement == NULL ){
        return;
    }

    int pos = m_parentScope->indexOfStatement(this);
    // 可能是插到后边
    pos += mapFromGlobal(QCursor::pos()).y() > this->height()/2;

    // 插入到指定位置
    m_parentScope->insertStastement( pos, newStatement );
}

CStatement *CStatement::getStatementByName(QString name)
{
    if( name == g_strBtnSentence ){
        return new CSentence;
    } else if ( name == g_strBtnIf ) {
        return new CIf;
    } else if ( name == g_strBtnIfElse ) {
        return new CIfElse;
    } else if ( name == g_strBtnWhile ) {
        return new CWhile;
    } else if ( name == g_strBtnDoWhile ) {
        return new CDoWhile;
    } else if ( name == g_strBtnFor ) {
        return new CFor;
    } else if ( name == g_strBtnSwitch ) {
        return new CSwitch;
    } else if ( name == g_strBtnBreakSentence ) {
        return new CBreakSentence;
    } else if ( name == g_strBtnContinueSentence ) {
        return new CContinueSentence;
    } else if ( name == g_strBtnReturnSentence ) {
        return new CReturnSentence;
    }

    return NULL;
}

void CStatement::mousePressEvent(QMouseEvent *e)
{
    if( Qt::LeftButton == e->button() ){ // 左键 无视
        return;
    }

    m_menu->popup(QCursor::pos());
}

/*
 * BUG
 * 当前方法未结束 控件已被删除 函数调用异常
 *
 * 百思不得解 给个老程序员分分钟找到了问题 可怕
 *
 * 理想：
 * 解决方法：交由主控件的方法来删除当前控件，而不是自己的方法删除自己
 *
 * 实际：
 * 暂时不删除控件 泄漏点内存吧 程序不会崩 懒得改了
*/
void CStatement::deleteSelf()
{
    if( m_parentScope != NULL ){
        m_parentScope->deleteStatement( this );
    }
}

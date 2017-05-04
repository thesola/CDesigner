#include "cstatement.h"
#include "cdef.h"
#include "cif.h"
#include "cifelse.h"
#include "cwhile.h"
#include "cdowhile.h"
#include "cfor.h"
#include "cscope.h"
#include "csentence.h"
#include <QMimeData>
#include <QDebug>

CStatement::CStatement(QWidget *parent) : QWidget(parent)
{
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

void CStatement::resizeEvent(QResizeEvent *e)
{
    QPixmap pixmap(this->size());
    pixmap.fill(Qt::transparent); // 透明化
    QPainter painter(&pixmap);
    painter.setPen(QPen(QColor(255,66,93),3));
    painter.setRenderHint(QPainter::Antialiasing);

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

    int pos = m_parentScope->indexOfStatement(this);
    // 可能是插到后边
    pos += e->pos().y() > this->height()/2;

    QString name = e->mimeData()->text();

    // 插入到指定位置
    m_parentScope->insertStastement( pos, getStatementByName( name ) );
}

CStatement *CStatement::getStatementByName(QString name)
{
    if( name == g_strBtnStatement ){
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
    }

    return NULL;
}

void CStatement::mousePressEvent(QMouseEvent *e)
{
    if( Qt::LeftButton == e->button() ){ // 左键 无视
        return;
    }

    m_menu->setGeometry( QCursor::pos().x() , QCursor::pos().y(), 90, 30 );
    m_menu->show();
}

#include <QDebug>
void CStatement::deleteSelf()
{
    if( m_parentScope != NULL ){
        m_parentScope->deleteStatement( this );
    }
}

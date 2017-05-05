#include "cscope.h"
#include <QDebug>
#include "cdef.h"
#include <QMimeData>

CScope::CScope()
{
    // 设置垂直布局器
    m_vBoxLayout = new QVBoxLayout(this);

    // 去除margin
    m_vBoxLayout->setMargin(0);

    // 去除间隔
    m_vBoxLayout->setSpacing(0);

    m_bIsFunctionScope = false;
}

void CScope::insertStastement(int index, CStatement *state)
{
    qDebug()<<"[CScope::insertStastement] index : "<<index<<" , state : "<< state;
    m_vBoxLayout->insertWidget(index,state);
    state->m_parentScope = this;

    // 发出信号
    emit contentChanged();
    // 关联信号
    connect( state, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()) );

    qDebug()<<"[CScope::insertStastement] finished ";
}

void CScope::deleteStatement(CStatement *state)
{
    // 取关信号
    disconnect( state, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()) );

    qDebug()<<"[CScope::deleteStatement] state : "<< state;
    m_vBoxLayout->removeWidget(state);
//    delete state;
    state->hide();

    // 发出信号
    emit contentChanged();
}

int CScope::indexOfStatement(CStatement *state)
{
    qDebug()<<"[CScope::indexOfStatement] state : "<< state;
    return m_vBoxLayout->indexOf(state);
}

void CScope::dropEvent(QDropEvent *e)
{
    CStatement *newStatement = getStatementByName( e->mimeData()->text() );

    if( newStatement == NULL ) {
        return;
    }

    insertStastement( 0, newStatement );
}

void CScope::drawBackGround(QPainter &painter)
{
    if( m_bIsFunctionScope ){
        painter.drawRect( 2, 2, this->width()-4, this->height()-4 );
    }
}

QString CScope::toCCode(int indent) const
{
    QString strIndent(indent,' ');
    QString strCode;

    strCode +=  strIndent + "{\n";

    for( int i=0, n=this->m_vBoxLayout->count() ; i<n ; ++i ){
        strCode +=  ((CStatement*)this->m_vBoxLayout->itemAt(i)->widget())->toCCode(indent+g_s32Indent);
    }

    strCode +=  strIndent + "}\n";

    return strCode;
}

void CScope::setAsFunctionScope(bool flag)
{
    m_bIsFunctionScope = flag;
}

void CScope::deleteSelf()
{
    if( m_parentScope != NULL ){
        CStatement::deleteSelf();
        return;
    }

    if( this->parent() != NULL ){
        ((CStatement*)this->parent())->deleteSelf();
    }
}

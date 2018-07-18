#include "cscope.h"
#include <QDebug>
#include "cdef.h"
#include <QMimeData>
#include "cdeclare.h"
#include "cfunction.h"

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
    state->setParentScope(this);

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

QString CScope::toCCodeWithTime() const
{
    QString strCode;

    strCode +=  "{\n";

    strCode += "    long t1 = currentTime();\n";

    int i, n;
    for( i=0, n=this->m_vBoxLayout->count()-1 ; i<n ; ++i ){
        strCode +=  ((CStatement*)this->m_vBoxLayout->itemAt(i)->widget())->toCCode(g_s32Indent);
    }

    strCode += "    long t2 = currentTime();\n"
                "    printf(\"\\n--------------------\\n运行时长 : %ld 毫秒\\n\", t2-t1);\n"
                ;

    strCode +=  ((CStatement*)this->m_vBoxLayout->itemAt(i)->widget())->toCCode(g_s32Indent);

    strCode +=  "}\n";

    return strCode;
}

void CScope::setAsFunctionScope(bool flag)
{
    m_bIsFunctionScope = flag;
}

void CScope::deleteSelf()
{
    if( m_parentScope != NULL ){ // 作为一个独立的对象来删除自身
        CStatement::deleteSelf();
        return;
    }

    if( this->parent() != NULL ){ // 作为父对象的一部分来删除父对象
        ((CStatement*)this->parent())->deleteSelf();
    }
}

void CScope::mousePressEvent(QMouseEvent *e)
{
    if( m_bIsFunctionScope ){
        return;
    }
    CStatement::mousePressEvent(e);
}

// 2017/6/14 获取指定语句所能获取的语句列表
QStringList CScope::getVarsBefore(CStatement *state)
{
    QStringList list;

    // 获取当前域中的变量列表
    int index = indexOfStatement(state);
    if( index != -1 )
    {
        for( int i = index-1 ; i >= 0 ; --i ) // 逆序添加
        {
            CStatement *state = (CStatement*)m_vBoxLayout->itemAt(i)->widget();
            if( state->inherits( "CDeclare" ) )
            {
                CDeclare *dec = (CDeclare*)state;
//                list.append(dec->getVarName());
                list += dec->getVarNames();
            }
        }
    }

    // 获取上级域的变量列表
    if( m_parentScope != NULL ) // 当前域为独立控件
    {
        list += m_parentScope->getVarsBefore( this );
    }
    else if ( ! m_bIsFunctionScope ) // 当前为子控件且非函数域
    {
        CStatement *parentStatement = (CStatement*)this->parent();
        list += parentStatement->parentScope()->getVarsBefore( parentStatement );
    }
    // 否则为函数域子控件 添加函数参数列表
    else
    {
        CFunction *func = (CFunction*)this->parent();
        ArgList args = func->argList();
        foreach (Arg arg, args) {
            if( ! arg.second.trimmed().isEmpty() )
            {
                list.append( arg.second.trimmed() );
            }
        }
    }


    return list;
}

#include "cif.h"
#include <QVBoxLayout>
#include <QPainter>
#include "cdef.h"

CIf::CIf()
{
    m_lineEdit = new CLineEdit();
    m_cScope = new CScope();

    m_lineEdit->setStatement(this);

    m_lineEdit->setParent(this);
    m_cScope->setParent(this);

    m_label = new QLabel("Y", this);
    m_label->setFont(QFont("宋体",14,QFont::Bold));
    m_label->setStyleSheet("QLabel{color:red}");

    // 设置信号联动
    connect( m_lineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(contentChanged()) );
    connect( m_cScope, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()) );
}

void CIf::drawBackGround(QPainter &painter)
{
    painter.drawPath( g_getPPathIf(this->width(),this->height()) );
}

// 垂直分割比为 1:5 水平分割比为 5:2
void CIf::resizeEvent(QResizeEvent *e)
{
    // 重置组件位置

    m_lineEdit->setGeometry( this->width()/20.*9, this->height()/14.-15, this->width()/3, 30 );
    m_cScope->setGeometry( 0,this->height()/6-1, this->width()/7*5,this->height() - this->height()/6+1 );
    m_label->setGeometry( this->width()/7, this->height()/32.*3-15,30,30 );

    CStatement::resizeEvent(e);
}

CScope *&CIf::cScope()
{
    return m_cScope;
}

void CIf::mousePressEvent(QMouseEvent *e)
{
    if( e->button() != Qt::LeftButton ){
        CStatement::mousePressEvent(e);
        return;
    }

    m_lineEdit->setFocus();
}

QString CIf::toCCode(int indent) const
{
    QString code, strIndent(indent,' ');

    // if 以及表达式
    code += strIndent + "if( " + m_lineEdit->text().trimmed() + " )\n";

    // 域
    code += m_cScope->toCCode(indent) + "";

    return code;
}

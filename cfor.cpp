#include "cfor.h"

CFor::CFor()
{
    m_cScope = new CScope();
    m_exp1 = new CLineEdit();
    m_exp2 = new CLineEdit();
    m_exp3 = new CLineEdit();

    m_cScope->setParent(this);
    m_exp1->setParent(this);
    m_exp2->setParent(this);
    m_exp3->setParent(this);

    // 设置信号联动
    connect( m_cScope, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()) );
    connect( m_exp1, SIGNAL(textChanged(QString)), this, SIGNAL(contentChanged()) );
    connect( m_exp2, SIGNAL(textChanged(QString)), this, SIGNAL(contentChanged()) );
    connect( m_exp3, SIGNAL(textChanged(QString)), this, SIGNAL(contentChanged()) );
}

void CFor::drawBackGround(QPainter &painter)
{
    // 绘制 exp1 与 exp2 之间的线
    painter.drawLine( 0, this->height()/10, this->width(), this->height()/10 );
    // 绘制 exp3 左边的竖线
    painter.drawLine( this->width()/10+2, this->height()-this->height()/10, this->width()/10+2,this->height()-2 );
    // 绘制底线
    painter.drawLine( 0, this->height()-2,this->width(),this->height()-2 );
}

void CFor::resizeEvent(QResizeEvent *e)
{

    m_exp1->setGeometry( 0, this->height()/20.-15,this->width(), 30 );
    m_exp2->setGeometry( 0, this->height()/20.*3-15,this->width(), 30 );
    m_cScope->setGeometry( this->width()/10, this->height()/20.*4, this->width()-this->width()/10,this->height()/20.*14 );
    m_exp3->setGeometry( this->width()/10, this->height()/20.*19-15, this->width()-this->width()/10, 30 );

    CStatement::resizeEvent(e);
}

QString CFor::toCCode(int indent) const
{
    QString code, strIndent(indent,' ');

    code += strIndent + "for( " + m_exp1->text().trimmed() + " ; " + m_exp2->text().trimmed() + " ; " + m_exp3->text().trimmed() + " )\n";
    code += m_cScope->toCCode(indent);

    return code;
}

CScope *CFor::cScope() const
{
    return this->m_cScope;
}

void CFor::mousePressEvent(QMouseEvent *e)
{
    if( e->button() != Qt::LeftButton ){
        CStatement::mousePressEvent(e);
        return;
    }

    if( e->pos().y() < this->height()/10. ){
        m_exp1->setFocus();

    } else if ( e->pos().y() < this->height()/10.*9 || e->pos().x() < this->width()/10 ) {
        m_exp2->setFocus();

    } else {
        m_exp3->setFocus();

    }
}


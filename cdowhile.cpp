#include "cdowhile.h"

CDoWhile::CDoWhile()
{
    m_cScope = new CScope();
    m_lineEdit = new CLineEdit();

    m_cScope->setParent(this);
    m_lineEdit->setParent(this);

    // 设置联动信号
    connect( m_cScope, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()) );
    connect( m_lineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(contentChanged()) );
}

void CDoWhile::drawBackGround(QPainter &painter)
{
//    painter.drawLine( 0,this->height()-2, this->width(),this->height()-2 );
    // 绘制拐线
    painter.drawLine( this->width()-this->width()/10, 0, this->width()-this->width()/10, this->height()-this->height()/7 );
    painter.drawLine( this->width()-this->width()/10, this->height()-this->height()/7, 0, this->height()-this->height()/7 );
}

void CDoWhile::resizeEvent(QResizeEvent *e)
{
    m_cScope->setGeometry( 0, 0, this->width()-this->width()/10,this->height()-this->height()/7 );
    m_lineEdit->setGeometry( 0, this->height()-this->height()/14-15,this->width(), 30 );

    CStatement::resizeEvent(e);
}

QString CDoWhile::toCCode(int indent) const
{
    QString code, strIndent(indent, ' ');

    code += strIndent + "do\n";
    code += m_cScope->toCCode(indent);
    code += strIndent + "while( " + m_lineEdit->text().trimmed() + " );\n";

    return code;
}

CScope *CDoWhile::cScope() const
{
    return m_cScope;
}

void CDoWhile::mousePressEvent(QMouseEvent *e)
{
    if( e->button() != Qt::LeftButton ){
        CStatement::mousePressEvent(e);
        return;
    }

    m_lineEdit->setFocus();
}


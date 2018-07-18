#include "cwhile.h"

CWhile::CWhile()
{
    m_cScope = new CScope();
    m_lineEdit = new CLineEdit();

    m_lineEdit->setStatement(this);

    m_cScope->setParent(this);
    m_lineEdit->setParent(this);

    // 设置信号联动
    connect( m_cScope, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()) );
    connect( m_lineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(contentChanged()) );
}

void CWhile::resizeEvent(QResizeEvent *e)
{

    m_lineEdit->setGeometry(0,this->height()/14-15,this->width(),30);
    m_cScope->setGeometry(this->width()/10,this->height()/7,this->width()-this->width()/10,this->height()-this->height()/7);

    CStatement::resizeEvent(e);
}

void CWhile::drawBackGround(QPainter &painter)
{
 //   painter.drawLine( 0, this->height()-2, this->width(),this->height() );
    // 绘制拐线
    painter.drawLine( this->width()/10,this->height()/7, this->width(), this->height()/7 );
    painter.drawLine( this->width()/10,this->height()/7, this->width()/10, this->height() );
}

QString CWhile::toCCode(int indent) const
{
    QString code, strIndent(indent,' ');

    code += strIndent + "while( " + m_lineEdit->text().trimmed() + " )\n";
    code += m_cScope->toCCode(indent) + "";

    return code;
}

CScope *CWhile::cScope()
{
    return m_cScope;
}

void CWhile::mousePressEvent(QMouseEvent *e)
{
    if( e->button() != Qt::LeftButton ){
        CStatement::mousePressEvent(e);
        return;
    }

    m_lineEdit->setFocus();
}


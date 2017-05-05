#include "cswitch.h"
#include "ccase.h"
#include <QDebug>

CSwitch::CSwitch()
{
    m_lineEdit = new CLineEdit("表达式");
    m_cases = new QWidget(this);

    m_lineEdit->setParent(this);

    m_vBoxLayout->setParent( m_cases );
    m_cases->setLayout( m_vBoxLayout );

    this->insertStastement(0, new CCase );
    this->insertStastement(1,CCase::getDefaultCase());

    connect( m_lineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(contentChanged()) );
}

CSwitch::~CSwitch()
{

}

void CSwitch::drawBackGround(QPainter &painter)
{
    // 绘制横线
    painter.drawLine( 0, this->height()/6, this->width(), this->height()/6 );
    // 绘制斜线
    painter.drawLine( 0, 0, this->width()/4,this->height()/6 );
    painter.drawLine( this->width(), 0, this->width()-this->width()/4, this->height()/6 );

}

QString CSwitch::toCCode(int indent) const
{
    QString code, strIndent(indent,' ');

    code += strIndent + "switch ( " + m_lineEdit->text().trimmed() + " )\n";
    code += strIndent + "{\n";

    for( int i=0, n=m_vBoxLayout->count() ; i<n ; ++i ){
        code += ((CCase*)m_vBoxLayout->itemAt(i)->widget())->toCCode(indent);
    }

    code += strIndent + "}\n";

    return code;
}

void CSwitch::resizeEvent(QResizeEvent *e)
{
    m_cases->setGeometry( 0, this->height()/6, this->width(), this->height()-this->height()/6 );
    m_lineEdit->setGeometry( this->width()/4, this->height()/12.-15, this->width()/2, 30 );
    CScope::resizeEvent(e);
}

void CSwitch::mousePressEvent(QMouseEvent *e)
{
    if( e->button() != Qt::LeftButton ){
        CScope::mousePressEvent(e);
        return;
    }

    m_lineEdit->setFocus();
}

void CSwitch::dropEvent(QDropEvent *e)
{
    CStatement::dropEvent(e);
}


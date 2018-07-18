#include "cifelse.h"
#include "cdef.h"
#include <QDebug>

CIfElse::CIfElse()
{
    m_YesLabel = new QLabel("Y",this);
    m_NotLabel = new QLabel("N",this);

    m_YesLabel->setFont(QFont("宋体",14,QFont::Bold));
    m_NotLabel->setFont(QFont("宋体",14,QFont::Bold));

    m_YesLabel->setStyleSheet("color:red");
    m_NotLabel->setStyleSheet("color:red");

    m_cYesScope = new CScope();
    m_cNotScope = new CScope();
    m_lineEdit = new CLineEdit();

    m_cYesScope->setParent(this);
    m_cNotScope->setParent(this);
    m_lineEdit->setParent(this);

    m_lineEdit->setStatement(this);

    // 设置挡板
    m_baffle = new CBaffle(this);

    // 设置信号联动
    connect( m_cYesScope, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()) );
    connect( m_cNotScope, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()) );
    connect( m_lineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(contentChanged()) );
    connect( m_baffle, SIGNAL(baffleDropEvent(QDropEvent*)), this, SLOT(doBaffleDrop(QDropEvent*)) );
}

void CIfElse::drawBackGround(QPainter &painter)
{
    painter.drawPath( g_getPPathIfElse(this->width(),this->height()) );
}


void CIfElse::resizeEvent(QResizeEvent *e)
{
    m_lineEdit->setGeometry( this->width()/4,this->height()/14-15,this->width()/2,30 );

    m_YesLabel->setGeometry( this->width()/7, this->height()/32.*3-15,30,30 );
    m_NotLabel->setGeometry( this->width()-this->width()/7, this->height()/32.*3-15,30,30 );

    m_cYesScope->setGeometry( 0, this->height()/6, this->width()/2,this->height()-this->height()/6 );
    m_cNotScope->setGeometry(this->width()/2,this->height()/6,this->width()/2+1,this->height()-this->height()/6);

    // 设置挡板的位置
    m_baffle->setGeometry( this->width()/4, this->height()-this->height()/5, this->width()/2, this->height()/5 );

    CStatement::resizeEvent(e);
}

QString CIfElse::toCCode(int indent) const
{
    QString code, strIndent(indent, ' ');

    code +=  strIndent + "if( " + m_lineEdit->text().trimmed() + " )\n";
    code += m_cYesScope->toCCode(indent);
    code += strIndent + "else\n";
    code += m_cNotScope->toCCode(indent) + "";

    return code;
}

CScope *CIfElse::yesScope()
{
    return m_cYesScope;
}

CScope *CIfElse::notScope()
{
    return m_cNotScope;
}

void CIfElse::mousePressEvent(QMouseEvent *e)
{
    if( e->button() != Qt::LeftButton ){
        CStatement::mousePressEvent(e);
        return;
    }

    m_lineEdit->setFocus();
}

void CIfElse::doBaffleDrop(QDropEvent *e)
{
    dropEvent(e);
}

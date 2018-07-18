#include "ccase.h"
#include "cdef.h"
#include "cbreaksentence.h"
#include <QDebug>

CCase::CCase()
{
    m_label = new QLabel("case", this);
    m_lineEdit = new CLineEdit("值");
    m_statements = new QWidget(this);

    m_lineEdit->setStatement(this);
    m_lineEdit->setText("值");

    m_lineEdit->setParent(this);
    m_vBoxLayout->setParent(m_statements);
    m_statements->setLayout(m_vBoxLayout);

    m_label->setFont(QFont("宋体",14,QFont::Bold));
    m_label->setStyleSheet("QLabel{color:black}");

    m_label->hide();

    insertStastement(-1,new CBreakSentence);

    connect( this->m_lineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(contentChanged()) );

    // 菜单设置
    m_menu->clear();
    m_menu->addAction("添加 上", this, SLOT(doAddBefore()));
    m_menu->addAction("添加 下", this, SLOT(doAddAfter()) );
    m_menu->addAction("删除", this, SLOT(doDeleteSelf()) );
}

CCase::~CCase()
{
    
}

void CCase::drawBackGround(QPainter &painter)
{
//    painter.drawLine( 0,this->height()-2, this->width(), this->height()-2 );
    painter.drawLine( this->width()/28.*5, 0, this->width()/28.*3, this->height() );
    painter.drawLine( this->width()/28.*5, 0, this->width()/28.*5, this->height() );
}

void CCase::resizeEvent(QResizeEvent *e)
{

    m_statements->setGeometry( this->width()/28.*5, 0, this->width()-this->width()/28.*5 , this->height() );

    if( m_lineEdit != NULL ){
        m_lineEdit->setGeometry( this->width()/28., this->height()/2.-15, this->width()/14., 30 );

    } else {
        m_label->setGeometry( this->width()/56., this->height()/2.-15, 100, 30 );

    }

    CScope::resizeEvent(e);
}

QString CCase::toCCode(int indent) const
{
    QString code, strIndent(indent, ' ');

    code += strIndent + m_label->text();

    if( m_lineEdit != NULL ){
        code += " " + m_lineEdit->text().trimmed();
    }

    code += ":\n";

    for( int i=0, n=this->m_vBoxLayout->count() ; i<n ; ++i ){
        code +=  ((CStatement*)this->m_vBoxLayout->itemAt(i)->widget())->toCCode(indent+g_s32Indent);
    }

    return code;
}

void CCase::dropEvent(QDropEvent *e)
{
    if( e->pos().x() > this->width()/7.*2 ){
        CScope::dropEvent(e);
        return;
    }

    // 交由 switch 处理
    if( m_parentScope ){
        m_parentScope->dropEvent(e);
    }
}

void CCase::mousePressEvent(QMouseEvent *e)
{
    if( e->button() != Qt::LeftButton ){
        CScope::mousePressEvent(e);
        return;
    }

    if( m_lineEdit != NULL ){
        m_lineEdit->setFocus();
    }
}

CCase *CCase::getDefaultCase()
{
    CCase *defaultCase = new CCase();

    defaultCase->m_label->setText("default");
    defaultCase->m_label->show();

    delete defaultCase->m_lineEdit;
    defaultCase->m_lineEdit = NULL;

    defaultCase->m_menu->clear();
    defaultCase->m_menu->addAction("添加 上", defaultCase, SLOT(doAddBefore()));

    return defaultCase;
}

void CCase::doAddBefore()
{
    if( m_parentScope == NULL ){
        return;
    }

    m_parentScope->insertStastement( m_parentScope->indexOfStatement(this), new CCase );
}

void CCase::doAddAfter()
{
    if( m_parentScope == NULL ){
        return;
    }

    m_parentScope->insertStastement( m_parentScope->indexOfStatement(this)+1, new CCase );
}

void CCase::doDeleteSelf()
{
    if( m_parentScope == NULL ){
        return;
    }

    m_parentScope->deleteStatement( this );
}


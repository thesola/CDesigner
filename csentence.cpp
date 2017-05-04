#include "csentence.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QDebug>

CSentence::CSentence(QString text)
{
    m_LineEdit = new CLineEdit(text);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(m_LineEdit);

    this->setLayout(layout);

    // 水平扩张 垂直让步
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum));

    // 设置信号联动
    connect( m_LineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(contentChanged()) );
}

void CSentence::drawBackGround(QPainter &painter)
{
    painter.drawLine(2,this->height()-2,this->width()-2,this->height()-2);
}

QString CSentence::toCCode(int indent) const
{
    QString code(indent,' ');
    code += m_LineEdit->text().trimmed() + "\n";
    return code;
}

void CSentence::mousePressEvent(QMouseEvent *e)
{
    if( e->button() != Qt::LeftButton ){
        CStatement::mousePressEvent(e);
        return;
    }

    m_LineEdit->setFocus();
}

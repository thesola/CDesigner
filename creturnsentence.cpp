#include "creturnsentence.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QMouseEvent>

CReturnSentence::CReturnSentence()
{
    m_Label = new QLabel(this);
    m_Label->setText("return");
    m_Label->setFont(QFont("宋体",12));
    m_Label->setAlignment(Qt::AlignVCenter | Qt::AlignRight );
    m_Label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    m_LineEdit = new CLineEdit;
    m_LineEdit->lineEdit()->setAlignment(Qt::AlignLeft);
    m_LineEdit->setStatement(this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget( m_Label );
    layout->addWidget( m_LineEdit );

    setLayout( layout );

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);

    connect( m_LineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(contentChanged()) );
}

QString CReturnSentence::toCCode(int indent) const
{
    return QString(indent,' ') + "return " + m_LineEdit->text().trimmed() + ";\n";
}

void CReturnSentence::drawBackGround(QPainter &painter)
{

}

void CReturnSentence::setText(const QString text)
{
    m_LineEdit->setText(text);
}

void CReturnSentence::mousePressEvent(QMouseEvent *e)
{
    if( e->button() != Qt::LeftButton )
    {
        CStatement::mousePressEvent(e);
        return;
    }

    m_LineEdit->setFocus();
}

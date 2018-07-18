#include "ccontinuesentence.h"
#include <QHBoxLayout>

CContinueSentence::CContinueSentence()
{
    m_Label = new QLabel;
    m_Label->setAlignment(Qt::AlignCenter);
    m_Label->setText("continue");
    m_Label->setFont(QFont("宋体",12));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_Label);

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
}

QString CContinueSentence::toCCode(int indent) const
{
    return QString(indent,' ') + "continue;\n";
}

void CContinueSentence::drawBackGround(QPainter &painter)
{

}



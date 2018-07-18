#include "cbreaksentence.h"
#include <QHBoxLayout>

CBreakSentence::CBreakSentence()
{
    m_Label = new QLabel;
    m_Label->setAlignment(Qt::AlignCenter);
    m_Label->setText("break");
    m_Label->setFont(QFont("宋体",12));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_Label);

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
}

QString CBreakSentence::toCCode(int indent) const
{
    return QString(indent,' ') + "break;\n";
}

void CBreakSentence::drawBackGround(QPainter &painter)
{

}



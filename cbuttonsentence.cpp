#include "cbuttonsentence.h"
#include <QPainterPath>
#include <QPainter>
#include <QBitmap>

CButtonSentence::CButtonSentence(QWidget *parent):CButtonBase(parent)
{
    drawButtonIcon();
}

CButtonSentence::~CButtonSentence()
{

}

void CButtonSentence::drawButtonIcon()
{
    QPainterPath path;

    int width = this->width();
    int height = this->height();
    int margin = 2;

    path.addRect(margin,height/8*3,width-2*margin,height/4);

    QPixmap pixmap(width,height);
    pixmap.fill(Qt::transparent); // 透明化
    QPainter painter(&pixmap);
    painter.setPen(QPen(QColor(255,66,93), 4));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(path);

    setIcon(pixmap);
    setIconSize(QSize(width,height));

}


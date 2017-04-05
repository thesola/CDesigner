#include "cbuttonfor.h"
#include <QPainterPath>
#include <QPainter>

CButtonFor::CButtonFor(QWidget *parent):CButtonBase(parent)
{
    drawButtonIcon();
}

CButtonFor::~CButtonFor()
{

}

void CButtonFor::drawButtonIcon()
{
    QPainterPath path;

    int width = this->width();
    int height = this->height();
    int margin = 2;

    path.addRect(margin,margin,width-2*margin,height-2*margin);
    path.moveTo(margin,height/6);
    path.lineTo(width-margin,height/6);
    path.moveTo(width-margin,height/6*2);
    path.lineTo(width/8,height/6*2);
    path.lineTo(width/8,height-margin);
    path.moveTo(width/8,height/6*5);
    path.lineTo(width-margin,height/6*5);

    QPixmap pixmap(width,height);
    pixmap.fill(Qt::transparent); // 透明化
    QPainter painter(&pixmap);
    painter.setPen(QPen(QColor(255,66,93),4));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(path);

    setIcon(pixmap);
    setIconSize(QSize(width,height));
}


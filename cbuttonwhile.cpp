#include "cbuttonwhile.h"
#include <QPainterPath>
#include <QPainter>

CButtonWhile::CButtonWhile(QWidget *parent):CButtonBase(parent)
{
    drawButtonIcon();
}

CButtonWhile::~CButtonWhile()
{

}

void CButtonWhile::drawButtonIcon()
{
    QPainterPath path;

    int width = this->width();
    int height = this->height();
    int margin = 2;

    path.addRect(margin,margin,width-2*margin,height-2*margin);
    path.moveTo(width/8,height/4);
    path.lineTo(width-margin,height/4);
    path.moveTo(width/8,height/4);
    path.lineTo(width/8,height-margin);

    QPixmap pixmap(width,height);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(QColor(255,66,93),4));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(path);

    setIcon(pixmap);
    setIconSize(QSize(width,height));

}


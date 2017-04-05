#include "cbuttondwhile.h"
#include <QPainterPath>
#include <QPainter>

CButtonDWhile::CButtonDWhile(QWidget *parent):CButtonBase(parent)
{
    drawButtonIcon();
}

CButtonDWhile::~CButtonDWhile()
{

}

void CButtonDWhile::drawButtonIcon()
{
    QPainterPath path;

    int width = this->width();
    int height = this->height();
    int margin = 2;

    path.addRect(margin,margin,width-2*margin,height-2*margin);
    path.moveTo(width/8*7,margin);
    path.lineTo(width/8*7,height/4*3);
    path.lineTo(margin,height/4*3);

    QPixmap pixmap(width,height);
    pixmap.fill(Qt::transparent); // 透明化
    QPainter painter(&pixmap);
    painter.setPen(QPen(QColor(255,66,93),4));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(path);

    setIcon(pixmap);
    setIconSize(QSize(width,height));
}


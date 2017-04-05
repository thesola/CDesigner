#include "cbuttonscope.h"
#include <QPainter>
#include <QPainterPath>

CButtonScope::CButtonScope(QWidget *parent):CButtonBase(parent)
{
    drawButtonIcon();
}

CButtonScope::~CButtonScope()
{

}

void CButtonScope::drawButtonIcon()
{
    QPainterPath path;

    int width = this->width();
    int height = this->height();
    int margin = 2;

    path.addRect(margin,margin,width-2*margin,height-2*margin);

    QPixmap pixmap(width,height);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(QColor(255,66,93), 4));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(path);

    setIcon(pixmap);
    setIconSize(QSize(width,height));
}


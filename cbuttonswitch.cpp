#include "cbuttonswitch.h"
#include <QPainterPath>
#include <QPainter>

CButtonSwitch::CButtonSwitch(QWidget *parent): CButtonBase(parent)
{
    drawButtonIcon();
}

CButtonSwitch::~CButtonSwitch()
{

}

void CButtonSwitch::drawButtonIcon()
{
    QPainterPath path;

    int width = this->width();
    int height = this->height();
    int margin = 2;

    path.addRect( margin, margin, width-2*margin, height-2*margin );
    path.moveTo(margin,height/4);
    path.lineTo(width-margin,height/4);
    path.moveTo(width/4,height/4);
    path.lineTo(width/4,height-margin);
    path.moveTo(margin,height/4*2);
    path.lineTo(width-margin,height/4*2);
    path.moveTo(margin,height/4*3);
    path.lineTo(width-margin,height/4*3);
    path.moveTo(margin,margin);
    path.lineTo(width/7*3,height/4);
    path.moveTo(width/7*4,height/4);
    path.lineTo(width-margin,margin);

    QPixmap pixmap(width, height);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(QColor(255,66,93),4));
    painter.setRenderHint( QPainter::Antialiasing );
    painter.drawPath(path);

    setIcon( pixmap );
    setIconSize( QSize(width, height) );
}


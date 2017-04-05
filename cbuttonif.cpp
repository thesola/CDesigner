#include "cbuttonif.h"
#include <QPainter>
#include <QPainterPath>

CButtonIf::CButtonIf(QWidget *parent) : CButtonBase(parent)
{
    drawButtonIcon();
}

CButtonIf::~CButtonIf()
{
}

void CButtonIf::drawButtonIcon()
{
    QPainterPath path;

    int height = this->height();
    int width = this->width();
    int margin = 2;

    path.addRect( margin, margin, width-2*margin, height-2*margin );
    path.moveTo(margin,margin);
    path.lineTo(width/7*3,height/4);
    path.moveTo(width/7*4,height/4);
    path.lineTo(width-margin,margin);
    path.moveTo(margin,height/4);
    path.lineTo(width-margin,height/4);
    path.moveTo(width/2,height/4);
    path.lineTo(width/2,height-margin);

    // 绘制到图片上
    QPixmap image(width, height);
    image.fill(Qt::transparent); // 透明化
    QPainter painter(&image);
    painter.setPen(QPen(QColor(255,66,93),4));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath( path );

    setIcon( QIcon(image) );				// 设置图标
    setIconSize( QSize(width, height) );	// 调整图标大小 否则将被缩放
}


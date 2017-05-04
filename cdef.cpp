#include "cdef.h"

QLabel *g_label = NULL;

#include <QPainterPath>
#include <QPainter>
#include <QPen>
#include <QFont>

QPen	g_Pen(QColor(255,66,93),2);
QFont	g_Font("Times New Roman",15,QFont::Bold,true);
int 	g_Margin = 6;

QPixmap g_getPixmapIf(int width, int height)
{
    QPainterPath path;
    path.addRect( g_Margin, g_Margin, width-2*g_Margin, height-2*g_Margin );
    path.moveTo(g_Margin,g_Margin);
    path.lineTo(width/7*4,height/4);
    path.moveTo(width/7*5,height/4);
    path.lineTo(width-g_Margin,g_Margin);
    path.moveTo(g_Margin,height/4);
    path.lineTo(width-g_Margin,height/4);
    // 画竖线
    path.moveTo(width/14.*9,height/4);
    path.lineTo(width/14.*9,height-g_Margin);
    // 画叉叉
    path.moveTo(width/28.*21,height/14.*8);
    path.lineTo(width/28.*23,height/14.*9);
    path.moveTo(width/28.*23,height/14.*8);
    path.lineTo(width/28.*21,height/14.*9);

    // 绘制到图片上
    QPixmap image(width, height);
    image.fill(Qt::transparent); // 透明化
    QPainter painter(&image);
    painter.setPen(g_Pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath( path );

    return image;
}

QPixmap g_getPixmapIfElse(int width, int height)
{
    QPainterPath path;
    path.addRect( g_Margin, g_Margin, width-2*g_Margin, height-2*g_Margin );
    path.moveTo(g_Margin,g_Margin);
    path.lineTo(width/7*3,height/4);
    path.moveTo(width/7*4,height/4);
    path.lineTo(width-g_Margin,g_Margin);
    path.moveTo(g_Margin,height/4);
    path.lineTo(width-g_Margin,height/4);
    path.moveTo(width/2,height/4);
    path.lineTo(width/2,height-g_Margin);

    // 绘制到图片上
    QPixmap image(width, height);
    image.fill(Qt::transparent); // 透明化
    QPainter painter(&image);
    painter.setPen(g_Pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath( path );

    return image;
}

QPixmap g_getPixmapSwitch(int width, int height)
{
    QPainterPath path;
    path.addRect( g_Margin, g_Margin, width-2*g_Margin, height-2*g_Margin );
    path.moveTo(g_Margin,height/4);
    path.lineTo(width-g_Margin,height/4);
    path.moveTo(g_Margin,height/4*2);
    path.lineTo(width-g_Margin,height/4*2);
    path.moveTo(g_Margin,height/4*3);
    path.lineTo(width-g_Margin,height/4*3);
    path.moveTo(g_Margin,g_Margin);
    path.lineTo(width/7*3,height/4);
    path.moveTo(width/7*4,height/4);
    path.lineTo(width-g_Margin,g_Margin);
    // 画斜线
    path.moveTo(width/8*3,height/4);
    path.lineTo(width/8*2,height/2);
    path.moveTo(width/8*3,height/2);
    path.lineTo(width/8*2,height/4*3);
    path.moveTo(width/8*3,height/4*3);
    path.lineTo(width/8*2,height-g_Margin);

    QPixmap pixmap(width, height);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(g_Pen);
    painter.setRenderHint( QPainter::Antialiasing );
    painter.drawPath(path);

    return pixmap;
}

QPixmap g_getPixmapWhile(int width, int height)
{
    QPainterPath path;
    path.addRect(g_Margin,g_Margin,width-2*g_Margin,height-2*g_Margin);
    path.moveTo(width/8,height/4);
    path.lineTo(width-g_Margin,height/4);
    path.moveTo(width/8,height/4);
    path.lineTo(width/8,height-g_Margin);

    QPixmap pixmap(width,height);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(g_Pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(path);

    return pixmap;
}

QPixmap g_getPixmapDoWhile(int width, int height)
{
    QPainterPath path;
    path.addRect(g_Margin,g_Margin,width-2*g_Margin,height-2*g_Margin);
    path.moveTo(width/8*7,g_Margin);
    path.lineTo(width/8*7,height/4*3);
    path.lineTo(g_Margin,height/4*3);

    QPixmap pixmap(width,height);
    pixmap.fill(Qt::transparent); // 透明化
    QPainter painter(&pixmap);
    painter.setPen(g_Pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(path);

    return pixmap;
}

QPixmap g_getPixmapFor(int width, int height)
{
    QPainterPath path;
    path.addRect(g_Margin,g_Margin,width-2*g_Margin,height-2*g_Margin);
    path.moveTo(g_Margin,height/6);
    path.lineTo(width-g_Margin,height/6);
    path.moveTo(width-g_Margin,height/6*2);
    path.lineTo(width/8,height/6*2);
    path.lineTo(width/8,height-g_Margin);
    path.moveTo(width/8,height/6*5);
    path.lineTo(width-g_Margin,height/6*5);

    QPixmap pixmap(width,height);
    pixmap.fill(Qt::transparent); // 透明化
    QPainter painter(&pixmap);
    painter.setPen(g_Pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(path);

    return pixmap;
}

QPixmap g_getPixmapFunction(int width, int height)
{
    QPixmap pixmap(width,height);
    pixmap.fill(Qt::transparent); // 透明化

    QPainter painter(&pixmap);
    painter.setPen(g_Pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont( g_Font ); // 设置字体
    painter.drawText(pixmap.rect(),Qt::AlignCenter,"Func");

    return pixmap;
}

QPixmap g_getPixmapScope(int width, int height)
{
    QPainterPath path;
    path.addRect(g_Margin,g_Margin,width-2*g_Margin,height-2*g_Margin);

    QPixmap pixmap(width,height);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(g_Pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(path);

    return pixmap;
}

QPixmap g_getPixmapStatement(int width, int height)
{
    QPainterPath path;

    // 高度为 30px 或者height/4
    if( height/4 <= 30 )
    {
        path.addRect(g_Margin,height/8*3,width-2*g_Margin,height/4);
    }
    else
    {
        path.addRect(g_Margin,height/2-15,width-2*g_Margin,30);
    }

    QPixmap pixmap(width,height);
    pixmap.fill(Qt::transparent); // 透明化
    QPainter painter(&pixmap);
    painter.setPen(g_Pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(path);

    return pixmap;
}

// 获取 if 的绘制路径 垂直分割比为 1:5 水平分割比为 5:2
QPainterPath g_getPPathIf(int width, int height)
{
    QPainterPath path;

    int vfactor = 6;

    path.moveTo(0,0);
    path.lineTo(width/7*5,height/vfactor);
    path.lineTo(width,0);
    path.moveTo(0,height/vfactor);
    path.lineTo(width,height/vfactor);
    // 画竖线
//    path.moveTo(width/7*5,height/vfactor);
//    path.lineTo(width/7*5,height);
    // 画叉叉
    path.moveTo(width/21.*17,height/2);
    path.lineTo(width/21.*19,height/7*4);
    path.moveTo(width/21.*19,height/2);
    path.lineTo(width/21.*17,height/7*4);
    // 画底线
    path.moveTo(0,height-2);
    path.lineTo(width,height-2);

    return path;
}


// 获取 if-else 的绘制路径 垂直分割比为 1:5 水平分割比为 1:1
QPainterPath g_getPPathIfElse(int width, int height)
{
    QPainterPath path;

    int vfactor = 6;

    path.moveTo(0,0);
    path.lineTo(width/2,height/vfactor);
    path.moveTo(width/2,height/vfactor);
    path.lineTo(width,0);
    path.moveTo(0,height/vfactor);
    path.lineTo(width,height/vfactor);
    path.moveTo(width/2,height/vfactor);
    path.lineTo(width/2,height);
    // 画底线
    path.moveTo(0,height-2);
    path.lineTo(width,height-2);

    return path;
}



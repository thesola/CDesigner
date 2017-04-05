#include "cbuttonfunction.h"
#include "QPainter"

CButtonFunction::CButtonFunction(QWidget *parent):CButtonBase(parent)
{
    drawButtonIcon();
}

CButtonFunction::~CButtonFunction()
{

}

void CButtonFunction::drawButtonIcon()
{
    int width = this->width(), height = this->height();
    QPixmap pixmap(width,height);
    pixmap.fill(Qt::transparent); // 透明化
    QPainter painter(&pixmap);
    painter.setPen(QPen(QColor(255,66,93)));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(QFont("Times New Roman",20,QFont::Bold,true)); // 设置字体
    painter.drawText(pixmap.rect(),Qt::AlignCenter,"Func");

    setIcon(pixmap);
    setIconSize(QSize(width,height));
}


#include "cbaffle.h"
#include <QDropEvent>
#include <QMimeData>
#include <QPainter>

CBaffle::CBaffle(QWidget *parent) : QWidget(parent)
{
    setAcceptDrops(true);
    setAutoFillBackground(true);

    // 设置背景
    QPixmap pixmap(this->size());
    pixmap.fill(Qt::transparent); // 透明化
    QPainter painter(&pixmap);
    painter.setPen(QPen(QColor(255,66,93),3));
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect( 0,0,this->width(),this->height(),QColor(0,0,0,4) );

    QPalette palette = this->palette();
    palette.setBrush(this->backgroundRole(),QBrush(pixmap));
    setPalette(palette);
}

void CBaffle::dropEvent(QDropEvent *e)
{
    emit baffleDropEvent(e);
}

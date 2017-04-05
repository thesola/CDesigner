#include "cscopescope.h"
#include <QLabel>

CScopeScope::CScopeScope(QWidget *parent):CScopeBase(parent)
{
}

CScopeScope::~CScopeScope()
{

}

void CScopeScope::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(mPen);
    painter.drawRect(0,0,this->width(),this->height());
}

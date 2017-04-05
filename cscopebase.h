#ifndef CSCOPEBASE_H
#define CSCOPEBASE_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QPen>

class CScopeBase : public QWidget
{
public:
    CScopeBase(QWidget* parent=0);
    ~CScopeBase();

protected:

//   virtual void addWidget(CScopeBase *child)=0;

    QPen	mPen;
    int 	mMargin;
};

#endif // CSCOPEBASE_H

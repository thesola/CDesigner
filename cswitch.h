/*
 * switch 类
 * 继承自 CScope
*/

#ifndef CSWITCH_H
#define CSWITCH_H

#include "cscope.h"
#include "clineedit.h"

class CCase;

class CSwitch : public CScope
{
    Q_OBJECT
public:
    CSwitch();
    ~CSwitch();

    void drawBackGround(QPainter& painter);
    QString toCCode(int indent) const;

    void resizeEvent(QResizeEvent *e);

    void mousePressEvent( QMouseEvent *e );

    void dropEvent(QDropEvent *e);

private:
    CLineEdit	*m_lineEdit;
    QWidget		*m_cases;
};

#endif // CSWITCH_H

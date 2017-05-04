/*
 * do-while类 拥有一个域和一个条件表达式
 * 继承自 CStatement
*/

#ifndef CDOWHILE_H
#define CDOWHILE_H

#include "cstatement.h"
#include "cscope.h"
#include "clineedit.h"

class CDoWhile : public CStatement
{
    Q_OBJECT
public:
    CDoWhile();

    void drawBackGround(QPainter &painter);
    void resizeEvent(QResizeEvent *e);
    QString toCCode(int indent) const;

    CScope* cScope()const;

    void mousePressEvent(QMouseEvent *e);

private:
    CLineEdit	*m_lineEdit;
    CScope		*m_cScope;
};

#endif // CDOWHILE_H

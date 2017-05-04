/*
 * for类 拥有三个表达式 一个域
 * 继承自 CStatement
*/

#ifndef CFOR_H
#define CFOR_H

#include "cstatement.h"
#include "cscope.h"
#include "clineedit.h"

class CFor : public CStatement
{
    Q_OBJECT
public:
    CFor();

    void drawBackGround(QPainter &painter);
    void resizeEvent(QResizeEvent *e);
    QString toCCode(int indent) const;

    CScope *cScope()const;

    void mousePressEvent(QMouseEvent *e);

private:
    CScope		*m_cScope;
    CLineEdit	*m_exp1, *m_exp2, *m_exp3;
};

#endif // CFOR_H

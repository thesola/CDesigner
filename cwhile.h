/*
 * while类 拥有一个条件表达式以及一个域
 * 继承自 CStatement
*/

#ifndef CWHILE_H
#define CWHILE_H

#include "cstatement.h"
#include "cscope.h"
#include "clineedit.h"

class CWhile : public CStatement
{
    Q_OBJECT
public:
    CWhile();

    void resizeEvent(QResizeEvent *e);
    void drawBackGround(QPainter& painter);
    QString toCCode(int indent) const;

    CScope* cScope();

    void mousePressEvent(QMouseEvent *e);

private:
    CLineEdit	*m_lineEdit;
    CScope		*m_cScope;
};

#endif // CWHILE_H

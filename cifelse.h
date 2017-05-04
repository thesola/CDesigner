/*
 * if-else 类 拥有一个表达式 两个域
 * 继承自 CStatement
*/

#ifndef CIFELSE_H
#define CIFELSE_H

#include "cstatement.h"
#include "cscope.h"
#include "clineedit.h"
#include "cbaffle.h"
#include <QLabel>

class CIfElse : public CStatement
{
    Q_OBJECT
public:
    CIfElse();

    void drawBackGround(QPainter& painter);
    void resizeEvent(QResizeEvent *e);
    QString toCCode(int indent) const;

    CScope* yesScope();
    CScope* notScope();

    void mousePressEvent(QMouseEvent *e);

public slots:
    void doBaffleDrop(QDropEvent *e);


private:
    CScope		*m_cYesScope,	*m_cNotScope;
    CLineEdit	*m_lineEdit;
    QLabel		*m_YesLabel,	*m_NotLabel;

    // 用于在下方添加东西的挡板
    CBaffle		*m_baffle;

};

#endif // CIFELSE_H

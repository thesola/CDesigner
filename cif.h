/*
 * if类 拥有一个行编辑器exp 和一个域
 * 继承自 CStatement
*/

#ifndef CIF_H
#define CIF_H

#include "cstatement.h"
#include "cscope.h"
#include "clineedit.h"
#include <QLabel>

class CIf : public CStatement
{
    Q_OBJECT
public:
    CIf();

    void drawBackGround(QPainter& painter);
    void resizeEvent(QResizeEvent *e);
    QString toCCode(int indent) const;

    CScope*& cScope();

    void mousePressEvent(QMouseEvent *e);

private:

    CLineEdit	*m_lineEdit;
    CScope		*m_cScope;
    QLabel		*m_label;

};

#endif // CIF_H

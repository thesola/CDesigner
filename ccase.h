/*
 * 供switch使用的case类 提供额外的弹出菜单 "添加 上" "添加 下"
 * 包含一个额外的标签 "值"
 * 继承自 CScope
*/

#ifndef CCASE_H
#define CCASE_H

#include "cscope.h"
#include "clineedit.h"
#include <QLabel>

class CCase : public CScope
{
    Q_OBJECT
public:
    CCase();
    ~CCase();

	void drawBackGround(QPainter& painter);
    void resizeEvent(QResizeEvent *e);
    QString toCCode(int indent) const;

    void dropEvent(QDropEvent *e);
    void mousePressEvent(QMouseEvent *e);

    static CCase *getDefaultCase();

public slots:

    void doAddBefore();
    void doAddAfter();
    void doDeleteSelf();

private:
    CLineEdit	*m_lineEdit;
    QLabel		*m_label;
    QWidget		*m_statements;
};

#endif // CCASE_H

/*
 * 域类 拥有语句列表 可自由增删语句 本身也是个语句
*/
#ifndef CSCOPE_H
#define CSCOPE_H


#include "cstatement.h"
#include <QVBoxLayout>


class CScope : public CStatement
{
    Q_OBJECT
public:
    CScope();

    // 增删语句

    // 在指定位置插入
    void insertStastement(int index, CStatement *state);
    // 删除指定语句
    void deleteStatement(CStatement *state);
    // 查找语句在列表中的位置
    int indexOfStatement(CStatement *state);

    // 重载拖入事件
    void dropEvent(QDropEvent *e);

    void drawBackGround(QPainter& painter);

    QString toCCode(int indent) const;

    void setAsFunctionScope(bool flag);

    void deleteSelf();

protected:
    QVBoxLayout			*m_vBoxLayout;
    bool				m_bIsFunctionScope;
};

#endif // CSCOPE_H

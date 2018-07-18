/*
 * 语句类 所有语句的顶级父类 只是个抽象类无任何具体内容
*/


#ifndef CSTATEMENT_H
#define CSTATEMENT_H

#include <QWidget>
#include <QPainter>
#include <QDropEvent>
#include <QMenu>

class CScope;

class CStatement : public QWidget
{
    Q_OBJECT
public:
    explicit CStatement(QWidget *parent = 0);
    virtual ~CStatement();

    void resizeEvent(QResizeEvent *e);

    virtual QString toCCode(int indent)const=0;

    void dragEnterEvent(QDragEnterEvent *e);

    virtual void dropEvent(QDropEvent *e);

    // 绘制背景
    virtual void drawBackGround(QPainter& painter)=0;

    // 通过名称获取语句实体
    CStatement* getStatementByName(QString name);

    // 鼠标右击出菜单
    void mousePressEvent(QMouseEvent *e);

    // 获取当前已经声明的变量列表
    virtual QStringList getCurrentVars();

    // 2017/6/14 父级域对象访问
    CScope* parentScope();
    void setParentScope(CScope* scope);

signals:
    // 发射内容变更信号
    void contentChanged();

public slots:
    virtual void deleteSelf();

protected:
    QMenu *m_menu;
    CScope *m_parentScope;

};

#endif // CSTATEMENT_H

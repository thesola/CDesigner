#ifndef CBUTTONBASE_H
#define CBUTTONBASE_H

#include<QPushButton>

/*
 * 基础按钮类 所有按钮继承此类 实现虚函数 setButtonIcon
*/

class CButtonBase : public QPushButton
{
    Q_OBJECT
public:
    explicit CButtonBase(QWidget *parent);
    ~CButtonBase();

protected:
    // 将绘制按钮图片功能设置为纯虚函数
    virtual void drawButtonIcon()=0;
};

#endif // CBUTTONBASE_H

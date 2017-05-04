#ifndef CBUTTON_H
#define CBUTTON_H

#include <QPushButton>
#include <QMimeData>
#include <QDrag>

class CButton : public QPushButton
{
public:
    CButton(QString btnType="", QWidget *parent=0);
    
    // 设置按钮为特定功能
    void setAsButtonIf();
    void setAsButtonIfElse();
    void setAsButtonWhile();
    void setAsButtonDWhile();
    void setAsButtonFor();
    void setAsButtonSwitch();
    void setAsButtonScope();
    void setAsButtonStatement();
    void setAsButtonFunction();

    QString typeName();

    void mousePressEvent(QMouseEvent *e);

private:
    QPixmap mPixmap;
    QString mTypeName;
    static const int mWidth, mHeight;
};

#endif // CBUTTON_H

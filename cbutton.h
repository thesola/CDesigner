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
    void setAsButtonFunction();
    
    void setAsButtonDeclare();
    void setAsButtonSentence();
    void setAsButtonBreakSentence();
    void setAsButtonContinueSentence();
    void setAsButtonReturnSentence();

    QString typeName();

    void mousePressEvent(QMouseEvent *e);

private:
    QPixmap mPixmap;
    QString mTypeName;
    static const int mWidth, mHeight;
};

#endif // CBUTTON_H

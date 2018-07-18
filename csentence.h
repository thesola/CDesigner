/*
 * 文本语句类 有';'号结尾的语句 只包含一个输入文本框
 * 继承自 CStatement
*/


#ifndef CSENTENCE_H
#define CSENTENCE_H

#include "cstatement.h"
#include "clineedit.h"

class CSentence : public CStatement
{
    Q_OBJECT
public:
//    CSentence(QString text="语句;");
    CSentence(QString text="表达式");

    // getter
    QString text();
    QLineEdit* lineEdit();

    // setter
    void setText(QString text);

    void drawBackGround(QPainter& painter);

    QString toCCode(int indent)const;

    void mousePressEvent(QMouseEvent *e);

protected:
    CLineEdit *m_LineEdit;
};

#endif // CSENTENCE_H

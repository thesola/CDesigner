#ifndef CRETURNSENTENCE_H
#define CRETURNSENTENCE_H

#include "cstatement.h"
#include "clineedit.h"
#include <QLabel>

class CReturnSentence : public CStatement
{
public:
    CReturnSentence();

    QString toCCode(int indent) const;
    void drawBackGround(QPainter &painter);

    void setText(const QString text);

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    QLabel		*m_Label;
    CLineEdit	*m_LineEdit;
};

#endif // CRETURNSENTENCE_H

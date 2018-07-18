#ifndef CCONTINUESENTENCE_H
#define CCONTINUESENTENCE_H

#include "cstatement.h"
#include <QLabel>

class CContinueSentence : public CStatement
{
public:
    CContinueSentence();
    QString toCCode(int indent) const;
    void drawBackGround(QPainter &painter);
private:
    QLabel *m_Label;
};

#endif // CCONTINUESENTENCE_H

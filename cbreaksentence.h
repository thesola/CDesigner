#ifndef CBREAKSENTENCE_H
#define CBREAKSENTENCE_H

#include "csentence.h"
#include <QLabel>

class CBreakSentence : public CStatement
{
public:
    CBreakSentence();
    QString toCCode(int indent) const;
    void drawBackGround(QPainter &painter);
private:
    QLabel *m_Label;
};

#endif // CBREAKSENTENCE_H

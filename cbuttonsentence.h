#ifndef CBUTTONSENTENCE_H
#define CBUTTONSENTENCE_H

#include "cbuttonbase.h"

class CButtonSentence : public CButtonBase
{
public:
    CButtonSentence(QWidget* parent=0);
    ~CButtonSentence();
protected:
    void drawButtonIcon();
};

#endif // CBUTTONSENTENCE_H

#ifndef CBUTTONSCOPE_H
#define CBUTTONSCOPE_H

#include "cbuttonbase.h"

class CButtonScope : public CButtonBase
{
public:
    CButtonScope(QWidget* parent=0);
    ~CButtonScope();
protected:
    void drawButtonIcon();
};

#endif // CBUTTONSCOPE_H

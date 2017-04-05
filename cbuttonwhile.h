#ifndef CBUTTONWHILE_H
#define CBUTTONWHILE_H

#include "cbuttonbase.h"

class CButtonWhile:public CButtonBase
{
public:
    CButtonWhile(QWidget*parent=0);
    ~CButtonWhile();

protected:
    void drawButtonIcon();
};

#endif // CBUTTONWHILE_H

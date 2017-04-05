#ifndef CBUTTONDWHILE_H
#define CBUTTONDWHILE_H

#include "cbuttonbase.h"

class CButtonDWhile:public CButtonBase
{
public:
    CButtonDWhile(QWidget* parent=0);
    ~CButtonDWhile();
protected:
    void drawButtonIcon();
};

#endif // CBUTTONDWHILE_H

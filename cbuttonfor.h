#ifndef CBUTTONFOR_H
#define CBUTTONFOR_H

#include "cbuttonbase.h"

class CButtonFor : public CButtonBase
{
public:
    CButtonFor(QWidget* parent=0);
    ~CButtonFor();
protected:
    void drawButtonIcon();
};

#endif // CBUTTONFOR_H

#ifndef CBUTTONSWITCH_H
#define CBUTTONSWITCH_H

#include "cbuttonbase.h"

class CButtonSwitch : public CButtonBase
{
public:
    CButtonSwitch(QWidget *parent=0);
    ~CButtonSwitch();

protected:
    void drawButtonIcon();

};

#endif // CBUTTONSWITCH_H

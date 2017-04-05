#ifndef CBUTTONFUNCTION_H
#define CBUTTONFUNCTION_H

#include "cbuttonbase.h"

class CButtonFunction : public CButtonBase
{
public:
    CButtonFunction(QWidget* parent=0);
    ~CButtonFunction();
protected:
    void drawButtonIcon();
};

#endif // CBUTTONFUNCTION_H

#ifndef CBUTTONIF_H
#define CBUTTONIF_H

#include "cbuttonbase.h"

class CButtonIf : public CButtonBase
{
    Q_OBJECT
public:
    explicit CButtonIf(QWidget *parent=0);
    ~CButtonIf();

protected:
    void drawButtonIcon();
};

#endif // CBUTTONIF_H

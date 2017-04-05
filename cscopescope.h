#ifndef CSCOPESCOPE_H
#define CSCOPESCOPE_H

#include "cscopebase.h"
#include <QLabel>

class CScopeScope:public CScopeBase
{
public:
    CScopeScope(QWidget* parent=0);
    ~CScopeScope();
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CSCOPESCOPE_H

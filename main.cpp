#include "widget.h"
#include <QApplication>

#include "ccase.h"
#include "cscope.h"
#include "cif.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();

    return a.exec();
}

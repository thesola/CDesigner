#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.setWindowTitle("C程序设计演示及代码自动生成系统");
    w.show();

    return a.exec();
}

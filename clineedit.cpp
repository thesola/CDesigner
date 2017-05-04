#include "clineedit.h"

CLineEdit::CLineEdit(QString text):QLineEdit(text)
{
    setFont(QFont("宋体",12));
    setStyleSheet("QLineEdit{border-width:0 0 1 0;border-color:rgba(0,0,0,40);border-style:outset;background-color:rgba(0,0,0,0)}");
    setAlignment(Qt::AlignCenter);
    // 不接收 drop
    setAcceptDrops(false);

}

/*
 * 一个无框、宋体、12号、居中对齐 的行编辑框
*/

#ifndef CLINEEDIT_H
#define CLINEEDIT_H

#include <QLineEdit>

class CLineEdit : public QLineEdit
{
public:
    CLineEdit(QString text="表达式");
};

#endif // CLINEEDIT_H

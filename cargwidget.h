#ifndef CARGWIDGET_H
#define CARGWIDGET_H

#include <QWidget>
#include "cfunction.h"
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

// 函数参数类 拥有一个下拉列表显示参数类型 以及一个文本框显示参数名 以及一个删除按钮
class CArgWidget : public QWidget
{
    Q_OBJECT
public:
    CArgWidget(QWidget *parent=0, const Arg arg = Arg() );

    Arg getArg()const;

signals:
    void deleteArg(QWidget *widget);

private slots:
    void ondeleteBtnClicked();

private:
    QComboBox	*m_ComboBox;
    QLineEdit	*m_LineEdit;
    QPushButton *m_PushButton;
};


#endif // CARGWIDGET_H

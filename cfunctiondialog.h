#ifndef CFUNCTIONDIALOG_H
#define CFUNCTIONDIALOG_H

#include <QDialog>
#include <QComboBox>
#include "cfunction.h"

namespace Ui {
class CFunctionDialog;
}

// 函数信息对话框类
class CFunctionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CFunctionDialog(QWidget *parent = 0);
    ~CFunctionDialog();

    // 设置绑定的函数对象
    void setCFunction(CFunction *cFunction);

    // 获取函数名
    QString funcName()const;

    bool isOkClicked();

signals:
    void okClicked();

private slots:
    void on_pb_ok_clicked();

    void on_pb_cancel_clicked();

    void closeEvent(QCloseEvent *e);

    void on_pb_addArg_clicked();

    // 删除指定参数组件
    void doDeleteArg(QWidget* widget);

private:
    Ui::CFunctionDialog *ui;

    CFunction	*m_cFunction;

    bool		m_bOkClicked;

};


#endif // CFUNCTIONDIALOG_H

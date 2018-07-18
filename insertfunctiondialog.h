#ifndef INSERTFUNCTIONDIALOG_H
#define INSERTFUNCTIONDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

namespace Ui {
class InsertFunctionDialog;
}

class InsertFunctionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsertFunctionDialog( QStringList vars, QWidget *parent = 0);
    ~InsertFunctionDialog();

    // 获取函数表达式
    static QString getFuncExp(QStringList vars);

private slots:
    void on_rb_printf_toggled(bool checked);

    void on_rb_puts_toggled(bool checked);

    void on_rb_putchar_toggled(bool checked);

    void on_rb_sscanf_toggled(bool checked);

    void on_rb_fprintf_toggled(bool checked);

    void on_rb_scanf_toggled(bool checked);

    void on_rb_gets_toggled(bool checked);

    void on_rb_getchar_toggled(bool checked);

    void on_rb_sprintf_toggled(bool checked);

    void on_rb_fscanf_toggled(bool checked);

    void on_rb_malloc_toggled(bool checked);

    void on_rb_calloc_toggled(bool checked);

    void on_rb_free_toggled(bool checked);

    void on_pb_ok_clicked();

    void on_pb_cancel_clicked();

    void on_pb_AddArg_clicked();

    void doDeleteArgName(QWidget *argName);

    void resetFuncInfoAsLibFunc( QString libFuncName, bool checked );

    void resetFuncInfo(QString funcNmae, QStringList funcArgs, bool checked );

    void on_rb_strlen_toggled(bool checked);

    void on_rb_strcmp_toggled(bool checked);

    void on_rb_strcat_toggled(bool checked);

    void on_rb_strcpy_toggled(bool checked);

    void on_rb_memcpy_toggled(bool checked);

    void on_cb_funcName_currentIndexChanged(int index);

private:
    Ui::InsertFunctionDialog *ui;

    QStringList m_VarNames;	// 变量名集
};

// 参数名类 用来显示参数名
class CArgName: public QWidget
{
    Q_OBJECT
public:
    CArgName( QString argName=QString(), QStringList argNames=QStringList(), bool isFirst=false);

    // 设置为显示的第一个参数
    void setAsFirstArg(bool isFirst);

    bool isFirstArg()const;

    // 获取编辑后的参数名
    QString argName();

signals:
    void deleteArgName(QWidget*);

private slots:
    void onDeleteClicked();

private:
    QLabel		*m_Label;	// 逗号标签
    QComboBox	*m_ComboBox;	// 参数名列表
    QPushButton	*m_PushButton;	// 删除按钮

};

#endif // INSERTFUNCTIONDIALOG_H

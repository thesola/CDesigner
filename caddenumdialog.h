#ifndef CADDENUMDIALOG_H
#define CADDENUMDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class CAddEnumDialog;
}

class CAddEnumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CAddEnumDialog(QWidget *parent = 0);
    ~CAddEnumDialog();

    static QString getEnumExp();

private slots:
    void on_pb_addMember_clicked();

    // 删除成员
    void doDeleteMember(QWidget *member);

    void on_pb_cancel_clicked();

    void on_pb_ok_clicked();

private:
    Ui::CAddEnumDialog *ui;
};

// 枚举成员
class CEnumMember : public QWidget
{
    Q_OBJECT
public:
    CEnumMember();

    QString text()const;

signals:
    void deleteMember(QWidget*);

private slots:
     void doBtnClicked();

private:
    QLineEdit	*m_LineEdit;
    QPushButton	*m_PushButton;
};

#endif // CADDENUMDIALOG_H

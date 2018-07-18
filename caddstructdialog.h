#ifndef CADDSTRUCTDIALOG_H
#define CADDSTRUCTDIALOG_H

#include <QDialog>

namespace Ui {
class CAddStructDialog;
}

class CAddStructDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CAddStructDialog(QWidget *parent = 0);
    ~CAddStructDialog();

    static QString getStructExp();

private slots:
    void on_pb_addMember_clicked();

    void doDeleteMember(QWidget *member);

    void on_pb_cancel_clicked();

    void on_pb_ok_clicked();

private:
    Ui::CAddStructDialog *ui;
};

#endif // CADDSTRUCTDIALOG_H

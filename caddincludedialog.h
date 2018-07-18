#ifndef CADDINCLUDEDIALOG_H
#define CADDINCLUDEDIALOG_H

#include <QDialog>

namespace Ui {
class CAddIncludeDialog;
}

class CAddIncludeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CAddIncludeDialog(QWidget *parent = 0);
    ~CAddIncludeDialog();

    static QString getIncludeExp();

private slots:
    void on_pb_cancel_clicked();

    void on_pb_ok_clicked();

private:
    Ui::CAddIncludeDialog *ui;
};

#endif // CADDINCLUDEDIALOG_H

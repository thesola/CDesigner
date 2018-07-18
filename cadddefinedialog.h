#ifndef CADDDEFINEDIALOG_H
#define CADDDEFINEDIALOG_H

#include <QDialog>

namespace Ui {
class CAddDefineDialog;
}

class CAddDefineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CAddDefineDialog(QWidget *parent = 0);
    ~CAddDefineDialog();

    static QString getDefineExp();

private slots:
    void on_pb_cancel_clicked();

    void on_pb_ok_clicked();

private:
    Ui::CAddDefineDialog *ui;
};

#endif // CADDDEFINEDIALOG_H

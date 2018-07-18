#ifndef CEXPMODIFYDIALOG_H
#define CEXPMODIFYDIALOG_H

#include <QDialog>

namespace Ui {
class CExpModifyDialog;
}

class CExpModifyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CExpModifyDialog(const QStringList& list,QWidget *parent = 0);
    ~CExpModifyDialog();

    static QString getExp(const QStringList &list);

private slots:
    void on_cb_kuohao_toggled(bool checked);

    void on_rb_jia_toggled(bool checked);

    void on_rb_jian_toggled(bool checked);

    // 单目运算
    void danmuyunsuan (const QString ysf/*运算符*/, bool checked, bool zqb/*在前边*/=true);
    // 双目运算
    void shuangmuyunsuan(const QString ysf/*运算符*/, bool checked);

    void on_rb_cheng_toggled(bool checked);

    void on_rb_chu_toggled(bool checked);

    void on_rb_qiuyu_toggled(bool checked);

    void on_rb_dengyu_toggled(bool checked);

    void on_rb_budengyu_toggled(bool checked);

    void on_rb_xiaoyu_toggled(bool checked);

    void on_rb_dayu_toggled(bool checked);

    void on_rb_xydy_toggled(bool checked);

    void on_rb_dydy_toggled(bool checked);

    void on_rb_lj_huo_toggled(bool checked);

    void on_rb_lj_qie_toggled(bool checked);

    void on_rb_lj_fei_toggled(bool checked);

    void on_rb_aw_yu_toggled(bool checked);

    void on_rb_aw_yihuo_toggled(bool checked);

    void on_rb_aw_huo_toggled(bool checked);

    void on_rb_aw_qiufan_toggled(bool checked);

    void on_rb_aw_zuoyi_toggled(bool checked);

    void on_rb_aw_youyi_toggled(bool checked);

    void on_rb_houzijia_toggled(bool checked);

    void on_rb_huozijian_toggled(bool checked);

    void on_rb_xiabiao_toggled(bool checked);

    void on_rb_qianzijia_toggled(bool checked);

    void on_rb_qianzijian_toggled(bool checked);

    void on_rb_sizeof_toggled(bool checked);

    void on_rb_fz_toggled(bool checked);

    void on_rb_fz_jia_toggled(bool checked);

    void on_rb_fz_jian_toggled(bool checked);

    void on_rb_fz_cheng_toggled(bool checked);

    void on_rb_fz_chu_toggled(bool checked);

    void on_rb_fz_qiuyu_toggled(bool checked);

    void on_rb_fz_zuoyi_toggled(bool checked);

    void on_rb_fz_youyi_toggled(bool checked);

    void on_rb_fz_yu_toggled(bool checked);

    void on_rb_fz_yihuo_toggled(bool checked);

    void on_rb_fz_huo_toggled(bool checked);

    void on_rb_tiaojian_toggled(bool checked);

    void on_rb_qvzhi_toggled(bool checked);

    void on_rb_jieyinyong_toggled(bool checked);

    void on_rb_wufuhao_toggled(bool checked);

    void on_pb_ok_clicked();

    void on_pb_cancel_clicked();

private:
    Ui::CExpModifyDialog *ui;
    QStringList m_strlist;

};

#endif // CEXPMODIFYDIALOG_H

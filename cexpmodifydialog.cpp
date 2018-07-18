#include "cexpmodifydialog.h"
#include "ui_cexpmodifydialog.h"
#include <QLabel>
#include <QCloseEvent>

static QString s_exp;
static bool	   s_isOk = false;

CExpModifyDialog::CExpModifyDialog(const QStringList &list, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CExpModifyDialog)
{
    ui->setupUi(this);
    ui->lb_0->hide();
    ui->lb_1->hide();
    ui->lb_2->hide();
    ui->cb_2->hide();
    ui->lb_3->hide();
    ui->cb_3->hide();
    ui->lb_4->hide();

    // 设置选项
    ui->cb_1->addItems(list);

    m_strlist = list;

    // 取消默认的问号
    setWindowFlags( Qt::WindowCloseButtonHint );
}

CExpModifyDialog::~CExpModifyDialog()
{
    delete ui;
}

QString CExpModifyDialog::getExp(const QStringList& list)
{
    s_exp.clear();
    s_isOk = false;

    CExpModifyDialog dialog(list);
    dialog.exec();

    if( s_isOk )
    {
        return s_exp.trimmed();
    }
    return "null";
}

void CExpModifyDialog::on_cb_kuohao_toggled(bool checked)
{
    if( checked )
    {
        ui->lb_0->setText("(");
        ui->lb_4->setText(")");
        ui->lb_0->show();
        ui->lb_4->show();
    }
    else
    {
        ui->lb_0->setText("");
        ui->lb_4->setText("");
        ui->lb_0->hide();
        ui->lb_4->hide();
    }
}

void CExpModifyDialog::on_rb_jia_toggled(bool checked)
{
    shuangmuyunsuan("+",checked);
}

void CExpModifyDialog::on_rb_jian_toggled(bool checked)
{
    shuangmuyunsuan("-",checked);
}

void CExpModifyDialog::danmuyunsuan(const QString ysf, bool checked, bool zqb)
{

    QLabel *label = zqb ? ui->lb_1 : ui->lb_2;

    if( checked )
    {
        label->setText(ysf);
        label->show();
    }
    else
    {
        label->setText("");
        label->hide();
    }
}

void CExpModifyDialog::shuangmuyunsuan(const QString ysf, bool checked)
{
    if( checked )
    {
        ui->lb_2->setText(ysf);
        ui->lb_2->show();

        ui->cb_2->addItems( m_strlist );
        ui->cb_2->show();
    }
    else
    {
        ui->lb_2->setText("");
        ui->lb_2->hide();

        ui->cb_2->clear();
        ui->cb_2->hide();
    }
}

void CExpModifyDialog::on_rb_cheng_toggled(bool checked)
{
    shuangmuyunsuan("*",checked);
}

void CExpModifyDialog::on_rb_chu_toggled(bool checked)
{
    shuangmuyunsuan("/",checked);
}

void CExpModifyDialog::on_rb_qiuyu_toggled(bool checked)
{
    shuangmuyunsuan("%",checked);
}

void CExpModifyDialog::on_rb_dengyu_toggled(bool checked)
{
    shuangmuyunsuan("==",checked);
}

void CExpModifyDialog::on_rb_budengyu_toggled(bool checked)
{
    shuangmuyunsuan("!=",checked);
}

void CExpModifyDialog::on_rb_xiaoyu_toggled(bool checked)
{
    shuangmuyunsuan("<",checked);
}

void CExpModifyDialog::on_rb_dayu_toggled(bool checked)
{
    shuangmuyunsuan(">",checked);
}

void CExpModifyDialog::on_rb_xydy_toggled(bool checked)
{
    shuangmuyunsuan("<=",checked);
}

void CExpModifyDialog::on_rb_dydy_toggled(bool checked)
{
    shuangmuyunsuan(">=",checked);
}

void CExpModifyDialog::on_rb_lj_huo_toggled(bool checked)
{
    shuangmuyunsuan("||",checked);
}

void CExpModifyDialog::on_rb_lj_qie_toggled(bool checked)
{
    shuangmuyunsuan("&&",checked);
}

void CExpModifyDialog::on_rb_lj_fei_toggled(bool checked)
{
    danmuyunsuan("!",checked);
}

void CExpModifyDialog::on_rb_aw_yu_toggled(bool checked)
{
    shuangmuyunsuan("&",checked);
}

void CExpModifyDialog::on_rb_aw_yihuo_toggled(bool checked)
{
    shuangmuyunsuan("^",checked);
}

void CExpModifyDialog::on_rb_aw_huo_toggled(bool checked)
{
    shuangmuyunsuan("|",checked);
}

void CExpModifyDialog::on_rb_aw_qiufan_toggled(bool checked)
{
    danmuyunsuan("~",checked);
}

void CExpModifyDialog::on_rb_aw_zuoyi_toggled(bool checked)
{
    shuangmuyunsuan("<<",checked);
}

void CExpModifyDialog::on_rb_aw_youyi_toggled(bool checked)
{
    shuangmuyunsuan(">>",checked);
}

void CExpModifyDialog::on_rb_houzijia_toggled(bool checked)
{
    danmuyunsuan("++",checked,false);
}

void CExpModifyDialog::on_rb_huozijian_toggled(bool checked)
{
    danmuyunsuan("--",checked,false);
}

// 下标运算
void CExpModifyDialog::on_rb_xiabiao_toggled(bool checked)
{
    if( checked )
    {
        ui->lb_2->setText("[");
        ui->lb_3->setText("]");
        ui->lb_2->show();
        ui->lb_3->show();

        ui->cb_2->addItems(m_strlist);
        ui->cb_2->show();
    }
    else
    {
        ui->lb_2->setText("");
        ui->lb_3->setText("");
        ui->lb_2->hide();
        ui->lb_3->hide();

        ui->cb_2->clear();
        ui->cb_2->hide();
    }
}

void CExpModifyDialog::on_rb_qianzijia_toggled(bool checked)
{
    danmuyunsuan("++",checked);
}

void CExpModifyDialog::on_rb_qianzijian_toggled(bool checked)
{
    danmuyunsuan("--",checked);
}

void CExpModifyDialog::on_rb_sizeof_toggled(bool checked)
{
    danmuyunsuan("sizeof",checked);
}

void CExpModifyDialog::on_rb_fz_toggled(bool checked)
{
    shuangmuyunsuan("=",checked);
}

void CExpModifyDialog::on_rb_fz_jia_toggled(bool checked)
{
    shuangmuyunsuan("+=",checked);
}

void CExpModifyDialog::on_rb_fz_jian_toggled(bool checked)
{
    shuangmuyunsuan("-=",checked);
}

void CExpModifyDialog::on_rb_fz_cheng_toggled(bool checked)
{
    shuangmuyunsuan("*=",checked);
}

void CExpModifyDialog::on_rb_fz_chu_toggled(bool checked)
{
    shuangmuyunsuan("/=",checked);
}

void CExpModifyDialog::on_rb_fz_qiuyu_toggled(bool checked)
{
    shuangmuyunsuan("%=",checked);
}

void CExpModifyDialog::on_rb_fz_zuoyi_toggled(bool checked)
{
    shuangmuyunsuan("<<=",checked);
}

void CExpModifyDialog::on_rb_fz_youyi_toggled(bool checked)
{
    shuangmuyunsuan(">>=",checked);
}

void CExpModifyDialog::on_rb_fz_yu_toggled(bool checked)
{
    shuangmuyunsuan("&=",checked);
}

void CExpModifyDialog::on_rb_fz_yihuo_toggled(bool checked)
{
    shuangmuyunsuan("^=",checked);
}

void CExpModifyDialog::on_rb_fz_huo_toggled(bool checked)
{
    shuangmuyunsuan("|=",checked);
}

// 条件运算
void CExpModifyDialog::on_rb_tiaojian_toggled(bool checked)
{
    if( checked )
    {
        ui->lb_2->setText("?");
        ui->lb_3->setText(":");
        ui->lb_2->show();
        ui->lb_3->show();

        ui->cb_2->addItems(m_strlist);
        ui->cb_3->addItems(m_strlist);
        ui->cb_2->show();
        ui->cb_3->show();
    }
    else
    {
        ui->lb_2->setText("");
        ui->lb_3->setText("");
        ui->lb_2->hide();
        ui->lb_3->hide();

        ui->cb_2->clear();
        ui->cb_3->clear();
        ui->cb_2->hide();
        ui->cb_3->hide();
    }
}

void CExpModifyDialog::on_rb_qvzhi_toggled(bool checked)
{
    danmuyunsuan("&",checked);
}

void CExpModifyDialog::on_rb_jieyinyong_toggled(bool checked)
{
    danmuyunsuan("*",checked);
}

// 无符号
void CExpModifyDialog::on_rb_wufuhao_toggled(bool checked)
{
    // 什么都不干
}

QString addSpace(const QString str)
{
    if( str.isEmpty() )
    {
        return str;
    }
    return str + " ";
}

// 点击确定
void CExpModifyDialog::on_pb_ok_clicked()
{
    s_exp += addSpace( ui->lb_0->text() );
    s_exp += addSpace( ui->lb_1->text() );
    s_exp += addSpace( ui->cb_1->currentText() );
    s_exp += addSpace( ui->lb_2->text() );
    s_exp += addSpace( ui->cb_2->currentText() );
    s_exp += addSpace( ui->lb_3->text() );
    s_exp += addSpace( ui->cb_3->currentText() );

    s_exp += ui->lb_4->text();

    s_isOk = true;

    QDialog::close();
}

// 点击取消
void CExpModifyDialog::on_pb_cancel_clicked()
{
    QDialog::close();
}


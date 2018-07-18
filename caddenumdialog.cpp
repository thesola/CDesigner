#include "caddenumdialog.h"
#include "ui_caddenumdialog.h"
#include "cdef.h"

static QString s_exp;

CAddEnumDialog::CAddEnumDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddEnumDialog)
{
    ui->setupUi(this);

    setWindowFlags( Qt::WindowCloseButtonHint );
}

CAddEnumDialog::~CAddEnumDialog()
{
    delete ui;
}

QString CAddEnumDialog::getEnumExp()
{
    s_exp.clear();
    CAddEnumDialog().exec();
    return s_exp.isEmpty() ? "null" : s_exp;
}

/************【枚举成员类型 beg】*****************************/

CEnumMember::CEnumMember()
{
    m_LineEdit = new QLineEdit();
    m_PushButton = new QPushButton("删除");

    m_LineEdit->setFont(QFont("宋体",12));
    m_PushButton->setFont(QFont("宋体",10));

    m_PushButton->setMinimumWidth(50);
    m_PushButton->setMaximumWidth(50);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);

    layout->addWidget(  m_LineEdit );
    layout->addWidget(m_PushButton);

    setLayout(layout);

    connect( m_PushButton, SIGNAL(clicked()), this, SLOT(doBtnClicked()) );
}

QString CEnumMember::text() const
{
    return m_LineEdit->text().trimmed();
}

void CEnumMember::doBtnClicked()
{
    emit deleteMember(this);
}
/************【枚举成员类型 end】*****************************/

void CAddEnumDialog::on_pb_addMember_clicked()
{
    CEnumMember *member = new CEnumMember;
    ui->vl_members->addWidget(member);
    connect( member, SIGNAL(deleteMember(QWidget*)), this, SLOT(doDeleteMember(QWidget*)) );
}

void CAddEnumDialog::doDeleteMember(QWidget *member)
{
    ui->vl_members->removeWidget(member);
    delete member;
}

void CAddEnumDialog::on_pb_cancel_clicked()
{
    close();
}

void CAddEnumDialog::on_pb_ok_clicked()
{
    s_exp = "enum " + ui->lineEdit->text().trimmed() + "\n{\n";

    for( int i=0,n=ui->vl_members->count() ; i < n ; ++i )
    {
        CEnumMember *member = (CEnumMember*)ui->vl_members->itemAt(i)->widget();
        s_exp += QString(g_s32Indent,' ') + member->text() + ",\n";
    }

    s_exp += "};\n";
    close();
}

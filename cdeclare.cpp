#include "cdeclare.h"
#include <QHBoxLayout>
#include "clineedit.h"

CDeclare::CDeclare(QWidget *parent) : CStatement(parent)
{
    m_lineEdit = new CLineEdit();
    m_comboBox = new QComboBox(this);

    m_lineEdit->setStatement(this);

    m_lineEdit->setParent(this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    QHBoxLayout *leftLayout = new QHBoxLayout();
    leftLayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Minimum) );
    leftLayout->addWidget( m_comboBox );
    m_comboBox->setEditable(true);
    QLineEdit *le = new QLineEdit(this);
    le->setAlignment(Qt::AlignRight);
    le->setFont(QFont("宋体",12));
    le->setAcceptDrops(false);
//    le->setStyleSheet("QLineEdit{border-width:0 0 0 0;border-style:outset;}");
    m_comboBox->setStyleSheet("QComboBox{border-width:0 0 0 0;border-style:none;}");
    m_comboBox->setLineEdit( le );
    leftLayout->setStretch(0,1);
    layout->addLayout( leftLayout );
    layout->addWidget( m_lineEdit );
    layout->setStretch(0,1);
    layout->setStretch(1,1);

    QStringList list;
    list<<"int"<<"char"<<"double"<<"float"<<" long long";
    m_comboBox->addItems(list);

    // 更改文本对齐方向
    m_comboBox->setLayoutDirection(Qt::RightToLeft);
    m_lineEdit->lineEdit()->setAlignment(Qt::AlignLeft);

    m_lineEdit->setText("变量名");

    m_comboBox->setFont(QFont("宋体",12));

    m_comboBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );

    // 关联修改信号
    connect( m_comboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(contentChanged()) );
    connect( m_lineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(contentChanged()) );
}

QString CDeclare::getVarName() const
{
    return m_lineEdit->text().trimmed();
}

QStringList CDeclare::getVarNames() const
{
    QStringList list;

    // 获取逗号分割的变量名列表
    QStringList vars = m_lineEdit->text().trimmed().split(",");
    foreach (QString var, vars) {
        // 寻找赋值符号 提取赋值符号左边的文本
        if( var.contains('=') ){
            QString str = var.left( var.indexOf("=") ).trimmed();
            if( ! str.isEmpty() )
            {
                list.append( str );
            }
        }
        else
        {
            if( ! var.trimmed().isEmpty() )
            {
                list.append( var.trimmed() );
            }
        }
    }

    return list;
}

QString CDeclare::toCCode(int indent) const
{
    QString code(indent,' ');
    code += m_comboBox->currentText().trimmed() + " " + m_lineEdit->text().trimmed() + ";\n";
    return code;
}

void CDeclare::drawBackGround(QPainter &painter)
{

}

void CDeclare::mousePressEvent(QMouseEvent *e)
{
    if( e->button() != Qt::LeftButton )
    {
        CStatement::mousePressEvent(e);
        return;
    }
    m_lineEdit->setFocus();
}

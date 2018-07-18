#include "cargwidget.h"

CArgWidget::CArgWidget(QWidget *parent, const Arg arg)
    :QWidget(parent)
{
    m_ComboBox = new QComboBox();
    m_LineEdit = new QLineEdit();
    m_PushButton = new QPushButton();

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget( m_ComboBox );
    layout->addWidget( m_LineEdit );
    layout->addWidget( m_PushButton );
    layout->setMargin(0);
    layout->setSpacing(4);

    // 设置各组件的值
    QStringList list;
    list<<"int"<<"char"<<"double"<<"float"<<"long long";
    m_ComboBox->addItems( list );
    if( ! arg.first.isEmpty() )
    {
        if( ! list.contains(arg.first) )
        {
            m_ComboBox->addItem(arg.first);
        }
        m_ComboBox->setCurrentText( arg.first );
    }
    m_ComboBox->setEditable(true);
    m_ComboBox->setFont( QFont("宋体",12) );
    QLineEdit *le = new QLineEdit();
    le->setFont(QFont("宋体",12));
    le->setAlignment( Qt::AlignRight );
    m_ComboBox->setLineEdit(le);
    m_ComboBox->setLayoutDirection(Qt::RightToLeft);

    m_LineEdit->setText( arg.second );
    m_LineEdit->setFont(QFont("宋体",12));

    m_PushButton->setFont(QFont("宋体",10));
    m_PushButton->setText("删除");
    m_PushButton->setMinimumWidth(50);
    m_PushButton->setMaximumWidth(50);
    m_PushButton->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );

    setLayout( layout );

    connect( m_PushButton, SIGNAL(clicked()), this, SLOT(ondeleteBtnClicked()) );
}

Arg CArgWidget::getArg() const
{
    return Arg( m_ComboBox->currentText().trimmed(), m_LineEdit->text().trimmed() );
}

void CArgWidget::ondeleteBtnClicked()
{
    emit deleteArg(this);
}

#include "clineedit.h"
#include <QMenu>
#include <QContextMenuEvent>
#include "cexpmodifydialog.h"
#include <QDebug>
#include "cstatement.h"
#include "insertfunctiondialog.h"


CLineEdit::CLineEdit(QString text)
{
    // 设置文本框
    m_LineEdit = new QLineEdit(text);
    m_LineEdit->setFont(QFont("宋体",12));
    m_LineEdit->setAlignment( Qt::AlignCenter );
    // 不接收 drop
    m_LineEdit->setAcceptDrops(false);

    // 设置下拉框
    setFont(QFont("宋体",12));
    setStyleSheet("QComboBox{border-style:none;background-color:rgba(0,0,0,0)}");
//    setStyleSheet("QLineEdit{border-width:0 0 1 0;border-color:rgba(0,0,0,40);border-style:outset;background-color:rgba(0,0,0,0)}");
    setLineEdit(m_LineEdit);
    addItem(tr("表达式"));

    m_statement = NULL;

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    setLayoutDirection(Qt::LayoutDirectionAuto);

    // 连接信号
    connect( this, SIGNAL(currentTextChanged(QString)), this, SIGNAL(textChanged(QString)) );
}

void CLineEdit::setStatement(CStatement *statement)
{
    m_statement = statement;
}

void CLineEdit::setText(QString text)
{
    setCurrentText(text);
}

QString CLineEdit::text() const
{
    return currentText();
}

void CLineEdit::showPopup()
{
    updateComboBox();
    QComboBox::showPopup();
}

void CLineEdit::insertExp()
{
    QStringList list;

    if( m_statement != NULL )
    {
        list = m_statement->getCurrentVars();
    }

    QString exp = CExpModifyDialog::getExp(list);
    if( exp != "null" )
    {
        m_LineEdit->insert( exp );
    }
}

void CLineEdit::editExp()
{
    insertExp();
}

void CLineEdit::insertFunction()
{
    QString funcExp = InsertFunctionDialog::getFuncExp( m_statement->getCurrentVars() );
    if( funcExp != "null" )
    {
        m_LineEdit->insert( funcExp );
    }
}

void CLineEdit::updateComboBox()
{
    QString str = currentText();
    clear();
    addItems( m_statement->getCurrentVars() );
    setCurrentText(str);
}

void CLineEdit::contextMenuEvent(QContextMenuEvent *e)
{
    // 设置右键菜单
    QMenu menu;

    // 编辑 & 插入
//    menu.addAction( tr("编辑表达式"), this, SLOT(editExp()) )->setEnabled( hasSelectedText() );
    menu.addAction( tr("插入运算符"), this, SLOT(insertExp()) );
    menu.addAction( tr("插入函数"), this, SLOT(insertFunction()) );
    menu.addSeparator();

    // 撤销 & 恢复
    menu.addAction( tr("撤销"), m_LineEdit, SLOT(undo()) )->setEnabled( m_LineEdit->isUndoAvailable() );
    menu.addAction( tr("恢复"), m_LineEdit, SLOT(redo()) )->setEnabled( m_LineEdit->isRedoAvailable() );
    menu.addSeparator();

    // 剪切 & 复制 & 粘贴
    menu.addAction( tr("剪切"), m_LineEdit, SLOT(cut()) )->setEnabled( m_LineEdit->hasSelectedText() );
    menu.addAction( tr("复制"), m_LineEdit, SLOT(copy()) )->setEnabled( m_LineEdit->hasSelectedText() );
    menu.addAction( tr("粘贴"), m_LineEdit, SLOT(paste()) );
    menu.addAction( tr("清空"), m_LineEdit, SLOT(clear()) )->setEnabled( ! m_LineEdit->text().isEmpty() );
    menu.addSeparator();

    // 全选
    menu.addAction( tr("全选"), m_LineEdit, SLOT(selectAll()) )->setEnabled( ! m_LineEdit->text().isEmpty() );

    // 显示菜单
    menu.exec( e->globalPos() );
}

/*
 * 一个无框、宋体、12号、居中对齐 的行编辑框
*/

#ifndef CLINEEDIT_H
#define CLINEEDIT_H

#include <QLineEdit>
#include <QComboBox>

class CStatement;

class CLineEdit : public QComboBox
{
    Q_OBJECT
public:
    CLineEdit(QString text="表达式");

    void setStatement(CStatement *statement);

    void setText(QString text);

    QString text()const;

    void showPopup();

signals:
    void textChanged(QString);

private slots:
    // 插入表达式
    void insertExp();
    // 编辑表达式
    void editExp();
    // 插入函数
    void insertFunction();
    // 更新下拉列表
    void updateComboBox();

protected:
    void contextMenuEvent(QContextMenuEvent *e);

private:
    QLineEdit	*m_LineEdit;
    CStatement	*m_statement;
};

#endif // CLINEEDIT_H

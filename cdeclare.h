#ifndef CDECLARE_H
#define CDECLARE_H

#include "cstatement.h"
#include <QComboBox>

class CLineEdit;

class CDeclare : public CStatement
{
    Q_OBJECT
public:
    explicit CDeclare(QWidget *parent = 0);

    QString getVarName()const;
    QStringList getVarNames()const;

    QString toCCode(int indent) const;
    void drawBackGround(QPainter&painter);

    void mousePressEvent(QMouseEvent *e);

private:
    QComboBox *m_comboBox;
    CLineEdit *m_lineEdit;
};

#endif // CDECLARE_H

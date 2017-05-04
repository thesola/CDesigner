#ifndef CBAFFLE_H
#define CBAFFLE_H

#include <QWidget>
#include <QDropEvent>

class CBaffle : public QWidget
{
    Q_OBJECT
public:
    explicit CBaffle(QWidget *parent = 0);

    void dropEvent(QDropEvent *e);

signals:
    void baffleDropEvent(QDropEvent *e);
};

#endif // CBAFFLE_H

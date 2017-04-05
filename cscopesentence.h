#ifndef CSCOPESENTENCE_H
#define CSCOPESENTENCE_H

#include "cscopebase.h"
#include <QLineEdit>

class CScopeSentence : public CScopeBase
{
public:
    CScopeSentence(QString text="语句 ;", QWidget *parent=0);
    ~CScopeSentence();

    QString text()const;
    void setText(QString text);

protected:
    void paintEvent(QPaintEvent *event);
private:
    QLineEdit *mText;
};

#endif // CSCOPESENTENCE_H

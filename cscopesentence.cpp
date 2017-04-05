#include "cscopesentence.h"

CScopeSentence::CScopeSentence(QString text, QWidget *parent):CScopeBase(parent)
{
    mText = new QLineEdit(this);
    mText->setText(text);
    mText->setFont(QFont("宋体",12));
    mText->setStyleSheet("QLineEdit{Border:0px none}");
}

CScopeSentence::~CScopeSentence()
{

}

QString CScopeSentence::text() const
{
    return mText->text();
}

void CScopeSentence::setText(QString text)
{
    mText->setText(text);
}

void CScopeSentence::paintEvent(QPaintEvent *event)
{
    int height = 20;
    int width = ((QWidget*)this->parent())->width();

    QPainter painter(this);
    painter.setPen(Qt::green);
    painter.drawRect(0,0,this->width(),this->height());
}


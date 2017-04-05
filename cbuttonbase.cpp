#include "cbuttonbase.h"

CButtonBase::CButtonBase(QWidget* parent):QPushButton(parent)
{
    setMinimumSize( 100, 100 );
    setStyleSheet("CButtonBase{background-color:#c7ede9}");
}

CButtonBase::~CButtonBase()
{

}


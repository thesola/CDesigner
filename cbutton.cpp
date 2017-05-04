#include "cbutton.h"
#include <cdef.h>
#include <QMap>


// 设置大小
const int CButton::mWidth 	= 80;
const int CButton::mHeight	= 80;


CButton::CButton(QString btnType, QWidget *parent) : QPushButton(parent)
{
    // 调整固定大小
    setFixedSize( mWidth, mHeight );
    // 设置背景色
    setStyleSheet("QPushButton{background-color:#c7ede9}");
    // 调整图标大小
    setIconSize( QSize(mWidth, mHeight) );
    // 设置接收拖拽事件
    setAcceptDrops(true);

    if( ! btnType.isEmpty() )
    {
        // 构建函数对应表
        QMap<QString,void (CButton::*)()> map;
        map.insert( g_strBtnIf,			setAsButtonIf );
        map.insert( g_strBtnIfElse,		setAsButtonIfElse );
        map.insert( g_strBtnSwitch,		setAsButtonSwitch );
        map.insert( g_strBtnWhile,		setAsButtonWhile );
        map.insert( g_strBtnDoWhile,	setAsButtonDWhile );
        map.insert( g_strBtnFor,		setAsButtonFor );
        map.insert( g_strBtnFunction,	setAsButtonFunction );
        map.insert( g_strBtnScope,		setAsButtonScope );
        map.insert( g_strBtnStatement, 	setAsButtonStatement );

        // 调用对应函数
        if( map.contains(btnType) )
        {
            (this->*map[btnType])();
        }
    }
}

void CButton::setAsButtonIf()
{
    mPixmap = g_getPixmapIf(mWidth,mHeight);
    setIcon( mPixmap );				// 设置图标
    mTypeName = g_strBtnIf;			// 设置类型名
}

void CButton::setAsButtonIfElse()
{
    mPixmap = g_getPixmapIfElse(mWidth,mHeight);
    setIcon( mPixmap );				// 设置图标
    mTypeName = g_strBtnIfElse;		// 设置类型名
}

void CButton::setAsButtonWhile()
{
    mPixmap = g_getPixmapWhile(mWidth,mHeight);
    setIcon( mPixmap );				// 设置图标
    mTypeName = g_strBtnWhile;		// 设置类型名
}

void CButton::setAsButtonDWhile()
{
    mPixmap = g_getPixmapDoWhile(mWidth,mHeight);
    setIcon( mPixmap );				// 设置图标
    mTypeName = g_strBtnDoWhile;	// 设置类型名
}

void CButton::setAsButtonFor()
{
    mPixmap = g_getPixmapFor(mWidth,mHeight);
    setIcon( mPixmap );				// 设置图标
    mTypeName = g_strBtnFor;		// 设置类型名
}

void CButton::setAsButtonSwitch()
{
    mPixmap = g_getPixmapSwitch(mWidth,mHeight);
    setIcon( mPixmap );				// 设置图标
    mTypeName = g_strBtnSwitch;		// 设置类型名
}

void CButton::setAsButtonScope()
{
    mPixmap = g_getPixmapScope(mWidth,mHeight);
    setIcon( mPixmap );				// 设置图标
    mTypeName = g_strBtnScope;		// 设置类型名
}

void CButton::setAsButtonStatement()
{
    mPixmap = g_getPixmapStatement(mWidth,mHeight);
    setIcon( mPixmap );				// 设置图标
    mTypeName = g_strBtnStatement;	// 设置类型名
}

void CButton::setAsButtonFunction()
{
    mPixmap = g_getPixmapFunction(mWidth,mHeight);
    setIcon( mPixmap );				// 设置图标
    mTypeName = g_strBtnFunction;	// 设置类型名
}

QString CButton::typeName()
{
    return mTypeName;
}

void CButton::mousePressEvent(QMouseEvent *e)
{
    if( mTypeName == g_strBtnFunction ) // 不拖拽
    {
        QPushButton::mousePressEvent(e);
        return;
    }

    QDrag *drag		= new QDrag(this);
    QMimeData *mime = new QMimeData();
    mime->setText( mTypeName );
    drag->setMimeData( mime );
    drag->setPixmap(mPixmap);
    drag->setHotSpot(QPoint(mWidth/2,mHeight/2));
    drag->start();

    QPushButton::mousePressEvent(e);
}


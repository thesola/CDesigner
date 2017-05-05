#ifndef CDEF_H
#define CDEF_H

#define STRING(s) const char s[]=#s;

// 几个全局常量
STRING(g_strBtnIf)
STRING(g_strBtnIfElse)
STRING(g_strBtnSwitch)
STRING(g_strBtnWhile)
STRING(g_strBtnDoWhile)
STRING(g_strBtnFor)
STRING(g_strBtnFunction)
STRING(g_strBtnScope)
STRING(g_strBtnSentence)
STRING(g_strBtnBreakSentence)
STRING(g_strBtnContinueSentence)
STRING(g_strBtnReturnSentence)

const int g_s32Indent = 4; // 缩进单位

STRING(g_strScope)
STRING(g_strSentence)

#include <QLabel>
extern QLabel *g_label;


// 几个绘图的全局函数
#include <QPixmap>

QPixmap g_getPixmapIf(int width, int height);
QPixmap g_getPixmapIfElse(int width, int height);
QPixmap g_getPixmapSwitch(int width, int height);
QPixmap g_getPixmapWhile(int width, int height);
QPixmap g_getPixmapDoWhile(int width, int height);
QPixmap g_getPixmapFor(int width, int height);
QPixmap g_getPixmapFunction(int width, int height);
QPixmap g_getPixmapScope(int width, int height);

QPixmap g_getPixmapSentence(int width, int height);
QPixmap g_getPixMapBreakSentence(int width, int height);
QPixmap g_getPixMapContinueSentence(int width, int height);
QPixmap g_getPixMapReturnSentence(int width, int height);

QPainterPath g_getPPathIf(int width, int height);
QPainterPath g_getPPathIfElse(int width, int height);


#endif // CDEF_H


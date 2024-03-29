/*
 * @Author: Zhao Yizhu
 * @Date: 2021-02-25 10:36:52
 * @LastEditors: Nestcc
 * @LastEditTime: 2022-01-24 01:23:55
 * @Description:  Some basic data structures
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#define NOCOLOR "\e[0m"   //清除颜色，即之后的打印为正常输出，之前的不受影响
#define BLACK "\e[0;30m"  //深黑
#define L_BLACK "\e[1;30m"  //亮黑，偏灰褐
#define RED "\e[0;31m"      //深红，暗红
#define L_RED "\e[1;31m"    //鲜红
#define GREEN "\e[0;32m"    //深绿，暗绿
#define L_GREEN "\e[1;32m"  //鲜绿
#define BROWN "\e[0;33m"    //深黄，暗黄
#define YELLOW "\e[1;33m"   //鲜黄
#define BLUE "\e[0;34m"     //深蓝，暗蓝
#define L_BLUE "\e[1;34m"   //亮蓝，偏白灰
#define PINK "\e[0;35m"     //深粉，暗粉，偏暗紫
#define L_PINK "\e[1;35m"   //亮粉，偏白灰
#define CYAN "\e[0;36m"     //暗青色
#define L_CYAN "\e[1;36m"   //鲜亮青色
#define GRAY "\e[0;37m"     //灰色
#define WHITE "\e[1;37m"    //白色，字体粗一点，比正常大，比bold小
#define BOLD "\e[1m"        //白色，粗体
#define UNDERLINE "\e[4m"   //下划线，白色，正常大小
#define BLINK "\e[5m"       //闪烁，白色，正常大小
#define REVERSE "\e[7m"     //反转，即字体背景为白色，字体为黑色
#define HIDE "\e[8m"        //隐藏
#define CLEAR "\e[2J"       //清除
#define CLRLINE "\r\e[K"    //清除行

// typedef struct _VM VM;
// typedef struct _PARSER Parser;
// typedef struct _CLASS Class;

class VM;
class Parser;
class BaseClass;

#include <cstdint>

// #define bool char
// #define True 1
// #define False 0
#define UNUSED __attribute__((unused))

#ifdef DEBUG
#define ASSERT(condition, errmsg)                                                             \
    do {                                                                                      \
        if (!(condition)) {                                                                   \
            fprintf(stderr, RED "An error occured!\n" NOCOLOR "%s at : %s,%d:%s()\n", errmsg, \
                    __FILE__, __LINE__, __func__);                                            \
            abort();                                                                          \
        }                                                                                     \
    } while (0);

#else
#define ASSERT(condition, errmsg)                                   \
    do {                                                            \
        if (!(condition)) {                                         \
            fprintf(stderr, RED "Error : " NOCOLOR "%s\n", errmsg); \
            exit(-1);                                               \
        }                                                           \
    } while (0);
#endif

#define NOT_REACHED()                                                                      \
    do {                                                                                   \
        fprintf(stderr, BROWN "Not reached:\n" NOCOLOR "%s,%d:%s()\n", __FILE__, __LINE__, \
                __func__);                                                                 \
    } while (0);

#endif

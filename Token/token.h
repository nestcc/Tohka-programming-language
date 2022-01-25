/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 19:24:39
 * @Discription: 
 */

#ifndef _TOHKA_TOKEN_H_
#define _TOHKA_TOKEN_H_

#include <cinttypes>
#include "object/value.h"

class Token {
public:
    enum TokenType {
        TOKEN_UNKNOWN,  // 0

        // 数据类型
        TOKEN_NUM,            //数字                   1
        TOKEN_STRING,         //字符串
        TOKEN_ID,             //变量名
        TOKEN_INTERPOLATION,  //内嵌表达式

        // 关键字(系统保留字)
        TOKEN_VAR,       //'var'                  5
        TOKEN_FUN,       //'fun'
        TOKEN_IF,        //'if'
        TOKEN_ELSE,      //'else'
        TOKEN_TRUE,      //'true'
        TOKEN_FALSE,     //'false'        10
        TOKEN_WHILE,     //'while'
        TOKEN_FOR,       //'for'
        TOKEN_BREAK,     //'break'
        TOKEN_CONTINUE,  //'continue'
        TOKEN_RETURN,    //'return'           15
        TOKEN_NULL,      //'null'

        //以下是关于类和模块导入的token
        TOKEN_CLASS,   //'class'
        TOKEN_THIS,    //'this'
        TOKEN_STATIC,  //'static'
        TOKEN_IS,      // 'is'                  20
        TOKEN_SUPER,   //'super'
        TOKEN_IMPORT,  //'import'

        //分隔符
        TOKEN_COMMA,          //','
        TOKEN_COLON,          //':'
        TOKEN_LEFT_PAREN,     //'('                25
        TOKEN_RIGHT_PAREN,    //')'
        TOKEN_LEFT_BRACKET,   //'['
        TOKEN_RIGHT_BRACKET,  //']'
        TOKEN_LEFT_BRACE,     //'{'
        TOKEN_RIGHT_BRACE,    //'}'                30
        TOKEN_DOT,            //'.'
        TOKEN_DOT_DOT,        //'..'

        //简单双目运算符
        TOKEN_ADD,  //'+'
        TOKEN_SUB,  //'-'
        TOKEN_MUL,  //'*'                    35
        TOKEN_DIV,  //'/'
        TOKEN_MOD,  //'%'

        //赋值运算符
        TOKEN_ASSIGN,  //'='

        // 位运算符
        TOKEN_BIT_AND,          //'&'
        TOKEN_BIT_OR,           //'|'                    40
        TOKEN_BIT_NOT,          //'~'
        TOKEN_BIT_SHIFT_RIGHT,  //'>>'
        TOKEN_BIT_SHIFT_LEFT,   //'<<'

        // 逻辑运算符
        TOKEN_LOGIC_AND,  //'&&'
        TOKEN_LOGIC_OR,   //'||'                   45
        TOKEN_LOGIC_NOT,  //'!'

        //关系操作符
        TOKEN_EQUAL,         //'=='
        TOKEN_NOT_EQUAL,     //'!='
        TOKEN_GREATE,        //'>'
        TOKEN_GREATE_EQUAL,  //'>='               50
        TOKEN_LESS,          //'<'
        TOKEN_LESS_EQUAL,    //'<='

        TOKEN_QUESTION,  //'?'

        TOKEN_SEMICOLON,  // ';'
        // 文件结束标记,仅词法分析时使用
        TOKEN_EOF  //'EOF'                  54
    };

public:
    TokenType type;
    const char *start;
    uint64_t length;
    uint64_t line_no;
    Value value;

public:
    Token() = default;

//    virtual void nud() = 0;
//    virtual void led() = 0;
//    virtual void method_sign() = 0;

};

#endif // end of _TOHKA_TOKEN_H_

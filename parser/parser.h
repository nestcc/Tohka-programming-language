/*
 * @Author: Nestcc
 * @Date: 2021-03-12 17:18:38
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-24 21:49:43
 * @Description:  < file content >
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#include "vm/mem_buffer_stl.h"
#include "vm/core.h"
#include "includes/common.h"
#include "includes/utils.h"
#include "includes/unicode.h"
#include "object/base_class.h"
#include "object/value.h"
#include "compiler/compiler_unit.h"

enum TokenType {
    TOKEN_UNKNOWN,                          // 0

    // 数据类型
    TOKEN_NUM,		   //数字                   1
    TOKEN_STRING,     	   //字符串
    TOKEN_ID,	     	   //变量名
    TOKEN_INTERPOLATION,     //内嵌表达式

    // 关键字(系统保留字)
    TOKEN_VAR,		   //'var'                  5
    TOKEN_FUN,		   //'fun'
    TOKEN_IF,		   //'if'
    TOKEN_ELSE,	     	   //'else'
    TOKEN_TRUE,	     	   //'true'
    TOKEN_FALSE,	     	   //'false'        10
    TOKEN_WHILE,	     	   //'while'
    TOKEN_FOR,	     	   //'for'
    TOKEN_BREAK,	     	   //'break'
    TOKEN_CONTINUE,         //'continue'
    TOKEN_RETURN,     	   //'return'           15
    TOKEN_NULL,	     	   //'null'

    //以下是关于类和模块导入的token
    TOKEN_CLASS,	     	   //'class'
    TOKEN_THIS,	     	   //'this'
    TOKEN_STATIC,     	   //'static'
    TOKEN_IS,		   // 'is'                  20
    TOKEN_SUPER,	     	   //'super'
    TOKEN_IMPORT,     	   //'import'

    //分隔符
    TOKEN_COMMA,		   //','
    TOKEN_COLON,		   //':'
    TOKEN_LEFT_PAREN,	   //'('                25
    TOKEN_RIGHT_PAREN,	   //')'
    TOKEN_LEFT_BRACKET,	   //'['
    TOKEN_RIGHT_BRACKET,	   //']'
    TOKEN_LEFT_BRACE,	   //'{'
    TOKEN_RIGHT_BRACE,	   //'}'                30
    TOKEN_DOT,		   //'.'
    TOKEN_DOT_DOT,	   //'..'

    //简单双目运算符
    TOKEN_ADD,		   //'+'
    TOKEN_SUB,		   //'-'
    TOKEN_MUL,		   //'*'                    35
    TOKEN_DIV,		   //'/'
    TOKEN_MOD,		   //'%'

    //赋值运算符
    TOKEN_ASSIGN,	   //'='

    // 位运算符
    TOKEN_BIT_AND,	   //'&'
    TOKEN_BIT_OR,	   //'|'                    40
    TOKEN_BIT_NOT,	   //'~'
    TOKEN_BIT_SHIFT_RIGHT,  //'>>'
    TOKEN_BIT_SHIFT_LEFT,   //'<<'

    // 逻辑运算符
    TOKEN_LOGIC_AND,	   //'&&'
    TOKEN_LOGIC_OR,	   //'||'                   45
    TOKEN_LOGIC_NOT,	   //'!'

    //关系操作符
    TOKEN_EQUAL,		   //'=='
    TOKEN_NOT_EQUAL,	   //'!='
    TOKEN_GREATE,	   //'>'
    TOKEN_GREATE_EQUAL,	   //'>='               50
    TOKEN_LESS,		   //'<'
    TOKEN_LESS_EQUAL,	   //'<='

    TOKEN_QUESTION,	   //'?'

    TOKEN_SEMICOLON,         // ';'
    // 文件结束标记,仅词法分析时使用
    TOKEN_EOF		   //'EOF'                  54
};

struct Token {
    TokenType type;
    const char *start;
    uint64_t length;
    uint64_t line_no;
    Value value;
};

class Parser {
public:
    Parser() = default;
    Parser(VM *vm, const char *file, const char *sourceCode, ObjModule *obj_mudule);

    /**
     * @description: 获取前一个字符
     */
    char look_ahead() const;

    /** 
     * @description: 下一个字符是否是期望的，是则读入并返回true，否则返回false
     */
    bool metch_token(TokenType expected);

    /**
     * @description: 跳过连续的空白
     */
    void skip_blanks();

    /**
     * @description: 解析token
     */    
    void parse_id(TokenType type);

    /**
     * @description: 获取下一个token
     */
    void get_next_token();

    /**
     * @description: 断言当前token为expected并读入下一token,否则报错errMsg
     */
    void consume_curr_token(TokenType expected, const char* errMsg);

    /**
     * @description: 断言下一个token为expected,否则报错errMsg
     */
    void consume_next_token(TokenType expected, const char* errMsg);

    const char *file;
    const char *source_code;

    const char *next_char_ptr;
    char curr_char;
    Token curr_token;
    Token prev_token;
    ObjModule *curr_module;
    CompilerUnit *curr_compile_unit;
    VM *vm;
    Parser *parent;

private:

    // 处于内嵌表达式之中时,期望的右括号数量.
    // 用于跟踪小括号对儿的嵌套
    int interpolation_expect_rparen_num;

    /**
     * @description: 查看下一个字符是否为期望的,如果是就读进来,返回true,否则返回false
     */
    bool match_next_char(char expected_char);

    /**
     * @description: 解析unicode码点
     */
    void parse_unicode_code_point(ByteBuffer *buf);

    /**
     * @description: 获取下一字符
     */
    void get_next_char();

    /**
     * @description: 解析字符串
     */
    void parse_string();

    /**
     * @description: 跳过注释
     */
    void skip_comment();

    /**
     * @description: 跳过一行
     */
    void skip_line();

    /**
     * @description: //若当前token为expected则读入下一个token并返回true,否则不读入token且返回false
     */
    bool match_token(TokenType expected);

    /**
 * @description: 解析十进制数
 */
    void parse_dec_number();

    /**
     * @description: 解析十六进制数
     */
    void parse_hex_number();

    /**
     * @description: 解析八进制数
     */
    void parse_oct_number();

    /**
     * @description: 解析数字
     */
    void parse_number();
};

#endif

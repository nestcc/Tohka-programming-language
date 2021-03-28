/*
 * @Author: Nestcc
 * @Date: 2021-03-12 17:18:38
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-03-16 12:21:56
 * @Description:  < file content >
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#include "../vm/vm.h"
#include "../vm/core.h"
#include "../includes/common.h"
#include "../includes/utils.h"
#include "../includes/unicode.h"

enum TokenType {
    TOKEN_UNKNOWN,

    // data type
    TOKEN_NUM,
    TOKEN_STRING,
    TOKEN_ID,
    TOKEN_INTERPOLATION,

    // key word
    TOKEN_VAR,		        //'var'
    TOKEN_FUN,		        //'fun'
    TOKEN_IF,		        //'if'
    TOKEN_ELSE,	     	    //'else'	
    TOKEN_TRUE,	     	    //'true'
    TOKEN_FALSE,	     	    //'false'
    TOKEN_WHILE,	     	    //'while'
    TOKEN_FOR,	     	    //'for'
    TOKEN_BREAK,	     	    //'break'
    TOKEN_CONTINUE,          //'continue'
    TOKEN_RETURN,     	    //'return'
    TOKEN_NULL,	     	    //'null'

    // class and module
    TOKEN_CLASS,	     	    //'class'
    TOKEN_THIS,	     	    //'this'
    TOKEN_STATIC,     	   //'static'
    TOKEN_IS,		   // 'is'
    TOKEN_SUPER,	     	   //'super'
    TOKEN_IMPORT,     	   //'import'

    //分隔符
    TOKEN_COMMA,		   //','
    TOKEN_COLON,		   //':'
    TOKEN_LEFT_PAREN,	   //'('
    TOKEN_RIGHT_PAREN,	   //')'
    TOKEN_LEFT_BRACKET,	   //'['
    TOKEN_RIGHT_BRACKET,	   //']'
    TOKEN_LEFT_BRACE,	   //'{'
    TOKEN_RIGHT_BRACE,	   //'}'
    TOKEN_DOT,		   //'.'
    TOKEN_DOT_DOT,	   //'..'

    //简单双目运算符
    TOKEN_ADD,		   //'+'
    TOKEN_SUB,		   //'-'
    TOKEN_MUL,		   //'*' 
    TOKEN_DIV,		   //'/' 
    TOKEN_MOD,		   //'%'

    //赋值运算符
    TOKEN_ASSIGN,	   //'='

    // 位运算符
    TOKEN_BIT_AND,	   //'&'
    TOKEN_BIT_OR,	   //'|'
    TOKEN_BIT_NOT,	   //'~'
    TOKEN_BIT_SHIFT_RIGHT,  //'>>'
    TOKEN_BIT_SHIFT_LEFT,   //'<<'

    // 逻辑运算符
    TOKEN_LOGIC_AND,	   //'&&'
    TOKEN_LOGIC_OR,	   //'||'
    TOKEN_LOGIC_NOT,	   //'!'

    //关系操作符
    TOKEN_EQUAL,		   //'=='
    TOKEN_NOT_EQUAL,	   //'!='
    TOKEN_GREATE,	   //'>'
    TOKEN_GREATE_EQUAL,	   //'>='
    TOKEN_LESS,		   //'<'
    TOKEN_LESS_EQUAL,	   //'<='

    TOKEN_QUESTION,	   //'?'

    //文件结束标记,仅词法分析时使用
    TOKEN_EOF		   //'EOF'
};

struct Token {
    TokenType type;
    const char *start;
    uint32_t length;
    uint32_t line_no;
};

class Parser {
public:
    Parser() = default;
    Parser(VM *vm, const char *file, const char *sourceCode);

    /**
     * @description: 获取前一个字符
     * @param {*}
     * @return {*}
     */
    char look_ahead() const;

    /** 
     * @description: 下一个字符是否是期望的，是则读入并返回true，否则返回false
     * @param {*}
     * @return {*}
     */
    bool metch_token(TokenType expected);

    /**
     * @description: 跳过连续的空白
     * @param {*}
     * @return {*}
     */
    void skip_blanks();

    /**
     * @description: 解析token
     * @param {TokenType} type
     * @return {*}
     */    
    void parse_id(TokenType type);

    /**
     * @description: 
     * @param {*}
     * @return {*}
     */
    void get_next_token();
    void consume_curr_token();
    void consume_next_token();

    bool metch_next_char(char expected_char);

    const char *file;
    const char *source_code;
    const char *next_char_ptr;
    char curr_char;
    Token curr_token;
    Token prev_token;

private:
    VM *vm;

    Parser *parent;

    // 处于内嵌表达式之中时,期望的右括号数量.
    // 用于跟踪小括号对儿的嵌套
    int interpolation_expect_rparen_num;

    void parse_unicode_code_point(ByteBuffer *buf);
    
    void get_next_char();
};

#endif

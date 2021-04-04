/*
 * @Author: Nestcc
 * @Date: 2021-03-12 17:18:43
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-03-29 15:44:19
 * @Description:  < file content > 
 */

#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#include "parser.h"

struct KeywordToken {
    std::string keyword;
    uint8_t     length;
    TokenType   token;
};  //关键字(保留字)结构

//关键字查找表
std::vector<KeywordToken> keywords_token = {
   {"var",      3,  TOKEN_VAR},
   {"fun",      3,  TOKEN_FUN},
   {"if",       2,  TOKEN_IF},
   {"else",     4,  TOKEN_ELSE},
   {"true",     4,  TOKEN_TRUE},
   {"false",    5,  TOKEN_FALSE},
   {"while",    5,  TOKEN_WHILE},
   {"for",      3,  TOKEN_FOR},
   {"break",    5,  TOKEN_BREAK},
   {"continue", 8,  TOKEN_CONTINUE},
   {"return",   6,  TOKEN_RETURN},
   {"null",     4,  TOKEN_NULL},
   {"class",    5,  TOKEN_CLASS},
   {"is",       2,  TOKEN_IS},
   {"static",   6,  TOKEN_STATIC},
   {"this",     4,  TOKEN_THIS},
   {"super",    5,  TOKEN_SUPER},
   {"import",   6,  TOKEN_IMPORT},
   {"",         0,  TOKEN_UNKNOWN}
};

static TokenType id_or_keyword(const char *str, size_t length) {
    TokenType ret;
    for (size_t i = 0; i < keywords_token.size(); i += 1) {
        if (keywords_token[i].length == length &&
            memcmp((char *) keywords_token[i].keyword.c_str(), str, length) == 0) {
                return (TokenType) (keywords_token[i].token);
        }
    }

    return TOKEN_ID;
}

Parser::Parser(VM* vm, const char* file, const char* source_code)  {
    this -> vm = vm;
    this -> file = file;
    this -> source_code = source_code;

    curr_char = *this -> source_code;
    next_char_ptr = this -> source_code + 1;

    curr_token = Token();
    prev_token = Token();

    curr_token.line_no = 1;
    curr_token.type = TOKEN_UNKNOWN;
    curr_token.start = nullptr;
    curr_token.length = 0;
    
    prev_token = curr_token;
    
    interpolation_expect_rparen_num = 0;

};

char Parser::look_ahead() const {
    return *next_char_ptr;
}

bool Parser::metch_token(TokenType expected) {
    if (curr_token.type == expected) {
        get_next_token();
        return true;
    }
    return false;
}

void Parser::skip_blanks() {
    while (isspace(curr_char)) {
        if (curr_char == '\n') { curr_token.line_no += 1; }
        get_next_char();
    }
    return ;
}

void Parser::parse_id(TokenType type) {
    while (isalnum(curr_char) || curr_char == '_') {
        get_next_char();
    }

    auto wlen = (size_t) (next_char_ptr - curr_token.start - 1);

    if (type != TOKEN_UNKNOWN) { curr_token.type = type; }
    else { curr_token.type = id_or_keyword(curr_token.start, wlen); }

    curr_token.length = wlen;
    return ;
}

void Parser::get_next_char() {
    curr_char = *next_char_ptr++;
}

void Parser::get_next_token() {
    prev_token = curr_token;
    skip_blanks();

    curr_token.type = TOKEN_EOF;
    curr_token.length = 0;
    curr_token.start = next_char_ptr - 1;

    while (curr_char != '\0') {
        switch (curr_char) {
        case ',':
            curr_token.type = TOKEN_COMMA;
            break;
        case ':':
            curr_token.type = TOKEN_COLON;
            break;
        case '(':
            if (interpolation_expect_rparen_num > 0) {
                interpolation_expect_rparen_num += 1;
            }
            curr_token.type = TOKEN_LEFT_PAREN;
            break;
        case ')':
            if (interpolation_expect_rparen_num > 0) {
                interpolation_expect_rparen_num -= 1;
                if (interpolation_expect_rparen_num == 0) {
                    parse_string();
                    break;
                }
            }
            curr_token.type = TOKEN_RIGHT_PAREN;
            break;
        case '[':
            curr_token.type = TOKEN_LEFT_BRACKET;
            break;
        case ']':
            curr_token.type = TOKEN_RIGHT_BRACKET;
            break;
        case '{':
            curr_token.type = TOKEN_LEFT_BRACE;
            break;
        case '}':
            curr_token.type = TOKEN_RIGHT_BRACE;
            break;
        case '.':
            if (match_next_char('.')) { curr_token.type = TOKEN_DOT_DOT; }
            else { curr_token.type = TOKEN_DOT; }
            break;
        case '=':
            if (match_next_char('=')) { curr_token.type = TOKEN_EQUAL; }
            else { curr_token.type = TOKEN_ASSIGN; }
            break;
        case '+':
            curr_token.type = TOKEN_ADD;
            break;
        case '-':
            curr_token.type = TOKEN_SUB;
            break;
        case '*':
            curr_token.type = TOKEN_MUL;
            break;
	    case '/':
	    //跳过注释'//'或'/*'
            if (match_next_char('/') || match_next_char('*')) {
                skip_comment();
                //重置下一个token起始地址
                curr_token.start = next_char_ptr - 1;
                continue;
            } 
            else { curr_token.type = TOKEN_DIV; } // '/' 
            break;
        case '%':
            curr_token.type = TOKEN_MOD;
            break;
        case '&':
            if (match_next_char('&')) { curr_token.type = TOKEN_LOGIC_AND; }
            else { curr_token.type = TOKEN_BIT_AND; }
            break;
        case '|':
            if (match_next_char('|')) { curr_token.type = TOKEN_LOGIC_OR; }
            else { curr_token.type = TOKEN_BIT_OR; }
	        break;
        case '~':
            curr_token.type = TOKEN_BIT_NOT;
            break;
        case '?':
            curr_token.type = TOKEN_QUESTION;
            break;
        case '>':
            if (match_next_char('=')) { curr_token.type = TOKEN_GREATE_EQUAL; }
            else if (match_next_char('>')) { curr_token.type = TOKEN_BIT_SHIFT_RIGHT; }
            else { curr_token.type = TOKEN_GREATE; }
            break;
        case '<':
            if (match_next_char('=')) { curr_token.type = TOKEN_LESS_EQUAL; }
            else if (match_next_char('<')) { curr_token.type = TOKEN_BIT_SHIFT_LEFT; }
            else { curr_token.type = TOKEN_LESS; }
            break;
        case '!':
            if (match_next_char('=')) { curr_token.type = TOKEN_NOT_EQUAL; }
            else { curr_token.type = TOKEN_LOGIC_NOT; }
            break;

        case '"':
            parse_string();
            break;

        default:    
            //处理变量名及数字
            //进入此分支的字符肯定是数字或变量名的首字符
            //后面会调用相应函数把其余字符一并解析
            //不过识别数字需要一些依赖,目前暂时去掉

            //首字符是字母或'_'则是变量名
            if (isalpha(curr_char) || curr_char == '_') {
                parse_id(TOKEN_UNKNOWN);  //解析变量名其余的部分
            }
            else {
                if (curr_char == '#' && match_next_char('!')) {
                    skip_line();
                    curr_token.start = next_char_ptr - 1;  //重置下一个token起始地址
                    continue;
                } 
                LEX_ERROR(this, "unsupport char: \'%c\', quit.", curr_char);
            }
            return;
        }
        curr_token.length = (uint32_t) (next_char_ptr - curr_token.start);
        get_next_char();
        return ;
    }
}

void Parser::consume_curr_token(TokenType expected, const char* errMsg) {
    if (curr_token.type != expected) {
        COMPILE_ERROR(this, errMsg);
    }
    get_next_token();
}

void Parser::consume_next_token(TokenType expected, const char* errMsg) {
    get_next_token();
    if (curr_token.type != expected) {
        COMPILE_ERROR(this, errMsg);
    }
}

bool Parser::match_next_char(char expected_char) {
    if (look_ahead() == expected_char) {
        get_next_char();
        return true;
    }
    return false;
}

void Parser::parse_unicode_code_point(ByteBuffer *buf) {
    uint32_t idx = 0;
    int value = 0;
    uint8_t digit = 0;

    while (idx ++ < 4) {
        get_next_char();
        if (curr_char >= '0' || curr_char <= '9') { digit = curr_char - '0'; }
        else if (curr_char >= 'a' || curr_char <= 'z') { digit = curr_char - 'a' + 10; }
        else if (curr_char >= 'A' || curr_char <= 'Z') { digit = curr_char - 'A' + 10; }
        else { LEX_ERROR(this, RED "invalid unicode!\n" NOCOLOR ); }

        value = value * 16 | digit;
    }

    uint32_t byte_num = get_number_encode_utf8(value);
    ASSERT(byteNum != 0, "utf8 encode bytes should be between 1 and 4!");

    buf -> fill_wirte(vm, 0, byte_num);
    encode_utf8(buf -> data() + buf -> size() - byte_num, value);

    return;
}

void Parser::parse_string() {
    ByteBuffer str;

    while (true) {
        get_next_char();

        if (curr_char == '\0') {
            LEX_ERROR(this, "unterminated string!");
        }

        if (curr_char == '"') {
            curr_token.type = TOKEN_STRING;
            break;
        }

        if (curr_char == '%') {
            if (!match_next_char('(')) {
                LEX_ERROR(this, "'%' should followed by '('!");
            }
            if (interpolation_expect_rparen_num > 0) {
                COMPILE_ERROR(this, "sorry, I don`t support nest interpolate expression!");
            }
            interpolation_expect_rparen_num = 1;
            curr_token.type = TOKEN_INTERPOLATION;
            break;
        }

        if (curr_char == '\\') {   //处理转义字符
            get_next_char();
            switch (curr_char) {
                case '0':
                    str.buff_add(vm, '\0');
                    break;
                case 'a':
                    str.buff_add(vm, '\a');
                    break;
                case 'b':
                    str.buff_add(vm, '\b');
                    break;
                case 'f':
                    str.buff_add(vm, '\f');
                    break;
                case 'n':
                    str.buff_add(vm, '\n');
                    break;
                case 'r':
                    str.buff_add(vm, '\r');
                    break;
                case 't':
                    str.buff_add(vm, '\t');
                    break;
                case 'u':
                    parse_unicode_code_point(&str);
                    break;
                case '"':
                    str.buff_add(vm, '"');
                    break;
                case '\\':
                    str.buff_add(vm, '\\');
                    break;
                default:
                    LEX_ERROR(this, "unsupport escape \\%c", curr_char);
                    break;
            }
        } else {   //普通字符
            str.buff_add(vm, curr_char);
        }
    }
    str.buff_clear(vm);
    return;
}

void Parser::skip_comment() {
    char next_ch = look_ahead();
    if (curr_char == '/') { skip_line(); }
    else {
        while (next_ch != '*' && next_ch != '\0') {
            get_next_char();
            if (curr_char == '\n') {
                curr_token.line_no++;
            }
            next_ch = look_ahead();
        }
        if (match_next_char('*')) {
            if (!match_next_char('/')) {   //匹配*/
                LEX_ERROR(this, "expect '/' after '*'!");
            }
            get_next_char();
        }
        else { LEX_ERROR(this, "expect '*/' before file end!"); }
    }
}

void Parser::skip_line() {
    get_next_char();
    while (curr_char != '\0') {
        if (curr_char == '\n') {
            curr_token.line_no += 1;
            get_next_char();
            break;
        }
        get_next_char();
    }
    return ;
}

bool Parser::match_token(TokenType expected) {
    if (curr_token.type == expected) {
        get_next_token();
        return true;
    }
    return false;
}

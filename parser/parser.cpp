/*
 * @Author: Nestcc
 * @Date: 2021-03-12 17:18:43
 * @LastEditors: Nestcc
 * @LastEditTime: 2022-01-24 01:28:06
 * @Description:  < file content >
 */

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "parser/parser.h"
#include "token/token.h"
#include "token/unused_rule_token/colon_token.h"
#include "token/unused_rule_token/comma_token.h"
#include "token/prefix_symbol_token/left_paren_token.h"
#include "token/unused_rule_token/unknown_token.h"

struct KeywordToken {
    std::string keyword;
    uint8_t length;
    Token::TokenType token;
};  //关键字(保留字)结构

//关键字查找表
std::vector<KeywordToken> keywords_token = {
    {"var", 3, Token::TOKEN_VAR},           {"fun", 3, Token::TOKEN_FUNC},       {"if", 2, Token::TOKEN_IF},
    {"else", 4, Token::TOKEN_ELSE},         {"true", 4, Token::TOKEN_TRUE},     {"false", 5, Token::TOKEN_FALSE},
    {"while", 5, Token::TOKEN_WHILE},       {"for", 3, Token::TOKEN_FOR},       {"break", 5, Token::TOKEN_BREAK},
    {"continue", 8, Token::TOKEN_CONTINUE}, {"return", 6, Token::TOKEN_RETURN}, {"null", 4, Token::TOKEN_NULL},
    {"class", 5, Token::TOKEN_CLASS},       {"is", 2, Token::TOKEN_IS},         {"static", 6, Token::TOKEN_STATIC},
    {"this", 4, Token::TOKEN_THIS},         {"super", 5, Token::TOKEN_SUPER},   {"import", 6, Token::TOKEN_IMPORT},
    {"", 0, Token::TOKEN_UNKNOWN}};

static Token::TokenType id_or_keyword(const char *str, uint64_t length) {
    Token::TokenType ret;
    for (uint64_t i = 0; i < keywords_token.size(); i += 1) {
        if (keywords_token[i].length == length &&
            memcmp((char *)keywords_token[i].keyword.c_str(), str, length) == 0) {
            return (Token::TokenType)(keywords_token[i].token);
        }
    }

    return Token::TOKEN_ID;
}

Parser::Parser(VM *vm, const char *file, const char *source_code, ObjModule *obj_mudule) {
    this->vm = vm;
    this->file = file;
    this->source_code = source_code;

    curr_char = *this->source_code;
    next_char_ptr = this->source_code + 1;

    curr_token = new UnknownToken();
    prev_token = curr_token;

    this->curr_module = obj_mudule;

    interpolation_expect_rparen_num = 0;
};

char Parser::look_ahead() const { return *next_char_ptr; }

bool Parser::metch_token(Token::TokenType expected) {
    if (curr_token->type == expected) {
        get_next_token();
        return true;
    }
    return false;
}

void Parser::skip_blanks() {
    while (isspace(curr_char)) {
        if (curr_char == '\n') {
            curr_token->line_no += 1;
        }
        get_next_char();
    }
    return;
}

void Parser::parse_id(Token::TokenType type) {
    while (isalnum(curr_char) || curr_char == '_') {
        get_next_char();
    }

    auto wlen = (uint64_t)(next_char_ptr - curr_token->start - 1);

    if (type != Token::TOKEN_UNKNOWN) {
        curr_token->type = type;
    } else {
        curr_token->type = id_or_keyword(curr_token->start, wlen);
    }

    curr_token->length = wlen;
    return;
}

void Parser::get_next_char() { curr_char = *(next_char_ptr++); }

void Parser::get_next_token() {
    prev_token = curr_token;
    skip_blanks();

//    curr_token.type = Token::TOKEN_EOF;
//    curr_token.length = 0;
//    curr_token.start = next_char_ptr - 1;

    while (curr_char != '\0' && curr_char != EOF) {
        switch (curr_char) {
        case ',':
            curr_token = new CommaToken();
            break;
        case ':':
            curr_token = new ColonToken();
            break;
        case '(':
            if (interpolation_expect_rparen_num > 0) {
                interpolation_expect_rparen_num += 1;
            }
            curr_token = new LeftParenToken();
            break;
        case ')':
            if (interpolation_expect_rparen_num > 0) {
                interpolation_expect_rparen_num -= 1;
                if (interpolation_expect_rparen_num == 0) {
                    parse_string();
                    break;
                }
            }
            curr_token->type = Token::TOKEN_RIGHT_PAREN;
            break;
        case '[':
            curr_token->type = Token::TOKEN_LEFT_BRACKET;
            break;
        case ']':
            curr_token->type = Token::TOKEN_RIGHT_BRACKET;
            break;
        case '{':
            curr_token->type = Token::TOKEN_LEFT_BRACE;
            break;
        case '}':
            curr_token->type = Token::TOKEN_RIGHT_BRACE;
            break;
        case '.':
            if (match_next_char('.')) {
                curr_token->type = Token::TOKEN_DOT_DOT;
            } else {
                curr_token->type = Token::TOKEN_DOT;
            }
            break;
        case '=':
            if (match_next_char('=')) {
                curr_token->type = Token::TOKEN_EQUAL;
            } else {
                curr_token->type = Token::TOKEN_ASSIGN;
            }
            break;
        case '+':
            curr_token->type = Token::TOKEN_ADD;
            break;
        case '-':
            curr_token->type = Token::TOKEN_SUB;
            break;
        case '*':
            curr_token->type = Token::TOKEN_MUL;
            break;
        case '/':
            //跳过注释'//'或'/*'
            if (match_next_char('/') || match_next_char('*')) {
                skip_comment();
                //重置下一个token起始地址
                curr_token->start = next_char_ptr - 1;
                continue;
            } else {
                curr_token->type = Token::TOKEN_DIV;
            }  // '/'
            break;
        case '%':
            curr_token->type = Token::TOKEN_MOD;
            break;
        case '&':
            if (match_next_char('&')) {
                curr_token->type = Token::TOKEN_LOGIC_AND;
            } else {
                curr_token->type = Token::TOKEN_BIT_AND;
            }
            break;
        case '|':
            if (match_next_char('|')) {
                curr_token->type = Token::TOKEN_LOGIC_OR;
            } else {
                curr_token->type = Token::TOKEN_BIT_OR;
            }
            break;
        case '~':
            curr_token->type = Token::TOKEN_BIT_NOT;
            break;
        case '?':
            curr_token->type = Token::TOKEN_QUESTION;
            break;
        case '>':
            if (match_next_char('=')) {
                curr_token->type = Token::TOKEN_GREATE_EQUAL;
            } else if (match_next_char('>')) {
                curr_token->type = Token::TOKEN_BIT_SHIFT_RIGHT;
            } else {
                curr_token->type = Token::TOKEN_GREATE;
            }
            break;
        case '<':
            if (match_next_char('=')) {
                curr_token->type = Token::TOKEN_LESS_EQUAL;
            } else if (match_next_char('<')) {
                curr_token->type = Token::TOKEN_BIT_SHIFT_LEFT;
            } else {
                curr_token->type = Token::TOKEN_LESS;
            }
            break;
        case '!':
            if (match_next_char('=')) {
                curr_token->type = Token::TOKEN_NOT_EQUAL;
            } else {
                curr_token->type = Token::TOKEN_LOGIC_NOT;
            }
            break;

        case '"':
            parse_string();
            break;

        case ';':
            curr_token->type = Token::TOKEN_SEMICOLON;
            break;

        default:
            //处理变量名及数字
            //进入此分支的字符肯定是数字或变量名的首字符
            //后面会调用相应函数把其余字符一并解析
            //不过识别数字需要一些依赖,目前暂时去掉

            //首字符是字母或'_'则是变量名
            if (isalpha(curr_char) || curr_char == '_') {
                parse_id(Token::TOKEN_UNKNOWN);  //解析变量名其余的部分
            } else if (isdigit(curr_char)) {
                parse_number();
            } else {
                if (curr_char == '#' && match_next_char('!')) {
                    skip_line();
                    curr_token->start = next_char_ptr - 1;  //重置下一个token起始地址
                    continue;
                }
                LEX_ERROR(this, "unsupport char: \'%c\' %d, quit.", curr_char, curr_char);
            }
            return;
        }
        curr_token->length = (uint64_t)(next_char_ptr - curr_token->start);
        get_next_char();
        return;
    }
}

void Parser::consume_curr_token(Token::TokenType expected, const char *errMsg) {
    if (curr_token->type != expected) {
        COMPILE_ERROR(this, errMsg);
    }
    get_next_token();
}

void Parser::consume_next_token(Token::TokenType expected, const char *errMsg) {
    get_next_token();
    if (curr_token->type != expected) {
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
    uint64_t idx = 0;
    int value = 0;
    uint8_t digit = 0;

    while (idx++ < 4) {
        get_next_char();
        if (curr_char >= '0' || curr_char <= '9') {
            digit = curr_char - '0';
        } else if (curr_char >= 'a' || curr_char <= 'z') {
            digit = curr_char - 'a' + 10;
        } else if (curr_char >= 'A' || curr_char <= 'Z') {
            digit = curr_char - 'A' + 10;
        } else {
            LEX_ERROR(this, RED "invalid unicode!\n" NOCOLOR);
        }

        value = value * 16 | digit;
    }

    uint64_t byte_num = get_number_encode_utf8(value);
    ASSERT(byte_num != 0, "utf8 encode bytes should be between 1 and 4!");

    buf->fill_wirte(0, byte_num);
    encode_utf8(buf->data() + buf->size() - byte_num, value);
}

void Parser::parse_string() {
    ByteBuffer str;
    str.vm = vm;

    while (true) {
        get_next_char();

        if (curr_char == '\0') {
            LEX_ERROR(this, "unterminated string!");
        }

        if (curr_char == '"') {
            curr_token->type = Token::TOKEN_STRING;
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
            curr_token->type = Token::TOKEN_INTERPOLATION;
            break;
        }

        if (curr_char == '\\') {  //处理转义字符
            get_next_char();
            switch (curr_char) {
            case '0':
                str.buff_add('\0');
                break;
            case 'a':
                str.buff_add('\a');
                break;
            case 'b':
                str.buff_add('\b');
                break;
            case 'f':
                str.buff_add('\f');
                break;
            case 'n':
                str.buff_add('\n');
                break;
            case 'r':
                str.buff_add('\r');
                break;
            case 't':
                str.buff_add('\t');
                break;
            case 'u':
                parse_unicode_code_point(&str);
                break;
            case '"':
                str.buff_add('"');
                break;
            case '\\':
                str.buff_add('\\');
                break;
            default:
                LEX_ERROR(this, "unsupport escape \\%c", curr_char);
                break;
            }
        } else {  //普通字符
            str.buff_add(curr_char);
        }
    }

    ObjString *obj_str = new ObjString(vm, (const char *)str.data(), (uint64_t)str.size());
    curr_token->value = new Value(obj_str);
    return;
}

void Parser::skip_comment() {
    char next_ch = look_ahead();
    if (curr_char == '/') {
        skip_line();
    } else {
        while (next_ch != '*' && next_ch != '\0') {
            get_next_char();
            if (curr_char == '\n') {
                curr_token->line_no++;
            }
            next_ch = look_ahead();
        }
        if (match_next_char('*')) {
            if (!match_next_char('/')) {  //匹配*/
                LEX_ERROR(this, "expect '/' after '*'!");
            }
            get_next_char();
        } else {
            LEX_ERROR(this, "expect '*/' before file end!");
        }
    }
}

void Parser::skip_line() {
    get_next_char();
    while (curr_char != '\0') {
        if (curr_char == '\n') {
            curr_token->line_no += 1;
            get_next_char();
            break;
        }
        get_next_char();
    }
    return;
}

bool Parser::match_token(Token::TokenType expected) {
    if (curr_token->type == expected) {
        get_next_token();
        return true;
    }
    return false;
}

void Parser::parse_dec_number() {
    while (isdigit(curr_char)) {
        get_next_char();
    }
    if (curr_char == '.' && isdigit(look_ahead())) {
        get_next_char();
        while (isdigit(curr_char)) {
            get_next_char();
        }
    }
}

void Parser::parse_hex_number() {
    while (isxdigit(curr_char)) {
        get_next_char();
    }
}

void Parser::parse_oct_number() {
    while (curr_char >= '0' && curr_char < '8') {
        get_next_char();
    }
}

void Parser::parse_number() {
    if (curr_char == '0' && match_next_char('x')) {
        get_next_char();  // skip 'x' behind '0'
        parse_hex_number();
        curr_token->value = new Value(strtol(curr_token->start, nullptr, 16));
    } else if (curr_char == '0' && isdigit(look_ahead())) {
        parse_oct_number();
        curr_token->value = new Value(strtol(curr_token->start, nullptr, 8));
    } else {
        parse_dec_number();
        curr_token->value = new Value(strtol(curr_token->start, nullptr, 10));
    }

    curr_token->length = (uint64_t)(next_char_ptr - curr_token->start - 1);
    curr_token->type = Token::TOKEN_NUM;
}

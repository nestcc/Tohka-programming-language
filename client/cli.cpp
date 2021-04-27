/*
 * @Author: Nestcc
 * @Date: 2021-03-28 10:22:48
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-04-26 17:40:22
 * @Description:  < file content > 
 */

#include <iostream>
#include <cstring>
#include "cli.h"
#include "../object/ObjFunction.h"
#include "../object/ObjModule.h"

void runFile(const char* path) {
    const char* lastSlash = strrchr(path, '/');
    if (lastSlash != nullptr) {
        char* root = (char*)malloc(lastSlash - path + 2);
        memcpy(root, path, lastSlash - path + 1);
        root[lastSlash - path + 1] = '\0';
        root_dir = root;
    }

    VM *vm = VM::getInstance();

    const char* sourceCode = read_file(path);

    Parser parser(vm, path, sourceCode, nullptr);

    #include "../parser/token.list"

    while (parser.curr_token.type != TOKEN_EOF) {
        parser.get_next_token();
        printf(" %llu L-tokenArray [%s] : [", parser.curr_token.line_no,
               tokenArray[parser.curr_token.type].c_str());
//        std::cout << tokenArray[parser.curr_token.type] << " [";
        uint32_t idx = 0;
        while (idx < parser.curr_token.length) {
            printf("%c", *(parser.curr_token.start + idx++));
        }
        printf("]\n");
    }
}

int main(int argc, const char **argv) {
    LOG_INFO("in main\n");

    if (argc == 1) {
        fprintf(stderr, RED "use %s [ file name ] ...\n" NOCOLOR, argv[0]);
    } else {
        runFile(argv[1]);
    }

    VM *vm = VM::getInstance();

    std::cout << " get all objects" << std::endl;
    ObjHeader *objs = vm -> all_objects, *tmp = objs -> next;
//    std::cout << objs -> type << std::endl;
    ObjString *str_obj = dynamic_cast<ObjString *> (objs);
    if (str_obj != nullptr)
        std::cout << " > objs : " << str_obj -> value << std::endl;

    while (tmp != objs) {
        ObjString *str_obj = dynamic_cast<ObjString *> (tmp);
        if (str_obj == nullptr) {
            std::cout << " > curr obj not ObjString, but " << tmp -> type << std::endl;
            tmp = tmp -> next;
            continue;
        }
        std::cout << " > curr obj : " << str_obj -> value << std::endl;
        tmp = tmp -> next;
    }

    return 0;
}

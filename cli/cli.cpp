/*
 * @Author: Nestcc
 * @Date: 2021-03-28 10:22:48
 * @LastEditors: Nestcc
 */

#include "cli/cli.h"

#include <cstring>
#include <iostream>

#include "object/obj_function.h"
#include "object/obj_module.h"

void run_file_parser(const char *path) {
    const char *lastSlash = strrchr(path, '/');
    VM *vm = VM::instance();

    if (lastSlash != nullptr) {
        char *root = (char *)malloc(lastSlash - path + 2);
        memcpy(root, path, lastSlash - path + 1);
        root[lastSlash - path + 1] = '\0';
        vm->root_dir = root;
    }

    const char *sourceCode = vm->read_file(path);

    Parser parser(vm, path, sourceCode, nullptr);

#include "Token/token_list.h"

    while (parser.curr_token.type != Token::TOKEN_EOF) {
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

static void run_file(const char *path) {
    const char *last_slash = strrchr(path, '/');
    VM *vm = VM::instance();
    if (last_slash != nullptr) {
        char *root = (char *)malloc(last_slash - path + 2);
        memcpy(root, path, last_slash - path + 1);
        root[last_slash - path + 1] = '\0';
        vm->root_dir = root;
    }

    const char *source_code = vm->read_file(path);

    std::string spath(path);
    ObjString src(vm, spath);
    vm->exec_module(new Value(&src), source_code);
}

int main(int argc, const char **argv) {
    LOG_INFO("in main\n");

    if (argc == 1) {
        fprintf(stderr, RED "use %s [ file name ] ...\n" NOCOLOR, argv[0]);
    } else {
        run_file(argv[1]);
    }

    VM *vm = VM::instance();

    std::cout << " get all objects" << std::endl;
    ObjHeader *objs = vm->all_objects, *tmp = objs->next;

    while (tmp != objs) {
        auto *str_obj = dynamic_cast<ObjString *>(tmp);
        if (str_obj == nullptr) {
            std::cout << " > curr obj not ObjString, but " << tmp->type
                      << std::endl;
            tmp = tmp->next;
            continue;
        }
        std::cout << " > curr obj : " << str_obj->value << std::endl;
        tmp = tmp->next;
    }

    return 0;
}

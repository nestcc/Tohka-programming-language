/*
 * @Author: nestcc
 * @Date: 2021/4/4 18:40
 * @LastEditors: Nestcc
 * @LastEditTime: 2022-01-24 01:58:04
 * @Discription:
 */

#include "object/obj_module.h"

#include "object/obj_string.h"
#include "object/value.h"
#include "parser/parser.h"

ObjModule::ObjModule(VM *vm, const std::string &mod_name) : ObjHeader(vm, OT_MODULE, nullptr) {
    // module_var_name = SymbolTable(vm, 0);
    new (&module_var_name) SymbolTable(vm, 0);
    // module_var_value = ValueBuffer(vm, 0);
    new (&module_var_value) ValueBuffer(vm, 0);

    //    delete name;
    name = new ObjString(vm, mod_name);
    vm->alloc_memory(sizeof(*this));
    LOG_INFO(" allocated ObjModule by %lu\n", sizeof(*this));
    LOG_INFO(" module name = %s\n", name->value.c_str());
}

ObjModule::~ObjModule() { delete name; }

void ObjModule::compile_module(const char *module_code) {
    Parser *parser = nullptr;
    if (name == nullptr) {
        parser = new Parser(vm, "../vm/core_script.h", module_code, this);
    } else {
        parser = new Parser(vm, name->value.c_str(), module_code, this);
    }
    parser->parent = vm->curr_parser;
    vm->curr_parser = parser;

    CompileUnit *cu = new CompileUnit(parser, nullptr, false);

    uint32_t module_var_num_before = module_var_value.size();

    parser->get_next_token();

    while (!parser->metch_token(Token::TOKEN_EOF)) {
        cu->compile_program();
    }

    if (vm->curr_parser == parser) {
        vm->curr_parser = vm->curr_parser->parent;
    }
    delete parser;
    delete cu;
    return;
}

uint64_t ObjModule::define_var(const std::string &name, Value *value) {
    if (name.size() > MAX_ID_LEN) {
        if (vm->curr_parser == nullptr) {
            COMPILE_ERROR(nullptr, "Invilad value name %s", name.c_str());
        } else {
            MEM_ERROR(nullptr, "Invilad value name %s", name.c_str());
        }
    }

    uint64_t symbol_index =
        std::find(module_var_name.begin(), module_var_name.end(), name) - module_var_name.begin();
    if (symbol_index == module_var_name.size()) {
        module_var_name.buff_add(name);
        module_var_value.buff_add(*value);
    } else if (module_var_name[symbol_index] == name) {
        module_var_value[symbol_index] = *value;
    } else {
        symbol_index = -1;
    }
    return symbol_index;
}

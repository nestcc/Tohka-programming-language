/*
 * @Author: Nestcc
 * @Date: 2021-04-27 18:43:46
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-05-08 16:08:00
 * @Description:  < file content > 
 */

#include "headers.h"
#include "../includes/utils.h"
#include "../vm/core.h"
#include "compiler.h"
#include "../object/ObjModule.h"
#include "../object/Value.h"

int define_module_value(VM *vm, ObjModule *obj_module, std::string name, const Value &val) {
    if (name.size() > MAX_ID_LEN) {
        if (vm -> curr_parser != nullptr) {
            COMPILE_ERROR(vm -> curr_parser, "Identifier %s is longer than MAX_ID_LEN(%d)", 
                            name.c_str(), MAX_ID_LEN);
        }
        else {
            MEM_ERROR("Identifier %s is longer than MAX_ID_LEN(%d)", 
                        name.c_str(), MAX_ID_LEN);
        }
    }

    // std::string module_name(name, length);
    int symbol_index = get_index_from_symbol_table(&(obj_module -> module_var_name), name);
    if (symbol_index == obj_module -> module_var_name.size()) {
        obj_module -> module_var_name.buff_add(name);
    }
    else if (obj_module -> module_var_value[symbol_index].type == VT_NULL) {
        obj_module -> module_var_value[symbol_index] = val;
    }
    else {
        symbol_index = -1;
    }
    return symbol_index;
}

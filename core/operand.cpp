/*
 * @Author: zhaoyzh
 * @Date: 2022-01-25 17:14:38
 * @Discription: 
 */

#include "core/operand.h"


ShortOperand::ShortOperand(uint64_t operand) {
    short_operand = short(operand);
}

ShortOperand::operator short() {
    return short_operand;
}

IntOperand::IntOperand(uint64_t operand) {
    int_operand = int(operand);
}

IntOperand::operator int() {
    return int_operand;
}

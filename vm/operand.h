/*
 * @Author: zhaoyzh
 * @Date: 2022-01-19 15:36:17
 * @Discription: 
 */

#ifndef _TOHKA_OPERAND_H_
#define _TOHKA_OPERAND_H_

#include <cstdint>
#include "includes/utils.h"


typedef Byte ByteOperand;

union ShortOperand {
    short short_operand;
    struct {
        Byte byte1;
        Byte byte2;
    };

    operator short () {
        return short_operand;
    }
};

union IntOperand {
    int int_operand;
    struct {
        Byte byte1;
        Byte byte2;
        Byte byte3;
        Byte byte4;
    };

    operator int () {
        return int_operand;
    }
};


#endif // end of _TOHKA_OPERAND_H_

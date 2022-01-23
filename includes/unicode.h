/*
 * @Author: Nestcc
 * @Date: 2021-03-12 16:58:25
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-03-16 10:22:09
 * @Description:  < file content >
 */

#ifndef _UNICODE_H_
#define _UNICODE_H_

uint64_t get_number_encode_utf8(int value);
uint64_t get_number_decode_utf8(uint8_t byte);
uint8_t encode_utf8(uint8_t *buff, int value);
int decode_utf8(const uint8_t *byte_ptr, uint64_t length);

#endif

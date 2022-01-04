/*
 * @Author: nestcc 
 * @Date: 2021/4/20 10:24
 * @LastEditors: Nestcc
 * @LastEditTime: 2021-05-01 09:29:14
 * @Discription: 
 */

#ifndef _MEMALLOCATOR_H_
#define _MEMALLOCATOR_H_

#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <cerrno>
#include "../includes/utils.h"

// TODO Replace MemBufferStl
template <typename Type>
class MemAllocator {
public:
    MemAllocator() : curr_size(0), curr_capacity(0), enlarge_ratio(2), data(nullptr) {};

    MemAllocator(uint64_t asize) :
        curr_size(0),
        curr_capacity(asize),
        enlarge_ratio(2),
        data(new Type[asize]) {};

    /*
     * @Description: return idx th of element, when idx less than `capacity`.
     */
    Type &at(uint64_t idx) {
        if (idx >= curr_capacity) {
            MEM_ERROR("List index out of range.");
            errno = ERROR_MEM;
            exit(EXIT_FAILURE);
        }
        return data[idx];
    }

    /*
     * @Description: return idx th of element, when idx less than `size`.
     */
    Type &get(uint64_t idx) {
        if (idx >= curr_size) {
            MEM_ERROR("List index out of range.");
            return data[curr_size - 1];
        }
        return data[idx];
    }

    void resize(uint64_t nsize) {
        Type *new_data = new Type[nsize];
        if (nsize < curr_capacity) {
            LOG_INFO("Resizing memory, but new size less than old size.");
        }
        for (uint64_t i = 0; i < nsize && i < curr_capacity; i += 1) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        curr_capacity = nsize;
        curr_size = curr_size < nsize ? curr_size : nsize;
    }

#define SHOULD_RESIZE if (curr_size == curr_capacity) { resize(curr_capacity * 2); }

    void push(const Type &val, uint64_t idx) {
        if (idx >= curr_size) {
            MEM_ERROR("List index out of range.");
            return;
        }
        if (curr_size == curr_capacity) { resize(curr_capacity * enlarge_ratio); }
        for (uint64_t i = curr_size; i > idx; i -= 1) {
            data[i] = data[i - 1];
        }
        data[idx] = val;
        curr_size += 1;
    }

    void push_back(const Type &val) {
        if (curr_size == curr_capacity) { resize(curr_capacity * enlarge_ratio); }
        data[curr_size++] = val;
    }

    void erase(uint64_t idx) {
        if (idx >= curr_size) {
            MEM_ERROR("List index out of range.");
            return;
        }

        for (uint64_t i = idx; i < curr_size - 1; i += 1) {
            data[i] = data[i] + 1;
        }
        curr_size -= 1;
        if (curr_size * enlarge_ratio < curr_capacity)
            resize(curr_capacity / enlarge_ratio);
    }

    void pop_back() {
        erase(curr_size - 1);
    }

    Type &operator[] (const uint64_t idx) {
        return get(idx);
    }

private:
    uint64_t curr_size;
    uint64_t curr_capacity;
    uint8_t enlarge_ratio;
    Type *data;
};


#endif //_MEMALLOCATOR_H_

#ifndef COMPARES_H
#define COMPARES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <io.h> // Для _open, _read, _close
#include <fcntl.h>    // Для флагов открытия (типа _O_RDONLY, _O_BINARY)
#include <sys/stat.h> // для макросов прав доступа

static const char ascii[256] = {
    ['A'] = 'a', ['B'] = 'b', ['C'] = 'c', ['D'] = 'd', ['E'] = 'e', ['F'] = 'f',
    ['G'] = 'g', ['H'] = 'h', ['I'] = 'i', ['J'] = 'j', ['K'] = 'k', ['L'] = 'l',
    ['M'] = 'm', ['N'] = 'n', ['O'] = 'o', ['P'] = 'p', ['Q'] = 'q', ['R'] = 'r',
    ['S'] = 's', ['T'] = 't', ['U'] = 'u', ['V'] = 'v', ['W'] = 'w', ['X'] = 'x',
    ['Y'] = 'y', ['Z'] = 'z',
    ['a'] = 'a', ['b'] = 'b', ['c'] = 'c', ['d'] = 'd', ['e'] = 'e', ['f'] = 'f',
    ['g'] = 'g', ['h'] = 'h', ['i'] = 'i', ['j'] = 'j', ['k'] = 'k', ['l'] = 'l',
    ['m'] = 'm', ['n'] = 'n', ['o'] = 'o', ['p'] = 'p', ['q'] = 'q', ['r'] = 'r',
    ['s'] = 's', ['t'] = 't', ['u'] = 'u', ['v'] = 'v', ['w'] = 'w', ['x'] = 'x',
    ['y'] = 'y', ['z'] = 'z'
};

int forward_strings_compare(const void* value1, const void* value2);
int reverse_strings_compare(const void* value1, const void* value2);
int pointers_compare(const void* value1, const void* value2);
int my_strcmp(const char* str1, int start_index1, const char* str2, int start_index2, int step);

#endif // FILE_OPERATIONS_H
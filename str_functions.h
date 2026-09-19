#ifndef STR_FUNCTIONS_H
#define STR_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int my_fputs(const char str[], FILE* stream);
int my_strcmp(const char* str1, const char* str2);
char* my_strdup(const char* str);
char* my_fgets(char* s, int size, FILE* stream);

#endif //STR_FUNCTIONS_H
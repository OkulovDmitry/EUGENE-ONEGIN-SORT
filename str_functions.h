#ifndef STR_FUNCTIONS_H
#define STR_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int my_fputs(const char str[], FILE* stream);
struct str_information** my_strdup(struct str_information** str, int len);
char* my_fgets(char* s, int size, FILE* stream);
void print_strings (struct str_information** order_array, int number_of_str, const char* restrict name);

#endif //STR_FUNCTIONS_H
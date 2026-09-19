//если просто записывать в буфер символы а потом записать EOF, то все символы до этого забываются и происходит потеря последней строчки
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "assert_canary.h"
#include "my_qsort.h"
#include "str_functions.h"

#define SMALL_LETTER 0
#define BIG_LETTER 1

const int MAX_STR = 50;
const int MAX_NUMBER_OF_STR = 100;

int read_from_file(const char* restrict name, char** order_array);
void print_strings(char** order_array, int number_of_str, const char* restrict name);
int strings_compare(const void* value1, const void* value2);
void go_free(void* ptr, size_t size);

int main()
{
    char* order_array[MAX_NUMBER_OF_STR] = {};

    int number_of_str = read_from_file("input.txt", order_array);
    //printf("last line: %s", order_array[number_of_str - 1]);
    //printf("number of str: %i\n", number_of_str);
    //printf("%i line before sort: %s\n", 1, order_array[0]);
    /*for (int i = 0; i < number_of_str; i++)
    {
        printf("%i line: %s", i, order_array[i]);
    }*/

    my_qsort(order_array, number_of_str, sizeof(char*), strings_compare);

    /*for (int i = 0; i < number_of_str; i++)
    {
        printf("%llu\n", order_array[i]);
    }*/

    print_strings(order_array, number_of_str, "output.txt");
    //printf("%i line after sort: %s\n", number_of_str, order_array[number_of_str - 1]);
    
    for (int i = 0; i < number_of_str; i++)
    {
        free(order_array[i]);
    }

    return 0;
}

int read_from_file(const char* restrict name, char** order_array)
{
    FILE* file = fopen(name, "r");
    int number_of_lines = 0;
    char buffer[MAX_STR];
    while (my_fgets(buffer, MAX_STR, file) != NULL) //после последней строки в input.txt нужен \n, иначе при выводе последняя строка склеится с той, которая выводится после неё
    {
        order_array[number_of_lines] = strdup(buffer);
        number_of_lines++;
    }

    fclose(file);
    return number_of_lines;
}

void print_strings (char** order_array, int number_of_str, const char* restrict name)
{ 
    FILE* file = fopen(name, "w");
    //printf("number_of_str in print_strings: %i", number_of_str);
    for (int i = 0; i < number_of_str; i++)
    {
        my_fputs(order_array[i], file);
    }
}

int strings_compare(const void* value1, const void* value2)
{
    char* value1_res = *((char**)value1);
    char* value2_res = *((char**)value2);

    return my_strcmp(value1_res, value2_res);
}

void go_free(void* ptr, size_t size)
{
    memset(ptr, 0, size);
    free(ptr);
    ptr = NULL;
}
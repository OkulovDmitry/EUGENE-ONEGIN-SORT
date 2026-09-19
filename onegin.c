//если просто записывать в буфер символы а потом записать EOF, то все символы до этого забываются и происходит потеря последней строчки
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "assert_canary.h"
#include "my_qsort.h"

#define SMALL_LETTER 0
#define BIG_LETTER 1

const int MAX_STR = 50;
const int MAX_NUMBER_OF_STR = 100;

int read_from_file(const char* restrict name, char text[][MAX_STR]);
char* my_fgets(char* s, int size, FILE* stream);

void print_strings(char** order_array, int number_of_str, const char* restrict name);
int my_fputs(const char str[], FILE* stream);

int strings_compare(const void* value1, const void* value2);
int my_strcmp(const char* str1, const char* str2);

int main()
{
    char text[MAX_NUMBER_OF_STR][MAX_STR] = {};
    char* order_array[MAX_NUMBER_OF_STR] = {};
    for (int i = 0; i < MAX_NUMBER_OF_STR; i++)
    {
        order_array[i] = (char*)(((size_t)text + i*MAX_STR));
    }

    int number_of_str = read_from_file("input.txt", text);
    //printf("last line: %s", text[number_of_str - 1]);
    //printf("number of str: %i\n", number_of_str);
    //printf("%i line before sort: %s\n", 1, text[0]);

    //*((char*)((size_t)text + MAX_STR*sizeof(char)*(number_of_str+1))) = '\x01';

    my_qsort(order_array, number_of_str, sizeof(char*), strings_compare);

    /*for (int i = 0; i < number_of_str; i++)
    {
        printf("%llu\n", order_array[i]);
    }*/

    print_strings(order_array, number_of_str, "output.txt");
    //printf("%i line after sort: %s\n", 2, text[1]);
    
    return 0;
}

int read_from_file(const char* restrict name, char text[][MAX_STR])
{
    FILE* file = fopen(name, "r");
    int number_of_lines = 0;
    while (my_fgets(text[number_of_lines++], MAX_STR, file) != NULL) {}
        //printf("%i line: %s\n", number_of_lines-1, text[number_of_lines-1]);
    fclose(file);
    //printf("last str in file:%s", text[number_of_lines - 1]);
    return number_of_lines;
}

char* my_fgets(char* s, int size, FILE* stream)
{
    int i = 0;
    int symbol = '\0';
    while (i < size && (symbol = fgetc(stream)) != EOF)
    {
        *((int*)((size_t)s+i*sizeof(char))) = symbol;
        if (*((char*)((size_t)s+i*sizeof(char))) == '\n')
        {
            i++;
            *((char*)((size_t)s+(i)*sizeof(char))) = '\0';
            break;
        }
        i++;
    }
    if (symbol == EOF)
    {
        *((char*)((size_t)s+i*sizeof(char))) = '\n';
        *((char*)((size_t)s+(i+1)*sizeof(char))) = '\0';
        return NULL;
    }
    //printf("number of symbols: %i\n", i);
    return s;
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

int my_fputs(const char* str, FILE* stream)
{
    char c;
    int i = 0;
    while((c = *((char*)((size_t)str+i*sizeof(char)))) != '\0')
    {
        i++;
        fputc(c, stream);
    }
    return 0;
}

int strings_compare(const void* value1, const void* value2)
{
    char* value1_res = *((char**)value1);
    char* value2_res = *((char**)value2);

    return my_strcmp(value1_res, value2_res);
}

int my_strcmp (const char *str1, const char *str2)
{
    int i = 0;
    int j = 0;
    while (str1[i] != '\0' || str2[j] != '\0')
    {
        char symbol1 = str1[i];
        char symbol2 = str2[j];

        if ('A' <= str1[i] && str1[i] <= 'Z')
        {
            symbol1 += 'a' - 'A';
        }
        if ('A' <= str2[j] && str2[j] <= 'Z')
        {
            symbol2 += 'a' - 'A';
        }

        if (!('a' <= symbol1 && symbol1 <= 'z') && symbol1 != '\0')
        {
            i++;
            continue;
        }
        if (!('a' <= symbol2 && symbol2 <= 'z') && symbol2 != '\0')
        {
            j++;
            continue;
        }

        if (symbol1 < symbol2){ return -1;}
        if (symbol1 > symbol2){ return 1;}
        if (symbol1 == '\0' && symbol2 == '\0'){ return 0;}
        i++;
        j++;
    }
}
//если просто записывать в буфер символы а потом записать EOF, то все символы до этого забываются и происходит потеря последней строчки
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <io.h> // Для _open, _read, _close
#include <fcntl.h>    // Для флагов открытия (типа _O_RDONLY, _O_BINARY)
#include <sys/stat.h> // для макросов прав доступа
#include "assert_canary.h"
#include "my_qsort.h"
#include "str_functions.h"

#define SMALL_LETTER 0
#define BIG_LETTER 1

//onst int MAX_STR = 50;
//const int MAX_NUMBER_OF_STR = 100;

//int read_from_file(FILE* file, char* buffer);
void print_strings(char** order_array, int number_of_str, const char* restrict name);
int strings_compare(const void* value1, const void* value2);
void go_free(void* ptr, size_t size);

int main()
{
    int fd = _open("input.txt", _O_RDONLY, _O_BINARY);
    if (fd == -1) {
        perror("Не удалось открыть файл");
        return 1;
    }
    struct _stat file_info;
    if (_fstat(fd, &file_info) != 0)
    {
        perror("Ошибка при вызове _fstat");
        _close(fd);
        return 1;
    }

    size_t file_size = file_info.st_size; //+2 под \0 и под канарейку
    char* buffer = (char* )calloc(file_size + 2, sizeof(char)); //+2 под \0 и под канарейку
    if (buffer == NULL)
    {
        _close(fd);
        return 1;
    }

    int bytes_read = _read(fd, buffer, (unsigned int)file_size);
    if (bytes_read == 1)
    {
        perror("Ошибка при чтении файлов через _read");
        free(buffer);
        _close(fd);
        return 1;
    }

    _close(fd);

    buffer[file_size] = '\0';
    buffer[file_size + 1] = '\0';

    int number_of_str = 0;

    for (int i = 0; i < file_size/sizeof(char); i++)
    {
        if (buffer[i] == '\r')
        {
            buffer[i] = '\0';
        }
        else if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            number_of_str++;
        }
    }

    char** order_array = (char**)calloc(number_of_str, sizeof(char*));
    order_array[0] = buffer;
    int ord_arr_position = 1;

    for (int i = 0; i < file_size/sizeof(char); i++)
    {
        if (buffer[i] == '\0' && (i + 1) < file_size/sizeof(char) && ord_arr_position < number_of_str)
        {
            order_array[ord_arr_position++] = (char*)((size_t)buffer + (i + 1)*sizeof(char));
        }
    }

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
    
    

    return 0;
}

void print_strings (char** order_array, int number_of_str, const char* restrict name)
{ 
    FILE* file = fopen(name, "w");
    //printf("number_of_str in print_strings: %i", number_of_str);
    for (int i = 0; i < number_of_str; i++)
    {
        my_fputs(order_array[i], file);
        fputc('\n', file);
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
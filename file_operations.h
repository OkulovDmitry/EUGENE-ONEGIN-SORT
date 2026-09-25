#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>
#include <io.h> // Для _open, _read, _close
#include <fcntl.h>    // Для флагов открытия (типа _O_RDONLY, _O_BINARY)
#include <sys/stat.h> // для макросов прав доступа

struct str_information
{
    char* order_array;
    size_t size_of_lines;
};

struct data_and_file_operations
{
    size_t file_size;
    int bytes_read;  //int
    char* file_buffer;
    int number_of_str;
    struct str_information* order_array_of_file;
    void (*read_from_file)(const char* restrict name, struct  data_and_file_operations* file_name);
    void (*break_down_buffer)(struct data_and_file_operations* file_name);
    int (*strings_compare)(const void* value1, const void* value2);
    const char* restrict name_of_output_file;
};

void* my_memcpy(void* restrict dest, const void* restrict src, size_t n);

void read_from_file(const char* restrict name, struct  data_and_file_operations* file_name);
void break_down_buffer(struct data_and_file_operations* file_name);

int my_fputs(const char str[], FILE* stream);
char* my_fgets(char* s, int size, FILE* stream);
void print_strings (struct str_information** ptr_array, int number_of_str, const char* restrict name);

#endif //FILE_OPERATIONS_H
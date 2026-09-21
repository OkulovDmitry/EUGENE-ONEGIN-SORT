// в input после последней строчки всегда enter
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

struct all_data_and_file_operations
{
    size_t file_size;
    int bytes_read;
    char* file_buffer;
    int number_of_str;
    char** order_array;
    void (*read_from_file)(const char* restrict name, struct  all_data_and_file_operations* file_name);
    void (*break_down_buffer)(struct all_data_and_file_operations* file_name);
    int (*strings_compare)(const void* value1, const void* value2);
    const char* restrict name_of_output_file;
};

void read_from_file(const char* restrict name, struct  all_data_and_file_operations* file_name);
void break_down_buffer(struct all_data_and_file_operations* file_name);
void print_strings(char** order_array, int number_of_str, const char* restrict name);
int forward_strings_compare(const void* value1, const void* value2);
int reverse_strings_compare(const void* value1, const void* value2);
void go_free(void* ptr, size_t size);

int main()
{
    struct all_data_and_file_operations forward_file_onegin = {0, 0, NULL, 0, NULL, read_from_file, break_down_buffer, forward_strings_compare, "forward_output.txt"};
    //printf("BEGIN!\n");
    forward_file_onegin.read_from_file("input.txt", &forward_file_onegin); // как то передавал неициализированную хрень
    //printf("I READ!\n");
    forward_file_onegin.break_down_buffer(&forward_file_onegin);
    //printf("I BREAK DOWN BUFFER!\n");
    struct all_data_and_file_operations reverse_file_onegin = forward_file_onegin;
    reverse_file_onegin.strings_compare = reverse_strings_compare;
    reverse_file_onegin.name_of_output_file = "reverse_output.txt";
    reverse_file_onegin.order_array = (char**)calloc(forward_file_onegin.number_of_str, sizeof(char*));
    memcpy(reverse_file_onegin.order_array, forward_file_onegin.order_array, forward_file_onegin.number_of_str * sizeof(char*));

    //printf("INITIALITATION END");
    my_qsort(forward_file_onegin.order_array, forward_file_onegin.number_of_str, sizeof(char*), forward_file_onegin.strings_compare);
    //printf("i SORT FORWARD");
    print_strings(forward_file_onegin.order_array, forward_file_onegin.number_of_str, "forward_output.txt");

    my_qsort(reverse_file_onegin.order_array, reverse_file_onegin.number_of_str, sizeof(char*), reverse_file_onegin.strings_compare);
    //printf("I SORT REVERSE");

    print_strings(reverse_file_onegin.order_array, reverse_file_onegin.number_of_str, "reverse_output.txt");
    //printf("%i line after sort: %s\n", number_of_str, order_array[number_of_str - 1]);

    return 0;
}

void read_from_file(const char* restrict name, struct all_data_and_file_operations* file_name)
{
    int fd = _open(name, _O_RDONLY | _O_BINARY); //сука ебучая запятая вместо побитового или не давала открыть файл в нормальном бинарном режиме и ебала мне мозги тем что bytes_read != file_size
    
    if (fd == -1) {
        perror("Не удалось открыть файл");
        exit(1);
    }
    struct _stat file_info;
    if (_fstat(fd, &file_info) != 0)
    {
        perror("Ошибка при вызове _fstat");
        _close(fd);
        exit(1);
    }

    file_name->file_size = file_info.st_size + sizeof(char); //+1 под канарейку
    file_name->file_buffer = (char* )calloc(file_name->file_size, sizeof(char));
    if (file_name->file_buffer == NULL)
    {
        _close(fd);
        exit(1);
    }

    file_name->bytes_read = _read(fd, file_name->file_buffer, (unsigned int)(file_name->file_size - sizeof(char)));
    if (file_name->bytes_read == -1)
    {
        perror("Ошибка при чтении файлов через _read");
        free(file_name->file_buffer);
        _close(fd);
        exit(1);
    }

    //printf("file_size: %llu\n", file_name->file_size);
    //printf("bytes read: %i\n", file_name->bytes_read);

    _close(fd);

    file_name->file_buffer[file_name->file_size - 1] = '\0';

    /*for (int i = 0 ; i < file_name->file_size; i++)
    {
        printf("%c", file_name->file_buffer[i]);
    }*/
}

void break_down_buffer(struct all_data_and_file_operations* file_name)
{
    /*for (int i = 0 ; i < file_name->file_size; i++)
    {
        printf("%c", file_name->file_buffer[i]);
    }*/

    for (int i = 0; i < file_name->bytes_read/sizeof(char); i++)
    {
        if (file_name->file_buffer[i] == '\r')
        {
            file_name->file_buffer[i] = '\n';
            file_name->number_of_str++;
        }
        else if (file_name->file_buffer[i] == '\n')
        {
            file_name->file_buffer[i] = '\0';
        }
    }

    file_name->order_array = (char**)calloc(file_name->number_of_str, sizeof(char*));
    
    file_name->order_array[0] = file_name->file_buffer;
    int ord_arr_position = 1;

    for (int i = 0; i < file_name->bytes_read/sizeof(char); i++)
    {
        if (file_name->file_buffer[i] == '\n' && (i + 2) < file_name->bytes_read/sizeof(char))
        {
            file_name->order_array[ord_arr_position++] = &file_name->file_buffer[i + 2];
        }
    }

    //printf("last line: %s", file_name->order_array[number_of_str - 1]);
    //printf("number of str: %i\n", file_name->number_of_str);
    //printf("%i line before sort: %s\n", 1, file_name->order_array[0]);
    /*for (int i = 0; i < file_name->number_of_str; i++)
    {
        printf("%i line: %s", i + 1, file_name->order_array[i]);
    }*/
}

void print_strings (char** order_array, int number_of_str, const char* restrict name)
{ 
    FILE* file = fopen(name, "w");
    
    //printf("number_of_str in print_strings: %i", number_of_str);
    for (int i = 0; i < number_of_str; i++)
    {
        my_fputs(order_array[i], file);
        //fputc('\n', file);
    }

    fclose(file);
}

int forward_strings_compare(const void* value1, const void* value2)
{
    char* value1_res = *((char**)value1);
    char* value2_res = *((char**)value2);

    int start_index1 = 0, start_index2 = 0;
    int step = 1;

    return my_strcmp(value1_res, start_index1, value2_res, start_index2, step);
}

int reverse_strings_compare(const void* value1, const void* value2)
{
    //printf("I in reverse_strings_compare");

    char* value1_res = *((char**)value1);
    char* value2_res = *((char**)value2);

    int start_index1 = 0, start_index2 = 0;
    while (value1_res[start_index1] != '\0') {start_index1++;}
    while (value2_res[start_index2] != '\0') {start_index2++;}
    int step = -1;

    return my_strcmp(value1_res, start_index1, value2_res, start_index2, step);
}

void go_free(void* ptr, size_t size)
{
    memset(ptr, 0, size);
    free(ptr);
    ptr = NULL;
}
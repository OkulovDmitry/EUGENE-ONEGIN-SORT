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
    void (*read_from_file)(char* name, struct  all_data_and_file_operations* file_name);
    void (*break_down_buffer)(struct all_data_and_file_operations* file_name);
};

void read_from_file(char* name, struct  all_data_and_file_operations* file_name);
void break_down_buffer(struct all_data_and_file_operations* file_name);
void print_strings(char** order_array, int number_of_str, const char* restrict name);
int strings_compare(const void* value1, const void* value2);
void go_free(void* ptr, size_t size);

int main()
{
    struct all_data_and_file_operations file_onegin = {0, 0, NULL, 0, NULL, read_from_file, break_down_buffer};
    //printf("BEGIN!\n");
    file_onegin.read_from_file("input.txt", &file_onegin); // как то передавал неициализированную хрень
    //printf("I READ!\n");
    file_onegin.break_down_buffer(&file_onegin);
    //printf("I BREAK DOWN BUFFER!\n");

    my_qsort(file_onegin.order_array, file_onegin.number_of_str, sizeof(char*), strings_compare);

    /*for (int i = 0; i < file_onegin.number_of_str; i++)
    {
        printf("%llu\n", file_onegin.order_array[i]);
    }*/

    print_strings(file_onegin.order_array, file_onegin.number_of_str, "output.txt");
    //printf("%i line after sort: %s\n", number_of_str, order_array[number_of_str - 1]);

    return 0;
}

void read_from_file(char* name, struct all_data_and_file_operations* file_name)
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
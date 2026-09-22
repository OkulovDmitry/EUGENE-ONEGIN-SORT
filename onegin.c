//"editor.tokenColorCustomizations": {
//    "comments": "#1e1e1e" // невидимость для комментариев
//}

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
#include "file_operations.h"
#include "my_qsort.h"
#include "str_functions.h"
#include "compares.h"

#define SMALL_LETTER 0
#define BIG_LETTER 1

void go_free(void* ptr, size_t size);

int main()
{
    clock_t time_start = clock();

    struct data_and_file_operations forward_file_onegin = {0, 0, NULL, 0, NULL, read_from_file, break_down_buffer, forward_strings_compare, "forward_output.txt"};
    printf("BEGIN!\n");
    forward_file_onegin.read_from_file("input.txt", &forward_file_onegin); // как то передавал неициализированную хрень
    printf("I READ!\n");
    forward_file_onegin.break_down_buffer(&forward_file_onegin);
    printf("I BREAK DOWN BUFFER!\n");

    print_strings(&forward_file_onegin.order_array_of_file, 
                  forward_file_onegin.number_of_str, 
                  "output.txt");

    struct data_and_file_operations reverse_file_onegin = forward_file_onegin;
    reverse_file_onegin.strings_compare = reverse_strings_compare;
    reverse_file_onegin.name_of_output_file = "reverse_output.txt";
    reverse_file_onegin.order_array_of_file = *(my_strdup(&forward_file_onegin.order_array_of_file,
                                                        reverse_file_onegin.number_of_str));
    
    my_qsort(&forward_file_onegin.order_array_of_file, 
             forward_file_onegin.number_of_str,
             sizeof(struct str_information*), 
             forward_file_onegin.strings_compare);
    printf("i SORT FORWARD");
    print_strings(&forward_file_onegin.order_array_of_file, 
                  forward_file_onegin.number_of_str, 
                  "forward_output.txt");

    my_qsort(&reverse_file_onegin.order_array_of_file, 
             reverse_file_onegin.number_of_str, 
             sizeof(struct str_information*), 
             reverse_file_onegin.strings_compare);
    //printf("I SORT REVERSE");

    print_strings(&reverse_file_onegin.order_array_of_file, 
                  reverse_file_onegin.number_of_str, 
                  "reverse_output.txt");

    my_qsort(&reverse_file_onegin.order_array_of_file, 
             reverse_file_onegin.number_of_str, 
             sizeof(struct str_information*),
             pointers_compare);
    print_strings(&reverse_file_onegin.order_array_of_file, 
                  reverse_file_onegin.number_of_str, 
                  "output.txt");

    go_free(reverse_file_onegin.file_buffer, reverse_file_onegin.file_size);
    //printf("%i line after sort: %s\n", number_of_str, order_array[number_of_str - 1]);

    clock_t time_end = clock();
    printf("Execution time: %.4f seconds.", (double)(time_end - time_start) / CLOCKS_PER_SEC);

    return 0;
}

void go_free(void* ptr, size_t size)
{
    memset(ptr, 0, size);
    free(ptr);
    ptr = NULL;
}
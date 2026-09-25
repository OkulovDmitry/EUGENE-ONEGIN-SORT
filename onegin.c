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
#include "my_qsort.h"
#include "generator.h"

void go_free(void** ptr, size_t size);

int main()
{
    struct data_and_file_operations forward_file_onegin = {0, 0, NULL, 0, NULL, read_from_file, break_down_buffer, forward_strings_compare, "forward_output.txt"};
    //printf("I BEGIN!\n");        
    forward_file_onegin.read_from_file("input.txt", &forward_file_onegin); // как то передавал неициализированную хрень
    //printf("I READ!\n");
    forward_file_onegin.break_down_buffer(&forward_file_onegin);
    //printf("I BREAK DOWN BUFFER!\n");

    size_t num_str = forward_file_onegin.number_of_str;

    /*print_strings(&forward_file_onegin, 
                  forward_file_onegin.number_of_str, 
                  "output.txt");*/

    struct data_and_file_operations reverse_file_onegin = forward_file_onegin;
    reverse_file_onegin.strings_compare = reverse_strings_compare;
    reverse_file_onegin.name_of_output_file = "reverse_output.txt";
    reverse_file_onegin.order_array_of_file = (struct str_information*)calloc(forward_file_onegin.number_of_str, sizeof(struct str_information));
    memcpy(reverse_file_onegin.order_array_of_file, 
           forward_file_onegin.order_array_of_file, 
           forward_file_onegin.number_of_str * sizeof(struct str_information));

    struct str_information** ptr_original = (struct str_information**)calloc(
        forward_file_onegin.number_of_str, 
        sizeof(struct str_information*)
    );
    struct str_information** ptr_forward = (struct str_information**)calloc(
        forward_file_onegin.number_of_str, 
        sizeof(struct str_information*)
    );
    struct str_information** ptr_reverse = (struct str_information**)calloc(
        reverse_file_onegin.number_of_str, 
        sizeof(struct str_information*)
    );

    size_t valid_str_count = 0;

    for (size_t i = 0; i < forward_file_onegin.number_of_str; i++)
    {
        ptr_original[i] = &forward_file_onegin.order_array_of_file[i];

        if (is_valid_poetic_line(&forward_file_onegin.order_array_of_file[i]))
        {
            ptr_forward[valid_str_count] = &forward_file_onegin.order_array_of_file[i];
            ptr_reverse[valid_str_count] = &forward_file_onegin.order_array_of_file[i];
            valid_str_count++;
        }
    }

    forward_file_onegin.number_of_str = valid_str_count;
    reverse_file_onegin.number_of_str = valid_str_count;

    /*for (int i = 0; i < reverse_file_onegin.number_of_str; i++)
    {
        printf("number of str: %i in line: %s", reverse_file_onegin.order_array_of_file[i].size_of_lines, reverse_file_onegin.order_array_of_file[i].order_array);
    }*/

    /*print_strings(&forward_file_onegin, 
                  forward_file_onegin.number_of_str, 
                  "output.txt");*/
    //printf("I MADE REVERSE STRUCT\n");

    clock_t time_start = clock();
    my_qsort(ptr_forward, 
             forward_file_onegin.number_of_str,
             sizeof(struct str_information*), 
             forward_file_onegin.strings_compare);
    clock_t time_end = clock();
    printf("Execution first sort time: %.5f seconds.\n", (double)(time_end - time_start) / CLOCKS_PER_SEC);

    //printf("i SORT FORWARD\n");

    print_strings(ptr_forward, 
                  forward_file_onegin.number_of_str, 
                  "forward_output.txt");

    time_start = clock();
    my_qsort(ptr_reverse, 
             reverse_file_onegin.number_of_str, 
             sizeof(struct str_information*), 
             reverse_file_onegin.strings_compare);
    time_end = clock();
    printf("Execution second time: %.5f seconds.\n", (double)(time_end - time_start) / CLOCKS_PER_SEC);
    //printf("I SORT REVERSE\n");

    print_strings(ptr_reverse, 
                  reverse_file_onegin.number_of_str, 
                  "reverse_output.txt");
    time_start = clock();

    print_strings(ptr_original, 
                  reverse_file_onegin.number_of_str, 
                  "output.txt");

    //printf("I BEGIN DO RAP");

    srand((unsigned int)time(NULL));
    struct rhyme_data dtb = rhyme_search(ptr_reverse, valid_str_count);
    printf("Rhyme pairs collected: %zu\n", dtb.number_of_pairs);

    generate_quadratian(&dtb, "ABAB");
    generate_quadratian(&dtb, "ABBA");

    go_free((void**)&ptr_forward, valid_str_count * sizeof(struct str_information*));
    go_free((void**)&ptr_reverse, valid_str_count * sizeof(struct str_information*));
    go_free((void**)&forward_file_onegin.order_array_of_file, valid_str_count * sizeof(struct str_information));
    go_free((void**)&forward_file_onegin.file_buffer, forward_file_onegin.file_size);
    //printf("%i line after sort: %s\n", number_of_str, order_array[number_of_str - 1]);

    return 0;
}

void go_free(void** ptr, size_t size)
{
    if (ptr != NULL && *ptr != NULL)
    {
        memset(*ptr, 0, size);
        free(*ptr);
        *ptr = NULL;
    }
}
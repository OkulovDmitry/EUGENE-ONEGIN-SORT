#include "compares.h"

int my_strcmp_forward (const char* str1, int start_index1, const char* str2, int start_index2)
{
    while (1)
    {
        char symbol1 = 0;
        while (str1[start_index1] != '\0')
        {
            symbol1 = ascii[(unsigned char)str1[start_index1]];
            if (symbol1 != 0) {break;}
            start_index1++;
        }

        char symbol2 = 0;
        while (str2[start_index2] != '\0')
        {
            symbol2 = ascii[(unsigned char)str2[start_index2]];
            if (symbol2 != 0) {break;}
            start_index2++;
        }

        int stop1 = (symbol1 == 0);
        int stop2 = (symbol2 == 0);

        
        if (stop1 && stop2) return 0;
        if (stop1) return -1;
        if (stop2) return 1;

        if (symbol1 != symbol2)
        {
            return (int)symbol1 - (int)symbol2;
        }
        
        start_index1++;
        start_index2++;
    }
}

int my_strcmp_reverse (const char* str1, int start_index1, const char* str2, int start_index2)
{
    while (1)
    {
        char symbol1 = 0;
        while (start_index1 >= 0)
        {
            symbol1 = ascii[(unsigned char)str1[start_index1]];
            if (symbol1 != 0) {break;}
            start_index1--;
        }

        char symbol2 = 0;
        while (start_index2 >= 0)
        {
            symbol2 = ascii[(unsigned char)str2[start_index2]];
            if (symbol2 != 0) {break;}
            start_index2--;
        }

        int stop1 = (symbol1 == 0);
        int stop2 = (symbol2 == 0);

        
        if (stop1 && stop2) return 0;
        if (stop1) return -1;
        if (stop2) return 1;

        if (symbol1 != symbol2)
        {
            return (int)symbol1 - (int)symbol2;
        }
        
        start_index1--;
        start_index2--;
    }
}

int forward_strings_compare(const void* value1, const void* value2)
{
    struct str_information* value1_res = *((struct str_information**)value1);
    struct str_information* value2_res = *((struct str_information**)value2);

    return my_strcmp_forward(value1_res->order_array, 0, value2_res->order_array, 0);
}

int reverse_strings_compare(const void* value1, const void* value2)
{
    //printf("I in reverse_strings_compare");

    struct str_information* value1_res = *((struct str_information**)value1);
    struct str_information* value2_res = *((struct str_information**)value2);

    /*int start_index1 = 0, start_index2 = 0;
    while (value1_res->order_array[start_index1] != '\0') {start_index1++;}
    while (value2_res->order_array[start_index2] != '\0') {start_index2++;}
    start_index1--;
    start_index2--;*/

    //printf("my size of first line: %llu and second line: %llu\n", value1_res->size_of_lines, value2_res->size_of_lines);
    //printf("really size of first line: %llu and second line: %llu\n", start_index1, start_index2);

    int start_index1 = (int)value1_res->size_of_lines - 2;
    int start_index2 = (int)value2_res->size_of_lines - 2;

    return my_strcmp_reverse(value1_res->order_array, start_index1, value2_res->order_array, start_index2);
}

int pointers_compare(const void* value1, const void* value2)
{
    struct str_information* value1_res = *((struct str_information**)value1);
    struct str_information* value2_res = *((struct str_information**)value2);

    if (value1_res->order_array == value2_res->order_array) {return 0;}
    else if (value1_res->order_array < value2_res->order_array) {return -1;}
    else {return 1;}
}
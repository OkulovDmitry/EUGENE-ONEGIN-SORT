#include "compares.h"

int my_strcmp_forward (const char* str1, ssize_t start_index1, const char* str2, ssize_t start_index2)
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

        int stop1 = (symbol1 == '\0');
        int stop2 = (symbol2 == '\0');

        
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

int my_strcmp_reverse (const char* str1, ssize_t start_index1, const char* str2, ssize_t start_index2) 
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
    struct str_information* value1_res = *((struct str_information**)value1);
    struct str_information* value2_res = *((struct str_information**)value2);

    ssize_t start_index1 = (ssize_t)value1_res->size_of_lines - 2;
    ssize_t start_index2 = (ssize_t)value2_res->size_of_lines - 2;

    return my_strcmp_reverse(value1_res->order_array, start_index1, value2_res->order_array, start_index2);
}
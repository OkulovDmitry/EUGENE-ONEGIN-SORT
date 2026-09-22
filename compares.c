#include "compares.h"

int my_strcmp (const char* str1, int start_index1, const char* str2, int start_index2, int step)
{
    while (1)
    {
        char symbol1 = 0;
        while (start_index1 >= 0 && str1[start_index1] != '\0')
        {
            symbol1 = ascii[(unsigned char)str1[start_index1]];
            if (symbol1 != 0) {break;}
            start_index1 += step;
        }

        char symbol2 = 0;
        while (start_index2 >= 0 && str2[start_index2] != '\0')
        {
            symbol2 = ascii[(unsigned char)str2[start_index2]];
            if (symbol2 != 0) {break;}
            start_index2 += step;
        }

        int stop1 = (symbol1 == 0);
        int stop2 = (symbol2 == 0);

        if (stop1 && stop2) return 0;
        if (stop1) return -1;
        if (stop2) return 1;

        if (symbol1 < symbol2){ return -1;}
        if (symbol1 > symbol2){ return 1;}
        
        start_index1 += step;
        start_index2 += step;
    }
}

int forward_strings_compare(const void* value1, const void* value2)
{
    struct str_information* value1_res = *((struct str_information**)value1);
    struct str_information* value2_res = *((struct str_information**)value2);

    int start_index1 = 0, start_index2 = 0;
    int step = 1;

    return my_strcmp(value1_res->order_array, start_index1, value2_res->order_array, start_index2, step);
}

int reverse_strings_compare(const void* value1, const void* value2)
{
    //printf("I in reverse_strings_compare");

    struct str_information* value1_res = *((struct str_information**)value1);
    struct str_information* value2_res = *((struct str_information**)value2);

    int step = -1;

    return my_strcmp(value1_res->order_array, value1_res->size_of_lines, value2_res->order_array, value2_res->size_of_lines, step);
}

int pointers_compare(const void* value1, const void* value2)
{
    struct str_information** value1_res = (struct str_information**)value1;
    struct str_information** value2_res = (struct str_information**)value2;

    if (*value1_res == *value2_res) {return 0;}
    else if (*value1_res < *value2_res) {return -1;}
    else {return 1;}
}
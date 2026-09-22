#include "str_functions.h"

char* my_fgets(char* s, int size, FILE* stream)
{
    int i = 0;
    int symbol = '\0';

    while (i < size - 1 && (symbol = fgetc(stream)) != EOF)
    {
        *((char*)((size_t)s+i*sizeof(char))) = (char)symbol;
        i++;
        if (symbol == '\n')
        {
            break;
        }
    }

    if (i == 0){ return NULL; }
    
    *((char*)((size_t)s+(i)*sizeof(char))) = '\0';
    //printf("number of symbols: %i\n", i);
    return s;
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

char** my_strdup(char** str, int len)
{
    char** copy = malloc(len * sizeof(char*));
    
    if (copy == NULL) {
        return NULL; 
    }
    
    for (int i = 0; i <= len; i++) {
        copy[i] = str[i];
    }
    
    return copy;
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